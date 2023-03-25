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
    int maxDepth = 3;

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
                std::string type;
                std::cin >> type;
                currentState.ALL[i].F = Kralj;/*TODO*/
            }
        }
        else if (comm == "minimax")
        {
            auto start = std::chrono::high_resolution_clock::now();
            int ind = minimax(brds.back(), curPlayer, maxDepth);
            auto end = std::chrono::high_resolution_clock::now();
            cout << "Calculated in " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "ms" << endl;// show state

            // new state
            brds.emplace_back(brds.back());
            brds.back().add(ind, curPlayer);// add coin
            if (showBoard)
            {
                cout << "------------------" << endl;// show state
                cout << brds.back() << "score: " << brds.back().score() << endl << endl;// show state
            }
            cout << "~Played " << ind << endl;// show state
            curPlayer = (curPlayer == Field::Red)? Field::Yellow : Field::Red;// switch turn
        }
        else if (comm == "depth")
        {
            std::cin >> maxDepth;
        }
        else if (comm == "end")
        {
            running = false;
        }
    }

    return 0;
}