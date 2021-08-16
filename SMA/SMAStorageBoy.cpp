#include "SMAStorageBoy.h"
#include <iostream>

#define INIT_STORAGEBOY_REGISTERS \
	soc(this,30845,1," %"), \
	chargeCurrent(this,31393,1," W"), \
	dischargeCurrent(this,31395,1," W"), \
	maxChargeCurrent(this,40189,1," W"), \
	maxDischargeCurrent(this,40191,1," W")

#define GENERATE_MB_GET_FUNC(type, mbRegister) \
    type StorageBoy::get_##mbRegister(bool* ret){ \
        type retval = 0; \
		if(online){ \
			retval = ##mbRegister.getValue(ret); \
		} \
        return (retval); \
    }

#define GENERATE_MB_SET_FUNC(type, mbRegister) \
    void StorageBoy::set_##mbRegister(type input, bool* ret){ \
		if(online){ \
        	##mbRegister.setValue(input, ret); \
		} \
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

	GENERATE_MB_GET_FUNC(unsigned int, soc);
	GENERATE_MB_GET_FUNC(unsigned int, dischargeCurrent);
	GENERATE_MB_GET_FUNC(unsigned int, chargeCurrent);
	GENERATE_MB_GET_FUNC(unsigned int, maxDischargeCurrent);
	GENERATE_MB_GET_FUNC(unsigned int, maxChargeCurrent);

	void StorageBoy::testRead(bool* ret /* = nullptr */)
	{
		std::cout << "online start: " << online << std::endl;
		std::cout << "power: " << get_power(ret) << std::endl;
		std::cout << "dcWatt: " << get_dcWatt(ret) << std::endl;
		std::cout << "mainsFeedIn: " << get_mainsFeedIn(ret) << std::endl;
		std::cout << "mainsSupply: " << get_mainsSupply(ret) << std::endl;
		std::cout << "soc: " << get_soc(ret) << std::endl;
		std::cout << "dischargeCurrent: " << get_dischargeCurrent(ret) << std::endl;
		std::cout << "chargeCurrent: " << get_chargeCurrent(ret) << std::endl;
		std::cout << "maxDischargeCurrent: " << get_maxDischargeCurrent(ret) << std::endl;
		std::cout << "maxChargeCurrent: " << get_maxChargeCurrent(ret) << std::endl;
		std::cout << "online end: " << online << std::endl;
	}
}
