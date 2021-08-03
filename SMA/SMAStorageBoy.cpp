#include "SMAStorageBoy.h"

#define INIT_STORAGEBOY_REGISTERS \
	power(this->connection,30775,1," W"), \
	dcWatt(this->connection,30773,1," W"), \
	soc(this->connection,30845,1," %")

#define GENERATE_MB_GET_FUNC(type, mbRegister) \
    type StorageBoy::get_##mbRegister(bool* ret){ \
        connection_semaphore->acquire(); \
        type retval = ##mbRegister.getValue(ret); \
        connection_semaphore->release(); \
        return (##mbRegister.getValue(ret)); \
    }

#define GENERATE_MB_SET_FUNC(type, mbRegister) \
    void StorageBoy::set_##mbRegister(type input, bool* ret){ \
        connection_semaphore->acquire(); \
        ##mbRegister.setValue(input, ret); \
        connection_semaphore->release(); \
    }

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

	int StorageBoy::get_power(bool* ret)
	{
		connection_semaphore->acquire();
		int temp{power.getValue(ret)};
		connection_semaphore->release();
		if(temp < 0)
			temp = 0;
		return temp;
	}

	int StorageBoy::get_dcWatt(bool* ret)
	{
		connection_semaphore->acquire();
		int temp{dcWatt.getValue(ret)};
		connection_semaphore->release();
		if(temp < 0)
			temp = 0;
		return temp;
	}

	GENERATE_MB_GET_FUNC(int, soc)
}
