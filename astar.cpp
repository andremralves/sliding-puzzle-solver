#include <iostream>
#include <queue>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <unordered_map>

#include "astar.h"

AStar::AStar() {}
AStar::AStar(int rows, int cols, stateMat goal) : Solver(rows, cols, goal) {}
AStar::~AStar() {}

void AStar::solve(stateMat iniState) {
    Node *root = new Node {
        .state = iniState, 
        .h = heuristic(iniState),
        .g = 0
    };
    search(root); 
    printHistory();
}

std::pair<int, int> AStar::findPosInMatrix(std::vector<std::vector<int>> matrix, int x) {
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
            if(matrix[i][j] == x) return {i, j};
        }
    } return {-1, -1};
}

void AStar::buildHistory(std::unordered_map<Node*, Node*> cameFrom, Node* n) {

    while(cameFrom.find(n) != cameFrom.end()) {
        history.push_back(n->state);
        n = cameFrom[n];
    }
    std::reverse(history.begin(), history.end());
}


void AStar::search(Node *start) {
    // start pqueue with the first node
    pqueue.push(start);
    // Will be used to reconstruct path
    std::unordered_map<Node*, Node*> cameFrom;
        
    while (!pqueue.empty())
    {
        // Takes the best node
        Node *current = pqueue.top();
        // Check if node is the goal
        if(isGoal(current->state, ans)) {
            buildHistory(cameFrom, current);
            return;
        };

        //std::cout<<pqueue.size()<<"\n";

        // pop current node
        pqueue.pop();

        // Get next nodes
        std::vector<stateMat> nextMvs = getPossibleMovments(current->state);
        for(auto move : nextMvs) {
            Node *child = new Node{
                .state = move,
                .h = heuristic(move),
                .g = current->g + 1
            };
            cameFrom.insert({child, current});
            pqueue.push(child);
        }
    }
}

// Calculate manhattan distance for each item in matrix
int AStar::heuristic(stateMat state) {
    int value = 0;
    std::pair<int, int> correctPos;
    for (size_t i = 0; i < state.size(); i++) {
        for (size_t j = 0; j < state[0].size(); j++) {
            if(state[i][j] == 0) continue;
            correctPos = {state[i][j]/state.size(), state[i][j]%state[0].size()};
            value += abs(correctPos.first - (int)i) + 
                abs(correctPos.second - (int)j);
        }
    }
    return value;
}

