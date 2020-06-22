#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"

$(namespace.format.start)

using namespace Arp;
using namespace Arp::System::Acf;

//$(settings.AttributePrefix)acfcomponent
class $(name) : public ComponentBase
{
public: // typedefs

public: // construction/destruction
    $(name)(IApplication& application, const String& name);
    virtual ~$(name)() = default;

public: // IComponent operations
    void Initialize() override;
    void SubscribeServices()override;
    void LoadSettings(const String& settingsPath)override;
    void SetupSettings()override;
    void PublishServices()override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;
    void Dispose()override;
    void PowerDown()override;

private: // methods
    $(name)(const $(name)& arg) = delete;
    $(name)& operator= (const $(name)& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& name);

private: // fields
};

inline IComponent::Ptr $(name)::Create(Arp::System::Acf::IApplication& application, const String& name)
{
    return IComponent::Ptr(new $(name)(application, name));
}

$(namespace.format.end) // end of namespace $(namespace)
