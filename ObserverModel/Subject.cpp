#include <Subject.h>
#include <algorithm>

Subject::Subject()
{
    ;
}

void Subject::add_observer(std::weak_ptr<Observer> observer)
{
    observers.push_back(observer);
}

void Subject::remove_observer(std::weak_ptr<Observer> observer)
{
    std::list<std::weak_ptr<Observer>>::iterator findIter = std::find_if(observers.begin(), observers.end(), [&observer](const std::weak_ptr<Observer> ptr) {
        return ptr.lock() == observer.lock();
    });
    if(findIter != observers.end())
    {
        observers.erase(findIter);
    }
}

void Subject::notify()
{
    for(auto it=observers.begin(); it!=observers.end(); ++it)
    {
        if(!it->expired())
        {
            auto observer = it->lock();
            observer->update();
        }
    }
}

std::list<std::string> Subject::observerNames()
{
    std::list<std::string> result;
    for(auto it=observers.begin(); it!=observers.end(); ++it)
    {
        auto observer = it->lock();
        result.push_back(observer->observer_name);
    }
    return result;
}
