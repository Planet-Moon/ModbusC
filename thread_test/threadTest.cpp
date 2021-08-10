#include <thread>
#include <map>
#include <string>
#include <chrono>
#include <vector>
#include <iostream>
#include <future>



unsigned int fibonacci(unsigned int to, unsigned int* result = nullptr)
{
    unsigned int result_ = 0;
    if(to == 0){
        result_ = 0;
    }
    else if(to < 2){
        result_ = 1;
    }
    else{
        result_ = fibonacci(to-1) + fibonacci(to-2);
    }
    if(result != nullptr){
        *result = result_;
    }
    return result_;
}


void test(int* a, int* b = nullptr)
{
    if(b != nullptr){
        std::cout<<"a: "<<*a<<std::endl;
        std::cout<<"b: "<<*b<<std::endl;
        *b += (*a);
    }
}


int test_prototype(){
    int test1 = 1;
    int test2 = 3;
    std::thread* test_thread = new std::thread(test, &test1, &test2);
    test_thread->join();
    std::cout<<test2<<std::endl;
    return 0;
}


int main(int argc, char* argv[])
{
    int nThreads = 45;
    std::map<std::string, std::thread*> threadMap;
    std::vector<unsigned int> result;
    result.reserve(nThreads);

    for(int i = 0; i < nThreads; ++i)
    {
        result.push_back(0);
        std::thread* t = new std::thread(fibonacci, i, &result.at(i));
        threadMap["thread_"+std::to_string(i)] = t;
        std::cout<<"thread_"+std::to_string(i)+" started"<<std::endl;
    }
    std::cout << "all threads running" << std::endl;
    for(auto const& t: threadMap)
    {
        if(t.second->joinable())
        {
            t.second->join();
        }
        std::cout<<t.first+" joined"<<std::endl;
    }
    std::cout << "all threads done" << std::endl;
    for(int i = 0; i<nThreads; ++i)
    {
        std::cout << i << ": " << result[i] << std::endl;
    }
    return 0;
}