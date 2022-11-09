#ifndef SERVICE_REGISTRY_HPP
#define SERVICE_REGISTRY_HPP

#include <any>
#include <map>
#include <memory>

class Service_registry {

  private:
    std::map<std::string, std::any> m_services;

  public:
    template <typename T>
    void add(std::shared_ptr<T> &&service)
    {
        m_services[typeid(T).name()] = service;
    }

    template <typename T>
    std::shared_ptr<T> get()
    {
        return std::any_cast<std::shared_ptr<T>>(m_services[typeid(T).name()]);
    }
};

#endif // SERVICE_REGISTRY_HPP
