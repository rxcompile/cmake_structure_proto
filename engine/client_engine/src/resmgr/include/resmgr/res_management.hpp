#pragma once

#include "resmgr/factory.hpp"

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <memory>
#include <mutex>
#include <fstream>
#include <filesystem>
#include <vector>
#include <iostream>

// ---------------------------------------------------------------------------------------------------------------------
// Resource management
// ---------------------------------------------------------------------------------------------------------------------

template <typename T>
class FstreamFactory : public Factory<FstreamFactory<T>, T>
{
    friend class Singleton<FstreamFactory>;

protected:
    FstreamFactory()
        : Factory<FstreamFactory, T>()
    {
    }

    explicit FstreamFactory(std::vector<std::string> extensions)
        : Factory<FstreamFactory, T>()
        , m_supportedExtensions(std::move(extensions))
    {
    }


    bool hasValidExtension(std::string_view resource) override
    {
        const auto extension = std::filesystem::path(resource).extension().string();

        return std::find(begin(m_supportedExtensions), end(m_supportedExtensions), extension) != end(
            m_supportedExtensions);
    }

    bool doLoad(std::string_view resource, typename FstreamFactory::ValueType& data) override
    {
        const auto resourcepath = std::string { resource };
        auto file = std::fstream { resourcepath, std::fstream::in | std::fstream::binary };

        if (!file.is_open())
        {
            std::cout << "ERROR: cannot open file!" << resourcepath << "\n";
            return false;
        }
        boost::archive::binary_iarchive ar { file };
        ar >> data;
        return true;
    }

    bool doSave(std::string_view resource, typename FstreamFactory::ValueType& data) override
    {
        const auto resourcepath = std::string { resource };
        auto file = std::fstream { resourcepath, std::fstream::out | std::fstream::binary };

        if (!file.is_open())
        {
            std::cout << "ERROR: cannot open file!" << resourcepath << "\n";
            return false;
        }
        boost::archive::binary_oarchive ar { file };
        ar << data;
        return true;
    }

private:
    std::vector<std::string> m_supportedExtensions;
};
