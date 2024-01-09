//
// Created by cz241 on 11/2/2023.
//
#include "Calculator.h"

int sign(int power){
    return power%2==0?1:-1;
}
void WriteToFile(const FLOAT data,const string filename){
    fstream writer;
    writer.open(filename, ios::out);
    if(writer.is_open()){
        writer<<data.str();
        writer.close();
    }
}

//用韦达定理求圆周率：
void FrancoisViete(int from,int to,FLOAT& result){
    FLOAT pi=1;
    FLOAT a=1;
    for(int i=0;i<PRECISE;i++){
        a=sqrt(2+a);
        pi*=2/a;
    }
    WriteToFile(pi*2,"FrancoisViete.txt");
}

void GregoryLeibniz_Pi(int from,int to,FLOAT& result){
    FLOAT res;
    for(int i=from;i<to;i++){
        FLOAT temp=2*i+1;
        res+=sign(i)/temp;
    }
    cout<<"thread "<<this_thread::get_id()<<" finished range "<<from<<" to "<<to<<endl;
    result=res*4;
}
void Nilakantha_Pi(int from,int to,FLOAT& result) {
    FLOAT res;
    for(int i=from;i<=to;i++){
        FLOAT temp= (2*i)*(2*i+1)*(2*i+2);
        FLOAT a=4/temp;
        res+=sign(i-1)*a;
    }
    cout<<"thread "<<this_thread::get_id()<<" finished range "<<from<<" to "<<to<<endl;
    result=res;
}

void Parallel_Calculator(int offset,int count,int n,void calculator(int,int,FLOAT&),string filename){
    FLOAT pi=offset;
    auto *threads=new thread[n];
    auto *results=new FLOAT[n];
    for(int i=0;i<n;i++){
        threads[i]=thread(calculator,i*count+1,(i+1)*count,ref(results[i]));
    }
    for(int i=0;i<n;i++){
        threads[i].join();
        pi+=results[i];
    }
    WriteToFile(pi,filename);
    delete[] threads;
    delete[] results;
}
