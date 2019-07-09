#include "$(template.files.component.format.include)"

$(namespace.format.start)

void $(name)::Initialize()
{
    // subscribe events from the event system (Es) here (use Arp::System::Es::EventManager)
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
    // never remove next line
    MetaComponentBase::SetupConfig();

    // setup project config here
}

void $(name)::ResetConfig()
{
    // never remove next line
    MetaComponentBase::ResetConfig();

    // implement this inverse to SetupConfig() and LoadConfig()
}

void $(name)::Dispose()
{
	// implement this inverse to SetupSettings(), LoadSettings() and Initialize()
}

void $(name)::PowerDown()
{
	// implement this only if data must be retained even on power down event
}

$(namespace.format.end) // end of namespace $(namespace)
