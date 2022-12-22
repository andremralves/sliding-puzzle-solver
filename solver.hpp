#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <array>

using stateMat = std::vector<std::vector<int>>;

class Solver
{
protected:
    bool found = false;
    int rows = 3;
    int cols = 3;
    stateMat ans;
    std::vector<stateMat> history;
public:
    Solver() {}
    Solver(int r, int c, stateMat ans) {
        this->rows = r; 
        this->cols = c;
        this->ans = ans;
    }

    virtual void solve(stateMat iniState) = 0;

    void printHistory() {
        int step = 0;
        for(auto state: history) {
            if(step == 0) std::cout<<"Initial State:"<<std::endl;
            else std::cout<<"Step: "<<step<<std::endl;
            step++;
            printMatrix(state);
        }
        std::cout<<"Total steps: "<<getHistorySize()-1<<std::endl;
    }

    void printMatrix(stateMat state) {
          for (size_t i = 0; i < state.size(); i++) {
              for (size_t j = 0; j < state[i].size(); j++) {
                    std::cout<<state[i][j]<<" ";
              }
              std::cout<<"\n";
          }
    }

    bool isGoal(stateMat state, stateMat goal) {
        for (size_t i = 0; i < state.size(); i++) {
            for (size_t j = 0; j < state[0].size(); j++) {
                if(state[i][j] != goal[i][j]) return false;
            }
        }
        return true;
    }

    std::vector<std::vector<char>> getMatrixFromString(std::string state) {
        std::vector<std::vector<char>> matrix(rows, std::vector<char>(cols));
        state[0];
        int si = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix[i][j] = state[si++];
            }
        }
        return matrix;
    }

    std::string getStringFromMatrix(std::vector<std::vector<char>> matrix) {
        std::string strMatrix = "";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                strMatrix += matrix[i][j];
            }
        }
        return strMatrix;
    }

    std::vector<stateMat> getPossibleMovments(stateMat currentState) {
        //std::cout<<"ok mov"<<"\n";
        std::vector<stateMat> possibleMovments;
        //std::vector<std::vector<char>> matrix = getMatrixFromString(currentState);
        //std::cout<<"ok mov 2"<<"\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if(currentState[i][j] == 0) {
                    if(i+1 < rows) {
                        stateMat newState = currentState;
                        int buff = newState[i][j];
                        newState[i][j] = newState[i+1][j];
                        newState[i+1][j] = buff;
                        possibleMovments.push_back(newState);
                    }
                    if(i-1 >= 0) {
                        stateMat newState = currentState;
                        int buff = newState[i][j];
                        newState[i][j] = newState[i-1][j];
                        newState[i-1][j] = buff;
                        possibleMovments.push_back(newState);
                    }
                    if(j+1 < rows) {
                        stateMat newState = currentState;
                        int buff = newState[i][j];
                        newState[i][j] = newState[i][j+1];
                        newState[i][j+1] = buff;
                        possibleMovments.push_back(newState);
                    }
                    if(j-1 >= 0) {
                        stateMat newState = currentState;
                        int buff = newState[i][j];
                        newState[i][j] = newState[i][j-1];
                        newState[i][j-1] = buff;
                        possibleMovments.push_back(newState);
                    }
                }
            }
        } 
        return possibleMovments; 
    }

    int getFound() {
        return found;
    }

    int getHistorySize() {
        return history.size();
    }

};
