#ifndef core_h
#define core_h

#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

struct Location {
    int X;
    int Y;

    Location(int X_, int Y_) : X(X_), Y(Y_) {}
    Location(const Location &A) : X(A.X), Y(A.Y) {}
};

class Core {
    int **Chessboard; //存储棋盘。人类落子记为1；AI落子记为-1；空位记为0；可下的点记为-2。

    int bestAIX;
    int bestAIY;

    void divide(int i, int j, vector<Location> &, vector<Location> &, vector<Location> &); //将可以落子的地方分到不同的级别
    int cal_value(int X, int Y); //计算棋子的价值
    void cal_range(bool IsAI, vector<Location> &Range); //计算可以落子的地方                                                             //判断是否赢棋了
    int rank_score(int Count, int Yoko); //计算每个棋子的的价值
    int evalute(); //评估棋盘

  public:
    Core();
    ~Core();

    void ai_do(int &tempAIX, int &tempAIY, int Deep); //计算每个点的得分，并将落子的地点传递给tempAIX和tempAIY
    void human_do(int tempHumanX, int tempHumanY); //人类落子
    int get(int X, int Y);

    int min(int Deep, int Alpha, int Beta); //最小搜索
    int max(int Deep, int Alpha, int Beta); //最大搜索

    bool win(int X, int Y);

    //    void print_chessboard() {
    //        for (int i = 0; i <= 15; ++i) {
    //            for (int j = 0; j <= 15; ++j) {
    //                if (Chessboard[i][j] >= 0)
    //                    cout << Chessboard[i][j] << "  ";
    //                if (Chessboard[i][j] < 0)
    //                    cout << Chessboard[i][j] << " ";
    //            }
    //            cout << endl;
    //        }
    //	cout << endl;
    //    }
};
#endif /* Core_hpp */
