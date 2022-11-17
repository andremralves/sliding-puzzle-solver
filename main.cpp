#include <iostream>
#include <string>
#include <vector>

class Solver
{
private:
    bool found = false;
    std::string ans = "012345678";
    std::vector<std::string> history;
public:
    void printHistory() {
        int step = 0;
        for(int i=history.size()-1; i>= 0; i--) {
            if(i == history.size()-1) 
                std::cout<<"Estado inicial:"<<std::endl;
            else
                std::cout<<"Passo: "<<step<<std::endl; step++;
            std::vector<std::string> rows = splitStringIntoRows(history[i]);
            for(std::string row : rows) {
                std::cout<<row<<"\n";
            }
            std::cout<<"\n";
        }
    }
    void dfs(std::string state, int cnt, int k) {
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

    std::vector<std::string> getPossibleMovments(std::string currentState) {
        std::vector<std::string> possibleMovments;
        std::vector<std::string> rows = splitStringIntoRows(currentState);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < rows[0].length(); j++) {
                if(rows[i][j] == '0') {
                    if(i+1 < 3) {
                        std::vector<std::string> newRows = rows;
                        int buff = newRows[i][j];
                        newRows[i][j] = newRows[i+1][j];
                        newRows[i+1][j] = buff;
                        std::string rowsString = appendRowsIntoString(newRows);
                        possibleMovments.push_back(rowsString);
                    }
                    if(i-1 >= 0) {
                        std::vector<std::string> newRows = rows;
                        int buff = newRows[i][j];
                        newRows[i][j] = newRows[i-1][j];
                        newRows[i-1][j] = buff;
                        std::string rowsString = appendRowsIntoString(newRows);
                        possibleMovments.push_back(rowsString);
                    }
                    if(j+1 < 3) {
                        std::vector<std::string> newRows = rows;
                        int buff = newRows[i][j];
                        newRows[i][j] = newRows[i][j+1];
                        newRows[i][j+1] = buff;
                        std::string rowsString = appendRowsIntoString(newRows);
                        possibleMovments.push_back(rowsString);
                    }
                    if(j-1 >= 0) {
                        std::vector<std::string> newRows = rows;
                        int buff = newRows[i][j];
                        newRows[i][j] = newRows[i][j-1];
                        newRows[i][j-1] = buff;
                        std::string rowsString = appendRowsIntoString(newRows);
                        possibleMovments.push_back(rowsString);
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
    //936
    //417
    //852
    Solver solv; 
    for (int k = 0; k < 25; k++) {
        if(solv.getFound() == true) break;
        //std::cout<<"k: "<<k<<std::endl;
        solv.dfs("012534678", 0, k);
    }
    std::cout<<"Total de passos: "<<solv.getHistorySize()-1<<std::endl;
    std::cout<<"Solução:"<<std::endl;
    solv.printHistory();
    return 0;
}
