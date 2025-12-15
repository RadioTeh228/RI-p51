#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QLabel>
#include <QProgressBar>

static QString idName(const char* base, int i){ return QString("%1%2").arg(base).arg(i); }

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i=0;i<5;++i) {
        lanes[i] = new ShooterLane(i+1, this);
        connect(lanes[i], &ShooterLane::updated,      this, &MainWindow::updateUi);
        connect(lanes[i], &ShooterLane::laneFinished, this, &MainWindow::onLaneFinished);
    }

    connect(ui->btnStart,   &QPushButton::clicked, this, &MainWindow::startGroup);
    connect(ui->btnStop,    &QPushButton::clicked, this, &MainWindow::stopToggle);
    connect(ui->btnReplace, &QPushButton::clicked, this, &MainWindow::replaceAll);
    connect(ui->btnReload,  &QPushButton::clicked, this, &MainWindow::reloadAll);
    connect(ui->btnNext,    &QPushButton::clicked, this, &MainWindow::nextGroup);

    setButtonsEnabled(false);
    ui->statusbar->showMessage("Готово. Натисни «Старт групи».");
}

MainWindow::~MainWindow(){ delete ui; }

void MainWindow::setButtonsEnabled(bool running){
    ui->btnStop->setEnabled(running);
    ui->btnReplace->setEnabled(running);
    ui->btnReload->setEnabled(running);
    ui->btnNext->setEnabled(running);
}

QString MainWindow::stateText(LaneState st, int secLeft){
    switch (st) {
    case LaneState::Idle:      return "Порожньо";
    case LaneState::Waiting:   return QString("Очікування %1с").arg(secLeft);
    case LaneState::Shooting:  return "Стрільба";
    case LaneState::Reloading: return QString("Перезарядка %1с").arg(secLeft);
    case LaneState::Replacing: return QString("Заміна банок %1с").arg(secLeft);
    case LaneState::Finished:  return "Завершив (вихід)";
    }
    return "";
}

void MainWindow::startGroup(){
    logger.log("SessionStart","Початок групи (5 учасників)");
    stopped=false;
    for (auto* l: lanes){ l->reset(); l->startWaiting(); }
    setButtonsEnabled(true);
    ui->btnStop->setText("Стоп (переривання)");
    ui->statusbar->showMessage("Група стартувала: 30с очікування.");
}

void MainWindow::stopToggle(){
    stopped = !stopped;
    for (auto* l: lanes) l->pause(stopped);
    logger.log("StopToggle", stopped?"PAUSE ON":"PAUSE OFF");
    ui->btnStop->setText(stopped? "Продовжити":"Стоп (переривання)");
    ui->statusbar->showMessage(stopped? "Пауза увімкнена":"Пауза знята");
}

void MainWindow::replaceAll(){
    logger.log("ReplaceTargets","Команда заміни банок");
    for (auto* l: lanes) if (l->state()!=LaneState::Finished) l->startReplace();
}

void MainWindow::reloadAll(){
    logger.log("ReloadAll","Команда перезарядки");
    for (auto* l: lanes) if (l->state()!=LaneState::Finished) l->startReload();
}

void MainWindow::nextGroup(){
    logger.log("NextGroup","Починається наступна група");
    startGroup();
}

void MainWindow::updateUi(){
    for (int i=1;i<=5;++i){
        auto* l = lanes[i-1];
        if (auto* pb = findChild<QProgressBar*>(idName("pbShots", i)))
            pb->setValue(l->stats().shotsFired);
        if (auto* pb2 = findChild<QProgressBar*>(idName("pbTargets", i)))
            pb2->setValue(l->stats().targetsHit);
        if (auto* lbl = findChild<QLabel*>(idName("lblState", i)))
            lbl->setText(stateText(l->state(), l->countdown()));
    }
}

void MainWindow::onLaneFinished(int id){
    const auto& s = lanes[id-1]->stats();
    logger.log("LaneFinished",
               QString("Місце %1: пострілів=%2, влучань=%3, приз=%4")
                   .arg(id).arg(s.shotsFired).arg(s.targetsHit)
                   .arg(s.prizeGiven? "так":"ні"));
    ui->statusbar->showMessage("Місце " + QString::number(id) + " завершило стрільбу.");
}
