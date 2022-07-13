#include "$(template.files.component.format.include)"
#include "$(root.template.files.library.name)"

$(namespace.format.start)

$(name)::$(name)(IApplication& application, const String& name)
: ComponentBase(application, ::$(root.namespace.format.cppFullName)::$(root.name.format.lastNamespacePart.format.escapeProjectName)Library::GetInstance(), name, ComponentCategory::Custom)
{
}

void $(name)::Initialize()
{
    // subscribe events from the event system (Nm) here
}

void $(name)::SubscribeServices()
{
	// subscribe the services used by this component here
}

void $(name)::LoadSettings(const String& /*settingsPath*/)
{
	// load firmware settings here
}

void $(name)::SetupSettings()
{
	// setup firmware settings here
}

void $(name)::PublishServices()
{
	// publish the services of this component here
}

void $(name)::LoadConfig()
{
    // load project config here
}

void $(name)::SetupConfig()
{
    // setup project config here
}

void $(name)::ResetConfig()
{
    // implement this inverse to SetupConfig() and LoadConfig()
}

void $(name)::Dispose()
{
	// implement this inverse to SetupSettings(), LoadSettings() and Initialize()
}

void $(name)::PowerDown()
{
	// implement this only if data must be retained even on power down event
	// will work only for PLCnext controllers with an "Integrated uninterruptible power supply (UPS)"
	// Available with 2021.6 FW
}

$(namespace.format.end) // end of namespace $(namespace)
