#include "playview.h"
#include "ui_playview.h"

PlayView::PlayView(QWidget *parent) : QWidget(parent), ui(new Ui::PlayView) {
    ui->setupUi(this);
    MyScene *Scene = new MyScene();
    ui->Chessboard->setScene(Scene);
    connect(this, &PlayView::start_game, Scene, &MyScene::start_game);
}
PlayView::~PlayView() { delete ui; }

void PlayView::on_pushButton_Exit_clicked() {
    QCoreApplication::exit();
}

void PlayView::on_pushButton_Start_clicked() {
    ui->pushButton_Start->setText("新游戏");
    emit start_game(true);
}
