#pragma once

#include "board.h"

Move broadMinimax(const Board& b, PlayerID curPlayer, int maxDepth, size_t maxMemory);