#ifndef MYSCENE_H
#define MYSCENE_H

#include "core.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <QWidget>

class MyScene : public QGraphicsScene
{
  Q_OBJECT
public:
  explicit MyScene(QWidget *parent = 0);
  ~MyScene()
  {
    if (C != NULL)
      delete C;
  }
  void start_game(bool StartGame);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent *E);
  Core *C;             //核心
  bool IsHumanPlaying; //人类是否可以落子
  int tempAIX;         //记录AI落子的X坐标
  int tempAIY;         //记录AI落子的Y坐标

  void ai_do();
  void ai_draw();

  void draw();
};

#endif // MYSCENE_H
