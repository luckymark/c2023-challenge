#include "Calculator.h"

//精度控制 see as PI/Calculator.h 定义的PRECISE宏

void Test(const int offset,const string& name,int count,int n,void calculator(int,int,FLOAT&)){
    cout<<"By using "<<name<<endl;
    auto start_time=system_clock::now();
    Parallel_Calculator(offset,count,n, calculator,name+".txt");
    auto end_time=system_clock::now();
    cout<<"Finished in "<<duration_cast<microseconds>(end_time-start_time).count()/1000.0<<"ms"<<endl;
}

int main(){
    //50*8=400次迭代 5w小数耗时~3.5s
    Test(3,"Nilakantha",50,8,Nilakantha_Pi);
    //烧CPU的垃圾方法
    //CPU 占用率68% 5w小数精度 耗时未知 本子烧坏了都算不出来..
    //Test(4,"Gregory Leibniz",1000,10,GregoryLeibniz_Pi);
    system("pause");
    return 0;
}