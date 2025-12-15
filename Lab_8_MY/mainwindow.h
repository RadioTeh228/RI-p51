#pragma once
#include <QMainWindow>
#include "lab8.h"
#include <array>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void startGroup();
    void stopToggle();
    void replaceAll();
    void reloadAll();
    void nextGroup();
    void updateUi();
    void onLaneFinished(int id);
private:
    Ui::MainWindow *ui;
    Logger logger;
    std::array<ShooterLane*,5> lanes{};
    bool stopped = false;

    void connectLane(int i);
    void setButtonsEnabled(bool running);
    static QString stateText(LaneState st, int secLeft);
};
