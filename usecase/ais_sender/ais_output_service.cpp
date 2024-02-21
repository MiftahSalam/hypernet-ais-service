#include "ais_output_service.h"
#include "usecase/ais_sender/ais_output_serializer_json.h"

#include <QList>
#include <QDateTime>

#ifdef USE_LOG4QT
#include <log4qt/logger.h>
LOG4QT_DECLARE_STATIC_LOGGER(logger, AISOutputService)
#else
#include <QDebug>
#endif

AISOutputService::AISOutputService(QObject *parent, AISTargetRepository *repo, QString cfg)
    : QObject{parent}, dataSendCounter(0), aisRepo(repo)
{
#ifdef USE_LOG4QT
    if(!repo) logger()->fatal("ais repo is null");
#else
    if(!repo) qFatal("ais repo is null");
#endif

    populateConfig(cfg);

    connect(&timer, &QTimer::timeout, this, &AISOutputService::onTimeout);

    timer.start(timeout);
}

QList<AISTargetModel*> AISOutputService::sendTarget()
{
    updateDataSendCounter();

    auto targets = getTargets();
    if (targets.size() > 0) {
#if QT_VERSION > QT_VERSION_CHECK(5, 13, 0)
        QList<AISTargetModel*> qlist(targets.begin(), targets.end());
#else
        QList<AISTargetModel*> qlist = QList<AISTargetModel*>::fromStdList(targets);
#endif
        AISOutputSerializer* serializer = new AISOutputSerializer_JSON(qlist);

        emit signalSendAISTargetRaw(serializer->decode().toUtf8());

        return qlist;
    }
#ifdef USE_LOG4QT
    else logger()->debug()<<Q_FUNC_INFO<<" - ais target query result  is empty";
#else
    qDebug()<<Q_FUNC_INFO<<" - ais target query result  is empty";
#endif

    return QList<AISTargetModel*>();
}

std::list<AISTargetModel *> AISOutputService::getTargets()
{
    AISTargetQueryFilter filter;
    filter.limit = sendLimit;
    filter.startIndex = dataSendCounter;

    return aisRepo->Find(filter);
}

void AISOutputService::onTimeout()
{
#ifdef USE_LOG4QT
    logger()->debug()<<Q_FUNC_INFO<<" - ais target size: "<<aisRepo->FindAll().size();
#else
    qDebug()<<Q_FUNC_INFO<<" - ais target size: "<<aisRepo->FindAll().size();
#endif

    auto sendedTarget = sendTarget();
    checkAndDeleteStaleTarget(sendedTarget);
}

void AISOutputService::checkAndDeleteStaleTarget(QList<AISTargetModel *> targets)
{
    auto now = QDateTime::currentMSecsSinceEpoch();
#ifdef USE_LOG4QT
    for (auto target : targets) {
        logger()->debug()<<Q_FUNC_INFO<<" - ais target: "<<target->MMSI;
        logger()->trace()<<Q_FUNC_INFO<<" - now: "<<now;
        logger()->trace()<<Q_FUNC_INFO<<" - timestamp: "<<target->timestamp;
        logger()->trace()<<Q_FUNC_INFO<<" - timeout: "<<now - target->timestamp;

        if(now - target->timestamp > expiredTimeout) {
            if(aisRepo->FindOne(target->MMSI))
            {
                aisRepo->Remove(target->MMSI);
                logger()->info()<<Q_FUNC_INFO<<" - delete stale target: "<<target->MMSI;
            }
            else logger()->warn()<<Q_FUNC_INFO<<" - failed to delete stale target: "<<target->MMSI<<". cannot find target";
        }
    }
#else
    for (auto target : targets) {
        qDebug()<<Q_FUNC_INFO<<" - ais target: "<<target->MMSI;
        qDebug()<<Q_FUNC_INFO<<" - now: "<<now;
        qDebug()<<Q_FUNC_INFO<<" - timestamp: "<<target->timestamp;
        qDebug()<<Q_FUNC_INFO<<" - timeout: "<<now - target->timestamp;

        if(now - target->timestamp > expiredTimeout) {
            if(aisRepo->FindOne(target->MMSI))
            {
                aisRepo->Remove(target->MMSI);
                qInfo()<<Q_FUNC_INFO<<" - delete stale target: "<<target->MMSI;
            }
            else qWarning()<<Q_FUNC_INFO<<" - failed to delete stale target: "<<target->MMSI<<". cannot find target";
        }
    }
#endif
}

void AISOutputService::populateConfig(const QString cfg)
{
#ifdef USE_LOG4QT
    logger()->debug()<<Q_FUNC_INFO<<" - config: "<<cfg;
#else
    qDebug()<<Q_FUNC_INFO<<" - config: "<<cfg;
#endif

#if QT_VERSION > QT_VERSION_CHECK(5, 13, 0)
    QStringList config_list = cfg.split(";", Qt::SkipEmptyParts);
#else
    QStringList config_list = cfg.split(";", QString::SkipEmptyParts);
#endif
    if(config_list.size() == 4)
    {
        bool ok;
        timeout = config_list.at(1).toInt(&ok);
        if(!ok)
        {
            timeout = 1000;
#ifdef USE_LOG4QT
            logger()->warn()<<Q_FUNC_INFO<<" - invalid timeout config "<<cfg<<". will use default";
#else
            qWarning()<<Q_FUNC_INFO<<" - invalid timeout config "<<cfg<<". will use default";
#endif
        }

        sendLimit = config_list.at(2).toInt(&ok);
        if(!ok)
        {
            sendLimit = 5;
#ifdef USE_LOG4QT
            logger()->warn()<<Q_FUNC_INFO<<" - invalid send limit config "<<cfg<<". will use default";
#else
            qWarning()<<Q_FUNC_INFO<<" - invalid send limit config "<<cfg<<". will use default";
#endif
        }

        expiredTimeout = config_list.at(3).toInt(&ok);
        if(!ok)
        {
            expiredTimeout = 10000;
#ifdef USE_LOG4QT
            logger()->warn()<<Q_FUNC_INFO<<" - invalid expired timeout config "<<cfg<<". will use default";
#else
            qWarning()<<Q_FUNC_INFO<<" - invalid expired timeout config "<<cfg<<". will use default";
#endif
        }
    }
#ifdef USE_LOG4QT
    else logger()->fatal("invalid config %s", cfg.toUtf8().constData());
#else
    else qFatal("invalid config %s", cfg.toUtf8().constData());
#endif
}

void AISOutputService::updateDataSendCounter()
{
    dataSendCounter += sendLimit;
    if (dataSendCounter >= aisRepo->Count()) {
        dataSendCounter = 0;
    }
}
