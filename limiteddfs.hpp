#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "solver.hpp"

class LimitedDfs: public Solver
{
public:
    LimitedDfs();
    LimitedDfs(int r, int c);
    void solve(std::string iniState);
    void k_limited(std::string iniState);
    void dfs(std::string state, int cnt, int k);
};
