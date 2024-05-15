#pragma once

#include <functional>

template<class... Args>
class UpdateComponent {
public:
    std::function<void(Args...)> update;
};