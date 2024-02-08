#include "data_input_adjuster.h"

#include "qdebug.h"

DataInputAdjuster::DataInputAdjuster(char firstChar, char endChar)
    : m_firstChar(firstChar), m_endChar(endChar) {}

QByteArray DataInputAdjuster::appendAndAdjustData(QByteArray data)
{
    qDebug()<<Q_FUNC_INFO<<buffer;

    buffer.append(data);
    if (buffer.length() > 200) {
        buffer.clear();
    }

    int idxFirstChar = buffer.indexOf(m_firstChar);
    if (idxFirstChar > 0) {
        buffer.remove(0, idxFirstChar);
    } else if (idxFirstChar < 0) {
        buffer.clear();
        return "";
    }

    for(int i=0; i<buffer.size(); i++)
    {
        if (buffer.at(i) == m_endChar)
        {
            QByteArray buf = buffer;
            buffer.remove(0, i);

            qDebug()<<Q_FUNC_INFO<<"adjusted"<<buf;

            return buf;
        }
    }

    return "";
}
