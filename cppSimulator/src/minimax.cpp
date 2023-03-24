#include "minimax.h"
#include <limits>

move minimax(const board& b, Field curPlayer, int maxDepth)
{
    std::vector<std::pair<move, board>> moves;
    b.listNextMoves(curPlayer, moves);

    move choosenMove;

    if (curPlayer == Field::Red)
    {
        int max = std::numeric_limits<int>::min();
        
        for (auto& moveBoard : moves)
        {
            int curMin = minVal(moveBoard.second, maxDepth, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            if (curMin > max)
            {
                choosenMove = moveBoard.first;
                max = curMin;
            }
        }
    }
    else
    {
        int min = std::numeric_limits<int>::max();
        
        for (auto& moveBoard : moves)
        {
            int curMax = maxVal(moveBoard.second, maxDepth, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            if (curMax < min)
            {
                choosenMove = moveBoard.first;
                min = curMax;
            }
        }
    }

    return choosenMove;
}

// Red is max
int maxVal(const board& b, int depthLeft, int alpha, int beta)
{
    if (depthLeft == 0 || b.isFinished())
        return b.score();

    std::vector<std::pair<move, board>> moves;
    int max = std::numeric_limits<int>::min();

    b.listNextMoves(Field::Red, moves);
    for (auto& moveBoard : moves)
    {
        int curMin = minVal(moveBoard.second, depthLeft-1, max, beta);
        if (curMin > max)
        {
            max = curMin;
            if (max >= beta) return beta;
        }
    }

    if (moves.size() == 0 || max == std::numeric_limits<int>::min())
    {
        int a = 0;
    }

    return max;
}

// Yellow is min
int minVal(const board& b, int depthLeft, int alpha, int beta)
{
    if (depthLeft == 0 || b.isFinished())
        return b.score();

    std::vector<std::pair<move, board>> moves;
    int min = std::numeric_limits<int>::max();

    b.listNextMoves(Field::Yellow, moves);
    for (auto& moveBoard : moves)
    {
        int curMax = maxVal(moveBoard.second, depthLeft-1, alpha, min);
        if (curMax < min)
        {
            min = curMax;
            if (min <= alpha) return alpha;
        }
    }

    if (moves.size() == 0 || min == std::numeric_limits<int>::max())
    {
        int a = 0;
    }

    return min;
}