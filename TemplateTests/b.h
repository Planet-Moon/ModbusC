#pragma once
#include <iostream>

template <class t>
class b{
    public:
        b();
        ~b();
        t data(t);
};

template <class t>
b<t>::b(){
    std::cout<<__FILE__<<" constructor" << std::endl;
}

template <class t>
b<t>::~b(){
    std::cout<<__FILE__<<" destructor" << std::endl;
}

template <class t>
t b<t>::data(t input){
    std::cout<<__FILE__<<" data "<< input << std::endl;
    return input;
}
