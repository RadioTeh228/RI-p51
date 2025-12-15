#include "lab8.h"
#include <QDir>
#include <QFileInfo>

// -------- Logger --------
Logger::Logger(QObject* parent): QObject(parent) {
    logPath = QDir::currentPath() + "/shootingLog.log";
}
void Logger::rotateIfNeeded() {
    QFileInfo fi(logPath);
    const qint64 limit = 50ll * 1024 * 1024; // 50 МБ
    if (fi.exists() && fi.size() >= limit) {
        QString ts = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
        QString newName = fi.absolutePath() + "/shootingLog_" + ts + ".log";
        QFile::rename(logPath, newName);
    }
}
void Logger::log(const QString& action, const QString& details) {
    rotateIfNeeded();
    QFile f(logPath);
    if (!f.open(QIODevice::Append | QIODevice::Text)) return;
    QTextStream out(&f);
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
        << " | " << action;
    if (!details.isEmpty()) out << " | " << details;
    out << "\n";
}

// -------- ShooterLane --------
ShooterLane::ShooterLane(int id, QObject* parent)
    : QObject(parent), laneId(id)
{
    tick.setInterval(1000);
    connect(&tick, &QTimer::timeout, this, &ShooterLane::onTick);
    reset();
}
void ShooterLane::reset() {
    tick.stop(); st=LaneState::Idle; s={}; secLeft=0; paused=false; emit updated();
}
void ShooterLane::startWaiting(){ st=LaneState::Waiting;  secLeft=30; tick.start(); emit updated(); }
void ShooterLane::startShooting(){ st=LaneState::Shooting; tick.start(); emit updated(); }
void ShooterLane::startReload(){   st=LaneState::Reloading; secLeft=30; tick.start(); emit updated(); }
void ShooterLane::startReplace(){  st=LaneState::Replacing; secLeft=30; tick.start(); emit updated(); }
void ShooterLane::pause(bool on){ paused=on; }

void ShooterLane::onTick() {
    if (paused) return;

    switch (st) {
    case LaneState::Waiting:
    case LaneState::Reloading:
    case LaneState::Replacing:
        if (secLeft > 0) { --secLeft; emit updated(); }
        if (secLeft == 0) {
            if (st == LaneState::Waiting) startShooting();
            else if (st == LaneState::Reloading) startReplace();
            else { // Replacing
                if (s.shotsFired < 10) startShooting();
                else { st=LaneState::Finished; tick.stop(); emit laneFinished(laneId); emit updated(); }
            }
        }
        break;
    case LaneState::Shooting:
        if (s.shotsFired < 10) {
            ++s.shotsFired;
            if (s.targetsHit < 9) ++s.targetsHit;
            if (!s.prizeGiven && s.targetsHit >= 5) s.prizeGiven = true;
            emit updated();
            if (s.shotsFired == 10) { st=LaneState::Finished; tick.stop(); emit laneFinished(laneId); }
        }
        break;
    default:
        tick.stop(); break;
    }
}
