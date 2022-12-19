#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <queue>
#include <vector>
#include "solver.hpp"
#include <queue>

struct Node {
    stateMat state;
    Node *parent;
    int h;
    int g;
    bool operator()(Node &a, Node &b) {
        return (a.h+a.g)>(b.g+b.h);
    }
};

class AStar : public Solver
{
public:
    AStar();
    AStar(int rows, int cols, stateMat goal);
    void buildHistory(Node *path);
    void solve(stateMat iniState);
    int heuristic(stateMat state);
    Node search(Node *root);
    std::pair<int, int> findPosInMatrix(std::vector<std::vector<int>> matrix, int x);
    ~AStar();
    
private:
    std::priority_queue<Node, std::vector<Node>, Node> pqueue;
};

#endif
