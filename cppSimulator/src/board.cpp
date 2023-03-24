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

int board::score() const
{
    int scr = 0;
    bool redWon = false;
    bool yellWon = false;

    // tester for each array

    auto testerFunc = [&](int x, int y, int xm, int ym)
    {
        // For array
        bool hasReds = false;
        bool hasYells = false;
        int numTaken = 0;

        for (int i=0; i<4; i++)
        {
            // For each field in array
            switch (get(x, y))
            {
            case Field::Red:
                hasReds = true;
                numTaken++;
                break;
            case Field::Yellow:
                hasYells = true;
                numTaken++;
                break;
            }

            x+=xm;
            y+=ym;
        }

        // For array
        if (!hasReds || !hasYells)
        {
            int mult = hasReds? 1 : -1;

            if (numTaken == 4)
            {
                if (hasReds)
                    redWon = true;
                if (hasYells)
                    yellWon = true;
                //scr += 10000*mult;
            }
            else
            {
                scr += numTaken*mult;
            }
        }
    };


    // Loop over all arrays

    // ----
    for (int x = 0; x <= W-4; x++)
    {
        for (int y = 0; y <= H-1; y++)
        {
            testerFunc(x,y,1,0);
        }
    }

    // |
    for (int x = 0; x <= W-1; x++)
    {
        for (int y = 0; y <= H-4; y++)
        {
            testerFunc(x,y,0,1);
        }
    }

    // /
    for (int x = 0; x <= W-4; x++)
    {
        for (int y = H-1; y >= 0; y--)
        {
            testerFunc(x,y,1,-1);
        }
    }

    // \ 

    for (int x = 0; x <= W-4; x++)
    {
        for (int y = 0; y <= H-4; y++)
        {
            testerFunc(x,y,1,1);
        }
    }

    if (redWon && !yellWon)
        scr = 10000;
    if (!redWon && yellWon)
        scr = -10000;

    return scr;
}

Field board::get(uint8_t x, uint8_t y) const
{
    return fields[x][y];
    /*if (is_filled[x] & ('\1' << y))
    {
        if (is_red[x] & ('\1' << y))
        {
            return Field::Red;
        }
        else
        {
            return Field::Yellow;
        }
    }
    else
    {
        return Field::Empty;
    }*/
}

bool board::canAdd(uint8_t x) const
{
    return (get(x, 0) == Field::Empty);
}

void board::add(uint8_t x, Field f)
{
    for (int y=H-1; y>=0; y--)
    {
        if (get(x, y) == Field::Empty)
        {
            set(x, y, f);
            return;
        }
    }
}


void board::set(uint8_t x, uint8_t y, Field f)
{
    fields[x][y] = f;
    /*switch (f)
    {
    case Field::Empty:
        is_filled[x] = is_filled[x] & ~('\1' << y);
        break;
    case Field::Red:
        is_filled[x] = is_filled[x] | ('\1' << y);
        is_red[x] = is_red[x] | ('\1' << y);
        break;
    case Field::Yellow:
        is_filled[x] = is_filled[x] | ('\1' << y);
        is_red[x] = is_red[x] & ~('\1' << y);
        break;
    }*/
}

void board::listNextMoves(Field turn, Board* outBoards, Move*) const
{
    for (int x=0; x<W; x++)
    {
        if (canAdd(x))
        {
            out.push_back({x, *this});
            out.back().second.add(x, turn);
        }
    }
}

std::ostream& operator << (std::ostream& o, const board& b)
{
    for (int x = 0; x < board::W; x++)
        o << x;
    o << std::endl;

    for (int y = 0; y < board::H; y++)
    {
        for (int x = 0; x < board::W; x++)
        {
            switch (b.get(x, y))
            {
            case Field::Empty:
                o << '_';
                break;
            case Field::Red:
                o << 'R';
                break;
            case Field::Yellow:
                o << 'Y';
                break;
            }
        }
        o << std::endl;
    }
    for (int x = 0; x < board::W; x++)
        o << x;

    o << std::endl;

    return o;
}