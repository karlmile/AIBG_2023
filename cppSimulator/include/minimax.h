#pragma once

#include "board.h"

move minimax(const board& b, Field curPlayer, int maxDepth);
int minVal(const board& b, int depthLeft, int alpha, int beta);
int maxVal(const board& b, int depthLeft, int alpha, int beta);