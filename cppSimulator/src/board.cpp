#include "board.h"


Board potez(Board X, Move M){
    //Promjena pozicije figurice u skladu sa onom navedenom u potezu
    X.ALL[M.index].Position [0] = M.Position[0];
    X.ALL[M.index].Position [1] = M.Position[1];

    PlayerID mi = X.ALL[M.index].player;
    PlayerID ploca = M.board;
    PlayerID druga_ploca = (ploca == A)?B : A;

    PlayerID suprotni = (mi == A )?B : A;

    for (int i = 0; i < 96; i++){
        if (X.ALL[i].board == M.board
            && X.ALL[i].player == suprotni
            && X.ALL[i].Position[0] == M.Position[0]
            && X.ALL[i].Position[0] == M.Position[0])
            {
                X.ALL[i].Position[0] = -1;
                X.ALL[i].Position[1] = -1;
                X.ALL[i].player = mi;
                X.ALL[i].board = druga_ploca;
            }
    }

    return X;

}

void Board::listNextMoves(PlayerID player, PlayerID ploca, Board* outBoards, Move* outMoves, size_t maxOutputs) const{
    int i = 0;
    while (i < maxOutputs){
        for (int j = 0; j < 96; j++){
            if (ALL[j].player == player && ALL[j].board == ploca){
                if (ALL[j].Position[0] == -1){
                    for (int i1 = 0; i1 < 12; i1++){
                        for (int i2 = 0; i2 < 12; i2++){
                            if 
                        }
                    }
                }
            }
        }
    }

}

std::ostream& operator << (std::ostream& o, const Board& b)
{

    return o;
}