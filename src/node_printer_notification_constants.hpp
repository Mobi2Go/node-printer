#ifndef __NODE_PRINTER_NOTIFICATION_CONSTANTS_HPP__
#define __NODE_PRINTER_NOTIFICATION_CONSTANTS_HPP__

#include "macros.hh"

/*
 * Change Event Map
 */
typedef std::map<DWORD, std::string> ChangeEventMapType;

const ChangeEventMapType& getChangeEventMap()
{
    static ChangeEventMapType ret;
    if (ret.empty()) {
        #define ADD_CHANGE_EVENT(value, str) ret.insert(std::pair<DWORD, std::string>(value, str));
        ADD_CHANGE_EVENT(PRINTER_CHANGE_ADD_FORM, "PRINTER_CHANGE_ADD_FORM");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_ADD_JOB, "PRINTER_CHANGE_ADD_JOB");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_ADD_PORT, "PRINTER_CHANGE_ADD_PORT");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_ADD_PRINT_PROCESSOR, "PRINTER_CHANGE_ADD_PRINT_PROCESSOR");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_ADD_PRINTER, "PRINTER_CHANGE_ADD_PRINTER");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_ADD_PRINTER_DRIVER, "PRINTER_CHANGE_ADD_PRINTER_DRIVER");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_CONFIGURE_PORT, "PRINTER_CHANGE_CONFIGURE_PORT");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_DELETE_FORM, "PRINTER_CHANGE_DELETE_FORM");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_DELETE_JOB, "PRINTER_CHANGE_DELETE_JOB");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_DELETE_PORT, "PRINTER_CHANGE_DELETE_PORT");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_DELETE_PRINT_PROCESSOR, "PRINTER_CHANGE_DELETE_PRINT_PROCESSOR");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_DELETE_PRINTER, "PRINTER_CHANGE_DELETE_PRINTER");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_DELETE_PRINTER_DRIVER, "PRINTER_CHANGE_DELETE_PRINTER_DRIVER");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_FAILED_CONNECTION_PRINTER, "PRINTER_CHANGE_FAILED_CONNECTION_PRINTER");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_SET_FORM, "PRINTER_CHANGE_SET_FORM");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_SET_JOB, "PRINTER_CHANGE_SET_JOB");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_SET_PRINTER, "PRINTER_CHANGE_SET_PRINTER");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_SET_PRINTER_DRIVER, "PRINTER_CHANGE_SET_PRINTER_DRIVER");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_WRITE_JOB, "PRINTER_CHANGE_WRITE_JOB");
        ADD_CHANGE_EVENT(PRINTER_CHANGE_TIMEOUT, "PRINTER_CHANGE_TIMEOUT");
        // ADD_CHANGE_EVENT(PRINTER_CHANGE_SERVER, "PRINTER_CHANGE_SERVER");
        #undef ADD_CHANGE_EVENT
    }
    return ret;
}

v8::Local<v8::Array> getEventNames(DWORD eventCode)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Array> result = v8::Array::New(isolate);
    int i = 0;

    if (eventCode & PRINTER_CHANGE_ADD_FORM) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_ADD_FORM").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_ADD_JOB) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_ADD_JOB").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_ADD_PORT) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_ADD_PORT").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_ADD_PRINT_PROCESSOR) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_ADD_PRINT_PROCESSOR").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_ADD_PRINTER_DRIVER) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_ADD_PRINTER_DRIVER").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_CONFIGURE_PORT) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_CONFIGURE_PORT").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_DELETE_FORM) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_DELETE_FORM").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_DELETE_JOB) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_DELETE_JOB").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_DELETE_PORT) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_DELETE_PORT").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_DELETE_PRINT_PROCESSOR) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_DELETE_PRINT_PROCESSOR").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_DELETE_PRINTER) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_DELETE_PRINTER").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_DELETE_PRINTER_DRIVER) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_DELETE_PRINTER_DRIVER").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_FAILED_CONNECTION_PRINTER) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_FAILED_CONNECTION_PRINTER").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_SET_FORM) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_SET_FORM").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_SET_JOB) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_SET_JOB").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_SET_PRINTER) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_SET_PRINTER").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_SET_PRINTER_DRIVER) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_SET_PRINTER_DRIVER").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_WRITE_JOB) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_WRITE_JOB").ToLocalChecked());
    }
    if (eventCode & PRINTER_CHANGE_TIMEOUT) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_CHANGE_TIMEOUT").ToLocalChecked());
    }

    return result;
}

v8::Local<v8::String> getEventName(DWORD eventCode)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    auto it = getChangeEventMap().find(eventCode);
    if (it == getChangeEventMap().end()) {
        return V8_STRING_NEW_UTF8("UNKOWN_EVENT");
    }
    return V8_STRING_NEW_UTF8(it->second.c_str());
}

/*
 * Printer Field Map
 */
typedef std::map<DWORD, std::string> NotifyInfoDataPrinterFieldMap;

const NotifyInfoDataPrinterFieldMap& getNotifyInfoDataPrinterFieldMap()
{
    static NotifyInfoDataPrinterFieldMap ret;
    if (ret.empty()) {
        #define ADD_FIELD(value, str) ret.insert(std::pair<DWORD, std::string>(value, str));
        ADD_FIELD(PRINTER_NOTIFY_FIELD_SERVER_NAME, "server_name");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_PRINTER_NAME, "printer_name");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_SHARE_NAME, "share_name");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_PORT_NAME, "port_name");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_DRIVER_NAME, "driver_name");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_COMMENT, "comment");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_LOCATION, "location");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_DEVMODE, "devmode");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_SEPFILE, "sepfile");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_PRINT_PROCESSOR, "print_processor");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_PARAMETERS, "parameters");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_DATATYPE, "datatype");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_SECURITY_DESCRIPTOR, "security_descriptor");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_ATTRIBUTES, "attributes");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_PRIORITY, "priority");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_DEFAULT_PRIORITY, "default_priority");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_START_TIME, "start_time");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_UNTIL_TIME, "until_time");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_STATUS, "status");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_CJOBS, "jobs_count");
        ADD_FIELD(PRINTER_NOTIFY_FIELD_AVERAGE_PPM, "average_ppm");
        #undef ADD_FIELD
    }
    return ret;
}

v8::Local<v8::String> getPrinterFieldName(DWORD fieldCode)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    auto it = getNotifyInfoDataPrinterFieldMap().find(fieldCode);
    if (it == getNotifyInfoDataPrinterFieldMap().end()) {
        return V8_STRING_NEW_UTF8("UNKOWN_FIELD");
    }
    return V8_STRING_NEW_UTF8(it->second.c_str());
}

/*
 * Printer Status Names
 */
v8::Local<v8::Array> getPrinterStatusNames(DWORD status)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Array> result = v8::Array::New(isolate);
    int i = 0;

    if (status & PRINTER_STATUS_BUSY) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_BUSY").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_DOOR_OPEN) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_DOOR_OPEN").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_ERROR) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_ERROR").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_INITIALIZING) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_INITIALIZING").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_IO_ACTIVE) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_IO_ACTIVE").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_MANUAL_FEED) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_MANUAL_FEED").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_NO_TONER) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_NO_TONER").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_NOT_AVAILABLE) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_NOT_AVAILABLE").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_OFFLINE) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_OFFLINE").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_OUT_OF_MEMORY) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_OUT_OF_MEMORY").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_OUTPUT_BIN_FULL) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_OUTPUT_BIN_FULL").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_PAGE_PUNT) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_PAGE_PUNT").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_PAPER_JAM) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_PAPER_JAM").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_PAPER_OUT) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_PAPER_OUT").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_PAPER_PROBLEM) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_PAPER_PROBLEM").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_PAUSED) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_PAUSED").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_PENDING_DELETION) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_PENDING_DELETION").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_POWER_SAVE) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_POWER_SAVE").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_PRINTING) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_PRINTING").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_PROCESSING) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_PROCESSING").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_SERVER_UNKNOWN) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_SERVER_UNKNOWN").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_TONER_LOW) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_TONER_LOW").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_USER_INTERVENTION) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_USER_INTERVENTION").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_WAITING) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_WAITING").ToLocalChecked());
    }
    if (status & PRINTER_STATUS_WARMING_UP) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("PRINTER_STATUS_WARMING_UP").ToLocalChecked());
    }

    return result;
}

/*
 * Job Field Map
 */
typedef std::map<DWORD, std::string> NotifyInfoDataJobFieldMap;

const NotifyInfoDataJobFieldMap& getNotifyInfoDataJobFieldMap()
{
    static NotifyInfoDataJobFieldMap ret;
    if (ret.empty()) {
        #define ADD_FIELD(value, str) ret.insert(std::pair<DWORD, std::string>(value, str));
        ADD_FIELD(JOB_NOTIFY_FIELD_PRINTER_NAME, "printer_name");
        ADD_FIELD(JOB_NOTIFY_FIELD_MACHINE_NAME, "machine_name");
        ADD_FIELD(JOB_NOTIFY_FIELD_PORT_NAME, "port_name");
        ADD_FIELD(JOB_NOTIFY_FIELD_USER_NAME, "user_name");
        ADD_FIELD(JOB_NOTIFY_FIELD_NOTIFY_NAME, "notify_name");
        ADD_FIELD(JOB_NOTIFY_FIELD_DATATYPE, "datatype");
        ADD_FIELD(JOB_NOTIFY_FIELD_PRINT_PROCESSOR, "print_processor");
        ADD_FIELD(JOB_NOTIFY_FIELD_PARAMETERS, "parameters");
        ADD_FIELD(JOB_NOTIFY_FIELD_DRIVER_NAME, "driver_name");
        ADD_FIELD(JOB_NOTIFY_FIELD_DEVMODE, "devmode");
        ADD_FIELD(JOB_NOTIFY_FIELD_STATUS, "status");
        ADD_FIELD(JOB_NOTIFY_FIELD_STATUS_STRING, "status_string");
        ADD_FIELD(JOB_NOTIFY_FIELD_SECURITY_DESCRIPTOR, "security_descriptor");
        ADD_FIELD(JOB_NOTIFY_FIELD_DOCUMENT, "document");
        ADD_FIELD(JOB_NOTIFY_FIELD_PRIORITY, "priority");
        ADD_FIELD(JOB_NOTIFY_FIELD_POSITION, "position");
        ADD_FIELD(JOB_NOTIFY_FIELD_SUBMITTED, "submitted");
        ADD_FIELD(JOB_NOTIFY_FIELD_START_TIME, "start_time");
        ADD_FIELD(JOB_NOTIFY_FIELD_UNTIL_TIME, "until_time");
        ADD_FIELD(JOB_NOTIFY_FIELD_TIME, "time");
        ADD_FIELD(JOB_NOTIFY_FIELD_TOTAL_PAGES, "total_pages");
        ADD_FIELD(JOB_NOTIFY_FIELD_PAGES_PRINTED, "pages_printed");
        ADD_FIELD(JOB_NOTIFY_FIELD_TOTAL_BYTES, "total_bytes");
        ADD_FIELD(JOB_NOTIFY_FIELD_BYTES_PRINTED, "bytes_printed");
        #undef ADD_FIELD
    }
    return ret;
}

v8::Local<v8::String> getJobFieldName(DWORD fieldCode)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    auto it = getNotifyInfoDataJobFieldMap().find(fieldCode);
    if (it == getNotifyInfoDataJobFieldMap().end()) {
        return V8_STRING_NEW_UTF8("UNKOWN_FIELD");
    }
    return V8_STRING_NEW_UTF8(it->second.c_str());
}

/*
 * Job Status Names
 */
v8::Local<v8::Array> getJobStatusNames(DWORD status)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Array> result = v8::Array::New(isolate);
    int i = 0;

    if (status & JOB_STATUS_BLOCKED_DEVQ) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("JOB_STATUS_BLOCKED_DEVQ").ToLocalChecked());
    }
    if (status & JOB_STATUS_DELETED) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("JOB_STATUS_DELETED").ToLocalChecked());
    }
    if (status & JOB_STATUS_DELETING) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("JOB_STATUS_DELETING").ToLocalChecked());
    }
    if (status & JOB_STATUS_ERROR) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("JOB_STATUS_ERROR").ToLocalChecked());
    }
    if (status & JOB_STATUS_OFFLINE) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("JOB_STATUS_OFFLINE").ToLocalChecked());
    }
    if (status & JOB_STATUS_PAPEROUT) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("JOB_STATUS_PAPEROUT").ToLocalChecked());
    }
    if (status & JOB_STATUS_PAUSED) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("JOB_STATUS_PAUSED").ToLocalChecked());
    }
    if (status & JOB_STATUS_PRINTED) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("JOB_STATUS_PRINTED").ToLocalChecked());
    }
    if (status & JOB_STATUS_PRINTING) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("JOB_STATUS_PRINTING").ToLocalChecked());
    }
    if (status & JOB_STATUS_RESTART) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("JOB_STATUS_RESTART").ToLocalChecked());
    }
    if (status & JOB_STATUS_SPOOLING) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("JOB_STATUS_SPOOLING").ToLocalChecked());
    }
    if (status & JOB_STATUS_USER_INTERVENTION) {
        MY_NODE_SET_OBJECT(result, i++, Nan::New("JOB_STATUS_USER_INTERVENTION").ToLocalChecked());
    }

    return result;
}

#endif