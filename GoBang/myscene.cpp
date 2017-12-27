#include "myscene.h"

MyScene::MyScene(QWidget *parent) : QGraphicsScene(parent), C(NULL), IsHumanPlaying(false) {
    setSceneRect(-13, -13, 476, 476);
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *E) {
    if (!IsHumanPlaying) {
        return;
    } else {
        int tempHumanX = E->lastScenePos().toPoint().ry() % 30;
        int tempHumanY = E->lastScenePos().toPoint().rx() % 30;
        if (tempHumanX > 15)
            tempHumanX = E->lastScenePos().toPoint().ry() / 30 + 1;
        else if (tempHumanX <= 15)
            tempHumanX = E->lastScenePos().toPoint().ry() / 30;
        if (tempHumanY > 15)
            tempHumanY = E->lastScenePos().toPoint().rx() / 30 + 1;
        else if (tempHumanY <= 15)
            tempHumanY = E->lastScenePos().toPoint().rx() / 30;

        if (C->get(tempHumanX, tempHumanY) == -1 || C->get(tempHumanX, tempHumanY) == 1)
            return;
        else {
            IsHumanPlaying = false;
            QPen QP;
            QBrush QB;
            QB.setStyle(Qt::SolidPattern);
            QB.setColor(Qt::white);
            QP.setBrush(Qt::white);
            addEllipse(tempHumanY * 30 - 13, tempHumanX * 30 - 13, 26, 26, QP, QB);
            C->human_do(tempHumanX, tempHumanY);
            if (C->win(tempHumanX, tempHumanY)) {
                QMessageBox Message(QMessageBox::NoIcon, "WIN!", "你赢了这场棋！", QMessageBox::Ok);
                if (Message.exec() == QMessageBox::Ok) {
                    start_game(true);
                    return;
                }
            }
            ai_do();
        }
    }
}

void MyScene::ai_do() {
    C->ai_do(tempAIX, tempAIY, 4);
    ai_draw();
    if (C->win(tempAIX, tempAIY)) {
        QMessageBox Message(QMessageBox::NoIcon, "FAIL!", "AI赢了这场棋！", QMessageBox::Ok);
        if (Message.exec() == QMessageBox::Ok) {
            start_game(true);
            return;
        }
    }
    IsHumanPlaying = true;
}

void MyScene::ai_draw() {
    QPen QP;
    QBrush QB;
    QB.setStyle(Qt::SolidPattern);
    QB.setColor(Qt::black);
    QP.setBrush(Qt::black);
    addEllipse(tempAIY * 30 - 13, tempAIX * 30 - 13, 26, 26, QP, QB);
}

void MyScene::start_game(bool StartGame) {
    IsHumanPlaying = true;
    if (StartGame) {
        if (C != NULL)
            delete C;
        C = new Core();
        draw();
    }
}

void MyScene::draw() {
    clear();
    QPen QP;
    QBrush QB;
    QB.setStyle(Qt::SolidPattern);
    QB.setColor(QColor(224, 174, 116));
    setBackgroundBrush(QB);
    QB.setColor(Qt::black);
    QP.setBrush(Qt::black);
    addEllipse(7 * 30 - 13, 7 * 30 - 13, 26, 26, QP, QB); //画已经下了的那颗黑子
    for (int i = 0; i <= 15; ++i) {
        addLine(i * 30, 0, i * 30, 15 * 30);
        addLine(0, i * 30, 15 * 30, i * 30);
    }
}
