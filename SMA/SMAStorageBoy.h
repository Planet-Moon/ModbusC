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
			int get_soc(bool* ret = nullptr);

		public:
			mb::Register<int> power;
			mb::Register<int> dcWatt;
			mb::Register<int> soc;
	};
}