#ifndef DATA_INPUT_ADJUSTER_H
#define DATA_INPUT_ADJUSTER_H

#include <QByteArray>

#ifdef USE_LOG4QT
#include <QObject>
class DataInputAdjuster: public QObject
{
public:
    DataInputAdjuster(QObject *parent = nullptr, char firstChar = '\0', char endChar = '\0');
#else
class DataInputAdjuster
{
public:
    DataInputAdjuster(char firstChar = '\0', char endChar = '\0');
#endif

   QList<QByteArray> appendAndAdjustData(QByteArray data);
//    QByteArray appendAndAdjustData(QByteArray data);

private:
    char m_firstChar;
    char m_endChar;
    bool start_append;
    bool stop_append;
    QByteArray buffer;
};

#endif // DATA_INPUT_ADJUSTER_H
