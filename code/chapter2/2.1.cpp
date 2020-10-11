#include<iostream>
#include<thread>
#include<unistd.h>
#include<cstdio>
using namespace std;

class oop{
    public:
    int& i;
    oop(int& i_):i(i_){}
    void operator()(){
        for(int index=0;index<10;index++){
            i+=1;
            cout<< i << endl;
            char fname[256];
            sprintf(fname, "%d.txt", i);
            FILE* fp = fopen(fname, "a");
            fclose(fp);
            sleep(1);
        }
    }
};

class thread_guard{
public:
    thread& t;
    thread_guard(thread& t_):t(t_){}
    ~thread_guard(){
        if(t.joinable()){
            FILE* fp = fopen("xigou.txt", "a");
            fclose(fp);
            t.join();
        }
    }
    thread_guard(thread_guard const& )=delete;
    thread_guard& operator=(thread_guard const& )=delete;

};

void do_someing(){
    int error = 0;
    try{
        throw error;
    }catch(int err){
        cout<<"error"<<endl;
    }
}

void run(){
    int local_state = 0;
    oop f(local_state);
    thread t(f);
    thread_guard manager(t);
    sleep(3);
    do_someing();
    // throw "error";
}

int main(){
    run();
    return 0;
}