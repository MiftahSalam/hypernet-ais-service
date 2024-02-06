#ifndef AIS_TARGET_MODEL_H
#define AIS_TARGET_MODEL_H

#include <string>

class AISTargetModel
{
public:
    AISTargetModel();
    AISTargetModel(const AISTargetModel &target);

    int                       MMSI;
    int                       IMO;
    unsigned char             Class;
    std::string               VendorID;
    unsigned char             ShipType;
    std::string               ShipName;
    std::string               ShipNameExtension;
    std::string               CallSign;
    int                       NavStatus;
    double                    Lat;
    double                    Lon;
    double                    SOG;
    double                    HDG;
    double                    COG;
    int                       ROTAIS;
    int                       ROTIND;
    int                       DimA;
    int                       DimB;
    int                       DimC;
    int                       DimD;
    double                    Draft;
    double                    Euro_Length;
    double                    Euro_Beam;
    double                    Euro_Draft;
    std::string               Euro_VIN;
    int                       UN_shiptype;
    int                       ETA_Mo;
    int                       ETA_Day;
    int                       ETA_Hr;
    int                       ETA_Min;
    int                       ETA_Simulation;
    std::string               Destination;
    unsigned long long        PositionReportTicks;
    unsigned long long        StaticReportTicks;
};

#endif // AIS_TARGET_MODEL_H
