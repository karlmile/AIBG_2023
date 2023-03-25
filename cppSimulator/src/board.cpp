#include "board.h"

const std::map<char, Figurica> CharFiguricaMap = {
    {'K', Kralj},
    {'P', Pijan},
    {'C', Cigla},
    {'D', Dama},
    {'J', Kamikaza},
    {'N', Konj},
    {'L', Lovac},
    {'T', Top},
    {'S', Snajper}
};

const std::map<char, Figurica> FiguricaCharMap = {
    {Kralj, 'K'},
    {Pijan, 'P'},
    {Cigla, 'C'},
    {Dama, 'D'},
    {Kamikaza, 'J'},
    {Konj, 'N'},
    {Lovac, 'L'},
    {Top, 'T'},
    {Snajper, 'S'}
};

float Board::score() const
{
    
}


Board Board::potez(Board X, Move M) const{
    //definiram ko sm mi a ko suprotni
    PlayerID mi = X.ALL[M.index].player;
    PlayerID ploca = M.board;

    PlayerID druga_ploca = ( ploca == A ) ? B : A;
    PlayerID suprotni = ( mi == A )?B : A;

    if (X.boards[ploca][M.x][M.y] == -1){ // provjera je i traženo mjesto prazno pa ako je samo obrišemo staru poziciju i stavimo novu
        //Promjena pozicije figurice u skladu sa onom navedenom u potezu
        //mijenjam pozicije na ploci
        X.boards[ploca][X.ALL[M.index].x][X.ALL[M.index].y] = -1; //mijenjam staru poziciju na ništa
        X.boards[ploca][M.x][M.y] = M.index;

        //mijenjam koordinate u nizu svih figura
        X.ALL[M.index].x = M.x;
        X.ALL[M.index].y = M.y;
    }

    
    else{ //ako nije prazno ubijamo
        //X.ALL[X.boards[ploca][M.x][M.y]]  //ovo mi je figura koja je trenutno na toj poziciji
        //X.ALL[M.index]  //ovo je moja figura

    
        switch (X.ALL[M.index].F)
        {
        case Kamikaza:
            if (X.ALL[X.boards[ploca][M.x][M.y]].F == Lovac){//ako je na polju na koje dolazimo lovac onda ubijamo susjedne dijagonalne
                if (X.boards[ploca][M.x+1][M.y+1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].x = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].y = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].player = mi;
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].board = druga_ploca;
                    X.boards[ploca][M.x+1][M.y+1] = -1;
                }
                if (X.boards[ploca][M.x-1][M.y+1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].x = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].y = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].player = mi;
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].board = druga_ploca;
                    X.boards[ploca][M.x-1][M.y+1] = -1;
                }
                if (X.boards[ploca][M.x-1][M.y-1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].x = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].y = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].player = mi;
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].board = druga_ploca;
                    X.boards[ploca][M.x-1][M.y-1] = -1;
                }
                if (X.boards[ploca][M.x+1][M.y-1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].x = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].y = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].player = mi;
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].board = druga_ploca;
                    X.boards[ploca][M.x+1][M.y-1] = -1;
                }
            }
            
            //cuvam stare koordinate kamikaze pa ih postavljam na (-2, -2) sto oznacava da se ne vraca u igru
            int x = X.ALL[M.index].x;
            int y = X.ALL[M.index].y;
            X.ALL[M.index].x = -2;
            X.ALL[M.index].y = -2;

            //ubije figuru koja je bila na toj poziciji i dodaje je na naš stack
            X.ALL[X.boards[ploca][M.x][M.y]].x = -1;
            X.ALL[X.boards[ploca][M.x][M.y]].y = -1;
            X.ALL[X.boards[ploca][M.x][M.y]].player = mi;
            X.ALL[X.boards[ploca][M.x][M.y]].board = druga_ploca;

            //stavljam novu na tu poziciju
            X.boards[ploca][x][y] = -1; //mijenjam staru poziciju na ništa
            X.boards[ploca][M.x][M.y] = M.index; // na novu poziciju dodajem figuru

            //mijenjam koordinate u nizu svih figura za našu figuru
            X.ALL[M.index].x = M.x;
            X.ALL[M.index].y = M.y;

            //postavljam x i y na nove koordinate 
            x=M.x;
            y=M.y;

            if (x == 0 ){ //ako smo u prvom redu
                if(X.ALL[X.boards[ploca][x + 1][y]].F != Cigla && X.ALL[boards[ploca][x + 1][y]].F != Kralj){
                    
                    X.ALL[X.boards[ploca][x + 1][y]].x = -1;
                    X.ALL[X.boards[ploca][x + 1][y]].y = -1;
                    X.ALL[X.boards[ploca][x + 1][y]].player = mi;
                    X.ALL[X.boards[ploca][x + 1][y]].board = druga_ploca;
                    X.boards[ploca][x + 1][y]  = -1; //ubije donjeg
                }

                if (y != 0 && y != 11){ //ako nije ni prvi ni zadnji i ako nije cigla ili kralj ubija lijevog i desnog
                    if(X.ALL[X.boards[ploca][x][y - 1]].F != Cigla && X.ALL[X.boards[ploca][x][y - 1]].F != Kralj){
                        
                        X.ALL[X.boards[ploca][x][y - 1]].x = -1;
                        X.ALL[X.boards[ploca][x][y - 1]].y = -1;
                        X.ALL[X.boards[ploca][x][y - 1]].player = mi;
                        X.ALL[X.boards[ploca][x][y - 1]].board = druga_ploca;
                        X.boards[ploca][x][y - 1] = -1;
                    }
                    else if(X.ALL[X.boards[ploca][x][y + 1]].F != Cigla && X.ALL[boards[ploca][x ][y + 1]].F != Kralj){
                        
                        X.ALL[X.boards[ploca][x][y + 1]].x = -1;
                        X.ALL[X.boards[ploca][x][y + 1]].y = -1;
                        X.ALL[X.boards[ploca][x][y + 1]].player = mi;
                        X.ALL[X.boards[ploca][x][y + 1]].board = druga_ploca;
                        X.boards[ploca][x][y + 1] = -1;
                    }
                }
                else if (y == 0){ // ako je prvi u prvom redu ubija desnog
                    
                    X.ALL[X.boards[ploca][x][y + 1]].x = -1;
                    X.ALL[X.boards[ploca][x][y + 1]].y = -1;
                    X.ALL[X.boards[ploca][x][y + 1]].player = mi;
                    X.ALL[X.boards[ploca][x][y + 1]].board = druga_ploca;
                    X.boards[ploca][x][y + 1] = -1;
                }
                else{ //ako je zadnji u prvom redu ubija lijevog
                    
                    X.ALL[X.boards[ploca][x][y - 1]].x = -1;
                    X.ALL[X.boards[ploca][x][y - 1]].y = -1;
                    X.ALL[X.boards[ploca][x][y - 1]].player = mi;
                    X.ALL[X.boards[ploca][x][y - 1]].board = druga_ploca;
                    X.boards[ploca][x][y - 1] = -1;
                }
            }

            if (x == 11 ){ //ako smo u zadnjem redu
                if(X.ALL[X.boards[ploca][x - 1][y]].F != Cigla && X.ALL[boards[ploca][x - 1][y]].F != Kralj){
                    
                    X.ALL[X.boards[ploca][x - 1][y]].x = -1;
                    X.ALL[X.boards[ploca][x - 1][y]].y = -1;
                    X.ALL[X.boards[ploca][x - 1][y]].player = mi;
                    X.ALL[X.boards[ploca][x - 1][y]].board = druga_ploca;
                    X.boards[ploca][x - 1][y]  = -1; //ubije gornjeg
                }

                if (y != 0 && y != 11){ //ako nije ni prvi ni zadnji i ako nije cigla ili kralj ubija lijevog i desnog
                    if(X.ALL[X.boards[ploca][x][y - 1]].F != Cigla && X.ALL[X.boards[ploca][x][y - 1]].F != Kralj){
                        
                        X.ALL[X.boards[ploca][x][y - 1]].x = -1;
                        X.ALL[X.boards[ploca][x][y - 1]].y = -1;
                        X.ALL[X.boards[ploca][x][y - 1]].player = mi;
                        X.ALL[X.boards[ploca][x][y - 1]].board = druga_ploca;
                        X.boards[ploca][x][y - 1] = -1;
                    }
                    else if(X.ALL[X.boards[ploca][x][y + 1]].F != Cigla && X.ALL[boards[ploca][x ][y + 1]].F != Kralj){

                        X.ALL[X.boards[ploca][x][y + 1]].x = -1;
                        X.ALL[X.boards[ploca][x][y + 1]].y = -1;
                        X.ALL[X.boards[ploca][x][y + 1]].player = mi;
                        X.ALL[X.boards[ploca][x][y + 1]].board = druga_ploca;
                        X.boards[ploca][x][y + 1] = -1;

                    }
                }
                else if (y == 0){ // ako je prvi u zadnjem redu ubija desnog
                    
                    X.ALL[X.boards[ploca][x][y + 1]].x = -1;
                    X.ALL[X.boards[ploca][x][y + 1]].y = -1;
                    X.ALL[X.boards[ploca][x][y + 1]].player = mi;
                    X.ALL[X.boards[ploca][x][y + 1]].board = druga_ploca;
                    X.boards[ploca][x][y + 1] = -1;
                }
                else{ //ako je zadnji u zadnjem redu ubija lijevog
                    
                    X.ALL[X.boards[ploca][x][y - 1]].x = -1;
                    X.ALL[X.boards[ploca][x][y - 1]].y = -1;
                    X.ALL[X.boards[ploca][x][y - 1]].player = mi;
                    X.ALL[X.boards[ploca][x][y - 1]].board = druga_ploca;
                    X.boards[ploca][x][y - 1] = -1;
                }
            }

            if (y == 0 ){ //ako smo lijevo
                if(X.ALL[X.boards[ploca][x][y + 1]].F != Cigla && X.ALL[boards[ploca][x ][y + 1]].F != Kralj){
                    
                    X.ALL[X.boards[ploca][x][y + 1]].x = -1;
                    X.ALL[X.boards[ploca][x][y + 1]].y = -1;
                    X.ALL[X.boards[ploca][x][y + 1]].player = mi;
                    X.ALL[X.boards[ploca][x][y + 1]].board = druga_ploca;
                    X.boards[ploca][x][y + 1]  = -1; //ubije desnog
                }

                if (x != 0 && x != 11){ //ako nije ni prvi ni zadnji i ako nije cigla ili kralj ubija gornjeg i donjeg
                    if(X.ALL[X.boards[ploca][x - 1][y]].F != Cigla && X.ALL[X.boards[ploca][x - 1][y]].F != Kralj){
                        
                        X.ALL[X.boards[ploca][x - 1][y]].x = -1;
                        X.ALL[X.boards[ploca][x - 1][y]].y = -1;
                        X.ALL[X.boards[ploca][x - 1][y]].player = mi;
                        X.ALL[X.boards[ploca][x - 1][y]].board = druga_ploca;
                        X.boards[ploca][x - 1][y] = -1;
                        
                    }
                    else if(X.ALL[X.boards[ploca][x + 1][y]].F != Cigla && X.ALL[boards[ploca][x + 1][y]].F != Kralj){
                        
                        X.ALL[X.boards[ploca][x + 1][y]].x = -1;
                        X.ALL[X.boards[ploca][x + 1][y]].y = -1;
                        X.ALL[X.boards[ploca][x + 1][y]].player = mi;
                        X.ALL[X.boards[ploca][x + 1][y]].board = druga_ploca;
                        X.boards[ploca][x + 1][y] = -1;
                    }
                }
            }

            if (y == 11 ){ //ako smo desno
                if(X.ALL[X.boards[ploca][x][y - 1]].F != Cigla && X.ALL[boards[ploca][x ][y - 1]].F != Kralj){
                    
                    X.ALL[X.boards[ploca][x][y - 1]].x = -1;
                    X.ALL[X.boards[ploca][x][y - 1]].y = -1;
                    X.ALL[X.boards[ploca][x][y - 1]].player = mi;
                    X.ALL[X.boards[ploca][x][y - 1]].board = druga_ploca;
                    X.boards[ploca][x][y - 1]  = -1; //ubije lijevog
                }

                if (x != 0 && x != 11){ //ako nije ni prvi ni zadnji i ako nije cigla ili kralj ubija gornjeg i donjeg
                    if(X.ALL[X.boards[ploca][x - 1][y]].F != Cigla && X.ALL[X.boards[ploca][x - 1][y]].F != Kralj){
                        
                        X.ALL[X.boards[ploca][x - 1][y]].x = -1;
                        X.ALL[X.boards[ploca][x - 1][y]].y = -1;
                        X.ALL[X.boards[ploca][x - 1][y]].player = mi;
                        X.ALL[X.boards[ploca][x - 1][y]].board = druga_ploca;
                        X.boards[ploca][x - 1][y] = -1;
                    }
                    else if(X.ALL[X.boards[ploca][x + 1][y]].F != Cigla && X.ALL[boards[ploca][x + 1][y]].F != Kralj){
                        
                        X.ALL[X.boards[ploca][x + 1][y]].x = -1;
                        X.ALL[X.boards[ploca][x + 1][y]].y = -1;
                        X.ALL[X.boards[ploca][x + 1][y]].player = mi;
                        X.ALL[X.boards[ploca][x + 1][y]].board = druga_ploca;
                        X.boards[ploca][x + 1][y] = -1;
                    }
                }
            }

            break;

        case Top:
            if (X.ALL[X.boards[ploca][M.x][M.y]].F == Lovac){//ako je na polju na koje dolazimo lovac onda ubijamo susjedne dijagonalne
                if (X.boards[ploca][M.x+1][M.y+1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].x = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].y = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].player = mi;
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].board = druga_ploca;
                    X.boards[ploca][M.x+1][M.y+1] = -1;
                }
                if (X.boards[ploca][M.x-1][M.y+1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].x = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].y = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].player = mi;
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].board = druga_ploca;
                    X.boards[ploca][M.x-1][M.y+1] = -1;
                }
                if (X.boards[ploca][M.x-1][M.y-1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].x = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].y = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].player = mi;
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].board = druga_ploca;
                    X.boards[ploca][M.x-1][M.y-1] = -1;
                }
                if (X.boards[ploca][M.x+1][M.y-1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].x = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].y = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].player = mi;
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].board = druga_ploca;
                    X.boards[ploca][M.x+1][M.y-1] = -1;
                }
            }
            
            //čuvam stare koordinate da mogu kasnije uspoređivati
            int x = X.ALL[M.index].x;
            int y = X.ALL[M.index].y;

            //ubije figuru koja je bila na toj poziciji i dodaje je na naš stack
            X.ALL[X.boards[ploca][M.x][M.y]].x = -1;
            X.ALL[X.boards[ploca][M.x][M.y]].y = -1;
            X.ALL[X.boards[ploca][M.x][M.y]].player = mi;
            X.ALL[X.boards[ploca][M.x][M.y]].board = druga_ploca;

            //stavljam novu na tu poziciju
            X.boards[ploca][x][y] = -1; //mijenjam staru poziciju na ništa
            X.boards[ploca][M.x][M.y] = M.index; // na novu poziciju dodajem figuru

            //mijenjam koordinate u nizu svih figura za našu figuru
            X.ALL[M.index].x = M.x;
            X.ALL[M.index].y = M.y;

        
            if (x == M.x && M.y != 0 && M.y!= 11){ //ako se giba po istom redu
                if (y < M.y){ //ako se giba prema desno
                    if (X.boards[ploca][M.x][M.y+1] != -1){ //ako ima neko na sljedećem desnom polju onda ga ubije
                        
                        X.ALL[X.boards[ploca][M.x][M.y+1]].x = -1;
                        X.ALL[X.boards[ploca][M.x][M.y+1]].y = -1;
                        X.ALL[X.boards[ploca][M.x][M.y+1]].player = mi;
                        X.ALL[X.boards[ploca][M.x][M.y+1]].board = druga_ploca;
                        X.boards[ploca][M.x][M.y+1] = -1;
                    }
                }
                if (y > M.y){ //ako se giba prema lijevo
                    if (X.boards[ploca][M.x][M.y-1] != -1){ //ako ima neko na sljedećem lijevom polju onda ga ubije
                        
                        X.ALL[X.boards[ploca][M.x][M.y-1]].x = -1;
                        X.ALL[X.boards[ploca][M.x][M.y-1]].y = -1;
                        X.ALL[X.boards[ploca][M.x][M.y-1]].player = mi;
                        X.ALL[X.boards[ploca][M.x][M.y-1]].board = druga_ploca;
                        X.boards[ploca][M.x][M.y-1] = -1;
                    }
                }

            }

            if (y == M.y && M.x != 0 && M.x != 11){ //ako se giba po stupcu
                if (x < M.x){ //ako se giba prema dolje
                    if (X.boards[ploca][M.x+1][M.y] != -1){ //ako ima neko na sljedećem desnom polju onda ga ubije
                        
                        X.ALL[X.boards[ploca][M.x+1][M.y]].x = -1;
                        X.ALL[X.boards[ploca][M.x+1][M.y]].y = -1;
                        X.ALL[X.boards[ploca][M.x+1][M.y]].player = mi;
                        X.ALL[X.boards[ploca][M.x+1][M.y]].board = druga_ploca;
                        X.boards[ploca][M.x+1][M.y] = -1;
                    }
                }
                if (x > M.x){ //ako se giba prema gore
                    if (X.boards[ploca][M.x-1][M.y] != -1){ //ako ima neko na sljedećem desnom polju onda ga ubije
                        
                        X.ALL[X.boards[ploca][M.x-1][M.y]].x = -1;
                        X.ALL[X.boards[ploca][M.x-1][M.y]].y = -1;
                        X.ALL[X.boards[ploca][M.x-1][M.y]].player = mi;
                        X.ALL[X.boards[ploca][M.x-1][M.y]].board = druga_ploca;
                        X.boards[ploca][M.x-1][M.y] = -1;
                    }
                }
            }
            break;
        case Snajper:
            if (X.ALL[X.boards[ploca][M.x][M.y]].F == Lovac){//ako je na polju na koje dolazimo lovac onda ubijamo susjedne dijagonalne
                if (X.boards[ploca][M.x+1][M.y+1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].x = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].y = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].player = mi;
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].board = druga_ploca;
                    X.boards[ploca][M.x+1][M.y+1] = -1;
                }
                if (X.boards[ploca][M.x-1][M.y+1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].x = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].y = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].player = mi;
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].board = druga_ploca;
                    X.boards[ploca][M.x-1][M.y+1] = -1;
                }
                if (X.boards[ploca][M.x-1][M.y-1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].x = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].y = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].player = mi;
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].board = druga_ploca;
                    X.boards[ploca][M.x-1][M.y-1] = -1;
                }
                if (X.boards[ploca][M.x+1][M.y-1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].x = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].y = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].player = mi;
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].board = druga_ploca;
                    X.boards[ploca][M.x+1][M.y-1] = -1;
                }
            }
            
            //ubije figuru koja je bila na toj poziciji i dodaje je na naš stack
            X.ALL[X.boards[ploca][M.x][M.y]].x = -1;
            X.ALL[X.boards[ploca][M.x][M.y]].y = -1;
            X.ALL[X.boards[ploca][M.x][M.y]].player = mi;
            X.ALL[X.boards[ploca][M.x][M.y]].board = druga_ploca;
            X.boards[ploca][M.x][M.y] = -1; //na novu poziciju ne stavlja ništa, on ostaje na staroj
            break;

        default:
            if (X.ALL[X.boards[ploca][M.x][M.y]].F == Lovac){//ako je na polju na koje dolazimo lovac onda ubijamo susjedne dijagonalne
                if (X.boards[ploca][M.x+1][M.y+1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].x = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].y = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].player = mi;
                    X.ALL[X.boards[ploca][M.x+1][M.y+1]].board = druga_ploca;
                    X.boards[ploca][M.x+1][M.y+1] = -1;
                }
                if (X.boards[ploca][M.x-1][M.y+1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].x = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].y = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].player = mi;
                    X.ALL[X.boards[ploca][M.x-1][M.y+1]].board = druga_ploca;
                    X.boards[ploca][M.x-1][M.y+1] = -1;
                }
                if (X.boards[ploca][M.x-1][M.y-1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].x = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].y = -1;
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].player = mi;
                    X.ALL[X.boards[ploca][M.x-1][M.y-1]].board = druga_ploca;
                    X.boards[ploca][M.x-1][M.y-1] = -1;
                }
                if (X.boards[ploca][M.x+1][M.y-1] != -1 && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F != Cigla && X.ALL[X.boards[ploca][M.x+1][M.y+1]].F !=Kralj){
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].x = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].y = -1;
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].player = mi;
                    X.ALL[X.boards[ploca][M.x+1][M.y-1]].board = druga_ploca;
                    X.boards[ploca][M.x+1][M.y-1] = -1;
                }
            }
            
            //ubije figuru koja je bila na toj poziciji
            X.ALL[X.boards[ploca][M.x][M.y]].x = -1;
            X.ALL[X.boards[ploca][M.x][M.y]].y = -1;


            //stavljam novu na tu poziciju
            X.boards[ploca][X.ALL[M.index].x][X.ALL[M.index].y] = -1; //mijenjam staru poziciju na ništa
            X.boards[ploca][M.x][M.y] = M.index;

            //mijenjam koordinate u nizu svih figura
            X.ALL[M.index].x = M.x;
            X.ALL[M.index].y = M.y;
            
            

            break;
        }
    }


    return X;

}

int Board::listNextMoves(PlayerID player, PlayerID ploca, Board* outBoards, Move* outMoves, size_t maxOutputs) const{
    int i = 0;
    const int (*P)[12][12] = &boards[ploca];
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
                        if (a > 0 && b > 0 && ((*P)[a-1][b-1] == -1)){
                            while(a > 0 && b > 0 && ((*P)[a][b] == -1) && ALL[(*P)[a-1][b-1]].F != Cigla && ALL[(*P)[a-1][b-1]].player != player){
                                a--; b--;
                            }
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        if (a > 0 && ((*P)[a-1][b] == -1)){
                            while(a > 0 && ((*P)[a][b] == -1) && ALL[(*P)[a-1][b]].F != Cigla && ALL[(*P)[a-1][b]].player != player){
                                a--;
                            }
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        if (a > 0 && b < 11 && ((*P)[a-1][b+1] == -1)){
                            while(a > 0 && b > 11 && ((*P)[a][b] == -1) && ALL[(*P)[a-1][b+1]].F != Cigla && ALL[(*P)[a-1][b+1]].player != player){
                                a--; b++;
                            }
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        if (a < 11 && b > 0 && ((*P)[a+1][b-1] == -1)){
                            while(a > 0 && b > 0 && ((*P)[a][b] == -1) && ALL[(*P)[a+1][b-1]].F != Cigla && ALL[(*P)[a+1][b-1]].player != player){
                                a++; b--;
                            }
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        if (a < 11 && ((*P)[a+1][b] == -1)){
                            while(a > 0 && ((*P)[a][b] == -1) && ALL[(*P)[a+1][b]].F != Cigla && ALL[(*P)[a+1][b]].player != player){
                                a++;
                            }
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        if (a < 11 && b < 11 && ((*P)[a+1][b+1] == -1)){
                            while(a > 0 && b > 0 && ((*P)[a][b] == -1) && ALL[(*P)[a+1][b+1]].F != Cigla && ALL[(*P)[a+1][b+1]].player != player){
                                a++; b++;
                            }
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        if (b < 11 && ((*P)[a][b+1] == -1)){
                            while(b < 11 && ((*P)[a][b] == -1) && ALL[(*P)[a][b+1]].F != Cigla && ALL[(*P)[a][b+1]].player != player){
                                b++;
                            }
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
                        }
                        int a = ALL[j].x;
                        int b = ALL[j].y;
                        if (b > 0 && ((*P)[a][b-1] == -1)){
                            while(b > 0 && ((*P)[a][b] == -1) && ALL[(*P)[a][b-1]].F != Cigla && ALL[(*P)[a][b-1]].player != player){
                                b--;
                            }
                            Move M;
                            M.board = ploca;
                            M.x = a;
                            M.y = b;
                            M.index = j;
                            outMoves[i] = M;
                            outBoards[i] = potez(*this, M);
                            i++;
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
                        if (0 <= a+2 && a+2 <= 11 && 0 <= b && b <= 11 && ALL[(*P)[a+2][b]].F != Cigla){
                            if ((*P)[a+1][b] == -1){
                                if ((*P)[a+2][b] == -1 || ALL[(*P)[a+2][b]].player != player){
                                    Move M;
                                    M.board = ploca;
                                    M.x = a+2;
                                    M.y = b;
                                    M.index = j;
                                    outMoves[i] = M;
                                    outBoards[i] = potez(*this, M);
                                    i++;
                                }
                            }
                        }
                        if (0 <= a-2 && a-2 <= 11 && 0 <= b && b <= 11 && ALL[(*P)[a-2][b]].F != Cigla){
                            if ((*P)[a-1][b] == -1){
                                if ((*P)[a-2][b] == -1 || ALL[(*P)[a-2][b]].player != player){
                                    Move M;
                                    M.board = ploca;
                                    M.x = a-2;
                                    M.y = b;
                                    M.index = j;
                                    outMoves[i] = M;
                                    outBoards[i] = potez(*this, M);
                                    i++;
                                }
                            }
                        }
                        if (0 <= a && a <= 11 && 0 <= b+2 && b+2 <= 11 && ALL[(*P)[a][b+2]].F != Cigla){
                            if ((*P)[a][b+1] == -1){
                                if ((*P)[a][b+2] == -1 || ALL[(*P)[a][b+2]].player != player){
                                    Move M;
                                    M.board = ploca;
                                    M.x = a;
                                    M.y = b+2;
                                    M.index = j;
                                    outMoves[i] = M;
                                    outBoards[i] = potez(*this, M);
                                    i++;
                                }
                            }
                        }
                        if (0 <= a && a <= 11 && 0 <= b-2 && b-2 <= 11 && ALL[(*P)[a][b-2]].F != Cigla){
                            if ((*P)[a][b-1] == -1){
                                if ((*P)[a][b-2] == -1 || ALL[(*P)[a][b-2]].player != player){
                                    Move M;
                                    M.board = ploca;
                                    M.x = a;
                                    M.y = b-2;
                                    M.index = j;
                                    outMoves[i] = M;
                                    outBoards[i] = potez(*this, M);
                                    i++;
                                }
                            }
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
    return i;
}

std::ostream& operator << (std::ostream& o, const Board& b)
{

    return o;
}