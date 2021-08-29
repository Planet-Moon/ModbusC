#pragma once
#include "SMADevice.h"

namespace SMA {
    /**
     * @brief Interface to a SMA StorageBoy
     *
     */
    class StorageBoy : virtual public Device
    {
        public:
            /**
             * @brief Construct a new Storage Boy object
             *
             * @param ipAddress Ip address of the device
             * @param port Port number of the device
             */
            explicit StorageBoy(const char* ipAddress, int port = 502);
            /**
             * @brief Construct a new Storage Boy object
             *
             * @param ipAddress Ip address of the device
             * @param port Port number of the device
             */
            explicit StorageBoy(std::string ipAddress, int port = 502);
            StorageBoy(const StorageBoy& other) = delete;
            ~StorageBoy() = default;

            /// Last read soc value from the device.
            unsigned int soc{0};
            /// Last read discharge current value from the device.
            unsigned int dischargeCurrent{0};
            /// Last read charge current value from the device.
            unsigned int chargeCurrent{0};
            /// Last read max discharge current value from the device (set once in #storageBoyInit).
            unsigned int maxDischargeCurrent{0}; // only set once after init
            /// Last read max charge current value from the device (set once in #storageBoyInit).
            unsigned int maxChargeCurrent{0}; // only set once after init

        private:
            /**
             * @brief Initialize constat device value
             *
             */
            void storageBoyInit();

        public:
            /**
             * @brief Read all storageBoy registers
             *
             * Called by #read_all_registers.
             *
             * @return true: Read successful
             * @return false: Read failed
             */
            virtual bool storageBoy_read_all_registers() final;
            /**
             * @brief Read all registers
             *
             * Calls #storageBoy_read_all_registers.
             *
             * @return true: Read successful
             * @return false: Read failed
             */
            virtual bool read_all_registers() override;
            /**
             * @brief Get the battery soc value
             *
             * Battery state of charge
             *
             * @param ret Return status (true: success, false: fail)
             * @return unsigned int: Battery Soc
             */
            unsigned int get_soc(bool* ret = nullptr);
            /**
             * @brief Get the current discharge value
             *
             * Current as in at this moment, not as amperes.
             * So 500 means 500 watts are currently drawn from the battery.
             *
             * @param ret Return status (true: success, false: fail)
             * @return unsigned int: Power drawn from the battery at this moment
             */
            unsigned int get_dischargeCurrent(bool* ret = nullptr);
            /**
             * @brief Get the current charge value
             *
             * Current as in at this moment, not as amperes.
             * So 500 means 500 watts are currently charged into the battery.
             *
             * @param ret Return status (true: success, false: fail)
             * @return unsigned int: Power charged into the battery at this moment
             */
            unsigned int get_chargeCurrent(bool* ret = nullptr);
            /**
             * @brief Get the maxDischargeCurrent value
             *
             * Maximum battery power output
             *
             * @param ret Return status (true: success, false: fail)
             * @return unsigned int: Maximum power output of the battery
             */
            unsigned int get_maxDischargeCurrent(bool* ret = nullptr);
            /**
             * @brief Get the maxChargeCurrent value
             *
             * @param ret Return status (true: success, false: fail)
             * @return unsigned int: Maximum power that can be charged into the battery
             */
            unsigned int get_maxChargeCurrent(bool* ret = nullptr);

            /**
             * @brief Test read the StorageBoy
             *
             * @param ret Return status (true: success, false: fail)
             */
            void testRead(bool* ret = nullptr);

        public:
            /// Register of the soc value
            mb::Register<unsigned int> mbReg_soc;
            /// Register of the current discharge power value
            mb::Register<unsigned int> mbReg_dischargeCurrent;
            /// Register of the current charge power value
            mb::Register<unsigned int> mbReg_chargeCurrent;
            /// Register of the maximum discharge power value
            mb::Register<unsigned int> mbReg_maxDischargeCurrent;
            /// Register of the maximum charge power value
            mb::Register<unsigned int> mbReg_maxChargeCurrent;
    };
}