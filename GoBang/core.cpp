#include "core.h"

Core::Core() : Chessboard(new int *[15 + 1]), bestAIX(-1), bestAIY(-1) {
    for (int i = 0; i <= 15; ++i)
        Chessboard[i] = new int[15 + 1]{0};
    Chessboard[7][7] = -1;
}

Core::~Core() {
    for (int i = 0; i <= 15; ++i)
        delete[] Chessboard[i];
    delete[] Chessboard;
}

bool Core::win(int X, int Y) {
    int tempX(X);
    int tempY(Y);
    int Dir[4][2][2]{{{-1, 0}, {1, 0}}, {{0, -1}, {0, 1}}, {{-1, -1}, {1, 1}}, {{1, -1}, {-1, 1}}};
    for (int i = 0; i < 4; ++i) {
        int Count = 1;
        for (int j = 0; j < 2; ++j) {
            bool Flag = true;
            while (Flag) {
                tempX = tempX + Dir[i][j][0];
                tempY = tempY + Dir[i][j][1];
                if (0 <= tempX && 0 <= tempY && tempX <= 15 && tempY <= 15) { //如果没有越界的话
                    if (Chessboard[tempX][tempY] == Chessboard[X][Y] && Chessboard[tempX][tempY] != 0 && Chessboard[tempX][tempY] != -2) {
                        Count++;
                        if (Count == 5)
                            return true;
                    } else {
                        Flag = false;
                    }
                } else //如果越界的话
                    Flag = false;
            }
            tempX = X;
            tempY = Y;
        }
    }
    return false;
}

int Core::get(int X, int Y) {
    return Chessboard[X][Y];
}


void Core::divide(int i, int j, vector<Location> &Scare1, vector<Location> &Scare2, vector<Location> &Scare3) {
    int temp = cal_value(i, j);
    if (temp < 1000)
        Scare1.push_back(Location(i, j));
    else if (1000 <= temp && temp < 10000)
        Scare2.push_back(Location(i, j));
    else if (10000 <= temp)
        Scare3.push_back(Location(i, j));
    Chessboard[i][j] = -2;
}

void Core::cal_range(bool IsAI, vector<Location> &Range) { //将可以走的地方加入到vector中去
    //1~100
    vector<Location> Scare1;
    //1000~10000
    vector<Location> Scare2;
    //10000~
    vector<Location> Scare3;
    //首先将所有的值都清空
    for (int i = 0; i <= 15; ++i) {
        for (int j = 0; j <= 15; ++j) {
            if (Chessboard[i][j] == -2)
                Chessboard[i][j] = 0;
        }
    }
    int Qi;
    if (IsAI)
        Qi = -1;
    else if (!IsAI)
        Qi = 1;

    int Dir[4][2][2]{{{-1, 0}, {1, 0}}, {{0, -1}, {0, 1}}, {{-1, -1}, {1, 1}}, {{1, -1}, {-1, 1}}};
    for (int i = 0; i <= 15; ++i) {
        for (int j = 0; j <= 15; ++j) {
            if (Chessboard[i][j] == 1 || Chessboard[i][j] == -1) { //如果这个点有棋子的话，判断这个棋子的上下左右棋子加入到行列中去
                for (int k = 0; k < 4; ++k) {
                    for (int l = 0; l < 2; ++l) {
                        int tempX = i + Dir[k][l][0];
                        int tempY = j + Dir[k][l][1];
                        if (0 <= tempX && 0 <= tempY && tempX <= 15 && tempY <= 15) {
                            if (Chessboard[tempX][tempY] == 0) {
                                Chessboard[tempX][tempY] = Qi;
                                divide(tempX, tempY, Scare1, Scare2, Scare3);
                            }
                        }
                    }
                }
            }
        }
    }
    if (IsAI) {
        Range.insert(Range.end(), Scare1.begin(), Scare1.end());
        Range.insert(Range.end(), Scare2.begin(), Scare2.end());
        Range.insert(Range.end(), Scare3.begin(), Scare3.end());
    } else if (!IsAI) {
        Range.insert(Range.end(), Scare3.begin(), Scare3.end());
        Range.insert(Range.end(), Scare2.begin(), Scare2.end());
        Range.insert(Range.end(), Scare1.begin(), Scare1.end());
    }
}


void Core::ai_do(int &tempAIX, int &tempAIY, int Deep) {
    max(Deep, -10000000, 10000000);
    tempAIX = bestAIX;
    tempAIY = bestAIY;
}

int Core::min(int Deep, int Alpha, int Beta) {
    int Best = 10000000;
    vector<Location> Range;
    cal_range(false, Range);
    while (!Range.empty()) {
        if (Chessboard[Range.back().X][Range.back().Y] != -1 && Chessboard[Range.back().X][Range.back().Y] != 1) {
            Chessboard[Range.back().X][Range.back().Y] = 1;
            int V = max(Deep - 1, Alpha, Best < Beta ? Best : Beta);
            Chessboard[Range.back().X][Range.back().Y] = 0;
            if (V < Best)
                Best = V;
            if (V <= Alpha)
                return V;
            Range.pop_back();
        }
    }
    return Best;
}

int Core::max(int Deep, int Alpha, int Beta) {
    if (Deep <= 0) {
        int Best = -10000000;
        vector<Location> Range;
        cal_range(true, Range);
        for (int i = 0; i < Range.size(); ++i) {
            Chessboard[Range[i].X][Range[i].Y] = -1;
            int temp = evalute();
            if (temp > Best)
                Best = temp;
            Chessboard[Range[i].X][Range[i].Y] = 0;
        }
        return Best;
    }

    int Best = -10000000;
    vector<Location> Range;
    cal_range(true, Range);
    while (!Range.empty()) {
        if (Chessboard[Range.back().X][Range.back().Y] != -1 && Chessboard[Range.back().X][Range.back().Y] != 1) {
            Chessboard[Range.back().X][Range.back().Y] = -1; //假装下棋
            int V = min(Deep - 1, Best > Alpha ? Best : Alpha, Beta);
            Chessboard[Range.back().X][Range.back().Y] = 0;
            if (V > Best) {
                if (Deep == 4) {
                    bestAIX = Range.back().X;
                    bestAIY = Range.back().Y;
                }
                Best = V;
            }
            if (V >= Beta) {
                if (Deep == 4)
                    Chessboard[bestAIX][bestAIY] = -1;
                return V;
            }
            Range.pop_back();
        }
    }
    if (Deep == 4)
        Chessboard[bestAIX][bestAIY] = -1;
    return Best;
}



void Core::human_do(int tempHumanX, int tempHumanY) { //人类落子
    if (Chessboard[tempHumanX][tempHumanY] == 0 || Chessboard[tempHumanX][tempHumanY] == -2)
        Chessboard[tempHumanX][tempHumanY] = 1;
}



int Core::cal_value(int X, int Y) {
    int SumScore = 0;
    int tempX(X);
    int tempY(Y);
    int Dir[4][2][2]{{{-1, 0}, {1, 0}}, {{0, -1}, {0, 1}}, {{-1, -1}, {1, 1}}, {{1, -1}, {-1, 1}}};
    for (int i = 0; i < 4; ++i) {
        int Count = 1;
        int Yoko = 2;
        for (int j = 0; j < 2; ++j) {
            bool Flag = true;
            while (Flag) {
                tempX = tempX + Dir[i][j][0];
                tempY = tempY + Dir[i][j][1];
                if (tempX != -1 && tempX != 16 && tempY != -1 && tempY != 16) { //如果没有越界的话
                    if (Chessboard[tempX][tempY] == Chessboard[X][Y]) {
                        Count++;
                    } else {
                        if (Chessboard[tempX][tempY] == -Chessboard[X][Y]) //如果这个地方它有别的棋子
                            Yoko--;
                        Flag = false;
                    }
                } else { //如果这个棋子到达了边界
                    Yoko--;
                    Flag = false;
                }
            }
            tempX = X;
            tempY = Y;
        }
        SumScore += rank_score(Count, Yoko);
    }
    return SumScore;
}

int Core::rank_score(int Count, int Yoko) {
    if (Count >= 5)
        return 100000;
    else {
        int Score;
        if (Count == 4) {
            Score = 10000;
        } else if (Count == 3) {
            Score = 1000;
        } else if (Count == 2) {
            Score = 100;
        } else if (Count == 1) {
            Score = 10;
        }
        if (Yoko == 1) {
            Score /= 10;
        } else if (Yoko == 0) {
            Score /= 100;
        }
        return Score;
    }
}

int Core::evalute() {
    int Human(0), AI(0);
    for (int i = 0; i <= 15; ++i) {
        for (int j = 0; j <= 15; ++j) {
            if (Chessboard[i][j] == 1) //评估每个棋子的价值
                Human += cal_value(i, j);
            else if (Chessboard[i][j] == -1) //评估每个棋子的价值
                AI += cal_value(i, j);
        }
    }
    return AI - Human;
}
