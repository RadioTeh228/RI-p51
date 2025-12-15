#pragma once
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QTimer>
#include <array>

enum class LaneState { Idle, Waiting, Shooting, Reloading, Replacing, Finished };

struct LaneStats {
    int shotsFired = 0;      // до 10
    int targetsHit = 0;      // до 9
    bool prizeGiven = false; // після 5 влучань
};

class Logger : public QObject {
    Q_OBJECT
public:
    explicit Logger(QObject* parent=nullptr);
    void log(const QString& action, const QString& details=QString());
private:
    void rotateIfNeeded();
    QString logPath;
};

class ShooterLane : public QObject {
    Q_OBJECT
public:
    explicit ShooterLane(int id, QObject* parent=nullptr);

    int id() const { return laneId; }
    LaneState state() const { return st; }
    const LaneStats& stats() const { return s; }
    int countdown() const { return secLeft; }

    void reset();           // скидання
    void startWaiting();    // 30с до початку
    void startShooting();   // постріли
    void startReload();     // 30с
    void startReplace();    // 30с
    void pause(bool on);    // Стоп/Продовжити
signals:
    void updated();
    void laneFinished(int id);
private slots:
    void onTick();
private:
    int laneId;
    LaneState st = LaneState::Idle;
    LaneStats s;
    QTimer tick;       // 1 Гц
    int secLeft = 0;   // лічильник 30с
    bool paused = false;
};
