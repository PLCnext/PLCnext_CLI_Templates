#include "$(template.files.component.format.include)"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"
#include "$(root.template.files.library.name)"

$(namespace.format.start)

$(name)::$(name)(IApplication& application, const String& name)
: ComponentBase(application, ::$(root.namespace.format.cppFullName)::$(root.name.format.lastNamespacePart.format.escapeProjectName)Library::GetInstance(), name, ComponentCategory::Custom)
, programProvider(*this)
, ProgramComponentBase(::$(root.namespace.format.cppFullName)::$(root.name.format.lastNamespacePart.format.escapeProjectName)Library::GetInstance().GetNamespace(), programProvider)
{
}

void $(name)::Initialize()
{
    // never remove next line
    ProgramComponentBase::Initialize();

    // subscribe events from the event system (Nm) here
}

void $(name)::LoadConfig()
{
    // load project config here
}

void $(name)::SetupConfig()
{
    // never remove next line
    ProgramComponentBase::SetupConfig();

    // setup project config here
}

void $(name)::ResetConfig()
{
    // never remove next line
    ProgramComponentBase::ResetConfig();

    // implement this inverse to SetupConfig() and LoadConfig()
}

void $(name)::PowerDown()
{
	// implement this only if data must be retained even on power down event
	// will work only for PLCnext controllers with an "Integrated uninterruptible power supply (UPS)"
	// Available with 2021.6 FW
}

$(namespace.format.end) // end of namespace $(namespace)
