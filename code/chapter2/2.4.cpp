#include<iostream>
#include<thread>
#include<vector>
void f(int i){
    std::cout<<i<<std::endl;
}
void multithread(){
    std::vector<std::thread> threads;
    for(int i=0;i<10;i++){
        threads.push_back(std::thread(f, i));
    }
    for(auto& t:threads){
        t.join();
    }
}
int main(){
    multithread();
    return 0;
}