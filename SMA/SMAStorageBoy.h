#include "SMADevice.h"

namespace SMA {
	class StorageBoy : public Device {
		public:
			StorageBoy(const char* ipAddress, int port = 502);
			StorageBoy(std::string ipAddress, int port = 502);

		private:
			void storageBoyInit();

		public:
			int readPower();
			int readDcWatt();
			int readSoC();

		private:
			mb::Register<int> mbPower;
			mb::Register<int> mbDcWatt;
			mb::Register<int> mbSoC;
	};
}