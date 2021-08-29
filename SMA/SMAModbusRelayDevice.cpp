#include <SMAModbusRelayDevice.h>

#define RELAY_VALUE(val_name, ret) i.second.setValue(#val_name,ret)
#define READ_VALUE(out_var_name, val_name) unsigned int (out_var_name)_temp = static_cast<unsigned int>(mbDeviceIn->val_name)

namespace SMA{
ModbusRelayDevice::ModbusRelayDevice(std::shared_ptr<Device> deviceIn_, std::shared_ptr<mb::Device> deviceOut_, unsigned int addressOffset_ /* = 0 */):
    deviceIn(deviceIn_),
    registerPower(deviceOut_.get(), static_cast<int>(0 + addressOffset_)),
    registerDcWatt(deviceOut_.get(), static_cast<int>(1 + addressOffset_))
{
}

void ModbusRelayDevice::update()
{
    bool ret = false;
    registerPower.setValue(deviceIn->power,&ret);
    registerDcWatt.setValue(deviceIn->dcWatt,&ret);
}
}
