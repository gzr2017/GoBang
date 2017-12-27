#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    delete this->centralWidget();
    PlayView *PV = new PlayView(this);
    this->setCentralWidget(PV);
    PV->setFixedHeight(30 * 15 + 210);
    PV->setFixedWidth(30 * 15 + 80);
}
MainWindow::~MainWindow() { delete ui; }
