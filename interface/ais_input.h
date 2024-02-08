#ifndef AISINPUT_H
#define AISINPUT_H

#include "infra/stream/stream.h"
#include "data_input_adjuster.h"
#include "usecase/ais_parser/ais_input_service.h"

#include <QObject>

#include <AISLib/aisdecoder.h>

class AISInput: public QObject
{
    Q_OBJECT
public:
    AISInput(Stream *input, AISInputService *service);
    ~AISInput();

private slots:
    void onAisInputDataReceived(const QString &data);
    void onNewAisTarget(AISLib::AISTargetData *data);

private:
    Stream *aisInput;
    AISInputService *aisService;

    AISLib::AISDecoder *decoder;
    DataInputAdjuster *adjuster;
};

#endif // AISINPUT_H
