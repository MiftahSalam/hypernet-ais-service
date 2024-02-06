#include "ais_target_model.h"

AISTargetModel::AISTargetModel(const AISTargetModel &track)
{
    this->id = track.id;
    this->rng = track.rng;
    this->brn = track.brn;
    this->spd = track.spd;
    this->crs = track.crs;
    this->lat = track.lat;
    this->lon = track.lon;
    this->alt = track.alt;
}
