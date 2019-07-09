#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Acf/ComponentBase.hpp"
#include "Arp/System/Acf/IApplication.hpp"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "$(template.files.programProvider.format.include)"
#include "$(root.template.files.library.name)"
#include "Arp/Plc/Commons/Meta/MetaLibraryBase.hpp"
#include "Arp/System/Commons/Logging.h"

$(namespace.format.start)

using namespace Arp;
using namespace Arp::System::Acf;
using namespace Arp::Plc::Commons::Esm;
using namespace Arp::Plc::Commons::Meta;

//$(settings.AttributePrefix)component
class $(name) : public ComponentBase, public ProgramComponentBase, private Loggable<$(name)>
{
public: // typedefs

public: // construction/destruction
    $(name)(IApplication& application, const String& name);
    virtual ~$(name)() = default;

public: // IComponent operations
    void Initialize() override;
    void LoadConfig() override;
    void SetupConfig() override;
    void ResetConfig() override;

public: // ProgramComponentBase operations
    void RegisterComponentPorts() override;

private: // methods
    $(name)(const $(name)& arg) = delete;
    $(name)& operator= (const $(name)& arg) = delete;

public: // static factory operations
    static IComponent::Ptr Create(Arp::System::Acf::IApplication& application, const String& name);

private: // fields
    $(name)ProgramProvider programProvider;

public: /* Ports
           =====
           Component ports are defined in the following way:
           //#port
           //#name(NameOfPort)
           boolean portField;

           The name comment defines the name of the port and is optional. Default is the name of the field.
           Attributes which are defined for a component port are IGNORED. If component ports with attributes
           are necessary, define a single structure port where attributes can be defined foreach field of the
           structure.
        */
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class $(name)
inline $(name)::$(name)(IApplication& application, const String& name)
: ComponentBase(application, ::$(root.namespace.format.cppFullName)::$(root.name.format.lastNamespacePart.format.escapeProjectName)Library::GetInstance(), name, ComponentCategory::Custom)
, programProvider(*this)
, ProgramComponentBase(::$(root.namespace.format.cppFullName)::$(root.name.format.lastNamespacePart.format.escapeProjectName)Library::GetInstance().GetNamespace(), programProvider)
{
}

inline IComponent::Ptr $(name)::Create(Arp::System::Acf::IApplication& application, const String& name)
{
    return IComponent::Ptr(new $(name)(application, name));
}

$(namespace.format.end) // end of namespace $(namespace)
