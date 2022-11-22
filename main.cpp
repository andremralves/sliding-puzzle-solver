#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "solver.hpp"

class LimitedDfs: public Solver
{
public:
    LimitedDfs() {}
    LimitedDfs(int r, int c) {
        rows = r; 
        cols = c;
    }

    void solve(std::string iniState) {
        k_limited(iniState); 
        printHistory();
    }

    void k_limited(std::string iniState) {
        // Without threads
        //for (int k = 0; k < 25; k++) {
        //    if(getFound() == true) break;
        //    dfs(iniState, 0, k);
        //}

        // With threads
        std::thread threads[4];
        for (int k = 0; k < 25; k++) {
            if(getFound() == true) break;
            threads[k%4] = std::thread(&LimitedDfs::dfs, this, iniState, 0, k);
            if(k%4 == 3) {
                threads[0].join();
                threads[1].join();
                threads[2].join();
                threads[3].join();
            }
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
    LimitedDfs solv; 
    solv.solve("012534678");
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout<<"Execution time: "<<duration.count()<<" seconds"<<"\n";
    return 0;
}
