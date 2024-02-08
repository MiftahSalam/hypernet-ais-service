#include "ais_input.h"

#include "qdebug.h"

AISInput::AISInput(Stream *input, AISInputService *service)
    : aisInput(input), aisService(service)
{
    decoder = new AISLib::AISDecoder(this);
    adjuster = new DataInputAdjuster('!', '\r');

    connect(aisInput, &Stream::SignalReceiveData, this, &AISInput::onAisInputDataReceived);
    connect(decoder, &AISLib::AISDecoder::signalNewTrarget, this, &AISInput::onNewAisTarget);

    aisInput->Reconnect();
}

void AISInput::onNewAisTarget(AISLib::AISTargetData *data)
{
    aisService->createNewTarget(data);
}

void AISInput::onAisInputDataReceived(const QString &data)
{
    qDebug()<<Q_FUNC_INFO<<data;

    //decode
    QString dataToProcess = QString(adjuster->appendAndAdjustData(data.toUtf8()));
    qDebug()<<Q_FUNC_INFO<<"dataToProcess"<<dataToProcess;
    if (!dataToProcess.isEmpty()) {
        qDebug()<<Q_FUNC_INFO<<"decode status"<<decoder->decode(dataToProcess);
    }
}

AISInput::~AISInput()
{
    delete adjuster;
}
