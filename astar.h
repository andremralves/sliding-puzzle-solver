#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <queue>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>

#include "solver.hpp"

struct Node {
    stateMat state;
    int h;
    int g;
    bool operator()(const Node *a, const Node *b) const{
        return (a->h+a->g)>(b->g+b->h);
    }
};

class AStar : public Solver
{
public:
    AStar();
    AStar(int rows, int cols, stateMat goal);
    void buildHistory(std::unordered_map<Node*, Node*> cameFrom, Node *n);
    void solve(stateMat iniState);
    int heuristic(stateMat state);
    void search(Node *root);
    std::pair<int, int> findPosInMatrix(std::vector<std::vector<int>> matrix, int x);
    ~AStar();
    
private:
    std::priority_queue<Node*, std::vector<Node*>, Node> pqueue;
};

#endif
