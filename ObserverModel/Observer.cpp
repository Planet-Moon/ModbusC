#include <Observer.h>

Observer::Observer(const std::string& _name)
{
    observer_name = _name;
}

void Observer::update(const std::string& message_from_subject)
{
    std::cout << "update: " << message_from_subject << std::endl;
}

void Observer::update()
{
    ;
}
