#pragma once
#include <Observer.h>
#include <ModbusRegister.h>
#include <map>

namespace SMA{
    /**
     * @brief Modbus relay interface
     *
     * Used to relay values from an Modbus device to another.
     *
     */
    class ModbusRelayInterface: public Observer
    {
    public:
        /**
         * @brief Construct a new Modbus Relay Interface object
         *
         * @param addressOffset Register offset of the registers the values are written to
         */
        explicit ModbusRelayInterface(unsigned int addressOffset);
        explicit ModbusRelayInterface();
        ModbusRelayInterface(const ModbusRelayInterface&) = delete;
        ~ModbusRelayInterface() = default;
        virtual void update() override;
    protected:
        /// Flag for the first run
        bool first_run;
    };
}