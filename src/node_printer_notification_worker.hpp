#ifndef __NODE_PRINTER_NOTIFICATION_WORKER_HPP__
#define __NODE_PRINTER_NOTIFICATION_WORKER_HPP__

#include <synchapi.h>
#include <Winspool.h>
#include <nan.h>
#include <node_version.h>
#include <chrono>
#include <thread>
#include <string>
#include <map>
#include <utility>
#include <atomic>

#include "node_printer_notification_constants.hpp"


WORD pPrinterNotifyFields[4] = {
    PRINTER_NOTIFY_FIELD_PRINTER_NAME,
    PRINTER_NOTIFY_FIELD_STATUS,
    PRINTER_NOTIFY_FIELD_CJOBS,
    PRINTER_NOTIFY_FIELD_PORT_NAME
};

WORD pJobNotifyFields[4] = {
    JOB_NOTIFY_FIELD_PRINTER_NAME,
    JOB_NOTIFY_FIELD_MACHINE_NAME,
    JOB_NOTIFY_FIELD_STATUS,
    JOB_NOTIFY_FIELD_DOCUMENT
};

PRINTER_NOTIFY_OPTIONS_TYPE pPrinterNotifyOptionsTypes[2] = {
    {
        0, // Type
        0,
        0,
        0,
        4, // Count
        pPrinterNotifyFields
    },
    {
        1, // Type
        0,
        0,
        0,
        4, // Count
        pJobNotifyFields
    }
};

PRINTER_NOTIFY_OPTIONS pPrinterNotifyOptions = {
    2, // Version
    PRINTER_NOTIFY_OPTIONS_REFRESH, // Flag
    2, // Count
    pPrinterNotifyOptionsTypes, // pTypes
};

typedef struct _ProgressData {
    DWORD code;
    LPVOID data;
} ProgressData;

class NotificationWorker : public Nan::AsyncProgressWorkerBase<ProgressData>
{
private:
    std::string printerName;
    DWORD error;
    DWORD eventCode;
    LPVOID eventData;
    std::atomic_bool stopRequested;
    HANDLE hPrinter;
    HANDLE hNotification;

public:
    NotificationWorker(std::string printerName, Nan::Callback *callback)
        : Nan::AsyncProgressWorkerBase<ProgressData>(callback),
            printerName(printerName),
            error(0),
            eventCode(0),
            eventData(0),
            stopRequested(false),
            hPrinter(INVALID_HANDLE_VALUE),
            hNotification(INVALID_HANDLE_VALUE)
        {}

    ~NotificationWorker() {
        if (this->hNotification != INVALID_HANDLE_VALUE) {
            FindClosePrinterChangeNotification(this->hNotification);
        }
        if (this->hPrinter != INVALID_HANDLE_VALUE) {
            ClosePrinter(this->hPrinter);
        }
    };

    void Stop()
    {
        this->stopRequested = true;
    }

    void Execute (const Nan::AsyncProgressWorkerBase<ProgressData>::ExecutionProgress& progress) {
        std::wstring wPrinterName = std::wstring(this->printerName.begin(), this->printerName.end());

        if (!OpenPrinterW((LPWSTR)(wPrinterName.c_str()), &this->hPrinter, NULL)) {
            this->SetErrorMessage("COULD_NOT_OPEN_PRINTER");
            this->error = GetLastError();
            return;
        }

        this->hNotification = FindFirstPrinterChangeNotification(
            this->hPrinter,
            PRINTER_CHANGE_ALL,
            0x001000,
            &pPrinterNotifyOptions
        );

        if (this->hNotification == INVALID_HANDLE_VALUE) {
            ClosePrinter(this->hPrinter);
            this->hPrinter = INVALID_HANDLE_VALUE;
            this->SetErrorMessage("COULD_NOT_SUBSCRIBE_FOR_NOTIFICATIONS");
            this->error = 0;
            return;
        }

        BOOL bKeepMonitoring = true;
        while (bKeepMonitoring && !this->stopRequested) {
            DWORD waitResult = WaitForSingleObject(this->hNotification, 500);
            if (waitResult == 0) {
                ProgressData progressData;
                if (FindNextPrinterChangeNotification(this->hNotification, &progressData.code, &pPrinterNotifyOptions, &progressData.data)) {
                    progress.Send(&progressData, 1);
                } else {
                    this->SetErrorMessage("GET_NOTIFICATION_ERROR");
                    this->error = GetLastError();
                    bKeepMonitoring = false;
                    continue;
                }
            } else if (waitResult == 0x00000102L) {
                continue;
            } else {
                this->SetErrorMessage("WAIT_ERROR");
                this->error = GetLastError();
                bKeepMonitoring = false;
                continue;
            }
        }

        FindClosePrinterChangeNotification(this->hNotification);
        ClosePrinter(this->hPrinter);
        this->hNotification = INVALID_HANDLE_VALUE;
        this->hPrinter = INVALID_HANDLE_VALUE;
    }

    void HandleProgressCallback(const ProgressData *progressData, size_t count)
    {
        Nan::HandleScope scope;
        MY_NODE_MODULE_ISOLATE_DECL

        v8::Local<v8::Object> result = v8::Object::New(MY_NODE_MODULE_ISOLATE);
        result->Set(V8_STRING_NEW_UTF8("type"), V8_STRING_NEW_UTF8("event"));
        result->Set(V8_STRING_NEW_UTF8("event_code"), v8::Number::New(MY_NODE_MODULE_ISOLATE, progressData->code));
        result->Set(V8_STRING_NEW_UTF8("event"), getEventNames(progressData->code));

        PPRINTER_NOTIFY_INFO data = (PPRINTER_NOTIFY_INFO) progressData->data;

        std::map<DWORD, v8::Local<v8::Object>> jobs;
        v8::Local<v8::Object> printer = v8::Object::New(MY_NODE_MODULE_ISOLATE);
        result->Set(V8_STRING_NEW_UTF8("printer"), printer);
        DWORD i = 0;
        while (i < data->Count) {
            PRINTER_NOTIFY_INFO_DATA info_data = data->aData[i];

            if (info_data.Type == 0) {
                // Printer event
                switch (info_data.Field) {
                    case PRINTER_NOTIFY_FIELD_PRINTER_NAME:
                    case PRINTER_NOTIFY_FIELD_PORT_NAME:
                        printer->Set(getPrinterFieldName(info_data.Field), v8::String::NewFromTwoByte(MY_NODE_MODULE_ISOLATE, (const uint16_t*)info_data.NotifyData.Data.pBuf));
                        break;
                    case PRINTER_NOTIFY_FIELD_STATUS:
                        printer->Set(getPrinterFieldName(info_data.Field), getPrinterStatusNames(info_data.NotifyData.adwData[0]));
                        break;
                    case PRINTER_NOTIFY_FIELD_CJOBS:
                        printer->Set(getPrinterFieldName(info_data.Field), Nan::New((unsigned int)info_data.NotifyData.adwData[0]));
                        break;
                }
            }
            if (info_data.Type == 1) {
                // Job event
                v8::Local<v8::Object> job;
                auto job_it = jobs.find(info_data.Id);
                if (job_it == jobs.end()) {
                    job = v8::Object::New(MY_NODE_MODULE_ISOLATE);
                    job->Set(V8_STRING_NEW_UTF8("id"), v8::Number::New(MY_NODE_MODULE_ISOLATE, info_data.Id));
                    jobs.insert(std::pair<DWORD, v8::Local<v8::Object>>(info_data.Id, job));
                } else {
                    job = job_it->second;
                }

                switch (info_data.Field) {
                    case JOB_NOTIFY_FIELD_PRINTER_NAME:
                    case JOB_NOTIFY_FIELD_MACHINE_NAME:
                    case JOB_NOTIFY_FIELD_USER_NAME:
                    case JOB_NOTIFY_FIELD_NOTIFY_NAME:
                    case JOB_NOTIFY_FIELD_DATATYPE:
                    case JOB_NOTIFY_FIELD_PRINT_PROCESSOR:
                    case JOB_NOTIFY_FIELD_PARAMETERS:
                    case JOB_NOTIFY_FIELD_DRIVER_NAME:
                    case JOB_NOTIFY_FIELD_STATUS_STRING:
                    case JOB_NOTIFY_FIELD_DOCUMENT:
                        job->Set(getJobFieldName(info_data.Field), v8::String::NewFromTwoByte(MY_NODE_MODULE_ISOLATE, (const uint16_t*)info_data.NotifyData.Data.pBuf));
                        break;
                    case JOB_NOTIFY_FIELD_STATUS:
                        job->Set(getJobFieldName(info_data.Field), getJobStatusNames(info_data.NotifyData.adwData[0]));
                        break;
                }
            }
            i += 1;
        }

        if (!jobs.empty()) {
            v8::Local<v8::Array> jobs_array = v8::Array::New(MY_NODE_MODULE_ISOLATE);
            auto it = jobs.begin();
            int i = 0;
            while (it != jobs.end()) {
                jobs_array->Set(i, it->second);
                it++;
                i++;
            }
            result->Set(V8_STRING_NEW_UTF8("jobs"), jobs_array);
        }

        v8::Local<v8::Value> argv[] = {
            Nan::Null(),
            result
        };

        if (progressData->data) {
            FreePrinterNotifyInfo((PPRINTER_NOTIFY_INFO) progressData->data);
        }

        this->callback->Call(2, argv, this->async_resource);
    }

    void HandleOKCallback () {
        Nan::HandleScope scope;
        MY_NODE_MODULE_ISOLATE_DECL

        v8::Local<v8::Object> result = v8::Object::New(MY_NODE_MODULE_ISOLATE);
        result->Set(V8_STRING_NEW_UTF8("type"), V8_STRING_NEW_UTF8("complete"));

        v8::Local<v8::Value> argv[] = {
            Nan::Null(),
            result
        };

        this->callback->Call(2, argv, this->async_resource);
    }

    void HandleErrorCallback() {
        Nan::HandleScope scope;
        MY_NODE_MODULE_ISOLATE_DECL

        v8::Local<v8::Value> argv[] = {
            V8_STRING_NEW_UTF8(this->ErrorMessage())
        };

        this->callback->Call(1, argv, this->async_resource);
    }
};

#endif
