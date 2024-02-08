#include "ais_output_service.h"
#include "usecase/ais_sender/ais_output_serializer_json.h"

#include <QDebug>
#include <QList>

AISOutputService::AISOutputService(QObject *parent, AISTargetRepository *repo, QString cfg)
    : QObject{parent}, dataSendCounter(0), aisRepo(repo)
{
    populateConfig(cfg);

    connect(&timer, &QTimer::timeout, this, &AISOutputService::onTimeout);

    timer.start(timeout);
}

void AISOutputService::sendTarget()
{
    updateDataSendCounter();

    auto targets = getTargets();
    if (targets.size() > 0) {
        QList<AISTargetModel*> qlist(targets.begin(), targets.end());
        AISOutputSerializer* serializer = new AISOutputSerializer_JSON(qlist);

        emit signalSendAISTargetRaw(serializer->decode().toUtf8());
    } else qDebug()<<Q_FUNC_INFO<<"ais target query result  is empty";
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

    sendTarget();
}

void AISOutputService::populateConfig(const QString cfg)
{
    qDebug()<<Q_FUNC_INFO<<"config"<<cfg;

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QStringList config_list = cfg.split(";", Qt::SkipEmptyParts);
#else
    QStringList config_list = config.split(";", QString::SkipEmptyParts);
#endif
    if(config_list.size() == 3)
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
    }
    else qDebug()<<Q_FUNC_INFO<<"invalid config"<<cfg;
}

void AISOutputService::updateDataSendCounter()
{
    dataSendCounter += sendLimit;
    if (dataSendCounter >= aisRepo->Count()) {
        dataSendCounter = 0;
    }
}
