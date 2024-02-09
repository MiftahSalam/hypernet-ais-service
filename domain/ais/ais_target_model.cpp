#include "ais_target_model.h"

AISTargetModel::AISTargetModel()
{
    IMO = 0;
    MMSI = 0;
    Class = 0;
    VendorID = "";
    ShipType = 19; //unknown
    ShipName = "";
    ShipNameExtension = "";
    CallSign = "";
    NavStatus = 15; //unknown
    Lat = 0.;
    Lon = 0.;
    SOG = 555.;
    COG = 666.;
    HDG = 511.;
    ROTAIS = -128;
    ROTIND = 0;
    DimA = DimB = DimC = DimD = 0;
    Draft = 0.;
    Euro_Length = 0;
    Euro_Beam = 0;
    Euro_Draft = 0;
    Euro_VIN = "";
    UN_shiptype = 0;
    ETA_Mo = 0;
    ETA_Day = 0;
    ETA_Hr = 24;
    ETA_Min = 60;
    Destination = "";
}

AISTargetModel::AISTargetModel(const AISTargetModel &target)
{
    timestamp = target.timestamp;
    IMO = target.IMO;
    MMSI = target.MMSI;
    Class = target.Class;
    VendorID = target.VendorID;
    ShipType = target.ShipType;
    ShipName = target.ShipName;
    ShipNameExtension = target.ShipNameExtension;
    CallSign = target.CallSign;
    NavStatus = target.NavStatus;
    Lat = target.Lat;
    Lon = target.Lon;
    SOG = target.SOG;
    COG = target.COG;
    HDG = target.HDG;
    ROTAIS = target.ROTAIS;
    ROTIND = target.ROTIND;
    DimA = target.DimA;
    DimB = target.DimB;
    DimC = target.DimC;
    DimD = target.DimD;
    Draft = target.Draft;
    Euro_Length = target.Euro_Length;
    Euro_Beam = target.Euro_Beam;
    Euro_Draft = target.Euro_Draft;
    Euro_VIN = target.Euro_VIN;
    UN_shiptype = target.UN_shiptype;
    ETA_Mo = target.ETA_Mo;
    ETA_Day = target.ETA_Day;
    ETA_Hr = target.ETA_Hr;
    ETA_Min = target.ETA_Min;
    Destination = target.Destination;

}
