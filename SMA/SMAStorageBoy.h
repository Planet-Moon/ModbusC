#include "SMADevice.h"

namespace SMA {
	class StorageBoy : public Device {
		public:
			StorageBoy(const char* ipAddress, int port = 502);
			StorageBoy(std::string ipAddress, int port = 502);

		private:
			void storageBoyInit();

		public:
			int get_power(bool* ret = nullptr);
			int get_dcWatt(bool* ret = nullptr);
			unsigned int get_soc(bool* ret = nullptr);
			unsigned int get_dischargeCurrent(bool* ret = nullptr);
			unsigned int get_chargeCurrent(bool* ret = nullptr);
			unsigned int get_maxDischargeCurrent(bool* ret = nullptr);
			unsigned int get_maxChargeCurrent(bool* ret = nullptr);

			void testRead(bool* ret = nullptr);

		public:
			mb::Register<int> power;
			mb::Register<int> dcWatt;
			mb::Register<unsigned int> soc;
			mb::Register<unsigned int> dischargeCurrent;
			mb::Register<unsigned int> chargeCurrent;
			mb::Register<unsigned int> maxDischargeCurrent;
			mb::Register<unsigned int> maxChargeCurrent;
	};
}