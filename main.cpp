#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
//#include "limiteddfs.hpp"
#include "astar.h"

int n, m;
stateMat iniState;
stateMat goal;

// read row, col and matrix
void readInput() {
    std::cin>>n>>m;
    iniState.resize(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin>>iniState[i][j];
        }
    }
}

// sets the goal matrix
void setGoal() {
    int val = 0;
    goal.resize(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            goal[i][j] = val++;
        }
    }
}

int main (int argc, char *argv[])
{
    readInput();
    setGoal();
    auto start = std::chrono::high_resolution_clock::now();

    // ininialize astar class with board sizes
    AStar solv(n, m, goal);

    // solve
    solv.solve(iniState);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout<<"Execution time: "<<duration.count()<<" milliseconds"<<"\n";

    return 0;
}
