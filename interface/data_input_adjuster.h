#ifndef DATA_INPUT_ADJUSTER_H
#define DATA_INPUT_ADJUSTER_H

#include <QByteArray>

class DataInputAdjuster
{
public:
    DataInputAdjuster(char firstChar, char endChar);

    QByteArray appendAndAdjustData(QByteArray data);

private:
    char m_firstChar;
    char m_endChar;
    QByteArray buffer;
};

#endif // DATA_INPUT_ADJUSTER_H
