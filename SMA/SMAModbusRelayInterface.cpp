#include <SMAModbusRelayInterface.h>
#include <iostream>

#define RELAY_VALUE(val_name, ret) i.second.setValue(val_name,ret)
#define READ_VALUE(out_var_name, val_name) unsigned int (out_var_name)_temp = static_cast<unsigned int>(mbDeviceIn->val_name)

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
