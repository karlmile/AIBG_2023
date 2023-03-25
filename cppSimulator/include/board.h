#pragma once

#include <vector>
#include <array>
#include <ostream>
#include <inttypes.h>

enum Figurica : uint8_t
{
    Kralj,
    Dama,
    Cigla,
    Kamikaza,
    Snajper,
    Lovac,
    Konj,
    Top,
    Pijan
};

enum PlayerID : uint8_t
{
    A,
    B
};

struct figura{
    Figurica F;
    int x;
    int y;
    PlayerID player;
    PlayerID board;
};

struct Move{
    PlayerID board;
    int index;
    int x;
    int y;
};

struct Board{
    int boards[2][12][12];
    const int empty = -1;
    figura ALL[96];
    Board potez(Board old, Move M) const;
    void listNextMoves(PlayerID player, PlayerID ploca, Board* outBoards, Move* outMoves, size_t maxOutputs) const;
    
};

std::ostream& operator << (std::ostream& o, const Board& b);