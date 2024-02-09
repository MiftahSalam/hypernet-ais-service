#include "data_input_adjuster.h"

#include "qdebug.h"

DataInputAdjuster::DataInputAdjuster(char firstChar, char endChar)
    : m_firstChar(firstChar), m_endChar(endChar) {}

QByteArray DataInputAdjuster::appendAndAdjustData(QByteArray data)
{
    buffer.append(data);
    if (buffer.length() > 200) {
        buffer.clear();
    }

    qDebug()<<Q_FUNC_INFO<<buffer;

    int idxFirstChar = buffer.indexOf(m_firstChar);
    if (idxFirstChar > 0) {
        buffer.remove(0, idxFirstChar);
    } else if (idxFirstChar < 0) {
        buffer.clear();
        return "";
    }

    for(int i=0; i<buffer.size(); i++)
    {
        unsigned char bufChar = buffer.at(i);
        if (bufChar == m_endChar)
        {
            QByteArray buf = buffer.mid(0, i);
            buffer.remove(0, i);
            qDebug()<<Q_FUNC_INFO<<"adjusted"<<buf;
            qDebug()<<Q_FUNC_INFO<<"buffer"<<buffer;

            return buf;
        }
    }

    return "";
}
