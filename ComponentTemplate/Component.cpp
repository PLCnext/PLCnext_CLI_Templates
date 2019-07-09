#include "$(template.files.component.format.include)"
#include "Arp/Plc/Commons/Esm/ProgramComponentBase.hpp"

$(namespace.format.start)

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

$(namespace.format.end) // end of namespace $(namespace)
