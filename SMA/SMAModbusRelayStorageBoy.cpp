#include <SMAModbusRelayStorageBoy.h>

namespace SMA{
ModbusRelayStorageBoy::ModbusRelayStorageBoy(std::shared_ptr<StorageBoy> deviceIn_, std::shared_ptr<mb::Device> deviceOut_, unsigned int addressOffset_ /* = 0 */):
    deviceIn(deviceIn_),
    registerSoc(deviceOut_.get(), static_cast<int>(0 + addressOffset_)),
    registerChargeCurrent(deviceOut_.get(), static_cast<int>(1 + addressOffset_)),
    registerDischargeCurrent(deviceOut_.get(), static_cast<int>(2 + addressOffset_))
{
}

void ModbusRelayStorageBoy::update()
{
    bool ret = false;
    registerSoc.setValue(deviceIn->soc,&ret);
    registerChargeCurrent.setValue(deviceIn->chargeCurrent,&ret);
    registerDischargeCurrent.setValue(deviceIn->dischargeCurrent,&ret);
}
}
