#pragma once

#include <vector>
#include "UpdateComponent.h"

template<class ...Args>
class ComponentHandler {
public:
    void add(UpdateComponent<Args...>& c_update) {vc_update.push_back(c_update);}
    
    void update(Args... args) { for(auto& c_update : vc_update) c_update.update(std::forward<Args>(args)...); }

private:
    std::vector<UpdateComponent<Args...>> vc_update;
};