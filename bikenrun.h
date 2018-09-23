#ifndef BIKENRUN_H
#define BIKENRUN_H

#include <QObject>
#include <QQmlListProperty>
#include <QTime>

#include "team.h"

class BikeNRun : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QObject> teams READ getTeams NOTIFY teamsChanged)

public:
    explicit BikeNRun(QObject *parent = nullptr);
    QQmlListProperty<QObject> getTeams();

private:
    QList<QObject *> _teams;
    QTime myTimer;

signals:
    void teamsChanged();

public slots:
    int handleOpenCSV(const QString& fileName);
    void recordLap(int index);
    void startTimer();
    void stopTimer(const QString& fileName);
    QString getElapsedTime();
};


#endif // BIKENRUN_H
