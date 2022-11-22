#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "limiteddfs.hpp"

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
