#include <SMAModbusRelayStorageBoy.h>

namespace SMA{
ModbusRelayStorageBoy::ModbusRelayStorageBoy(std::shared_ptr<StorageBoy> deviceIn_, std::shared_ptr<mb::Device> deviceOut_, unsigned int addressOffset_ /* = 0 */):
    deviceIn(deviceIn_),
    registerSoc(deviceOut_.get(), static_cast<int>(0 + addressOffset_)),
    registerChargeCurrent(deviceOut_.get(), static_cast<int>(1 + addressOffset_)),
    registerDischargeCurrent(deviceOut_.get(), static_cast<int>(2 + addressOffset_))
{
}

void ModbusRelayStorageBoy::storageBoy_update()
{
    bool ret = false;

    if(abs(static_cast<int>(deviceIn->soc)-static_cast<int>(_soc_old))>1 || first_run)
    {
        registerSoc.setValue(deviceIn->soc,&ret);
        _soc_old = deviceIn->soc;
    }

    if(abs(static_cast<int>(deviceIn->chargeCurrent)-static_cast<int>(_chargeCurrent_old))>3 || first_run)
    {
        registerChargeCurrent.setValue(deviceIn->chargeCurrent,&ret);
        _chargeCurrent_old = deviceIn->chargeCurrent;
    }

    if(abs(static_cast<int>(deviceIn->dischargeCurrent)-static_cast<int>(_dischargeCurrent_old))>3 || first_run)
    {
        registerDischargeCurrent.setValue(deviceIn->dischargeCurrent,&ret);
        _dischargeCurrent_old = deviceIn->dischargeCurrent;
    }
}

void ModbusRelayStorageBoy::update()
{
    storageBoy_update();
    if(first_run)
        first_run = false;
}
}
