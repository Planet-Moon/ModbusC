#pragma once
#include <string>
#include <iostream>

class Observer {
    public:
        explicit Observer(const std::string& name);
        Observer(const Observer&) = delete;
        ~Observer() = default;
        virtual void update(const std::string& message_from_subject);
        virtual void update();
        std::string observer_name;
};
