#pragma once

#include <memory>
#include <mutex>

template <typename T>
class Singleton
{
public:
    static T& instance()
    {
        // unsafe to call
        // there should be assert or something like that
        return *pInstance();
    }

    static T * pInstance()
    {
        return s_instance.get();
    }

    template<typename ... Args>
    static void construct(Args&& ... args)
    {
        std::call_once(
            get_once_flag(),
            [](Args&& ... args)
        {
            s_instance = std::make_unique<T>(std::forward<Args>(args) ...);
        }, std::forward<Args>(args) ...);
    }

protected:
    explicit Singleton<T>() {}
    ~Singleton<T>() {}

    Singleton(const Singleton&) = delete;
    const Singleton& operator=(const Singleton&) = delete;

private:
    static inline std::unique_ptr<T> s_instance = {};

    static std::once_flag& get_once_flag()
    {
        static std::once_flag s_once;

        return s_once;
    }
};
