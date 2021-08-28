#pragma once
#include <list>
#include <string>
#include <Observer.h>

class Subject {
    public:
        explicit Subject();
        virtual ~Subject() = default;
        virtual void add_observer(std::weak_ptr<Observer> observer);
        virtual void remove_observer(std::weak_ptr<Observer> observer);
        virtual void notify();
        std::list<std::string> observerNames();

    private:
        std::list<std::weak_ptr<Observer>> observers;
};