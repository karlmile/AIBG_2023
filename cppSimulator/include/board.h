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
    int Position[2];
    PlayerID player;
    PlayerID board;
};

struct Move{
    PlayerID board;
    int index;
    int Position[2];
};

struct Board{
    int A[12][12];
    int B[12][12];
    figura ALL[96];
    Board potez(Board old, Move M);
    void listNextMoves(PlayerID player, PlayerID ploca, Board* outBoards, Move* outMoves, size_t maxOutputs) const;
    
};

std::ostream& operator << (std::ostream& o, const Board& b);