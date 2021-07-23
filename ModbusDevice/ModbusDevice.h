#pragma once
#include <modbus.h>
#include <string>
#include <map>
#include <vector>

namespace mb{

    class Device{
        public:
            //properties
            std::string ipAddress;
            int port;
            //methods
            Device(const char* ipAddress, int port = 502);
            Device(std::string ipAddress, int port = 502);
            ~Device();
            modbus_t* connection;
        private:            
            void test_class();
            void test_all_registers();
    };

    void test_modbus();
}
