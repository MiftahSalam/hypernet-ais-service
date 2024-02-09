#ifndef DATA_INPUT_ADJUSTER_H
#define DATA_INPUT_ADJUSTER_H

#include <QByteArray>

class DataInputAdjuster
{
public:
    DataInputAdjuster(char firstChar, char endChar);

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
