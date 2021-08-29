#pragma once
#include <modbus.h>
#include <string>
#include <vector>
#include <ModbusDevice.h>
#include <cassert>

namespace mb{

    std::string printVector(std::vector<uint16_t> input);

    /**
     * @brief Modbus register for a #mb::Device
     *
     * @tparam T Type of value inside the register (short, unsigned int, int, long, float, double)
     */
    template<class T>
    class Register{
        public:
            /**
             * @brief Construct a new Register object
             *
             * @param device_ #mb::Device instance this register belongs to
             * @param addr_ Address of the register
             * @param factor_ Factor to multiply the value of the register
             * @param unit_ Unit of the register value
             */
            explicit Register(Device* device_, int addr_, float factor_ = 1., std::string unit_ = "") :
                device(device_),
                addr(addr_),
                factor(factor_),
                unit(unit_),
                data(std::vector<uint16_t>(sizeof(T)/2, 0))
            {
                dataSize = data.size();
            }
            Register(const Register& other) = delete;
            ~Register() = default;
            /**
             * @brief Address of the register
             *
             */
            int addr = 0;
            /**
             * @brief Factor to multiply the value of the register
             *
             */
            float factor = 0;
            /**
             * @brief Unit of the register value
             *
             */
            std::string unit = "";

        private:
            /**
             * @brief Data vector for raw data of the register
             *
             */
            std::vector<uint16_t> data = std::vector<uint16_t>(0,0);
            /**
             * @brief Length of the register in numbers of words(16bit)
             *
             */
            unsigned short dataSize = 0;
            /**
             * @brief #mb::Device instance this register belongs to
             *
             */
            Device* device = nullptr;

        public:
            /**
             * @brief Read raw data from the register
             *
             * @param ret Return status (true: success, false: fail)
             * @return std::vector<uint16_t> Data vector with raw data from the register
             */
            std::vector<uint16_t> readRawData(bool* ret = nullptr)
            {
                assert(device != nullptr && "Device must not be nullptr");
                device->modbus_mtx.lock();
                int status = modbus_read_registers(device->connection, addr, dataSize, data.data());
                device->modbus_mtx.unlock();
                if (ret) {
                    *ret = status == dataSize;
                }
                return data;
            }

            /**
             * @brief Write raw data to the register
             *
             * @param input Data vector to be written to the register
             * @param ret Return status (true: success, false: fail)
             */
            void writeRawData(const std::vector<uint16_t>* input, bool* ret = nullptr)
            {
                assert(device != nullptr);
                device->modbus_mtx.lock();
                int status = modbus_write_registers(device->connection, addr, dataSize, input->data());
                device->modbus_mtx.unlock();
                if (ret) {
                    *ret = status == dataSize;
                }
            }

            /**
             * @brief Get value from the register
             *
             * Uses #readRawData to get data and then converts it to T.
             *
             * @param ret Return status (true: success, false: fail)
             * @return T Value of the register
             */
            T getValue(bool* ret = nullptr)
            {
                std::vector<uint16_t> rawData = readRawData(ret);
                short temp16{0};
                int temp32{0};
                long temp64{0};
                T tempT{0};
                if(rawData.size() != dataSize){
                    std::string assert_message = "Invalid data size read from device "+device->ipAddress+", expected " + std::to_string(dataSize) + " got "+std::to_string(rawData.size())+".";
                    std::cout<<assert_message<<std::endl;
                    *ret = false;
                    return static_cast<T>(0);
                }
                switch(rawData.size()) {
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
            /**
             * @brief Set the Value of the register
             *
             * @param input Data to be written to the register
             * @param ret Return status (true: success, false: fail)
             */
            void setValue(short input, bool* ret = nullptr)
            {
                std::vector<uint16_t> buffer(dataSize);
                buffer = input & 0xFFFFFFFF;
                break;
                writeRawData(&buffer,ret);
            };

            /**
             * @brief Set the Value of the register
             *
             * @param input Data to be written to the register
             * @param ret Return status (true: success, false: fail)
             */
            void setValue(unsigned int input, bool* ret = nullptr)
            {
                input /= factor;
                std::vector<uint16_t> buffer(dataSize);
                MODBUS_SET_INT32_TO_INT16(buffer.data(), 0, input);
                writeRawData(&buffer,ret);
                return;
            }

            /**
             * @brief Set the Value of the register
             *
             * @param input Data to be written to the register
             * @param ret Return status (true: success, false: fail)
             */
            void setValue(int input, bool* ret = nullptr)
            {
                input /= factor;
                std::vector<uint16_t> buffer(dataSize);
                MODBUS_SET_INT32_TO_INT16(buffer.data(), 0, input);
                writeRawData(&buffer,ret);
                return;
            }

            /**
             * @brief Set the Value of the register
             *
             * @param input Data to be written to the register
             * @param ret Return status (true: success, false: fail)
             */
            void setValue(long input, bool* ret = nullptr)
            {
                input /= factor;
                std::vector<uint16_t> buffer(dataSize);
                MODBUS_SET_INT64_TO_INT16(buffer.data(), 0, input);
                writeRawData(&buffer,ret);
                return;
            }


            /**
             * @brief Set the Value of the register
             *
             * @param input Data to be written to the register
             * @param ret Return status (true: success, false: fail)
             */
            void setValue(float input, bool* ret = nullptr)
            {
                int temp = input/factor;
                std::vector<uint16_t> buffer(dataSize);
                MODBUS_SET_INT32_TO_INT16(buffer.data(), 0, temp);
                writeRawData(&buffer,ret);
                return;
            }

            /**
             * @brief Set the Value of the register
             *
             * @param input Data to be written to the register
             * @param ret Return status (true: success, false: fail)
             */
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
