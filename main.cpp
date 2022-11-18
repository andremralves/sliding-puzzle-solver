#include <iostream>
#include <string>
#include <vector>
#include <chrono>

class Solver
{
private:
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

    void printHistory() {
        int step = 0;
        for(int i=history.size()-1; i>= 0; i--) {
            if(i == history.size()-1) 
                std::cout<<"Initial State:"<<std::endl;
            else
                std::cout<<"Step: "<<step<<std::endl; step++;
            std::vector<std::string> rows = splitStringIntoRows(history[i]);
            for(std::string row : rows) {
                std::cout<<row<<"\n";
            }
            std::cout<<"\n";
        }
        std::cout<<"Total steps: "<<getHistorySize()-1<<std::endl;
    }

    void solve(std::string iniState) {
        k_limited(iniState); 
        printHistory();
    }

    void k_limited(std::string iniState) {
        for (int k = 0; k < 25; k++) {
            if(getFound() == true) break;
            int initialState[3][3] = {
                {0, 1, 2},
                {3, 4, 5},
                {6, 7, 8},
            };
            dfs(iniState, 0, k);
        }
    }

    void dfs(std::string state, int cnt, int k) {
        //std::cout<<"ok dfs"<<"\n";
        if(found == true) return;
        if(cnt >= k) {
            //printHistory();
            history.clear();
            //std::cout<<"K: "<<cnt<<std::endl;
            return;
        }
        cnt++; 
        //std::cout<<state<<std::endl;
        if(state == ans) {
            found = true;
            history.clear();
            history.push_back(state);
            //std::cout<<cnt<<std::endl;
            return;
        }
        std::vector<std::string> movments = getPossibleMovments(state);
        for(std::string m: movments) {
            dfs(m,cnt, k);
        }
        history.push_back(state);
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

int main (int argc, char *argv[])
{
    auto start = std::chrono::high_resolution_clock::now();
    //int n, m;
    //std::cin>>n>>m;
    //std::string s = "";
    //for (int i = 0; i < n*m; i++) {
    //    char c;
    //    std::cin>>c; 
    //    s += c;
    //}
    Solver solv; 
    solv.solve("012534678");
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout<<"Execution time: "<<duration.count()<<" seconds"<<"\n";
    return 0;
}
