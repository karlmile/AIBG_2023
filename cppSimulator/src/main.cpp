#include "board.h"
#include "minimax.h"
#include <iostream>
#include <list>
#include <string>
#include <chrono>

int main()
{
    Board currentState;
    PlayerID curPlayer = PlayerID::A;
    PlayerID curBoard = PlayerID::A;
    int maxDepth = 3;
    size_t maxMemory = 1000000;

    std::cout << "Size of structure: " << sizeof(Board) << "B" << std::endl;

    // loop
    bool running = true;
    while (running)
    {
        std::cout << "??? set (board state); depth (d); minimax; end;" << std::endl;
        std::string comm;
        std::cin >> comm;

        if (comm == "set")
        {
            int num;

            // potez
            std::cin >> num;
            curPlayer = (PlayerID)num;
            std::cin >> num;
            curBoard = (PlayerID)num;

            // board
            for (int b: {0,1}) {
                for (int y=0; y<12; y++) {
                    for (int x=0; x<12; x++) {
                        std::cin >> currentState.boards[b][y][x];
                        if (currentState.boards[b][y][x] != -1) {
                            currentState.ALL[currentState.boards[b][x][y]].x = x;
                            currentState.ALL[currentState.boards[b][x][y]].y = y;
                        }
                    }
                }
            }

            // figures
            for (int i=0; i<96; i++) {
                char type;
                std::cin >> type;
                if (type != '-') {
                    currentState.ALL[i].F = CharFiguricaMap.at(type);
                }
            }
        }
        else if (comm == "minimax")
        {
            auto start = std::chrono::high_resolution_clock::now();
            Move mov = broadMinimax(currentState, curPlayer, curBoard, maxDepth, maxMemory);
            auto end = std::chrono::high_resolution_clock::now();

            if (currentState.ALL[mov.index].x == -1) {
                std::cout << "P-" << FiguricaCharMap[currentState.ALL[mov.index].F] <<"-" << mov.y << "-" << mov.x << std::endl;
            } 
            else {
                std::cout << "M-" << currentState.ALL[mov.index].y << "-" << currentState.ALL[mov.index].x <<"-" << mov.y << "-" << mov.x << std::endl;
            } 

            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "ms" << std::endl;// show state
        }
        else if (comm == "depth")
        {
            std::cin >> maxDepth;
        }
        else if (comm == "memory")
        {
            std::cin >> maxMemory;
        }
        else if (comm == "end")
        {
            running = false;
        }
    }

    return 0;
}