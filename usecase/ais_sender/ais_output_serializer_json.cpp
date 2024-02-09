#include "ais_output_serializer_json.h"

#include <QJsonDocument>
#include <QJsonArray>

AISOutputSerializer_JSON::AISOutputSerializer_JSON(AISTargetModel *data)
    : AISOutputSerializer(data)
{

}

AISOutputSerializer_JSON::AISOutputSerializer_JSON(QList<AISTargetModel *> data)
    : AISOutputSerializer(data)
{

}

QString AISOutputSerializer_JSON::decode()
{
    QJsonDocument doc;

        if (m_data.size() > 1) {
            QJsonArray array;

            foreach (auto m, m_data) {
                array.append(toJsonObj(m));
            }

            doc = QJsonDocument(array);
        } else {
            if (isArray) {
                QJsonArray array;

                array.append(toJsonObj(m_data[0]));
                doc = QJsonDocument(array);
            } else doc = QJsonDocument(toJsonObj(m_data[0]));
        }

        return QString(doc.toJson(QJsonDocument::Compact));
}

QJsonObject AISOutputSerializer_JSON::toJsonObj(const AISTargetModel *m)
{
    QJsonObject obj;

    obj["time_utc"] = m->timestamp;
    obj["mmsi"] = m->MMSI;
    obj["imo"] = m->IMO;
//    obj["class"] = m->Class;
    obj["class"] = QString::fromStdString(m->ClassStr);
    obj["vendor_id"] = QString::fromStdString(m->VendorID);
//    obj["ship_type"] = m->ShipType;
    obj["ship_type"] = QString::fromStdString(m->ShipTypeString);
    obj["ship_name"] = QString::fromStdString(m->ShipName);
    obj["ship_name_ext"] = QString::fromStdString(m->ShipNameExtension);
    obj["call_sign"] = QString::fromStdString(m->CallSign);
//    obj["nav_status"] = m->NavStatus;
    obj["nav_status"] = QString::fromStdString(m->NavStatusString);
    obj["latitude"] = m->Lat;
    obj["longitude"] = m->Lon;
    obj["speed"] = m->SOG;
    obj["bearing"] = m->HDG;
    obj["course"] = m->COG;
    obj["rate_of_turn"] = m->ROTAIS;
    obj["dim_a"] = m->DimA;
    obj["dim_b"] = m->DimB;
    obj["dim_c"] = m->DimD;
    obj["dim_d"] = m->DimD;
    obj["draft"] = m->Draft;
    obj["euro_length"] = m->Euro_Length;
    obj["euro_beam"] = m->Euro_Beam;
    obj["euro_draft"] = m->Euro_Draft;
    obj["euro_vin"] = QString::fromStdString(m->Euro_VIN);
    obj["un_ship_type"] = m->UN_shiptype;
    obj["eta_month"] = m->ETA_Mo;
    obj["eta_day"] = m->ETA_Day;
    obj["eta_hour"] = m->ETA_Hr;
    obj["eta_minute"] = m->ETA_Min;
    obj["eta_simulation"] = m->ETA_Simulation;
    obj["position_report_tick"] = static_cast<qint64>(m->PositionReportTicks);
    obj["position_report_period"] = static_cast<qint64>(m->StaticReportTicks);
    obj["destination"] = QString::fromStdString(m->Destination);

    return obj;
}
