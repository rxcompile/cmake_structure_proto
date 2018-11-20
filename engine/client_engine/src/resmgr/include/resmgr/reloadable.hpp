#pragma once
//#include <boost/signals2/signal.hpp>

class IReloadableBase
{
public:
    virtual ~IReloadableBase() = default;

    virtual void requestReload() = 0;
    virtual void reloadDone() = 0;

// scoped for auto disconnect
    //boost::signals2::scoped_connection requestReloadConnection;
    //boost::signals2::scoped_connection reloadDoneConnection;
};

template <typename ResourceType, typename IntermediateStateType>
class IReloadable : public IReloadableBase
{
public:
    virtual IntermediateStateType prepareReload() const = 0;
    virtual void reloadFromData(const IntermediateStateType& state, const ResourceType& data) = 0;
};
