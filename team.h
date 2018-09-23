#ifndef TEAM_H
#define TEAM_H

#include <QObject>

class Team : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString dossard READ dossard NOTIFY dossardChanged)
    Q_PROPERTY(QString laps_as_string READ laps_as_string NOTIFY lapsChanged)
    Q_PROPERTY(int current_lap READ current_lap NOTIFY currentLapChanged)
    Q_PROPERTY(int target_laps READ target_laps NOTIFY targetLapsChanged)

public:
    explicit Team(QObject *parent = nullptr);
    Team(const QString &dossard, QObject *parent = nullptr);

    QString dossard() const;
    QString laps_as_string() const;
    int current_lap();
    int target_laps();
    int _current_lap;
    int _target_laps;

    QList<int> laps;
    QList<QString> members;

signals:
    void dossardChanged();
    void lapsChanged();
    void currentLapChanged();
    void targetLapsChanged();

private:
    QString _dossard;


public slots:

};

#endif // TEAM_H
