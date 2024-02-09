#include "device_wrapper.h"

DeviceWrapper::DeviceWrapper(QObject *parent) :
    QObject(parent)
{
//    _currentData = "";
    m_last_data_time = QDateTime::currentSecsSinceEpoch();
}

QString DeviceWrapper::GetStatusString()
{
    QString status = "Unknown";
    switch (m_currentStatus) {
    case DeviceWrapper::NOT_AVAIL:
        status = "io device not available";
        break;
    case DeviceWrapper::NO_INPUT_DATA:
        status = "io device available but data not present";
        break;
    case DeviceWrapper::INPUT_AVAIL:
        status = "ok";
        break;
    default:
        break;
    }

    return status;
}
