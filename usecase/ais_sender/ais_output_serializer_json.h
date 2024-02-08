#ifndef AISOUTPUTSERIALIZER_JSON_H
#define AISOUTPUTSERIALIZER_JSON_H

#include "ais_output_serializer.h"

#include <QJsonObject>

class AISOutputSerializer_JSON: public AISOutputSerializer
{
public:
    AISOutputSerializer_JSON(AISTargetModel* data);
    AISOutputSerializer_JSON(QList<AISTargetModel*> data);

    // AISOutputSerializer interface
    QString decode() override;

private:
    QJsonObject toJsonObj(const AISTargetModel* m);
};

#endif // AISOUTPUTSERIALIZER_JSON_H
