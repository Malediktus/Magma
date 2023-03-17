#pragma once

#include <Magma/pch.h>

namespace Magma
{
    class Event
    {
    public:
        virtual ~Event() {}
    };

    using EventMap = std::multimap<const std::type_info *, const std::function<void(const Event &)>>;

    class EventDispatcher
    {
    public:
        template <typename T>
        static void Subscribe(const std::function<void(const Event &)> &fn) { m_EventMap.emplace(&typeid(T), fn); }
        static void Post(const Event &event);

    private:
        static EventMap m_EventMap;
    };
}