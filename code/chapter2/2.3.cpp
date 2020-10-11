#include<iostream>
#include<thread>
#include<unistd.h>

class oop{
    int& i;
public:
    oop(int& i_):i(i_){}
    void operator()(){
        for(int index=0;index<10;index++){
            i+=1;
            std::cout << i << std::endl;
        }
    }
};

class thread_guard{
    public:
    std::thread t;
    explicit thread_guard(std::thread t_):t(std::move(t_)){
        if(!t.joinable()){
            throw "Not joinable";
        }
    }
    ~thread_guard(){
        t.join();
    }
    thread_guard(thread_guard const&)=delete;
    thread_guard& operator=(thread_guard const&)=delete;
};

void do_some_error_fun(){
    int error = 0;
    try{
        throw error;
    }catch(int err){
        std::cout << "err" << std::endl;
    }
}

void thread_fun(std::thread t){
    t.join();
}

void run(){
    int local_state = 0;
    oop f(local_state);
    thread_guard manager( (std::thread(oop(local_state))) );
    // thread_guard manager(std::thread(oop(local_state))); //error 少括号

    // std::thread t(f);
    // thread_guard manager(std::move(t));
    // sleep(5);
    do_some_error_fun();
}
int main(){
    run();
    return 0;
}