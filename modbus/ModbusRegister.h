#pragma once
#include <modbus.h>
#include <string>
#include <vector>
#include <ModbusDevice.h>
#include <cassert>

namespace mb{

    std::string printVector(std::vector<uint16_t> input);

    template<class T>
    class Register{
        public:
            Register(Device* device_, int addr_, float factor_ = 1., std::string unit_ = "") :
                device(device_),
                addr(addr_),
                factor(factor_),
                unit(unit_),
                data(std::vector<uint16_t>(sizeof(T)/2, 0))
            {
                dataSize = data.size();
                return;
            }
            Register(const Register& other) = delete;
            ~Register() = default;
            int addr;
            float factor;
            std::string unit;

        private:
            std::vector<uint16_t> data;
            unsigned short dataSize;
            Device* device;

        public:
            std::vector<uint16_t> readRawData(bool* ret = nullptr) {
                assert(device != nullptr);
                device->modbus_mtx.lock();
                int status = modbus_read_registers(device->connection, addr, dataSize, data.data());
                device->modbus_mtx.unlock();
                if (ret) {
                    *ret = status == dataSize;
                }
                return data;
            }

            void writeRawData(const std::vector<uint16_t>* input, bool* ret = nullptr) {
                assert(device != nullptr);
                device->modbus_mtx.lock();
                int status = modbus_write_registers(device->connection, addr, dataSize, input->data());
                device->modbus_mtx.unlock();
                if (ret) {
                    *ret = status == dataSize;
                }
            }

            T getValue(bool* ret = nullptr)
            {
                std::vector<uint16_t> rawData = readRawData(ret);
                short temp16{0};
                int temp32{0};
                long temp64{0};
                T tempT{0};
                switch(dataSize) {
                    case 2:
                        temp32 = MODBUS_GET_INT32_FROM_INT16(rawData.data(), 0);
                        tempT = static_cast<T>(temp32*factor);
                        break;
                    case 4:
                        temp64 = MODBUS_GET_INT64_FROM_INT16(rawData.data(), 0);
                        tempT = static_cast<T>(temp64*factor);
                        return tempT;
                        break;
                    default:
                        temp16 = rawData[0];
                        tempT = static_cast<T>(temp16*factor);
                        break;
                    break;
                }
                return tempT;
            }

        public:
            void setValue(short input, bool* ret = nullptr)
            {
                std::vector<uint16_t> buffer(dataSize);
                buffer = input & 0xFFFFFFFF;
                break;
                writeRawData(&buffer,ret);
            };

            void setValue(int input, bool* ret = nullptr)
            {
                input /= factor;
                std::vector<uint16_t> buffer(dataSize);
                MODBUS_SET_INT32_TO_INT16(buffer.data(), 0, input);
                writeRawData(&buffer,ret);
                return;
            }

            void setValue(long input, bool* ret = nullptr)
            {
                input /= factor;
                std::vector<uint16_t> buffer(dataSize);
                MODBUS_SET_INT64_TO_INT16(buffer.data(), 0, input);
                writeRawData(&buffer,ret);
                return;
            }

            void setValue(float input, bool* ret = nullptr)
            {
                int temp = input/factor;
                std::vector<uint16_t> buffer(dataSize);
                MODBUS_SET_INT32_TO_INT16(buffer.data(), 0, temp);
                writeRawData(&buffer,ret);
                return;
            }

            void setValue(double input, bool* ret = nullptr)
            {
                long temp = input/factor;
                std::vector<uint16_t> buffer(dataSize);
                MODBUS_SET_INT64_TO_INT16(buffer.data(), 0, temp);
                writeRawData(&buffer,ret);
                return;
            }
    };
}
