#include <iostream>
#include <queue>
#include <vector>
#include "solver.hpp"
#include <queue>

typedef struct {
    std::string state;
    int h;
    int g;
} Node;

class compare
{
public:
    bool operator()(Node &a, Node &b) {
        return (a.h+a.g)>(b.g+b.h);
    }
};

class AStar : public Solver
{
public:
    AStar();
    //AStar(AStar &&) = default;
    //AStar(const AStar &) = default;
    //AStar &operator=(AStar &&) = default;
    //AStar &operator=(const AStar &) = default;
    void solve(std::string iniState);
    int heuristic(std::string state);
    void search(Node root);
    std::pair<int, int> findPosInMatrix(std::vector<std::vector<char>> matrix, char c);
    //~AStar();
    
private:
    std::priority_queue<Node, std::vector<Node>, compare> pqueue;
};

AStar::AStar()
{
}

void AStar::solve(std::string iniState) {
    Node root;
    root.state = iniState;
    search(root); 
}

std::pair<int, int> AStar::findPosInMatrix(std::vector<std::vector<char>> matrix, char c) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if(matrix[i][j] == c) return {i, j};
        }
    } return {-1, -1};
}

void AStar::search(Node root) {
    root.h = heuristic(root.state);
    root.g = 1;
    pqueue.push(root);
    std::cout<<pqueue.top().h<<"\n";
    //std::vector<std::string> nextMvs = getPossibleMovments(pqueue.top().state);
    //for(auto mv: nextMvs) {
    //    Node curr;
    //    curr.state = mv;
    //    std::cout<<heuristic(curr)<<"\n";
    //    std::cout<<mv<<"\n";
    //}
    //return;
    while (!pqueue.empty())
    {
        //std::cout<<pqueue.top().h<<"\n";
        std::cout<<pqueue.top().state<<"\n";
        Node parent = pqueue.top();
        if(pqueue.top().state == ans) break;
        std::vector<std::string> nextMvs = getPossibleMovments(pqueue.top().state);
        pqueue.pop();
        //std::cout<<"Next moves: "<<"\n";
        for(auto move : nextMvs) {
            Node current; 
            current.state = move;
            current.h = heuristic(move);
            current.g = parent.g+1;
            //std::cout<<current.state<<"\n";
            //std::cout<<current.h<<"\n";
            pqueue.push(current);
        }
        //std::cout<<"--------------------"<<"\n";
    }
}

// Using manhattan distance for each item in matrix
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

void testHeuristic() {
    //Node n1, n2, n3;
    //n1.state = "012345678";
    //n2.state = "012435678";
    //n3.state = "012354687";
    //std::cout<<solv.heuristic(n1)<<"\n";
    //std::cout<<solv.heuristic(n2)<<"\n";
    //std::cout<<solv.heuristic(n3)<<"\n";
}

int main (int argc, char *argv[])
{
    auto start = std::chrono::high_resolution_clock::now();
    AStar solv; 
    //std::cout<<solv.heuristic("125306748")<<"\n";
    solv.solve("012534678");
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout<<"Execution time: "<<duration.count()<<" seconds"<<"\n";
    return 0;
}
