#pragma once

#include <vector>
#include <array>
#include <ostream>
#include <inttypes.h>

enum Field : uint8_t
{
    Empty,
    Red,
    Yellow
};

enum PlayerID : uint8_t
{
    Red,
    Yellow
};

/*struct Move
{
    int columnSelected;
};*/

struct Move{

};

struct Board
{
    void listNextMoves(PlayerID turn, Board* outBoards, Move* outMoves, size_t maxOutputs) const;
    
};

std::ostream& operator << (std::ostream& o, const Board& b);