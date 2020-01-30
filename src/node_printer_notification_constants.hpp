#ifndef __NODE_PRINTER_NOTIFICATION_CONSTANTS_HPP__
#define __NODE_PRINTER_NOTIFICATION_CONSTANTS_HPP__

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

v8::Local<v8::String> getFieldName(DWORD fieldCode)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    auto it = getNotifyInfoDataJobFieldMap().find(fieldCode);
    if (it == getNotifyInfoDataJobFieldMap().end()) {
        return V8_STRING_NEW_UTF8("UNKOWN_FIELD");
    }
    return V8_STRING_NEW_UTF8(it->second.c_str());
}

/*
 * Job Status Map
 */
typedef std::map<DWORD, std::string> JobStatusMap;

const JobStatusMap& getJobStatusMap()
{
    static JobStatusMap ret;
    if (ret.empty()) {
        #define ADD_STATUS(value, str) ret.insert(std::pair<DWORD, std::string>(value, str));
        ADD_STATUS(JOB_STATUS_BLOCKED_DEVQ, "JOB_STATUS_BLOCKED_DEVQ");
        ADD_STATUS(JOB_STATUS_DELETED, "JOB_STATUS_DELETED");
        ADD_STATUS(JOB_STATUS_DELETING, "JOB_STATUS_DELETING");
        ADD_STATUS(JOB_STATUS_ERROR, "JOB_STATUS_ERROR");
        ADD_STATUS(JOB_STATUS_OFFLINE, "JOB_STATUS_OFFLINE");
        ADD_STATUS(JOB_STATUS_PAPEROUT, "JOB_STATUS_PAPEROUT");
        ADD_STATUS(JOB_STATUS_PAUSED, "JOB_STATUS_PAUSED");
        ADD_STATUS(JOB_STATUS_PRINTED, "JOB_STATUS_PRINTED");
        ADD_STATUS(JOB_STATUS_PRINTING, "JOB_STATUS_PRINTING");
        ADD_STATUS(JOB_STATUS_RESTART, "JOB_STATUS_RESTART");
        ADD_STATUS(JOB_STATUS_SPOOLING, "JOB_STATUS_SPOOLING");
        ADD_STATUS(JOB_STATUS_USER_INTERVENTION, "JOB_STATUS_USER_INTERVENTION");
        #undef ADD_STATUS
    }
    return ret;
}

v8::Local<v8::String> getJobStatusName(DWORD statusCode)
{
    v8::Isolate* isolate = v8::Isolate::GetCurrent();
    auto it = getJobStatusMap().find(statusCode);
    if (it == getJobStatusMap().end()) {
        return V8_STRING_NEW_UTF8("UNKOWN_STATUS");
    }
    return V8_STRING_NEW_UTF8(it->second.c_str());
}

#endif