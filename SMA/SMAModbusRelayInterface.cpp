#include <SMAModbusRelayInterface.h>
#include <iostream>

namespace SMA{
    ModbusRelayInterface::ModbusRelayInterface(unsigned int addressOffset_ /* = 0 */):
        Observer("ModbusRelayInterface")
    {
    }

    ModbusRelayInterface::ModbusRelayInterface():
        Observer("ModbusRelayInterface")
    {
    }

    void ModbusRelayInterface::update()
    {
    }
}
