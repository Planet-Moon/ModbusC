#include <SMAModbusRelayInterface.h>
#include <iostream>

#define RELAY_VALUE(val_name, ret) i.second.setValue(val_name,ret)
#define READ_VALUE(out_var_name, val_name) unsigned int (out_var_name)_temp = static_cast<unsigned int>(mbDeviceIn->val_name)

namespace SMA{
    ModbusRelayInterface::ModbusRelayInterface(std::shared_ptr<mb::Device> mbDeviceIn_, std::shared_ptr<mb::Device> mbDeviceOut_, unsigned int addressOffset_ /* = 0 */):
        Observer("ModbusRelayInterface"),
        deviceIn(mbDeviceIn_),
        deviceOut(mbDeviceOut_),
        addressOffset(addressOffset_)
    {
        initRegisters();
    }

    ModbusRelayInterface::ModbusRelayInterface(unsigned int addressOffset_ /* = 0 */):
        Observer("ModbusRelayInterface"),
        addressOffset(addressOffset_)
    {
        initRegisters();
    }

    ModbusRelayInterface::ModbusRelayInterface():
        Observer("ModbusRelayInterface")
    {
    }

    void ModbusRelayInterface::initRegisters()
    {
        /*
        * examples:
        * registerMap["test"] = mb::Register<unsigned int>(mbDeviceOut.get(), 0 + addressOffset);
        * registerMap["test2"] = mb::Register<unsigned int>(mbDeviceOut.get(), 1 + addressOffset);
        */
    }

    void ModbusRelayInterface::update()
    {
        for(auto& i : registerMap)
        {
            bool ret = false;
            unsigned int test = 0;
            i.second.getValue(&ret);
            i.second.setValue(test, &ret);
            //unsigned int test_temp = static_cast<unsigned int>(mbDeviceIn->power);
            //READ_VALUE(i.first,power);
            RELAY_VALUE(test,&ret);
            std::cout<<i.first<<std::endl;
        }
    }
}
