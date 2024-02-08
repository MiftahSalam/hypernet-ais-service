#include "serial_device_wrapper.h"

#include "qdebug.h"

SerialDeviceWrapper::SerialDeviceWrapper(QObject *parent):
    DeviceWrapper(parent)
{
    m_serial = new QSerialPort(this);

    qDebug()<<Q_FUNC_INFO;
}

SerialDeviceWrapper::~SerialDeviceWrapper()
{
}

bool SerialDeviceWrapper::InitConfig(const QString config)
{
    bool ret_val = false;
#if QT_VERSION > QT_VERSION_CHECK(5, 13, 0)
    QStringList config_list = config.split(":", Qt::SkipEmptyParts);
#else
    QStringList config_list = config.split(":", QString::SkipEmptyParts);
#endif

    if(config_list.size() == 6)
    {
        ret_val = true;

        m_serialConfig.portname = config_list.at(0);
        m_serialConfig.baudrate = str2Baud(config_list.at(1));
        m_serialConfig.databits = str2DataBit(config_list.at(2));
        m_serialConfig.stopbits = str2StopBit(config_list.at(3));
        m_serialConfig.parity = str2parity(config_list.at(4));
        m_serialConfig.flowcontrol = str2flwCtrl(config_list.at(5));
    }
    else qDebug()<<Q_FUNC_INFO<<"invalid config"<<config;

    return ret_val;
}


void SerialDeviceWrapper::Reconnect()
{
    disconnect(m_serial, &QSerialPort::readyRead, this, &SerialDeviceWrapper::onNativeReadyRead);
    if (m_serial->isOpen()) m_serial->close();

    m_serial->setPortName(m_serialConfig.portname);
    if(m_serial->open(QIODevice::ReadOnly))
    {
        connect(m_serial, &QSerialPort::readyRead, this, &SerialDeviceWrapper::onNativeReadyRead);

        m_serial->setBaudRate(m_serialConfig.baudrate);
        m_serial->setDataBits(m_serialConfig.databits);
        m_serial->setStopBits(m_serialConfig.stopbits);
        m_serial->setParity(m_serialConfig.parity);
        m_serial->setFlowControl(m_serialConfig.flowcontrol);

        qInfo()<<Q_FUNC_INFO<<"open serial port"<<m_serial->portName();
    }
    else qWarning()<<Q_FUNC_INFO<<"cannot open serial with error"<<m_serial->errorString();

}

DeviceWrapper::DeviceStatus SerialDeviceWrapper::GetStatus()
{
    if(m_serial->isOpen())
    {
        qint64 now = QDateTime::currentSecsSinceEpoch();

        if((now-m_last_data_time) > 10) m_currentStatus = DeviceWrapper::NO_INPUT_DATA;
        else m_currentStatus = DeviceWrapper::INPUT_AVAIL;
    }
    else m_currentStatus = DeviceWrapper::NOT_AVAIL;

    return  m_currentStatus;
}

void SerialDeviceWrapper::receiveData(QByteArray message)
{
    QString payload = QString::fromUtf8(message);

    qDebug()<<Q_FUNC_INFO<<"payload"<<payload;
    m_last_data_time = QDateTime::currentSecsSinceEpoch();
    emit ReadyRead(payload);
}

void SerialDeviceWrapper::onNativeReadyRead()
{
    QString payload = QString::fromUtf8(m_serial->readAll());

    qDebug()<<Q_FUNC_INFO<<"payload"<<payload;
    m_last_data_time = QDateTime::currentSecsSinceEpoch();
    emit ReadyRead(payload);
}

void SerialDeviceWrapper::ChangeConfig(const QString command)
{
    InitConfig(command);
}

void SerialDeviceWrapper::Write(const QString data)
{
    if (m_serial->isOpen() && m_serial->isWritable()) m_serial->write(data.toUtf8());
    else qWarning()<<Q_FUNC_INFO<<"cannot write serial with error"<<m_serial->errorString();
}

QSerialPort::BaudRate SerialDeviceWrapper::str2Baud(QString baud)
{
    if (baud == "4800")
        return QSerialPort::Baud4800;
    else if (baud == "9600")
        return QSerialPort::Baud9600;
    else if (baud =="19200")
        return QSerialPort::Baud19200;
    else if (baud == "34800")
        return QSerialPort::Baud38400;
    else if (baud == "57600")
        return QSerialPort::Baud57600;
    else if(baud == "115200")
        return QSerialPort::Baud115200;
    else
        return QSerialPort::UnknownBaud; //invalid
}

QSerialPort::DataBits SerialDeviceWrapper::str2DataBit(QString databit)
{
    if (databit == "8")
        return QSerialPort::Data8;
    else if (databit == "7")
        return QSerialPort::Data7;
    else if (databit == "6")
        return QSerialPort::Data6;
    else if(databit == "5")
        return QSerialPort::Data5;
    else
        return QSerialPort::UnknownDataBits; //invalid

}

QSerialPort::FlowControl SerialDeviceWrapper::str2flwCtrl(QString flwCtrl)
{
    if (flwCtrl == "No")
        return QSerialPort::NoFlowControl;
    else if (flwCtrl == "HW")
        return QSerialPort::HardwareControl;
    else if (flwCtrl == "SW")
        return QSerialPort::SoftwareControl;
    else
        return QSerialPort::UnknownFlowControl; //invalid
}

QSerialPort::Parity SerialDeviceWrapper::str2parity(QString parity)
{
    if (parity == "0")
        return QSerialPort::NoParity;
    else if (parity == "2")
        return QSerialPort::EvenParity;
    else if (parity == "3")
        return QSerialPort::OddParity;
    else if (parity == "4")
        return QSerialPort::SpaceParity;
    else if (parity == "5")
        return QSerialPort::MarkParity;
    else
        return QSerialPort::UnknownParity; //invalid
}

QSerialPort::StopBits SerialDeviceWrapper::str2StopBit(QString stopBit)
{
    if (stopBit == "1")
        return QSerialPort::OneStop;
    else if (stopBit == "3")
        return QSerialPort::OneAndHalfStop;
    else if (stopBit == "2")
        return QSerialPort::TwoStop;
    else
        return QSerialPort::UnknownStopBits; //invalid
}
