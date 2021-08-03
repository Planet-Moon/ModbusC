#pragma once
#include <modbus.h>
#include <string>
#include <map>
#include <vector>

#include <thread>
#include <semaphore>

namespace mb{

    class Device{
        public:
            //properties
            std::string ipAddress;
            int port;
            bool online;
            //methods
            Device(const char* ipAddress, int port = 502);
            Device(std::string ipAddress, int port = 502);
            ~Device();
            modbus_t* connection;
            bool connect(const char* ipAddress, int port = 502);
            bool disconnect();
        private:
            void test_class();
            void test_all_registers();
            void init(const char* ipAddress, int port = 502);
            std::thread* check_online_thread;
            bool test_connection_run;
            void test_connection_wrapper();

        protected:
            virtual void test_connection();
            void start_thread();
            void stop_thread();
            std::binary_semaphore* connection_semaphore;
    };

    void test_modbus();
}
