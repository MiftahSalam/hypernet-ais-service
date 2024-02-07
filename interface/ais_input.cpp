#include "ais_input.h"

#include "qdebug.h"

AISInput::AISInput(Stream *input, AISInputService *service)
    : aisInput(input), aisService(service)
{
    decoder = new AISLib::AISDecoder(this);

    connect(aisInput, &Stream::SignalReceiveData, this, &AISInput::onAisInputDataReceived);
    connect(decoder, &AISLib::AISDecoder::signalNewTrarget, this, &AISInput::onNewAisTarget);

    aisInput->Reconnect();
}

void AISInput::onAisInputDataReceived(const QString &data)
{
    qDebug()<<Q_FUNC_INFO<<data;

    //decode
    decoder->decode(data);
}

void AISInput::onNewAisTarget(AISLib::AISTargetData *data)
{
    aisService->createNewTarget(data);
}
