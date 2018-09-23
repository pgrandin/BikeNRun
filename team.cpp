#include "team.h"

Team::Team(QObject *parent) : QObject(parent)
{

}

Team::Team(const QString &dossard, QObject *parent)
    : QObject(parent), _dossard(dossard)
{
}

QString Team::dossard() const
{
    return _dossard;
}

QString Team::laps_as_string() const
{
    return QString::number(_current_lap) + "/" +QString::number(_target_laps);
}


int Team::current_lap()
{
    return _current_lap;
}

int Team::target_laps()
{
    return _target_laps;
}
