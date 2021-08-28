#include <iostream>
#include <Subject.h>
#include <Observer.h>


void print_list(std::list<std::string> list)
{
    for(auto it = list.begin(); it != list.end(); it++)
    {
        std::cout<<*it<<std::endl;
    }
}

void test_subscribing()
{
    std::cout<<"test_subscribing ------------------"<<std::endl;
    std::shared_ptr<Observer>observer = std::make_shared<Observer>("observer");
    std::shared_ptr<Observer>observer2 = std::make_shared<Observer>("observer2");
    std::shared_ptr<Observer>observer3 = std::make_shared<Observer>("observer3");
    Subject subject = Subject();
    std::cout<<"------------------"<<std::endl;
    print_list(subject.observerNames());
    subject.add_observer(observer);
    std::cout<<"------------------"<<std::endl;
    print_list(subject.observerNames());
    subject.add_observer(observer2);
    std::cout<<"------------------"<<std::endl;
    print_list(subject.observerNames());
    subject.add_observer(observer3);
    std::cout<<"------------------"<<std::endl;
    print_list(subject.observerNames());
    subject.remove_observer(observer2);
    std::cout<<"------------------"<<std::endl;
    print_list(subject.observerNames());
    subject.remove_observer(observer);
    std::cout<<"------------------"<<std::endl;
    print_list(subject.observerNames());
    subject.remove_observer(observer3);
    std::cout<<"------------------"<<std::endl;
    print_list(subject.observerNames());
}

void test_update()
{
    std::cout<<"test_update ------------------"<<std::endl;
    Subject subject = Subject();

    class ObserverNameOnUpdate: public Observer {
        public:
            ObserverNameOnUpdate(std::string name): Observer(name) {}
            ~ObserverNameOnUpdate() = default;
            virtual void update() override {
                std::cout<<observer_name<<" update called"<<std::endl;
            }
    };

    std::shared_ptr<ObserverNameOnUpdate>observer = std::make_shared<ObserverNameOnUpdate>("observer");
    {
        std::shared_ptr<ObserverNameOnUpdate>observer2 = std::make_shared<ObserverNameOnUpdate>("observer2");
        subject.add_observer(observer);
        subject.notify();
        std::cout<<"------------------"<<std::endl;
        subject.add_observer(observer2);
        subject.notify();
        std::cout<<"------------------"<<std::endl;
        subject.remove_observer(observer);
        subject.notify();
        std::cout<<"------------------"<<std::endl;
    }
    subject.notify();
    std::cout<<"------------------"<<std::endl;
}

int main(int argc, char *argv[])
{
    test_subscribing();
    test_update();
}
