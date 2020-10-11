#include<iostream>
#include<thread>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;

template<typename Iterator, typename T>
void accumulate_block(Iterator first, Iterator end, T& result){
    result = std::accumulate(first, end, result);
}

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init){
    const unsigned long length = std::distance(first, last);
    if(!length){
        return init;
    }

    const unsigned long min_per_thread = 25;
    const unsigned long max_threads = 
        (length + min_per_thread - 1) / min_per_thread;
    const unsigned long hardware_threads = std::thread::hardware_concurrency();

    const unsigned long num_threads = 
        min(hardware_threads==0?2:hardware_threads, max_threads);
    
    const unsigned long block_size = length / num_threads;
  
    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads-1);

    Iterator block_start = first;
    for(unsigned long i = 0;i<num_threads-1;i++){
        Iterator block_end = block_start;
        std::advance(block_end, block_size);
        // threads.push_back(
        //     std::thread(
        //         accumulate_block<Iterator, T>,
        //         block_start,
        //         block_end,
        //         std::ref(results[i])
        //     )
        // );
        threads[i] = std::thread(
            accumulate_block<Iterator, T>,
            block_start,
            block_end,
            std::ref(results[i])
        );
        block_start = block_end;
    }
    accumulate_block<Iterator, T>(block_start, last, results[num_threads-1]);
    for(auto& t:threads){
        t.join();
    }
    return std::accumulate(results.begin(), results.end(), init);
}
int main(){
    vector<int> data;
    for(int i=0;i<10000;i++){
        data.push_back(i);
    }
    int sum = parallel_accumulate(data.begin(), data.end(), 5);
    std::cout << sum << std::endl;
    std::cout << std::accumulate(data.begin(), data.end(), 5) << endl;
    return 0;
}