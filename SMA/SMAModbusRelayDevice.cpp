#include <SMAModbusRelayDevice.h>

namespace SMA{
ModbusRelayDevice::ModbusRelayDevice(std::shared_ptr<Device> deviceIn_, std::shared_ptr<mb::Device> deviceOut_, unsigned int addressOffset_ /* = 0 */):
    deviceIn(deviceIn_),
    registerPower(deviceOut_.get(), static_cast<int>(0 + addressOffset_)),
    registerDcWatt(deviceOut_.get(), static_cast<int>(1 + addressOffset_))
{
}

void ModbusRelayDevice::device_update()
{
    bool ret = false;
    if(abs(static_cast<int>(deviceIn->power)-static_cast<int>(_power_old))>3 || first_run)
    {
        registerPower.setValue(deviceIn->power,&ret);
        _power_old = deviceIn->power;
    }

    if(abs(static_cast<int>(deviceIn->dcWatt)-static_cast<int>(_dcWatt_old))>3 || first_run)
    {
        registerDcWatt.setValue(deviceIn->dcWatt,&ret);
        _dcWatt_old = deviceIn->dcWatt;
    }
}

void ModbusRelayDevice::update()
{
    device_update();
    if(first_run)
        first_run = false;
}
}
