#include "board.h"


Board Board::potez(Board X, Move M) const{
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
    const int (*P)[12][12] = &boards[ploca];
    while (i < maxOutputs){
        for (int j = 0; j < 96; j++){
            if (ALL[j].player == player && ALL[j].board == ploca){
                if (ALL[j].x == -1){
                    for (int i1 = 0; i1 < 12; i1++){
                        for (int i2 = 0; i2 < 12; i2++){
                            if ((*P)[i1][i2] == -1){
                                Move M;
                                M.board = ploca;
                                M.x = i1;
                                M.y = i2;
                                M.index = j;
                                outMoves[i] = M;
                                outBoards[i] = potez(*this, M);
                                i++;
                            }
                        }
                    }
                }
                else if (ALL[j].x >= 0){
                    int a = ALL[j].x;
                    int b = ALL[j].y;
                    switch (ALL[j].F)
                    {
                    case Kralj:
                        if (a > 0 && b > 0 && ((*P)[a-1][b-1] == -1 || (ALL[(*P)[a-1][b-1]].F != Cigla && ALL[(*P)[a-1][b-1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a-1;
                            M.y = b-1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (a > 0 && ((*P)[a-1][b] == -1 || (ALL[(*P)[a-1][b]].F != Cigla && ALL[(*P)[a-1][b]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a-1;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (a > 0 && b < 11 && ((*P)[a-1][b+1] == -1 || (ALL[(*P)[a-1][b+1]].F != Cigla && ALL[(*P)[a-1][b+1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a-1;
                            M.y = b+1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (a < 11 && b > 0 && ((*P)[a+1][b-1] == -1 || (ALL[(*P)[a+1][b-1]].F != Cigla && ALL[(*P)[a+1][b-1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b-1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (a < 11 && ((*P)[a+1][b] == -1 || (ALL[(*P)[a+1][b]].F != Cigla && ALL[(*P)[a+1][b]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (a < 11 && b < 11 && ((*P)[a+1][b+1] == -1 || (ALL[(*P)[a+1][b+1]].F != Cigla && ALL[(*P)[a+1][b+1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b+1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (b > 0 && ((*P)[a][b-1] == -1 || (ALL[(*P)[a][b-1]].F != Cigla && ALL[(*P)[a][b-1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b-1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (b < 11 && ((*P)[a][b+1] == -1 || (ALL[(*P)[a][b+1]].F != Cigla && ALL[(*P)[a][b+1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b+1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        break;
                    case Dama:
                        while (a > 0 && b > 0 && ((*P)[a-1][b-1] == -1 || (ALL[(*P)[a-1][b-1]].F != Cigla && ALL[(*P)[a-1][b-1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a-1;
                            M.y = b-1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a-1][b-1]].player != player){break;}
                            a--; b--;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        while (a > 0 && ((*P)[a-1][b] == -1 || (ALL[(*P)[a-1][b]].F != Cigla && ALL[(*P)[a-1][b]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a-1;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a-1][b]].player != player){break;}
                            a--;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        while (a > 0 && b < 11 && ((*P)[a-1][b+1] == -1 || (ALL[(*P)[a-1][b+1]].F != Cigla && ALL[(*P)[a-1][b+1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a-1;
                            M.y = b+1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a-1][b+1]].player != player){break;}
                            a--; b++;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        while (a < 11 && b > 0 && ((*P)[a+1][b-1] == -1 || (ALL[(*P)[a+1][b-1]].F != Cigla && ALL[(*P)[a+1][b-1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b-1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a+1][b-1]].player != player){break;}
                            a++; b--;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        while (a < 11 && ((*P)[a+1][b] == -1 || (ALL[(*P)[a+1][b]].F != Cigla && ALL[(*P)[a+1][b]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a+1][b]].player != player){break;}
                            a++;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        while (a < 11 && b < 11 && ((*P)[a+1][b+1] == -1 || (ALL[(*P)[a+1][b+1]].F != Cigla && ALL[(*P)[a+1][b+1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b+1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a+1][b+1]].player != player){break;}
                            a++; b++;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        while (b > 0 && ((*P)[a][b-1] == -1 || (ALL[(*P)[a][b-1]].F != Cigla && ALL[(*P)[a][b-1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b-1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a][b-1]].player != player){break;}
                            b--;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        while (b < 11 && ((*P)[a][b+1] == -1 || (ALL[(*P)[a][b+1]].F != Cigla && ALL[(*P)[a][b+1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b+1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a][b+1]].player != player){break;}
                            b++;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        break;
                    case Lovac:
                        while (a < 11 && b < 11 && ((*P)[a+1][b+1] == -1 || (ALL[(*P)[a+1][b+1]].F != Cigla && ALL[(*P)[a+1][b+1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b+1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a+1][b+1]].player != player){break;}
                            a++; b++;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        while (a < 11 && b > 0 && ((*P)[a+1][b-1] == -1 || (ALL[(*P)[a+1][b-1]].F != Cigla && ALL[(*P)[a+1][b-1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b-1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a+1][b-1]].player != player){break;}
                            a++; b--;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        while (a > 0 && b < 11 && ((*P)[a-1][b+1] == -1 || (ALL[(*P)[a-1][b+1]].F != Cigla && ALL[(*P)[a-1][b+1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a-1;
                            M.y = b+1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a-1][b+1]].player != player){break;}
                            a--; b++;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        while (a > 0 && b > 0 && ((*P)[a-1][b-1] == -1 || (ALL[(*P)[a-1][b-1]].F != Cigla && ALL[(*P)[a-1][b-1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a-1;
                            M.y = b-1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a-1][b--]].player != player){break;}
                            a--; b--;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        break;
                    case Konj:
                        if (0 <= a+1 && a+1 <= 11 && 0 <= b+3 && b+3 <= 11 && ((*P)[a+1][b+3] == -1 || (ALL[(*P)[a+1][b+3]].F != Cigla && ALL[(*P)[a+1][b+3]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b+3;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;                            
                        }
                        if (0 <= a-1 && a-1 <= 11 && 0 <= b+3 && b+3 <= 11 && ((*P)[a-1][b+3] == -1 || (ALL[(*P)[a-1][b+3]].F != Cigla && ALL[(*P)[a-1][b+3]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a-1;
                            M.y = b+3;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;                            
                        }
                        if (0 <= a+1 && a+1 <= 11 && 0 <= b-3 && b-3 <= 11 && ((*P)[a+1][b-3] == -1 || (ALL[(*P)[a+1][b-3]].F != Cigla && ALL[(*P)[a+1][b-3]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b-3;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;                            
                        }
                        if (0 <= a-1 && a-1 <= 11 && 0 <= b-3 && b-3 <= 11 && ((*P)[a-1][b-3] == -1 || (ALL[(*P)[a-1][b-3]].F != Cigla && ALL[(*P)[a-1][b-3]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a-1;
                            M.y = b-3;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;                            
                        }
                        if (0 <= a+3 && a+3 <= 11 && 0 <= b+1 && b+1 <= 11 && ((*P)[a+3][b+1] == -1 || (ALL[(*P)[a+3][b+1]].F != Cigla && ALL[(*P)[a+3][b+1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b+3;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;                            
                        }
                        if (0 <= a-3 && a-3 <= 11 && 0 <= b+1 && b+1 <= 11 && ((*P)[a-3][b+1] == -1 || (ALL[(*P)[a-3][b+1]].F != Cigla && ALL[(*P)[a-3][b+1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a-3;
                            M.y = b+1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;                            
                        }
                        if (0 <= a+3 && a+3 <= 11 && 0 <= b-1 && b-1 <= 11 && ((*P)[a+3][b-1] == -1 || (ALL[(*P)[a+3][b-1]].F != Cigla && ALL[(*P)[a+3][b-1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b-3;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;                            
                        }
                        if (0 <= a-3 && a-3 <= 11 && 0 <= b-1 && b-1 <= 11 && ((*P)[a-3][b-1] == -1 || (ALL[(*P)[a-3][b-1]].F != Cigla && ALL[(*P)[a-3][b-1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a-1;
                            M.y = b-3;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;                            
                        }
                        break;
                    case Top:
                        while (a > 0 && ((*P)[a-1][b] == -1 || (ALL[(*P)[a-1][b]].F != Cigla && ALL[(*P)[a-1][b]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a-1;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a-1][b]].player != player){break;}
                            a--;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        while (a < 11 && ((*P)[a+1][b] == -1 || (ALL[(*P)[a+1][b]].F != Cigla && ALL[(*P)[a+1][b]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a+1][b]].player != player){break;}
                            a++;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        while (b > 0 && ((*P)[a][b-1] == -1 || (ALL[(*P)[a][b-1]].F != Cigla && ALL[(*P)[a][b-1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b-1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a][b-1]].player != player){break;}
                            b--;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        while (b < 11 && ((*P)[a][b+1] == -1 || (ALL[(*P)[a][b+1]].F != Cigla && ALL[(*P)[a][b+1]].player != player))){
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b+1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                            if (ALL[(*P)[a][b+1]].player != player){break;}
                            b++;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        break;
                    case Cigla:
                        if (a > 0 && b > 0 && (*P)[a-1][b-1] == -1 ){
                            Move M;
                            M.board = ploca;
                            M.x = a-1;
                            M.y = b-1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (a > 0 && (*P)[a-1][b] == -1){
                            Move M;
                            M.board = ploca;
                            M.x = a-1;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (a > 0 && b < 11 && (*P)[a-1][b+1] == -1){
                            Move M;
                            M.board = ploca;
                            M.x = a-1;
                            M.y = b+1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (a < 11 && b > 0 && (*P)[a+1][b-1] == -1){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b-1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (a < 11 && (*P)[a+1][b] == -1){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (a < 11 && b < 11 && (*P)[a+1][b+1] == -1){
                            Move M;
                            M.board = ploca;
                            M.x = a+1;
                            M.y = b+1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (b > 0 && (*P)[a][b-1] == -1){
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b-1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (b < 11 && (*P)[a][b+1] == -1){
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b+1;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        break;
                    case Kamikaza:
                        if (0 <= a+2 && a+2 <= 11 && 0 <= b+2 && b+2 <= 11 && ((*P)[a+2][b+2] ==-1 || (ALL[(*P)[a+2][b+2]].player != player && ALL[(*P)[a+2][b+2]].F != Cigla))){
                            Move M;
                            M.board = ploca;
                            M.x = a+2;
                            M.y = b+2;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (0 <= a-2 && a-2 <= 11 && 0 <= b+2 && b+2 <= 11 && ((*P)[a-2][b+2] ==-1 || (ALL[(*P)[a-2][b+2]].player != player && ALL[(*P)[a-2][b+2]].F != Cigla))){
                            Move M;
                            M.board = ploca;
                            M.x = a-2;
                            M.y = b+2;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (0 <= a+2 && a+2 <= 11 && 0 <= b-2 && b-2 <= 11 && ((*P)[a+2][b-2] ==-1 || (ALL[(*P)[a+2][b-2]].player != player && ALL[(*P)[a+2][b-2]].F != Cigla))){
                            Move M;
                            M.board = ploca;
                            M.x = a+2;
                            M.y = b-2;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (0 <= a-2 && a-2 <= 11 && 0 <= b-2 && b-2 <= 11 && ((*P)[a-2][b-2] ==-1 || (ALL[(*P)[a-2][b-2]].player != player && ALL[(*P)[a-2][b-2]].F != Cigla))){
                            Move M;
                            M.board = ploca;
                            M.x = a-2;
                            M.y = b-2;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        break;
                    case Snajper:
                        if (0 <= a+2 && a+2 <= 11 && 0 <= b && b <= 11 && ((*P)[a+2][b] ==-1 || (ALL[(*P)[a+2][b]].player != player && ALL[(*P)[a+2][b]].F != Cigla))){
                            Move M;
                            M.board = ploca;
                            M.x = a+2;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (0 <= a-2 && a-2 <= 11 && 0 <= b && b <= 11 && ((*P)[a-2][b] ==-1 || (ALL[(*P)[a-2][b]].player != player && ALL[(*P)[a-2][b]].F != Cigla))){
                            Move M;
                            M.board = ploca;
                            M.x = a-2;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (0 <= a && a <= 11 && 0 <= b-2 && b-2 <= 11 && ((*P)[a][b-2] ==-1 || (ALL[(*P)[a][b-2]].player != player && ALL[(*P)[a][b-2]].F != Cigla))){
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b-2;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        if (0 <= a && a <= 11 && 0 <= b+2 && b+2 <= 11 && ((*P)[a][b+2] ==-1 || (ALL[(*P)[a][b+2]].player != player && ALL[(*P)[a][b+2]].F != Cigla))){
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b+2;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        break;
                    case Pijan:
                        if (player == ploca){
                            if(a==1){
                                if(0 <= a+2 && a+2 <= 11 && 0 <= b+2 && b+2 <= 11 && (*P)[a+2][b+2] == -1){
                                    Move M;
                                    M.board = ploca;
                                    M.x = a+2;
                                    M.y = b+2;
                                    M.index = j;
                                    outMoves[i] = M;
                                    outBoards[i] = potez(*this, M);
                                    i++;
                                }
                                if(0 <= a+2 && a+2 <= 11 && 0 <= b-2 && b-2 <= 11 && (*P)[a+2][b-2] == -1){
                                    Move M;
                                    M.board = ploca;
                                    M.x = a+2;
                                    M.y = b-2;
                                    M.index = j;
                                    outMoves[i] = M;
                                    outBoards[i] = potez(*this, M);
                                    i++;
                                }
                            }
                            if (0 <= a+1 && a+1 <= 11 && 0 <= b+1 && b+1 <= 11 && (*P)[a+1][b+1] == -1){
                                Move M;
                                M.board = ploca;
                                M.x = a+1;
                                M.y = b+1;
                                M.index = j;
                                outMoves[i] = M;
                                outBoards[i] = potez(*this, M);
                                i++;
                            }
                            if (0 <= a+1 && a+1 <= 11 && 0 <= b-1 && b-1 <= 11 && (*P)[a+1][b-1] == -1){
                                Move M;
                                M.board = ploca;
                                M.x = a+1;
                                M.y = b-1;
                                M.index = j;
                                outMoves[i] = M;
                                outBoards[i] = potez(*this, M);
                                i++;
                            }
                            if (0<=a+1 && a+1 <= 11 && (ALL[(*P)[a+1][b]].player != player && ALL[(*P)[a+1][b]].F != Cigla)){
                                Move M;
                                M.board = ploca;
                                M.x = a+1;
                                M.y = b;
                                M.index = j;
                                outMoves[i] = M;
                                outBoards[i] = potez(*this, M);
                                i++;
                            }
                        }
                        else{
                            if(a==10){
                                if(0 <= a-2 && a-2 <= 11 && 0 <= b+2 && b+2 <= 11 && (*P)[a-2][b+2] == -1){
                                    Move M;
                                    M.board = ploca;
                                    M.x = a-2;
                                    M.y = b+2;
                                    M.index = j;
                                    outMoves[i] = M;
                                    outBoards[i] = potez(*this, M);
                                    i++;
                                }
                                if(0 <= a-2 && a-2 <= 11 && 0 <= b-2 && b-2 <= 11 && (*P)[a-2][b-2] == -1){
                                    Move M;
                                    M.board = ploca;
                                    M.x = a-2;
                                    M.y = b-2;
                                    M.index = j;
                                    outMoves[i] = M;
                                    outBoards[i] = potez(*this, M);
                                    i++;
                                }
                            }
                            if (0 <= a-1 && a-1 <= 11 && 0 <= b+1 && b+1 <= 11 && (*P)[a-1][b+1] == -1){
                                Move M;
                                M.board = ploca;
                                M.x = a-1;
                                M.y = b+1;
                                M.index = j;
                                outMoves[i] = M;
                                outBoards[i] = potez(*this, M);
                                i++;
                            }
                            if (0 <= a-1 && a-1 <= 11 && 0 <= b-1 && b-1 <= 11 && (*P)[a-1][b-1] == -1){
                                Move M;
                                M.board = ploca;
                                M.x = a-1;
                                M.y = b-1;
                                M.index = j;
                                outMoves[i] = M;
                                outBoards[i] = potez(*this, M);
                                i++;
                            }
                            if (0<=a-1 && a-1 <= 11 && (ALL[(*P)[a-1][b]].player != player && ALL[(*P)[a-1][b]].F != Cigla)){
                                Move M;
                                M.board = ploca;
                                M.x = a-1;
                                M.y = b;
                                M.index = j;
                                outMoves[i] = M;
                                outBoards[i] = potez(*this, M);
                                i++;
                            }
                        }
                        break;
                    default:
                        break;
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