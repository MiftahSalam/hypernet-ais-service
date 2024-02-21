#include "ais_input.h"

#ifdef USE_LOG4QT
#include <log4qt/logger.h>
LOG4QT_DECLARE_STATIC_LOGGER(logger, AISInput)
#else
#include <QDebug>
#endif

AISInput::AISInput(Stream *input, AISInputService *service)
    : aisInput(input), aisService(service)
{
#ifdef USE_LOG4QT
    if(!input) logger()->fatal("ais input stream is null");
    if(!service) logger()->fatal("ais input service is null");

    adjuster = new DataInputAdjuster(this, '!', '\r');
#else
    if(!input) qFatal("ais input stream is null");
    if(!service) qFatal("ais input service is null");

    adjuster = new DataInputAdjuster('!', '\r');
#endif
    decoder = new AISLib::AISDecoder(this);

    connect(aisInput, &Stream::SignalReceiveData, this, &AISInput::onAisInputDataReceived);
    connect(decoder, &AISLib::AISDecoder::signalNewTrarget, this, &AISInput::onNewAisTarget);
    connect(&timer, &QTimer::timeout, this, &AISInput::onTimerTimeout);

    aisInput->Reconnect();

    timer.start(1000);
}

void AISInput::onNewAisTarget(AISLib::AISTargetData *data)
{
    //validation?

    //create or insert data
    aisService->createOrUpdateTarget(data);
}

void AISInput::onTimerTimeout()
{
    //check stream status
#ifdef USE_LOG4QT
    logger()->debug()<<Q_FUNC_INFO<<" - "<<aisInput->GetStreamStatusString();
#else
    qDebug()<<Q_FUNC_INFO<<" - "<<aisInput->GetStreamStatusString();
#endif
}

void AISInput::onAisInputDataReceived(const QString &data)
{
#ifdef USE_LOG4QT
    logger()->debug()<<Q_FUNC_INFO<<" - "<<data;
#else
    qDebug()<<Q_FUNC_INFO<<" - "<<data;
#endif

    //decode
    for (auto result : adjuster->appendAndAdjustData(data.toUtf8())) {
        QString dataToProcess = QString(result);
#ifdef USE_LOG4QT
        logger()->trace()<<Q_FUNC_INFO<<" - dataToProcess: "<<dataToProcess;
        if (!dataToProcess.isEmpty()) {
            logger()->debug()<<Q_FUNC_INFO<<" - decode status: "<<decoder->decode(dataToProcess);
        }
#else
        qDebug()<<Q_FUNC_INFO<<" - dataToProcess: "<<dataToProcess;
        if (!dataToProcess.isEmpty()) {
            qDebug()<<Q_FUNC_INFO<<" - decode status: "<<decoder->decode(dataToProcess);
        }
#endif
    }
}

AISInput::~AISInput()
{
    delete adjuster;
}
