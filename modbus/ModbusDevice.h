#pragma once
#include <modbus.h>
#include <string>
#include <map>
#include <vector>
#include <thread>
#include <mutex>
#include <Subject.h>


namespace mb{

    class Device: public Subject
    {
        public:
            //properties
            std::string ipAddress;
            int port;
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
            unsigned short read_values_period{5}; //seconds
            bool online;
            void stop_thread();
            void start_thread();
            virtual bool read_all_registers();

        private:
            void test_class();
            void test_all_registers();
            void init(const char* ipAddress, int port = 502);
            std::unique_ptr<std::thread> read_values_thread;
            bool read_values_run{false};
            void update_connections_stats(char connection_state);
            void read_values_task();

        protected:

            long test_counter{0};
            long test_counter_success{0};
            long test_counter_fail{0};
            std::string test_history{""};
    };

    void test_modbus();
}
