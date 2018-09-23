#include "bikenrun.h"

#include <QDebug>
#include <QFile>

BikeNRun::BikeNRun(QObject *parent) : QObject(parent)
{

}

QQmlListProperty<QObject> BikeNRun::getTeams()
{
    return QQmlListProperty<QObject>(this, _teams);
}

int BikeNRun::handleOpenCSV(const QString &fileName)
{
    QString trimmedFileName = fileName;
    qDebug() << "About to open "+fileName;
    QFile file(trimmedFileName.remove(0, 7));
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return 1;
    }

    _teams.clear();

    // Skip the first line
    QByteArray line = file.readLine();
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QString d = line.split(',')[1];
        QString gender = line.split(',')[6];
        bool found=false;
        for(int i = 0; i < _teams.size(); i++)
        {
            Team *t2 = (Team *)_teams.at(i);
            if(t2->dossard() == d)
            {
                found=true;
                t2->members.append(gender);
            }
        }
        if(not(found)){
            Team * new_team = new Team(d);
            new_team->_target_laps = line.split(',')[3].toInt();
            new_team->_current_lap = 0;
            new_team->members.append(gender);
            _teams.append(new_team);
        }
    }
    emit teamsChanged();

}

void BikeNRun::recordLap(int index) {
    Team *t2 = (Team *)_teams.at(index);
    if(t2->_current_lap < t2->_target_laps ) {
        int nMilliseconds = myTimer.elapsed();
        t2->laps.append(nMilliseconds);
        t2->_current_lap++;
        emit teamsChanged();

        for(int i =0; i < t2->laps.size(); i++){
            QString out = QString("%1:%2").arg( t2->laps.at(i) / 60000        , 2, 10, QChar('0'))
                    .arg((t2->laps.at(i) % 60000) / 1000, 2, 10, QChar('0'));

            qDebug() << "lap " << (i+1) << ":" << out;
        }
    }
}

void BikeNRun::startTimer()
{
    myTimer.start();
}

void BikeNRun::stopTimer(const QString& fileName)
{

    QString trimmedFileName = fileName;
    qDebug() << "About to open "+fileName;
    QFile file(trimmedFileName.remove(0, 7));

    if ( file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text) )
    {
        QTextStream stream( &file );
        stream << "Dossard,Group,Chrono,Tours" << endl;

        for(int i = 0; i < _teams.size(); i++)
        {
            Team *t2 = (Team *)_teams.at(i);

            int male_count = 0;
            for(int i =0; i < t2->members.size(); i++){
                if(t2->members.at(i) == "M"){
                    male_count++;
                }
            }

            qDebug() << male_count << " males in the team";
            QString group = "";
            if (male_count == 2){
                group += "H";
            } else if (male_count == 1){
                group += "M";
            } else {
                group += "F";
            }

            group += QString::number(t2->target_laps());

            QString laps;
            int total_time_ms = 0;

            for(int i =0; i < t2->laps.size(); i++){
                QString lap_time = QString("%1:%2").arg( t2->laps.at(i) / 60000        , 2, 10, QChar('0'))
                        .arg((t2->laps.at(i) % 60000) / 1000, 2, 10, QChar('0'));

                if(laps.length() >0 )
                    laps +=  QString(",");

                laps += lap_time;

                total_time_ms += t2->laps.at(i);
            }

            for(int i = t2->laps.size(); i < t2->target_laps(); i++){
                if(laps.length() >0 )
                    laps +=  QString(",");
                laps += QString("--:--");
            }

            QString total_time = QString("%1:%2").arg( total_time_ms / 60000        , 2, 10, QChar('0'))
                    .arg((total_time_ms % 60000) / 1000, 2, 10, QChar('0'));


             QString line = t2->dossard() + QString(",")
                               + group + QString(",")
                               + total_time + QString(",")
                               + laps;
            stream << line << endl;
        }
    }
}

QString BikeNRun::getElapsedTime()
{
    int nMilliseconds = myTimer.elapsed();
    return QString("%1:%2").arg( nMilliseconds / 60000        , 2, 10, QChar('0'))
            .arg((nMilliseconds  % 60000) / 1000, 2, 10, QChar('0'));

}
