#include "data_input_adjuster.h"

#include <QList>

#ifdef USE_LOG4QT
#include <log4qt/logger.h>
LOG4QT_DECLARE_STATIC_LOGGER(logger, DataInputAdjuster)
DataInputAdjuster::DataInputAdjuster(QObject *parent, char firstChar, char endChar)
    : QObject(parent), m_firstChar(firstChar), m_endChar(endChar), start_append(false), stop_append(false) {}
#else
#include <QDebug>
DataInputAdjuster::DataInputAdjuster(char firstChar, char endChar)
    : m_firstChar(firstChar), m_endChar(endChar), start_append(false), stop_append(false) {}
#endif

QList<QByteArray> DataInputAdjuster::appendAndAdjustData(QByteArray data)
{
    char bufChar = '\0';
    QList<QByteArray> ret_string;
    ret_string.clear();

    for(int i=0; i<data.size(); i++)
    {
        bufChar = data.at(i);
        if(bufChar == m_firstChar) start_append = true;
        if(bufChar == m_endChar && start_append) stop_append = true;
        if(start_append) buffer.append(bufChar);
        if(start_append && stop_append)
        {
            start_append = false;
            stop_append = false;
            ret_string.append(buffer);
            buffer.clear();

#ifdef USE_LOG4QT
            logger()->trace()<<Q_FUNC_INFO<<" - "<<ret_string.last();
#else
            qDebug()<<Q_FUNC_INFO<<" - "<<ret_string.last();
#endif
        }
    }

    return ret_string;


    //    buffer.append(data);
    //    if (buffer.length() > 200) {
    //        buffer.clear();
    //    }

    //    qDebug()<<Q_FUNC_INFO<<buffer;

    //    int idxFirstChar = buffer.indexOf(m_firstChar);
    //    if (idxFirstChar > 0) {
    //        buffer.remove(0, idxFirstChar);
    //    } else if (idxFirstChar < 0) {
    //        buffer.clear();
    //        return "";
    //    }

    //    for(int i=0; i<buffer.size(); i++)
    //    {
    //        unsigned char bufChar = buffer.at(i);
    //        if (bufChar == m_endChar)
    //        {
    //            QByteArray buf = buffer.mid(0, i);
    //            buffer.remove(0, i);
    //            qDebug()<<Q_FUNC_INFO<<"adjusted"<<buf;
    //            qDebug()<<Q_FUNC_INFO<<"buffer"<<buffer;

    //            return buf;
    //        }
    //    }

    //    return "";
}
