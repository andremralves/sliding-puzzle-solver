#include <iostream>
#include <string>
#include <vector>
#include <chrono>

class Solver
{
protected:
    bool found = false;
    int rows = 3;
    int cols = 3;
    std::string ans = "012345678";
    std::vector<std::string> history;
public:
    Solver() {}
    Solver(int r, int c) {
        rows = r; 
        cols = c;
    }

    virtual void solve(std::string iniState) = 0;

    void printHistory() {
        int step = 1;
        for(int i = history.size()-1; i>= 0; i--) {
          if(i == (int)history.size()-1) 
              std::cout<<"Initial State:"<<std::endl;
          else {
              std::cout<<"Step: "<<step<<std::endl;
              step++;
          }
          std::vector<std::string> rows = splitStringIntoRows(history[i]);
          for(std::string row : rows) {
              std::cout<<row<<"\n";
          }
          std::cout<<"\n";
        }
        std::cout<<"Total steps: "<<getHistorySize()-1<<std::endl;
    }

    std::string appendRowsIntoString(std::vector<std::string> rows) {
        std::string rowsString;
        rowsString.append(rows[0]);
        rowsString.append(rows[1]);
        rowsString.append(rows[2]);
        return rowsString;
    }

    std::vector<std::string> splitStringIntoRows(std::string state) {
        std::vector<std::string> rows;
        rows.push_back(state.substr(0, 3));
        rows.push_back(state.substr(3, 3));
        rows.push_back(state.substr(6, 3));
        return rows;
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

    std::vector<std::string> getPossibleMovments(std::string currentState) {
        //std::cout<<"ok mov"<<"\n";
        std::vector<std::string> possibleMovments;
        std::vector<std::vector<char>> matrix = getMatrixFromString(currentState);
        //std::cout<<"ok mov 2"<<"\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if(matrix[i][j] == '0') {
                    if(i+1 < 3) {
                        std::vector<std::vector<char>> newMatrix = matrix;
                        int buff = newMatrix[i][j];
                        newMatrix[i][j] = newMatrix[i+1][j];
                        newMatrix[i+1][j] = buff;
                        std::string rowsString = getStringFromMatrix(newMatrix);
                        possibleMovments.push_back(rowsString);
                    }
                    if(i-1 >= 0) {
                        std::vector<std::vector<char>> newMatrix = matrix;
                        int buff = newMatrix[i][j];
                        newMatrix[i][j] = newMatrix[i-1][j];
                        newMatrix[i-1][j] = buff;
                        std::string strMatrix = getStringFromMatrix(newMatrix);
                        possibleMovments.push_back(strMatrix);
                    }
                    if(j+1 < 3) {
                        std::vector<std::vector<char>> newMatrix = matrix;
                        int buff = newMatrix[i][j];
                        newMatrix[i][j] = newMatrix[i][j+1];
                        newMatrix[i][j+1] = buff;
                        std::string strMatrix = getStringFromMatrix(newMatrix);
                        possibleMovments.push_back(strMatrix);
                    }
                    if(j-1 >= 0) {
                        std::vector<std::vector<char>> newMatrix = matrix;
                        int buff = newMatrix[i][j];
                        newMatrix[i][j] = newMatrix[i][j-1];
                        newMatrix[i][j-1] = buff;
                        std::string strMatrix = getStringFromMatrix(newMatrix);
                        possibleMovments.push_back(strMatrix);
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
