#include <iostream>
#include "templateTest.h"
#include "b.h"

// template implementations need to be in a header file,
// because they need to be compiled each time they get used in other files

int main(int argc, char** argv){
    std::cout << "Template Test" << std::endl;
    auto template1 = TestTemplate::TemplateTest<double>();
    auto template2 = TestTemplate::TemplateTest<long long int>((long long int)2);
    auto testVector = std::vector<uint16_t>({0,5});
    template1.convert(testVector);
    template2.convert(4295163911);
    template2.data[0] += 1;
    template2.convert(template2.data);
    return 0;
}
