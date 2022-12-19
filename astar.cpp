#include <iostream>
#include <queue>
#include <vector>
#include <queue>
#include "astar.h"


AStar::AStar() {}
AStar::AStar(int rows, int cols, stateMat goal) : Solver(rows, cols, goal) {}

AStar::~AStar() {}


void AStar::solve(stateMat iniState) {
    Node *root = new Node;
    root->state = iniState;
    //std::cout<<"ok"<<"\n";
    Node path = search(root); 
    printHistory();
}

std::pair<int, int> AStar::findPosInMatrix(std::vector<std::vector<int>> matrix, int x) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if(matrix[i][j] == x) return {i, j};
        }
    } return {-1, -1};
}

void AStar::buildHistory(Node *path) {
    while (path != nullptr)
    {
        history.push_back(path->state);
        path = path->parent;
    } 
}


Node AStar::search(Node *root) {
    root->h = heuristic(root->state);
    root->g = 1;
    root->parent = nullptr;
    pqueue.push(*root);
    //std::cout<<root->h+root->g<<"\n";
    while (!pqueue.empty())
    {
        Node *current = new Node;
        current->parent = pqueue.top().parent;
        current->state = pqueue.top().state;
        current->g = pqueue.top().g;
        current->h = pqueue.top().h;
        //std::cout<<"---------------\n";
        //std::cout<<current->g<<" ";
        //printMatrix(current->state);
        if(isGoal(current->state, ans)) break;
        std::vector<stateMat> nextMvs = getPossibleMovments(current->state);

        // pop current node
        pqueue.pop();

        //std::cout<<"Next moves: "<<"\n";
        for(auto move : nextMvs) {
            Node *child = new Node; 
            child->parent = current;
            child->state = move;
            child->h = heuristic(move);
            child->g = current->g+1;
            //std::cout<<child.parent<<"\n";
            //std::cout<<current.h<<"\n";
            pqueue.push(*child);
        }
        //std::cout<<"--------------------"<<"\n";
    }
    Node end = pqueue.top();
    buildHistory(&end);
    return pqueue.top();
}

// Calculate manhattan distance for each item in matrix
int AStar::heuristic(stateMat state) {
    int value = 0;
    std::pair<int, int> correctPos;
    std::pair<int, int> currentPos;
    for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < state[0].size(); j++) {
            if(state[i][j] == 0) continue;
            correctPos = findPosInMatrix(ans, state[i][j]);
            currentPos = findPosInMatrix(state, state[i][j]);

            value += abs(correctPos.first - currentPos.first) + abs(correctPos.second - currentPos.second);
        }
    }
    return value;
}

