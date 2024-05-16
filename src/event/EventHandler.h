#pragma once

#include "Event.h"
#include <unordered_map>
#include <vector>
#include <functional>

class EventHandler {
public:
    using EventCallback = std::function<void(const Event&)>;

    void subscribe(EventType type, const EventCallback& callback) {
        listeners[type].push_back(callback);
    }

    void dispatch(const Event& event) {
        auto it = listeners.find(event.type);
        if (it != listeners.end()) 
            for(const auto& callback : it->second) 
                callback(event);
    }

private:
    std::unordered_map<EventType, std::vector<EventCallback>> listeners;
};