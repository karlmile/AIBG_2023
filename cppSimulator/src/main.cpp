#include "board.h"
#include "minimax.h"
#include <iostream>
#include <list>
#include <string>
#include <chrono>

using namespace std;

int main()
{
    list<board> brds;
    Field curPlayer = Field::Red;
    int maxDepth = 3;
    bool showBoard = true;

    cout << "Size of structure: " << sizeof(board) << "B" << endl;

    // starting state
    brds.emplace_back();
    cout << brds.back();

    // loop
    bool running = true;
    while (running)
    {
        cout << (curPlayer == Field::Red? "Red" : "Yellow") << "'s turn" << endl;
        cout << "??? add x; set y/r; depth d; minimax; undo; show; hide; end;" << endl;
        string comm;
        cin >> comm;

        if (comm == "add" || comm == "a")
        {
            int ind;
            cin >> ind;

            // new state
            brds.emplace_back(brds.back());
            brds.back().add(ind, curPlayer);// add coin
            if (showBoard)
            {
                cout << "------------------" << endl;// show state
                cout << brds.back() << "score: " << brds.back().score() << endl << endl;// show state
            }
            curPlayer = (curPlayer == Field::Red)? Field::Yellow : Field::Red;// switch turn
        }
        else if (comm == "autoplay")
        {
            auto it = brds.end();
            it--;

            auto start = std::chrono::high_resolution_clock::now();
            while (!brds.back().isFinished())
            {
                int ind = minimax(brds.back(), curPlayer, maxDepth);

                brds.emplace_back(brds.back());
                brds.back().add(ind, curPlayer);// add coin
                curPlayer = (curPlayer == Field::Red)? Field::Yellow : Field::Red;// switch turn
            }
            auto end = std::chrono::high_resolution_clock::now();
            cout << "Calculated in " << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "ms" << endl;// show state
            
            it++;
            while (it != brds.end())
            {
                cout << "------------------" << endl;// show state
                cout << *it << endl;// show state
                it++;
            }
        }
        else if (comm == "set")
        {
            char c;
            cin >> c;
            if (c == 'y')
                curPlayer = Field::Yellow;
            if (c == 'r')
                curPlayer = Field::Red;
        }
        else if (comm == "hide")
        {
            showBoard = false;
        }
        else if (comm == "show")
        {
            cout << brds.back() << "score: " << brds.back().score() << endl << endl;// show state
            showBoard = true;
        }
        else if (comm == "minimax" || comm == "m")
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
            cin >> maxDepth;
        }
        else if (comm == "undo" || comm == "u")
        {
            brds.pop_back();
            cout << brds.back() << "score: " << brds.back().score() << endl << endl;// show state
            curPlayer = (curPlayer == Field::Red)? Field::Yellow : Field::Red;// switch turn
        }
        else if (comm == "end")
        {
            running = false;
        }
    }

    return 0;
}