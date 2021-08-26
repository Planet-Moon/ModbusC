#pragma once
#include "SMADevice.h"

namespace SMA {
	class StorageBoy : virtual public Device, private std::enable_shared_from_this<StorageBoy>
	{
		public:
			explicit StorageBoy(const char* ipAddress, int port = 502);
			explicit StorageBoy(std::string ipAddress, int port = 502);
			StorageBoy(const StorageBoy& other) = delete;
			~StorageBoy() = default;

			unsigned int soc{0};
			unsigned int dischargeCurrent{0};
			unsigned int chargeCurrent{0};
			unsigned int maxDischargeCurrent{0};
			unsigned int maxChargeCurrent{0};

		private:
			void storageBoyInit();

		public:
			virtual bool storageBoy_read_all_registers() final;
			virtual bool read_all_registers() override;
			unsigned int get_soc(bool* ret = nullptr);
			unsigned int get_dischargeCurrent(bool* ret = nullptr);
			unsigned int get_chargeCurrent(bool* ret = nullptr);
			unsigned int get_maxDischargeCurrent(bool* ret = nullptr);
			unsigned int get_maxChargeCurrent(bool* ret = nullptr);

			void testRead(bool* ret = nullptr);

		public:
			mb::Register<unsigned int> mbReg_soc;
			mb::Register<unsigned int> mbReg_dischargeCurrent;
			mb::Register<unsigned int> mbReg_chargeCurrent;
			mb::Register<unsigned int> mbReg_maxDischargeCurrent;
			mb::Register<unsigned int> mbReg_maxChargeCurrent;
	};
}