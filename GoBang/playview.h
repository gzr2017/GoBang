#ifndef PLAYVIEW_H
#define PLAYVIEW_H

#include "myscene.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>

namespace Ui {
class PlayView;
}

class PlayView : public QWidget {
    Q_OBJECT

  public:
    explicit PlayView(QWidget *parent = 0);
    ~PlayView();

  private slots:
    void on_pushButton_Exit_clicked();
    void on_pushButton_Start_clicked();

  private:
    Ui::PlayView *ui;

  signals:
    bool start_game(bool StartGame);
};

#endif // PLAYVIEW_H
