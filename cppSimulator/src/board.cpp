#include "board.h"


Board potez(Board X, Move M){
    //definiram ko sm mi a ko suprotni
    PlayerID mi = X.ALL[M.index].player;
    PlayerID ploca = M.board;

    PlayerID druga_ploca = ( ploca == A ) ? B : A;
    PlayerID suprotni = ( mi == A )?B : A;

    //Promjena pozicije figurice u skladu sa onom navedenom u potezu
    X.ploca[X.ALL[M.index].x][X.ALL[M.index].y] = -1; //mijenjam staru poziciju na ništa
    X.ploca[M.x][M.y] = 

    //mijenjam koordinate u nizu
    X.ALL[M.index].x = M.Position[0];
    X.ALL[M.index].y = M.Position[1];

    
    

    for (int i = 0; i < 96; i++){
        if (X.ALL[i].board == M.board
            && X.ALL[i].player == suprotni
            && X.ALL[i].Position[0] == M.Position[0]
            && X.ALL[i].Position[0] == M.Position[0])
            {
                

                switch (X.ALL[M.index].F)
                {
                case Kamikaza:
                    //cuvam stare koordinate kamikaze pa ih postavljam na (-2, -2) sto oznacava da se ne vraca u igru
                    int x_kamikaza = X.ALL[M.index].x;
                    int y_kamikaza = X.ALL[M.index].y;
                    X.ALL[M.index].x = -2;
                    X.ALL[M.index].y = -2;

                    if (x_kamikaza == 0 ){ //ako smo u prvom redu
                        if(X.ploca[x_kamikaza + 1][y_kamikaza].F != Cigla && X.ploca[x_kamikaza + 1][y_kamikaza].F != Kralj){
                            X.ploca[x_kamikaza + 1][y_kamikaza]  = -1; //ubije donjeg
                        }

                        if (y_kamikaza != 0 && y_kamikaza != 11){ //ako nije ni prvi ni zadnji i ako nije cigla ubija lijevog i desnog
                            if(X.ALL[X.A[x_kamikaza][y_kamikaza - 1]].F != Cigla && X.ALL[X.A[x_kamikaza][y_kamikaza - 1]].F != Kralj){
                                X.ploca[x_kamikaza][y_kamikaza - 1] = -1;
                            }
                            else if(X.A[x_kamikaza][y_kamikaza + 1].F != Cigla && X.A[x_kamikaza][y_kamikaza + 1].F != Kralj){
                                X.ploca[x_kamikaza][y_kamikaza + 1] = -1;
                            }
                        }
                        else if (y_kamikaza == 0){ // ako je prvi u prvom redu ubija desnog
                            X.ploca[x_kamikaza][y_kamikaza + 1] = -1;
                        }
                        else{ //ako je zadnji u prvom redu ubija lijevog
                            X.ploca[x_kamikaza][y_kamikaza - 1] = -1;
                        }
                    }
                    //mijenja 
                    X.ploca[x_kamikaza - 1][y_kamikaza] = X.ploca[x_kamikaza + 1][y_kamikaza] = -1;
                    X.ploca[x_kamikaza][y_kamikaza - 1] = X.ploca[x_kamikaza][y_kamikaza + 1] = -1;
                    break;
                
                default:
                    break;
                }
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