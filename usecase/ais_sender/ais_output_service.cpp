#include "ais_output_service.h"

#include <QDebug>

AISOutputService::AISOutputService(QObject *parent, AISTargetRepository *repo, QString cfg)
    : QObject{parent}, aisRepo(repo)
{
    populateConfig(cfg);

    connect(&timer, &QTimer::timeout, this, &AISOutputService::onTimeout);

    timer.start(timeout);
}

void AISOutputService::onTimeout()
{
    qDebug()<<Q_FUNC_INFO<<"ais target size"<<aisRepo->FindAll().size();
}

void AISOutputService::populateConfig(const QString cfg)
{
    qDebug()<<Q_FUNC_INFO<<"config"<<cfg;

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QStringList config_list = cfg.split(";", Qt::SkipEmptyParts);
#else
    QStringList config_list = config.split(";", QString::SkipEmptyParts);
#endif
    if(config_list.size() == 2)
    {
        bool ok;
        timeout = config_list.at(1).toInt(&ok);
        if(!ok)
        {
            timeout = 1000;
            qWarning()<<Q_FUNC_INFO<<"invalid timeout config"<<cfg<<". will use default";
        }
    }
    else qDebug()<<Q_FUNC_INFO<<"invalid config"<<cfg;
}
