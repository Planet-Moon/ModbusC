#pragma once
#include <modbus.h>
#include <string>
#include "stdint.h"
#include <vector>
#include <cmath>
#include "../Conversions/Conversions.h"
#include "../ModbusDevice/ModbusDevice.h"

namespace mb{

    std::string printVector(std::vector<uint16_t> input);

    template<class T>
    class Register{
        public:
            Register(modbus_t* device_, int addr_, int nb_ = 1, float factor_ = 1., std::string unit_ = "") :
                device(device_),
                addr(addr_),
                nb(nb_),
                factor(factor_),
                unit(unit_),
                data(std::vector<uint16_t>(nb, 0))
            {
                return;
            }
            int addr;
            int nb;
            float factor;
            std::string unit;

        private:
            std::vector<uint16_t> data;
            modbus_t* device;

        public:
            std::vector<uint16_t> readRawData(bool* ret = nullptr) {
                int status = modbus_read_registers(device, addr, nb, data.data());
                if (ret) {
                    *ret = status == nb;
                }
                return data;
            }
            
            void writeRawData(const std::vector<uint16_t>* input, bool* ret = nullptr) {
                int status = modbus_write_registers(device, addr, nb, input->data());
                if (ret) {
                    *ret = status == nb;
                }
            }

            T getValue()
            {
                return T();
            }

            void setValue(T)
            {
            }
    };
}
