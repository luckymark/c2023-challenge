//
// Created by cz241 on 11/2/2023.
//
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <fstream>
#include <thread>
#include <chrono>
#define PRECISE 50000

using namespace boost::multiprecision;
using namespace std;
using namespace chrono;

using FLOAT =number<cpp_bin_float<PRECISE>>;
void GregoryLeibniz_Pi(int from,int to,FLOAT& result);
void Nilakantha_Pi(int from,int to,FLOAT& result);
//并发多线程计算Pi offset:初始值 count:每个线程计算的次数 n:线程数
void Parallel_Calculator(int offset,int count,int n,void calculator(int,int,FLOAT&),string filename);