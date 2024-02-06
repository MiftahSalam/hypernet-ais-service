#ifndef SERIAL_DEVICE_WRAPPER_H
#define SERIAL_DEVICE_WRAPPER_H

#include <QObject>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "devicewrapper.h"

class SerialDeviceWrapper : public DeviceWrapper
{
    Q_OBJECT
public:
    SerialDeviceWrapper(QObject *parent = nullptr);
    ~SerialDeviceWrapper() override;

    void Write(const QString data) override;
    DeviceStatus GetStatus() override;
    void Reconnect() override;
    void ChangeConfig(const QString command) override;
    bool InitConfig(const QString config = "") override;

private slots:
    void receiveData(QByteArray message);

private:
    struct SerialConfig {
        QString portname;
        QSerialPort::BaudRate baudrate;
        QSerialPort::DataBits databits;
        QSerialPort::StopBits stopbits;
        QSerialPort::Parity parity;
        QSerialPort::FlowControl flowcontrol;
    } m_serialConfig;

    QSerialPort* m_serial;

    QSerialPort::BaudRate str2Baud(QString baud);
    QSerialPort::DataBits str2DataBit(QString databit);
    QSerialPort::FlowControl str2flwCtrl(QString flwCtrl);
    QSerialPort::Parity str2parity(QString parity);
    QSerialPort::StopBits str2StopBit(QString stopBit);
};


#endif // SERIAL_DEVICE_WRAPPER_H
