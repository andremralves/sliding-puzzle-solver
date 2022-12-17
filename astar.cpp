#include <iostream>
#include <queue>
#include <vector>
#include "solver.hpp"
#include <queue>

struct Node {
    std::string state;
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
    AStar(int rows, int cols);
    void buildHistory(Node *path);
    void solve(std::string iniState);
    int heuristic(std::string state);
    Node search(Node *root);
    std::pair<int, int> findPosInMatrix(std::vector<std::vector<char>> matrix, char c);
    ~AStar();
    
private:
    std::priority_queue<Node, std::vector<Node>, Node> pqueue;
};

AStar::AStar() {}
AStar::AStar(int rows, int cols) : Solver(rows, cols) {}

AStar::~AStar() {}


void AStar::solve(std::string iniState) {
    Node *root = new Node;
    root->state = iniState;
    Node path = search(root); 
    printHistory();
}

std::pair<int, int> AStar::findPosInMatrix(std::vector<std::vector<char>> matrix, char c) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if(matrix[i][j] == c) return {i, j};
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
    //std::cout<<pqueue.top().h<<"\n";
    while (!pqueue.empty())
    {
        Node *current = new Node;
        current->parent = pqueue.top().parent;
        current->state = pqueue.top().state;
        current->g = pqueue.top().g;
        current->h = pqueue.top().h;
        if(current->state == ans) break;
        std::vector<std::string> nextMvs = getPossibleMovments(current->state);

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
int AStar::heuristic(std::string state) {
    std::vector<std::vector<char>> curMatrix = getMatrixFromString(state);
    //std::vector<std::vector<char>> target = getMatrixFromString("123456780");
    std::vector<std::vector<char>> target = getMatrixFromString(this->ans);
    int value = 0;
    std::pair<int, int> correctPos;
    std::pair<int, int> currentPos;
    for (int i = 0; i < curMatrix.size(); i++) {
        for (int j = 0; j < curMatrix[0].size(); j++) {
            if(curMatrix[i][j] == '0') continue;
            correctPos = findPosInMatrix(target, curMatrix[i][j]);
            currentPos = findPosInMatrix(curMatrix, curMatrix[i][j]);

            value += abs(correctPos.first - currentPos.first) + abs(correctPos.second - currentPos.second);
        }
    }
    return value;
}

int main (int argc, char *argv[])
{
    auto start = std::chrono::high_resolution_clock::now();
    AStar solv; 
    //std::cout<<solv.heuristic("125306748")<<"\n";
    //solv.solve("012534678");
    solv.solve("386205741");
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout<<"Execution time: "<<duration.count()<<" seconds"<<"\n";
    return 0;
}
