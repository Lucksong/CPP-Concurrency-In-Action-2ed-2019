//线程传递
#include<iostream>
#include<thread>
using namespace std;

void fun1(){
    cout<<"fun1"<<endl;
}

void fun2(int a){
    cout<<"fun2: "<<a<<endl;
}

std::thread f1(){
    return std::thread(fun1);
}

std::thread f2(){
    // return std::thread(fun2, 5);
    std::thread t(fun2, 5);
    return t;
}

int main(){
    std::thread t1 = f1();
    t1.join();
    std::thread t2 = f2();
    t2.join();
    return 0;
}