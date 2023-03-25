#include "board.h"
#include "minimax.h"
#include <iostream>
#include <list>
#include <string>
#include <chrono>
#include <sstream>

int main()
{
    bool enableDebug = false;
    Board currentState;
    PlayerID curPlayer = PlayerID::A;
    PlayerID curBoard = PlayerID::A;
    int maxDepth = 3;
    size_t maxMemory = 1000000;

    if (enableDebug) {
        std::cout << "Size of structure: " << sizeof(Board) << "B" << std::endl;
    }

    // loop
    bool running = true;
    while (running)
    {
        if (enableDebug || true) {
            std::cerr << "??? set (board state); depth (d); minimax; end;" << std::endl;
        }
        std::string line;
        std::getline(std::cin, line);
        std::stringstream lineSS;
        lineSS << line;
        std::string comm;
        lineSS >> comm;

        std::cerr << "Recved line '" << line << "', command '" << comm << std::endl;

        if (comm == "set")
        {
            int num;

            // potez
            std::cerr << "Setting moves" << std::endl;
            lineSS >> num;
            curPlayer = (PlayerID)num;
            lineSS >> num;
            curBoard = (PlayerID)num;

            // figureposs
            for (int i=0; i<96; i++) {
                currentState.ALL[i].x = -1;
                currentState.ALL[i].y = -1;
            }

            // board
            std::cerr << "Setting board" << std::endl;
            for (int b: {0,1}) {
                for (int y=0; y<12; y++) {
                    for (int x=0; x<12; x++) {
                        int ind;
                        lineSS >> ind;
                        currentState.boards[b][y][x] = ind;
                        if (ind != -1) {
                            currentState.ALL[ind].x = x;
                            currentState.ALL[ind].y = y;
                        }
                    }
                }
            }

            // figures
            std::cerr << "Setting figures" << std::endl;
            for (int i=0; i<96; i++) {
                char type, plocaC, vlasnikC;
                lineSS >> type;
                lineSS >> plocaC;
                lineSS >> vlasnikC;
                if (type != '-') {
                    currentState.ALL[i].F = CharFiguricaMap.at(type);
                    currentState.ALL[i].player = (PlayerID)(vlasnikC - '0');
                    currentState.ALL[i].board = (PlayerID)(plocaC - '0');
                }
            }

            std::cerr << "Set board" << std::endl;
        }
        else if (comm == "minimax")
        {
            auto start = std::chrono::high_resolution_clock::now();
            Move mov = broadMinimax(currentState, curPlayer, curBoard, maxDepth, maxMemory);
            auto end = std::chrono::high_resolution_clock::now();

            if (currentState.ALL[mov.index].x == -1) {
                std::cout << "P-" << FiguricaCharMap.at(currentState.ALL[mov.index].F) <<"-" << mov.y << "-" << mov.x << std::endl;
            } 
            else {
                std::cout << "M-" << currentState.ALL[mov.index].y << "-" << currentState.ALL[mov.index].x <<"-" << mov.y << "-" << mov.x << std::endl;
            } 

            std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "ms" << std::endl;// show state
        }
        else if (comm == "depth")
        {
            lineSS >> maxDepth;
        }
        else if (comm == "memory")
        {
            lineSS >> maxMemory;
        }
        else if (comm == "end")
        {
            running = false;
        }
    }

    return 0;
}