#include "SMAStorageBoy.h"

#define INIT_STORAGEBOY_REGISTERS \
	mbPower(this->connection,30775,2,1," W"), \
	mbDcWatt(this->connection,30773,2,1," W"), \
	mbSoC(this->connection,30845,2)

namespace SMA {
	StorageBoy::StorageBoy(const char* ipAddress, int port):
		Device(ipAddress,port),
		INIT_STORAGEBOY_REGISTERS
	{
	}

	StorageBoy::StorageBoy(std::string ipAddress, int port):
		Device(ipAddress, port),
		INIT_STORAGEBOY_REGISTERS
	{
	}

	void StorageBoy::storageBoyInit()
	{
	}

	int registerToInt(std::vector<uint16_t> input)
	{
		return MODBUS_GET_INT32_FROM_INT16(input.data(), 0);
	}

	int StorageBoy::readPower()
	{
		int retval = registerToInt(mbPower.readRawData());
		if (retval < 0)
			retval = 0;
		return retval;
	}

	int StorageBoy::readDcWatt()
	{
		int retval = registerToInt(mbDcWatt.readRawData());
		if (retval < 0)
			retval = 0;
		return retval;
	}

	int StorageBoy::readSoC()
	{
		int retval = registerToInt(mbSoC.readRawData());
		if (retval < 0)
			retval = 0;
		return retval;
	}

}
