#include "ais_input.h"

#include "qdebug.h"

AISInput::AISInput(Stream *input, AISInputService *service)
    : aisInput(input), aisService(service)
{
    if(!input) qFatal("ais input stream is null");
    if(!service) qFatal("ais input service is null");

    decoder = new AISLib::AISDecoder(this);
    adjuster = new DataInputAdjuster('!', '\r');

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
    qDebug()<<Q_FUNC_INFO<<aisInput->GetStreamStatusString();

    //update ais input service
    aisService->update();
}

void AISInput::onAisInputDataReceived(const QString &data)
{
    qDebug()<<Q_FUNC_INFO<<data;

    //decode
    for (auto result : adjuster->appendAndAdjustData(data.toUtf8())) {
        QString dataToProcess = QString(result);
        qDebug()<<Q_FUNC_INFO<<"dataToProcess"<<dataToProcess;
        if (!dataToProcess.isEmpty()) {
            qDebug()<<Q_FUNC_INFO<<"decode status"<<decoder->decode(dataToProcess);
        }
    }
}

AISInput::~AISInput()
{
    delete adjuster;
}
