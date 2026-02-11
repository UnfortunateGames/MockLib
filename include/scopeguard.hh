#pragma once

class ScopeGuard {
    using function = void (*)();
    public:
        ScopeGuard(function func)
            : func(func) {}
        ~ScopeGuard() {
            func();
        }
        ScopeGuard(ScopeGuard&& other) = delete;
        ScopeGuard(const ScopeGuard& other) = delete;
        ScopeGuard& operator=(ScopeGuard&& other) = delete;
        ScopeGuard& operator=(const ScopeGuard& other) = delete;
    private:
        function func;
};
