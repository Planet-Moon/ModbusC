#pragma once
#include <modbus.h>
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <mutex>


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
            Device(const Device& other) = delete;
            ~Device();
            modbus_t* connection;
            std::mutex modbus_mtx;
            bool connect(const char* ipAddress, int port = 502);
            bool disconnect();
            virtual void print_counters() final;

        private:
            void test_class();
            void test_all_registers();
            void init(const char* ipAddress, int port = 502);
            std::unique_ptr<std::thread> check_online_thread;
            bool test_connection_run = false;
            void test_connection_wrapper();

        protected:
            virtual bool test_connection();
            void start_thread();
            void stop_thread();

            long test_counter{0};
            long test_counter_success{0};
            long test_counter_fail{0};
            std::string test_history{""};
    };

    void test_modbus();
}
