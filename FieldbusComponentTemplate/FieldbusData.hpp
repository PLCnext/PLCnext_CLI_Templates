///////////////////////////////////////////////////////////////////////////////
//
//  Copyright Phoenix Contact GmbH & Co. KG
//
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Commons/Logging.h"
#include "Arp/Plc/Domain/Commons/DomainBase.hpp"
#include "Arp/Io/Commons/Configuration/TicConfiguration.hpp"

$(namespace.format.start)
namespace Internal
{
    using namespace Arp;

    using Arp::Plc::Domain::Commons::DomainBase;

    // TODO: add variables and methods to handle project dependent configuration
    // This class is optional and used for download change (not implemented for fieldbus components)
    class FieldbusData : public DomainBase, private Loggable<FieldbusData>
    {
    public: // usings
        using TicConfiguration = Arp::Io::Commons::Configuration::TicConfiguration;

    public: // construction
        FieldbusData(void) = default;

    public: // setter/getter operations
        const TicConfiguration& GetTicConfiguration(void)const noexcept;

    public: // operations
        void LoadTicConfig(const String& linksFilePath);
        void UnloadTicConfig(void);

    private: // fields
        std::unique_ptr<TicConfiguration> ticConfigurationPtr{ std::make_unique<TicConfiguration>() };
    };

    ///////////////////////////////////////////////////////////////////////////////
    // inline methods of class FieldbusData
    inline const FieldbusData::TicConfiguration& FieldbusData::GetTicConfiguration()const noexcept
    {
        return *this->ticConfigurationPtr;
    }
}
$(namespace.format.end) // end of namespace $(namespace)
