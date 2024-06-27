#include "$(template.files.program.format.include)"
#include "Arp/System/Commons/Logging.h"
#if ARP_ABI_VERSION_MAJOR < 2
#include "Arp/System/Core/ByteConverter.hpp"
#else
#include "Arp/Base/Core/ByteConverter.hpp"
#endif

$(namespace.format.start)
 
void $(name)::Execute()
{
    //implement program 
}

$(namespace.format.end) // end of namespace $(namespace)
