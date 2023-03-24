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

using Move = uint8_t;

struct Board
{
    static const int W = 7;
    static const int H = 6;

    /*uint8_t is_filled[7] = {0,0,0,0,0,0,0};
    uint8_t is_red[7] = {0,0,0,0,0,0,0};*/
    Field fields[7][6];

    Field get(uint8_t x, uint8_t y) const;
    bool canAdd(uint8_t x) const;
    void add(uint8_t x, Field f);
    void set(uint8_t x, uint8_t y, Field f);

    int score() const;
    bool isFinished() const;
    void listNextMoves(PlayerID turn, Board[] outBoards, Move[] outMoves, size_t maxOutputs) const;
    
};

std::ostream& operator << (std::ostream& o, const Board& b);