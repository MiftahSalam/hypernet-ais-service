#ifndef AIS_OUTPUT_SERIALIZER_H
#define AIS_OUTPUT_SERIALIZER_H

#include "domain/ais/ais_target_model.h"

#include <QList>

class AISOutputSerializer
{
public:
    AISOutputSerializer(AISTargetModel* data) {
        m_data.append(data);
    }
    AISOutputSerializer(QList<AISTargetModel*> data) {
        m_data.append(data);
    };

    virtual ~AISOutputSerializer(){}

    virtual QString decode() = 0;

protected:
    QList<AISTargetModel*> m_data;
};
#endif // AIS_OUTPUT_SERIALIZER_H
