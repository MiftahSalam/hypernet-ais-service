#include "di/di.h"

#include <QCoreApplication>
#include <QDir>

#ifdef USE_LOG4QT
#include <log4qt/logger.h>
#include <log4qt/propertyconfigurator.h>
#include <log4qt/loggerrepository.h>

static void initializeRootLogger();
static void shutdownRootLogger();
static void logStartup();
static void logShutdown();
static void setupRootLogger(const QString &introMessage);
static void shutDownRootLogger(const QString &extroMessage);
#endif


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

#ifdef USE_LOG4QT
    initializeRootLogger();
    logStartup();
#endif

    DI di;
    di.setup();

    int ret;
    {
        ret = a.exec();
    }

#ifdef USE_LOG4QT
    logShutdown();
    shutdownRootLogger();
#endif

    return ret;
}

#ifdef USE_LOG4QT
void initializeRootLogger()
{
    setupRootLogger(QStringLiteral("Root logger is setup."));
}

void shutdownRootLogger()
{
    shutDownRootLogger(QStringLiteral("Root logger was shutdown."));
}

void logStartup()
{
    auto logger = Log4Qt::Logger::rootLogger();

    logger->info(QStringLiteral("################################################################"));
    logger->info(QStringLiteral("#                          START                               #"));
    logger->info(QStringLiteral("################################################################"));
}

void logShutdown()
{
    auto logger = Log4Qt::Logger::rootLogger();

    logger->info(QStringLiteral("################################################################"));
    logger->info(QStringLiteral("#                          STOP                                #"));
    logger->info(QStringLiteral("################################################################"));
}

void setupRootLogger(const QString &introMessage)
{
    QString configFile = QCoreApplication::applicationDirPath() + QDir::separator() + QStringLiteral(".log4qt.properties");
    qDebug()<<configFile;
    if (QFile::exists(configFile))
        Log4Qt::PropertyConfigurator::configureAndWatch(configFile);
    if (!introMessage.isEmpty())
        Log4Qt::Logger::rootLogger()->info(introMessage);
}

void shutDownRootLogger(const QString &extroMessage)
{
    auto logger = Log4Qt::Logger::rootLogger();

    if (!extroMessage.isEmpty())
        logger->info(extroMessage);
    logger->removeAllAppenders();
    logger->loggerRepository()->shutdown();
}
#endif
