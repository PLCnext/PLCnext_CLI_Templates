///////////////////////////////////////////////////////////////////////////////
//
//  Copyright Phoenix Contact GmbH & Co. KG
//
///////////////////////////////////////////////////////////////////////////////
#include "Internal/FieldbusData.hpp"
#include "Arp/System/Commons/Io/Path.hpp"
#include "Arp/System/Commons/Io/File.hpp"
#include "Arp/System/Commons/Io/FileSystemInfo.hpp"

$(namespace.format.start)
namespace Internal
{
    using namespace Arp::System::Commons::Io;

    void FieldbusData::LoadTicConfig(const String& linksFilePath)
    {
        if(linksFilePath.IsEmpty())
        {
            log.Error("No links file path defined");
            return;
        }

        if (File::Exists(linksFilePath))
        {
            ticConfigurationPtr->Load(linksFilePath);
        }
    }

    void FieldbusData::UnloadTicConfig(void)
    {
        this->ticConfigurationPtr = std::make_unique<TicConfiguration>();
    }
}    
$(namespace.format.end) // end of namespace $(namespace)

