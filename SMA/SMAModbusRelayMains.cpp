#include <SMAModbusRelayMains.h>

#define RELAY_VALUE(val_name, ret) i.second.setValue(#val_name,ret)
#define READ_VALUE(out_var_name, val_name) unsigned int (out_var_name)_temp = static_cast<unsigned int>(mbDeviceIn->val_name)

namespace SMA{
ModbusRelayMains::ModbusRelayMains(std::shared_ptr<Device> deviceIn_, std::shared_ptr<mb::Device> deviceOut_, unsigned int addressOffset_ /* = 0 */):
    deviceIn(deviceIn_),
    registerMainsFeedIn(deviceOut_.get(), static_cast<int>(0 + addressOffset_)),
    registerMainsSupply(deviceOut_.get(), static_cast<int>(1 + addressOffset_))
{
}

void ModbusRelayMains::set_MainsFeedIn_register_address(int address)
{
    registerMainsFeedIn.addr = address;
}

void ModbusRelayMains::set_MainsSuppy_register_address(int address)
{
    registerMainsSupply.addr = address;
}

void ModbusRelayMains::mains_update()
{
    bool ret = false;
    if(abs(static_cast<int>(deviceIn->mainsFeedIn)-static_cast<int>(_mainsFeedIn_old))>3 || first_run)
    {
        registerMainsFeedIn.setValue(deviceIn->mainsFeedIn,&ret);
        _mainsFeedIn_old = deviceIn->mainsFeedIn;
    }

    if(abs(static_cast<int>(deviceIn->mainsSupply)-static_cast<int>(_mainsSupply_old))>3 || first_run)
    {
        registerMainsSupply.setValue(deviceIn->mainsSupply,&ret);
        _mainsSupply_old = deviceIn->mainsSupply;
    }
}

void ModbusRelayMains::update()
{
    mains_update();
    if(first_run)
        first_run = false;
}
}
