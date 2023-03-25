#pragma once

#include <vector>
#include <array>
#include <ostream>
#include <inttypes.h>
#include <map>

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

extern const std::map<char, Figurica> CharFiguricaMap;
extern const std::map<Figurica, char> FiguricaCharMap;

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

const int EMPTY_FIELD = -1;
const int MAX_POTEZA = 230;

struct Board{
    int boards[2][12][12];
    figura ALL[96];
    float score(PlayerID ploca , PlayerID player) const;
    Board potez(Board old, Move M) const;
    int listNextMoves(PlayerID player, PlayerID ploca, Board* outBoards, Move* outMoves, size_t maxOutputs, bool pocetak) const;
};

std::ostream& operator << (std::ostream& o, const Board& b);