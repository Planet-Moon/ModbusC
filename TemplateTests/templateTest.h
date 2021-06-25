#pragma once
#include <vector>
#include "stdint.h"
#include <cmath>

namespace TestTemplate{
    template<class T>
    class TemplateTest{
        public:
            TemplateTest();
            TemplateTest(T value);
            T value;
            std::vector<uint16_t> data;
            T convert(std::vector<uint16_t> input);
            std::vector<uint16_t> convert(T input);
    };

    template<class T>
    TemplateTest<T>::TemplateTest(T value_){
        value = value_;
        data = std::vector<uint16_t>(1,0);
    }

    template<class T>
    TemplateTest<T>::TemplateTest(){
        value = T(0);
        data = std::vector<uint16_t>(1,0);
    }

    template<class T>
    T TemplateTest<T>::convert(std::vector<uint16_t> input){
        data = input;
        T retVal(0);
        for(int i = input.size()-1; i >= 0; i--){
            T ze = input[i]*pow(2,16*i);
            retVal += ze;
        }
        value = retVal;
        return retVal;
    }

    template<class T>
    std::vector<uint16_t> TemplateTest<T>::convert(T input){
        value = input;
        std::vector<uint16_t> result;
        const T zwei_hoch_16(pow(2, 16));
        while(input){
            result.push_back(round(input%zwei_hoch_16));
            input /= zwei_hoch_16;
        }
        data = result;
        return result;
    }
}
