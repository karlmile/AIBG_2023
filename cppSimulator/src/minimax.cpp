#include "minimax.h"
#include <limits>
#include <memory>
#include <iostream>

Move broadMinimax(const Board& b, PlayerID curPlayer, PlayerID curBoard, int maxDepth, size_t maxMemory, bool pocetak)
{
    /*
    ply 0 - max
    ply 1 - min
    */
    float dynScoreMultiplier = (curPlayer == PlayerID::A)? 1.0f : -1.0f;
    PlayerID dynCurPlayer = curPlayer;
    std::unique_ptr<Board[]> boardLayers[maxDepth];
    std::unique_ptr<Move[]> moveLayers[maxDepth];
    std::unique_ptr<float[]> scoreLayers[maxDepth];
    std::unique_ptr<std::pair<size_t, size_t>[]> childRangeLayers[maxDepth];
    size_t layerSizes[maxDepth];
    
    // starting move
    boardLayers[0] = std::make_unique<Board[]>(1);
    moveLayers[0] = std::make_unique<Move[]>(1);
    scoreLayers[0] = std::make_unique<float[]>(1);
    childRangeLayers[0] = std::make_unique<std::pair<size_t, size_t>[]>(1);
    layerSizes[0] = 1;
    boardLayers[0][0] = b;

    // generate moves
    for (int nextD = 1; nextD < maxDepth; nextD++) {
        //std::cerr << "nextD" << nextD << " ";
        int curD = nextD-1;
        // switch 
        dynCurPlayer = (dynCurPlayer == A)? B : A;
        dynScoreMultiplier = -dynScoreMultiplier;

        // alloc
        layerSizes[nextD] = layerSizes[curD]*MAX_POTEZA;
        boardLayers[nextD] = std::make_unique<Board[]>(layerSizes[nextD]);
        moveLayers[nextD] = std::make_unique<Move[]>(layerSizes[nextD]);
        scoreLayers[nextD] = std::make_unique<float[]>(layerSizes[nextD]);
        childRangeLayers[nextD] = std::make_unique<std::pair<size_t, size_t>[]>(layerSizes[nextD]);

        // list moves
        size_t curLayerPos = 0;
        for (int i=0; i<layerSizes[curD]; i++) {
            childRangeLayers[curD][i].first = curLayerPos;
            curLayerPos += boardLayers[curD][i].listNextMoves(
                dynCurPlayer,
                curBoard,
                boardLayers[nextD].get()+curLayerPos,
                moveLayers[nextD].get()+curLayerPos,
                layerSizes[nextD] - curLayerPos,
                pocetak
            );
            childRangeLayers[curD][i].second = curLayerPos;
        }
        layerSizes[nextD] = curLayerPos;
    }
    //std::cerr << "NEXT" << std::endl;

    // evaluate deepest layer scores
    for (int j=0; j<layerSizes[maxDepth-1]; j++) {
        scoreLayers[maxDepth-1][j] = boardLayers[maxDepth-1][j].score(A, A);
    }

    // collect scores 
    for (int nextD = maxDepth-1; nextD >= 1; nextD--) {
        //std::cerr << "nextD" << nextD << " ";
        int curD = nextD-1;

        // find scores
        for (int i=0; i<layerSizes[curD]; i++) {
            moveLayers[curD][i] = moveLayers[nextD][childRangeLayers[curD][i].first];
            scoreLayers[curD][i] = scoreLayers[nextD][childRangeLayers[curD][i].first];
            for (int j=childRangeLayers[curD][i].first+1; j<childRangeLayers[curD][i].second; j++) {
                float s = scoreLayers[nextD][j];
                if (s*dynScoreMultiplier > scoreLayers[curD][i]*dynScoreMultiplier) {
                    scoreLayers[curD][i] = s;
                    moveLayers[curD][i] = moveLayers[nextD][j];
                }
            }
        }
        

        // switch 
        dynCurPlayer = (dynCurPlayer == A)? B : A;
        dynScoreMultiplier = -dynScoreMultiplier;
    }
    //std::cerr << "NEXT" << std::endl;

    return moveLayers[0][0];
}