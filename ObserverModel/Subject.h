#pragma once
#include <list>
#include <string>
#include <Observer.h>

/**
 * @brief Subject for ObserverPattern
 *
 */
class Subject {
    public:
        /**
         * @brief Construct a new Subject object
         *
         */
        explicit Subject();
        virtual ~Subject() = default;
        /**
         * @brief Add a observer to the notification list
         *
         * @param observer
         */
        virtual void add_observer(std::weak_ptr<Observer> observer);
        /**
         * @brief Remove a observer from the notification list
         *
         * @param observer
         */
        virtual void remove_observer(std::weak_ptr<Observer> observer);
        /**
         * @brief Notify all observers from the notification list
         *
         */
        virtual void notify();
        /**
         * @brief Return all the names of observers from the notification list
         *
         * @return std::list<std::string>
         */
        std::list<std::string> observerNames();

    private:
        /**
         * @brief Notification list
         * The update function will be called of the observes from the notification list when notify() is called.
         */
        std::list<std::weak_ptr<Observer>> observers;
};