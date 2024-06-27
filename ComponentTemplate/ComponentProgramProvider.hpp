#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Esm/ProgramProviderBase.hpp"

$(namespace.format.start)

using namespace Arp;
using namespace Arp::Plc::Commons::Esm;

//forwards
class $(name);

class $(name)ProgramProvider : public ProgramProviderBase
{

public:   // construction/destruction
    $(name)ProgramProvider($(name)& $(l:name)Arg);
#if ARP_ABI_VERSION_MAJOR < 2
    virtual ~$(name)ProgramProvider() = default;
#endif

public:   // IProgramProvider operations
    IProgram::Ptr CreateProgramInternal(const String& programName, const String& programType) override;

#if ARP_ABI_VERSION_MAJOR < 2
private:   // deleted methods
    $(name)ProgramProvider(const $(name)ProgramProvider& arg) = delete;
    $(name)ProgramProvider& operator=(const $(name)ProgramProvider& arg) = delete;
#endif

private: // fields
    $(name)& $(l:name);
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of class $(name)ProgramProvider

#if ARP_ABI_VERSION_MAJOR < 2
inline $(name)ProgramProvider::$(name)ProgramProvider($(name)& $(l:name)Arg)
    : $(l:name)($(l:name)Arg)
{
}
#endif
$(namespace.format.end) // end of namespace $(namespace)
