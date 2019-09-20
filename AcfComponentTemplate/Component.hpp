#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "$(root.template.files.library.name)"
#include "Arp/Plc/Commons/Meta/MetaComponentBase.hpp"
#include "Arp/System/Commons/Logging.h"

$(namespace.format.start)

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Meta;

//$(settings.AttributePrefix)acfcomponent
class $(name) : public ComponentBase, public MetaComponentBase, private Loggable<$(name)>
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

public: // MetaComponentBase operations
    void RegisterComponentPorts() override;

private: // methods
    $(name)(const $(name)& arg) = delete;
    $(name)& operator= (const $(name)& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& name);

private: // fields

};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class $(name)
inline $(name)::$(name)(IApplication& application, const String& name)
: ComponentBase(application, ::$(root.namespace.format.cppFullName)::$(root.name.format.lastNamespacePart.format.escapeProjectName)Library::GetInstance(), name, ComponentCategory::Custom)
, MetaComponentBase(::$(root.namespace.format.cppFullName)::$(root.name.format.lastNamespacePart.format.escapeProjectName)Library::GetInstance().GetNamespace())
{
}

inline IComponent::Ptr $(name)::Create(Arp::System::Acf::IApplication& application, const String& name)
{
    return IComponent::Ptr(new $(name)(application, name));
}

inline void $(name)::RegisterComponentPorts(){}

$(namespace.format.end) // end of namespace $(namespace)
