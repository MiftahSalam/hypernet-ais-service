#include "ais_output_service.h"
#include "usecase/ais_sender/ais_output_serializer_json.h"

#include <QDebug>
#include <QList>

AISOutputService::AISOutputService(QObject *parent, AISTargetRepository *repo, QString cfg)
    : QObject{parent}, dataSendCounter(0), aisRepo(repo)
{
    if(!repo) qFatal("ais repo is null");

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
    } else qDebug()<<Q_FUNC_INFO<<"ais target query result  is empty";

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
    qDebug()<<Q_FUNC_INFO<<"ais target size"<<aisRepo->FindAll().size();

    auto sendedTarget = sendTarget();
    checkAndDeleteStaleTarget(sendedTarget);
}

void AISOutputService::checkAndDeleteStaleTarget(QList<AISTargetModel *> targets)
{
    auto now = QDateTime::currentMSecsSinceEpoch();
    for (auto target : targets) {
        qDebug()<<Q_FUNC_INFO<<"ais target"<<target->MMSI;
        qDebug()<<Q_FUNC_INFO<<"now"<<now;
        qDebug()<<Q_FUNC_INFO<<"timestamp"<<target->timestamp;
        qDebug()<<Q_FUNC_INFO<<"timeout"<<now - target->timestamp;

        if(now - target->timestamp > expiredTimeout) {
            if(aisRepo->FindOne(target->MMSI))
            {
                aisRepo->Remove(target->MMSI);
                qInfo()<<Q_FUNC_INFO<<"delete stale target"<<target->MMSI;
            }
            else qWarning()<<Q_FUNC_INFO<<"failed to delete stale target"<<target->MMSI<<". cannot find target";
        }
    }
}

void AISOutputService::populateConfig(const QString cfg)
{
    qDebug()<<Q_FUNC_INFO<<"config"<<cfg;

#if QT_VERSION > QT_VERSION_CHECK(5, 13, 0)
    QStringList config_list = cfg.split(";", Qt::SkipEmptyParts);
#else
    QStringList config_list = config.split(";", QString::SkipEmptyParts);
#endif
    if(config_list.size() == 4)
    {
        bool ok;
        timeout = config_list.at(1).toInt(&ok);
        if(!ok)
        {
            timeout = 1000;
            qWarning()<<Q_FUNC_INFO<<"invalid timeout config"<<cfg<<". will use default";
        }

        sendLimit = config_list.at(2).toInt(&ok);
        if(!ok)
        {
            sendLimit = 5;
            qWarning()<<Q_FUNC_INFO<<"invalid send limit config"<<cfg<<". will use default";
        }

        expiredTimeout = config_list.at(3).toInt(&ok);
        if(!ok)
        {
            expiredTimeout = 10000;
            qWarning()<<Q_FUNC_INFO<<"invalid expired timeout config"<<cfg<<". will use default";
        }
    }
    else qFatal("invalid config %s", cfg.toUtf8().constData());
}

void AISOutputService::updateDataSendCounter()
{
    dataSendCounter += sendLimit;
    if (dataSendCounter >= aisRepo->Count()) {
        dataSendCounter = 0;
    }
}
