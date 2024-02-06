#ifndef AIS_TARGET_MODEL_H
#define AIS_TARGET_MODEL_H

class AISTargetModel
{
public:
    AISTargetModel() {}
    AISTargetModel(const AISTargetModel &track);

    int id;
    double lat;
    double lon;
    double alt;
    double rng;
    double brn;
    double spd;
    double crs;
};

#endif // AIS_TARGET_MODEL_H
