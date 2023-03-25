#pragma once

#include "board.h"

Move broadMinimax(const Board& b, PlayerID curPlayer, PlayerID curBoard, int maxDepth, size_t maxMemory);