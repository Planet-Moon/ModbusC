#include <iostream>
#include <exception>
#include <ModbusDevice.h>
#include <chrono>
#include <exception>

namespace mb{

    void Device::init(const char* ipAddress_, int port_){
        ipAddress = ipAddress_;
        port = port_;
        connect(ipAddress.c_str(), port);
    }

    void Device::start_thread(){
        if(test_connection_run == false){
            test_connection_run = true;
            check_online_thread = new std::thread(&Device::test_connection_wrapper, this);
            #ifdef DEBUG
                std::cerr << "modbus connection " + ipAddress + ":" << port << " thread started" << std::endl;
            #endif // DEBUG
        }
    }

    Device::Device(const char* ipAddress_, int port_/*=502*/){
        init(ipAddress_, port_);
    }

    Device::Device(std::string ipAddress_, int port_/*=502*/){
        init(ipAddress_.c_str(), port_);
    }

    Device::~Device(){
        stop_thread();
        disconnect();
        #ifdef DEBUG
            std::cerr << "modbus device "+ ipAddress + ":" << port << " destroyed" << std::endl;
        #endif // DEBUG
    }

    void Device::stop_thread(){
        if(test_connection_run){
            std::thread::id thread_id = check_online_thread->get_id();
            if(check_online_thread->joinable())
                test_connection_run = false;
                check_online_thread->join();
            #ifdef DEBUG
                std::cerr << "modbus connection " + ipAddress + ":" << port << " thread stopped"<< std::endl;
            #endif // DEBUG
        }
    }

    bool Device::connect(const char* ipAddress_, int port_){
        connection = modbus_new_tcp(ipAddress_,port_);
        if (modbus_connect(connection) == -1)
        {
            #ifdef DEBUG
                std::cerr << "modbus connection error to ip " + ipAddress + ":" << port_ << std::endl;
            #endif // DEBUG
            modbus_free(connection);
            connection = nullptr;
            online = false;
        }
        else
        {
            #ifdef DEBUG
                std::cerr << "modbus successfully connected to ip " + ipAddress + ":" << port_ << std::endl;
            #endif // DEBUG
            online = true;
        }
        return online;
    }

    bool Device::disconnect(){
        modbus_close(connection);
        modbus_free(connection);
        connection = nullptr;
        online = false;
        #ifdef DEBUG
            std::cerr << "modbus connection " + ipAddress + ":" << port << " disconnected"<< std::endl;
        #endif // DEBUG
        return true;
    }

    void Device::test_class(){
        std::cout << "ipAddress: " << ipAddress << std::endl;
        std::cout << "port: " << port << std::endl;
        // modbus_read_registers(connection,2,5,tab_reg);
        // for(int i=0; i<32; ++i){
        //     std::cout << "tab_reg[" << i << "]: " << tab_reg[i] << std::endl;
        // }
    }

    void Device::test_all_registers(){
        // for(auto& x: registers){
        //     auto registerValue = x.second.readRawData(connection);
        // }
    }

    void test_modbus(){
        modbus_t *mb;
        uint16_t tab_reg[32] = {0};
        mb = modbus_new_tcp("192.168.178.107",502);
        modbus_connect(mb);
        int read_registers = modbus_read_registers(mb,2,5,tab_reg);
        modbus_close(mb);
        modbus_free(mb);
        for(int i=0; i<32; ++i){
            std::cout << "tab_reg[" << i << "]: " << tab_reg[i] << std::endl;
        }
    }

    void Device::test_connection_wrapper(){
        #ifdef DEBUG
            std::cerr << "modbus connection " + ipAddress + ":" << port << " thread started"<< std::endl;
        #endif // DEBUG
        while(test_connection_run){
            #ifdef DEBUG
                std::cerr << "modbus connection " + ipAddress + ":" << port << " thread running"<< std::endl;
            #endif // DEBUG
            try
            {
                test_counter++;
                if(test_connection()){
                    test_counter_success++;
                }
                else{
                    test_counter_fail++;
                }
            }
            catch(std::exception& e)
            {
                std::cout << e.what() << std::endl;
                test_counter_fail++;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        }
    }

    bool Device::test_connection()
    {
        if(connection != NULL){
            online = true;
        }
        else{
            online = false;
        }
        return online;
    }
}
