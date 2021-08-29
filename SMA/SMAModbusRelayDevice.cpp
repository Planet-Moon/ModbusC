#include <SMAModbusRelayDevice.h>

#define RELAY_VALUE(val_name, ret) i.second.setValue(#val_name,ret)
#define READ_VALUE(out_var_name, val_name) unsigned int (out_var_name)_temp = static_cast<unsigned int>(mbDeviceIn->val_name)

namespace SMA{
ModbusRelayDevice::ModbusRelayDevice(std::shared_ptr<Device> deviceIn_, std::shared_ptr<mb::Device> deviceOut_, unsigned int addressOffset_ /* = 0 */):
    deviceIn(deviceIn_),
    deviceOut(deviceOut_)
{
    addressOffset = addressOffset_;
    initRegisters();
}

void ModbusRelayDevice::initRegisters()
{
    registerMap["power"] = mb::Register<unsigned int>(deviceOut.get(), 0 + addressOffset);
    registerMap["dcWatt"] = mb::Register<unsigned int>(deviceOut.get(), 1 + addressOffset);
    inputMap["power"] = std::make_shared<unsigned int>(deviceIn->power);
    inputMap["dcWatt"] = std::make_shared<unsigned int>(deviceIn->dcWatt);
}

void ModbusRelayDevice::update()
{
    bool ret = false;
    registerMap["power"].setValue(*inputMap["power"],&ret);
    registerMap["dcWatt"].setValue(*inputMap["dcWatt"],&ret);
}
}
