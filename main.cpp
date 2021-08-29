#include <iostream>
#include <hello.h>
#include <ModbusDevice.h>
#include <ModbusRegister.h>
#include <SMADevice.h>
#include <SMADeviceMqtt.h>
#include <SMAMainsMqtt.h>
#include <SMAStorageBoy.h>
#include <SMAStorageBoyMqtt.h>
#include <MqttClient.h>
#include <SMAModbusRelayDevice.h>
#include <cassert>
#include <chrono>
#include <signal.h>


bool run_test = true;

void signal_handler(int signal)
{
    if(signal != SIGINT){
        return;
    }
    else{
        run_test = false;
        std::cout<<"stopping test"<<std::endl;
    }
}

int main(int argc, char** argv){

    signal(SIGINT, signal_handler);

    hello::hello_world();
    std::shared_ptr<mb::Device> heatingControl = std::make_shared<mb::Device>("192.168.178.107",502);

    bool ret_val = false;

    mb::Register<short> waterTankTop(heatingControl.get(), 2, 0.1, "°C");
    std::cout << "waterTankTop: " + mb::printVector(waterTankTop.readRawData(&ret_val)) + ", status: " << ret_val << std::endl;

    mb::Register<short> waterTankMiddle(heatingControl.get(), 5, 0.1, "°C");
    std::cout << "waterTankMiddle: " + mb::printVector(waterTankMiddle.readRawData(&ret_val)) + ", status: " << ret_val << std::endl;

    mb::Register<float> testRegister(heatingControl.get(), 45, 0.1, "°C");
    std::cout << "testRegister: " << testRegister.getValue(&ret_val) << ", status: "<< ret_val << std::endl;

    mb::Register<unsigned int> testRegistersMany(heatingControl.get(), 32);

    testRegister.setValue(float(753));
    float testValue = 3.14156;
    testRegister.setValue(testValue);
    float testValueRet = testRegister.getValue();
    float testDiff = abs(testValueRet - testValue);
    assert(testDiff <= testRegister.factor);

    std::shared_ptr<myMqtt::Client> mqttClient = std::make_shared<myMqtt::Client>("tcp://192.168.178.107:1883", "cpp_test_client");

    std::shared_ptr<SMA::StorageBoy> storageBoy = std::make_shared<SMA::StorageBoy>("192.168.178.113", 502);
    std::shared_ptr<SMA::StorageBoyMqtt> storageBoyMqtt = std::make_shared<SMA::StorageBoyMqtt>("storageBoy", storageBoy, mqttClient);
    storageBoy->add_observer(storageBoyMqtt);
    storageBoyMqtt->topicPrefix = "testTopic";
    storageBoyMqtt->sending(true);

    std::shared_ptr<SMA::Device> sunnyBoy0 = std::make_shared<SMA::Device>("192.168.178.128", 502);
    std::shared_ptr<SMA::DeviceMqtt> sunnyBoyMqtt0 = std::make_shared<SMA::DeviceMqtt>("sunnyBoy0", sunnyBoy0, mqttClient);
    sunnyBoy0->add_observer(sunnyBoyMqtt0);
    sunnyBoyMqtt0->topicPrefix = "testTopic";
    sunnyBoyMqtt0->sending(true);

    std::shared_ptr<SMA::MainsMqtt> mainsMqtt = std::make_shared<SMA::MainsMqtt>("mains", sunnyBoy0, mqttClient);
    sunnyBoy0->add_observer(mainsMqtt);
    mainsMqtt->topicPrefix = "testTopic";
    mainsMqtt->sending(true);

    std::shared_ptr<SMA::ModbusRelayDevice> modbusRelay = std::make_shared<SMA::ModbusRelayDevice>(sunnyBoy0, heatingControl, 32);
    sunnyBoy0->add_observer(modbusRelay);

    std::shared_ptr<SMA::Device> sunnyBoy1 = std::make_shared<SMA::Device>("192.168.178.142", 502);
    std::shared_ptr<SMA::DeviceMqtt> sunnyBoyMqtt1 = std::make_shared<SMA::DeviceMqtt>("sunnyBoy1", sunnyBoy1, mqttClient);
    sunnyBoy1->add_observer(sunnyBoyMqtt1);
    sunnyBoyMqtt1->topicPrefix = "testTopic";
    sunnyBoyMqtt1->sending(true);

    std::shared_ptr<SMA::Device> sunnyBoy2 = std::make_shared<SMA::Device>("192.168.178.152", 502);
    std::shared_ptr<SMA::DeviceMqtt> sunnyBoyMqtt2 = std::make_shared<SMA::DeviceMqtt>("sunnyBoy2", sunnyBoy2, mqttClient);
    sunnyBoy2->add_observer(sunnyBoyMqtt2);
    sunnyBoyMqtt2->topicPrefix = "testTopic";
    sunnyBoyMqtt2->sending(true);


    for(int i = 0; i <10000 && run_test; ++i){
        std::cout << i << "-------------------------" << std::endl;
        std::cout << "->sunnyBoy0" << std::endl;
        sunnyBoy0->testRead();
        volatile int sunnyBoy_slaveId = modbus_get_slave(sunnyBoy0->connection);
        volatile int sunnyBoy_power = sunnyBoy0->get_power();
        volatile int sunnyBoy_dcWatt = sunnyBoy0->get_dcWatt();
        volatile int sunnyBoy_mainsFeedIn = sunnyBoy0->get_mainsFeedIn();
        volatile int sunnyBoy_mainsSupply = sunnyBoy0->get_mainsSupply();
        volatile bool sunnyBoy_online = sunnyBoy0->online;

        std::cout << "->storageBoy" << std::endl;
        storageBoy->testRead();
        volatile int storageBoy_slaveId = modbus_get_slave(storageBoy->connection);
        volatile int storageBoy_power = storageBoy->get_power();
        volatile int storageBoy_dcWatt = storageBoy->get_dcWatt();
        volatile unsigned int storageBoy_soc = storageBoy->get_soc();
        volatile unsigned int storageBoy_dischargeCurrent = storageBoy->get_dischargeCurrent();
        volatile unsigned int storageBoy_chargeCurrent = storageBoy->get_chargeCurrent();
        volatile unsigned int storageBoy_maxDischargeCurrent = storageBoy->get_maxDischargeCurrent();
        volatile unsigned int storageBoy_maxChargeCurrent = storageBoy->get_maxChargeCurrent();
        volatile unsigned int storageBoy_mainsFeedIn = storageBoy->get_mainsFeedIn();
        volatile unsigned int storageBoy_mainsSupply = storageBoy->get_mainsSupply();
        volatile bool storageBoy_online = storageBoy->online;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));

        std::vector<uint16_t> testRegisters = testRegistersMany.readRawData();
        std::cout << i << "+++---+++---+++---+++---" << std::endl;
    }
    std::cout<<"storageBoy:"<<std::endl;
    storageBoy->print_counters();
    std::cout<<"sunnyBoy0:"<<std::endl;
    sunnyBoy0->print_counters();
    std::cout<<"sunnyBoy1:"<<std::endl;
    sunnyBoy1->print_counters();
    std::cout<<"sunnyBoy2:"<<std::endl;
    sunnyBoy2->print_counters();

    return 0;
}
