#pragma once
#include <string>
#include <iostream>

/**
 * @brief Observer for observer pattern
 *
 */
class Observer {
    public:
        /**
         * @brief Construct a new observer object
         *
         * @param name Name of the observer
         */
        explicit Observer(const std::string& name);
        Observer(const Observer&) = delete;
        ~Observer() = default;
        /**
         * @brief Function called from subject when observer is notified
         *
         * @param message_from_subject Message sent from subject
         */
        virtual void update(const std::string& message_from_subject);
        /**
         * @brief Function called from subject when observer is notified
         *
         */
        virtual void update();
        /**
         * @brief Name of the observer
         *
         */
        std::string observer_name;
};
