/**
 * Test for observer events pattern in cpp.
 * 
 * Quick protoypeimplementation as proof of concept/test
 * Event type / name is a string
 * TODO: Event parameters ????
 * EventDispatcher Class - holds all the listener functions for an event
 * EventDispatcherCollection - holds a list with different type of events that can be triggered
 * 
 * Author: Kent Tang Charlo
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>

// In order to handle different kinds of parameters there should be a pointer and a class to reconstruct the object in the pointer
// maybe using variable parameters? or templates?
// TODO: later
class EventDispatcher
{
  public:
    void addListener(void (*f)(int));
    void removeListener(void (*f)(int));
    virtual void dispatchEvent(int i);

  private:
    std::vector<void (*)(int)> mListeners;
};

void EventDispatcher::addListener(void (*f)(int))
{
    mListeners.push_back(f);
}

void EventDispatcher::removeListener(void (*f)(int))
{

}

void EventDispatcher::dispatchEvent(int i)
{
    for (std::vector<void (*)(int)>::iterator listener = mListeners.begin(); listener != mListeners.end(); ++listener)
    {
        (*listener)(i);
    }
}

/**
 * This class has a map to name different events
 */
class EventDispatcherCollection
{
  public:
    void addEventListener(std::string eventName, void (*f)(int));
    void dispatchEvent(std::string eventName, int i);

  private:
    std::map<std::string, EventDispatcher> events;
};

void EventDispatcherCollection::addEventListener(std::string eventName, void (*f)(int))
{
    if (events.find(eventName) == events.end())
    {
        // not found, initialize
        events[eventName] = EventDispatcher();
    }
    events[eventName].addListener(f);
}

void EventDispatcherCollection::dispatchEvent(std::string eventName, int i)
{
    if (events.find(eventName) == events.end()) {
        // not found return
        return;
    }

    events[eventName].dispatchEvent(i);
}



int main()
{
    EventDispatcherCollection button;
    auto lambda = [](int i) {
        std::cout << "hello world! " << i << std::endl;

    };

    button.addEventListener("click", [](int i) {
        std::cout << "Button Clicked " << i << std::endl;

    });

    std::cout << "hello world!" << std::endl;

    button.dispatchEvent("click", 5);
    return 0;
}