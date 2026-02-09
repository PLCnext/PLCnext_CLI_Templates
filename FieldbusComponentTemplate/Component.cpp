///////////////////////////////////////////////////////////////////////////////
//
//  Copyright Phoenix Contact GmbH & Co. KG
//
///////////////////////////////////////////////////////////////////////////////
#include "$(template.files.component.format.include)"
#include "$(root.template.files.library.name)"
#include "Arp/Plc/Commons/Domain/PlcDomainProxy.hpp"
#include "Arp/Plc/Meta/Commons/Io/VariableRegistry.hpp"
#include "Arp/System/Commons/Xml/XmlConfigDocument.hpp"
#include "Arp/Plc/Meta/Commons/Io/PortDefinition.hpp"
#include "Arp/Io/Commons/DataManager.hpp"
#include "Arp/Io/Commons/Data/BufferInfo.hpp"


$(namespace.format.start)

using namespace Arp;
using namespace Arp::System::Commons::Xml;
using namespace Arp::Plc::Meta::Commons;
using namespace Arp::Plc::Meta::Commons::Io;
using Arp::Io::Commons::Data::BufferInfo;

#pragma region IComponent operations

$(name)::$(name)(ILibrary& library, const String& name)
    : IoComponentBase(dynamic_cast<IoLibraryBase&>(library), name,Endianness::BigEndian)
{
}

void $(name)::InitializeInternal()
{
    this->GetDataManager().RegisterStatusVariable("StatusVariable", DataType::UInt32);
}

void $(name)::SubscribeServicesInternal()
{
    // subscribe the services used by this component here
}

void $(name)::LoadSettingsInternal(const String& settingsPath)
{
    // load firmware settings here
    XmlConfigDocument settingsDoc("FieldbusComponentSettingsDocument", this->settings);
    try
    {
        settingsDoc.Load(settingsPath);
    }
    catch (const XmlException& e)
    {
        throw InvalidConfigException(e.ToString());
    }
}

void $(name)::SetupSettingsInternal()
{
    // setup firmware settings here
}

void $(name)::PublishServicesInternal()
{
    // publish the services of this component here
}

void $(name)::LoadConfigInternal()
{
    // load project config here
}

void $(name)::SetupConfigInternal()
{
    // setup project config here
    this->pStatusVariable = reinterpret_cast<uint32*>(this->GetDataManager().GetStatusVariableAddress("StatusVariable"));
    *this->pStatusVariable = 0;
}

void $(name)::ResetConfigInternal()
{
    // implement this inverse to SetupConfig() and LoadConfig()
    this->pStatusVariable = nullptr;
}

void $(name)::DisposeInternal()
{
    // implement this inverse to SetupSettings(), LoadSettings() and Initialize()
}

void $(name)::PowerDownInternal()
{
    // implement this only if data must be retained even on power down event
}

#pragma endregion

#pragma region IPlcComponent operations

DcgResultInfo $(name)::LoadPlcInternal(bool isChanging)
{
    // add code here which is executed after each project download to reload the Plc config
    // if 'isChanging'==true, a download-changes is in process, otherwise it is a regular downolad after Plc reset
    this->domain.Get(isChanging).LoadTicConfig(this->settings.GetLinksFilePath());

    return DcgResultInfo::CreateEmpty();
}

DcgResultInfo $(name)::SetupPlcInternal(bool isChanging, PlcStartKind /*startKind*/)
{
    // Always register PortDefinitions to current domain independent of download change support. This is necessary because the ports get compared
    // by the Meta system.

#ifdef USE_TIC_CONFIGURATION
    for (const auto& portDefinition : this->domain.Get(isChanging).GetTicConfiguration().GetPortDefinitions())
    {
        this->GetVariableRegistry().AddPort(portDefinition, isChanging);
    }
#else // Use configuration register port definitions (same content as from TIC files)
    PortDefinition demoPortDefinition { "DemoDevice", {},
        {
            {
                "DemoModule1", {}, {
                    { "IN_UINT32", DataType::UInt32, {}, StandardAttribute::Io, {}, "IN", BitSize(0, 0) },
                    { "OUT_UINT32", DataType::UInt32, {}, StandardAttribute::Io, {}, "OUT", BitSize(0, 0) },
                }
            },
            {
                "DemoModule2", {}, {
                    { "IN_UINT8ARRAY", DataType::UInt8, { {4, 0} }, StandardAttribute::Io, {}, "IN", BitSize(6, 0) }
                }
            },
        }
    };
    this->GetVariableRegistry().AddPort(demoPortDefinition, isChanging);
#endif // !USE_TIC_CONFIGURATION

    // add code here which is executed after each project download to setup the Plc using the reloaded config
    // if 'isChanging'==true, a download-changes is in process, otherwise it is a regular downolad after Plc reset

    if(isChanging)
    {
        // TODO: Download Change is not allowed for this demo component:
        // Compare new configuration in background domain with loaded configuration in foreground domain
        // If project configuration changed, this method has to return false to refuse DCg else return true to keep old configuration loaded
        bool equals = (this->domain.Get(false).GetTicConfiguration().GetBufferInfos() == this->domain.Get(true).GetTicConfiguration().GetBufferInfos());
        if (!equals)
        {
            return DcgResultInfo::CreateRefused("Configuration of IO DemoComponent has changed");
        }
    }
    else
    {
        this->dataExchange.CreateIoBuffers(this->domain.Get(isChanging).GetTicConfiguration());
    }

    // TODO: setup project dependendend configuration (in case of normal Download without Download-Changes)
    return DcgResultInfo::CreateEmpty();
}

void $(name)::StartPlcInternal(PlcStartKind /*startKind*/)
{
    // add code here which is executed after each project download when plc is re-started
    // start your threads here accessing any PLCnext components
    *this->pStatusVariable = 1;
}

void $(name)::StopPlcInternal()
{
    // add code here which is executed after each project download when plc is stopped to reload the downloaded config
    // stop your threads here accessing any PLCnext components
    *this->pStatusVariable = 0;
}

void $(name)::ResetPlcInternal(bool isChanging, bool /*onError*/)
{
    // add code here which is executed after each project download to unload the actual Plc config
    // and reloading the new config by LoadPlc() and SetupPlc()
    // implement this inverse to LoadPlc() and SetupPlc()

    if(isChanging)
    {
        return;
    }

    this->dataExchange.ResetIoBuffer();
}

void $(name)::UnloadPlcInternal(bool isChanging, bool /*onError*/)
{
    // add code here which is executed after each project download to unload the actual Plc config
    // and reloading the new config by LoadPlc()
    // implement this inverse to SetupPlc()

    this->domain.Get(isChanging).UnloadTicConfig();
}

#pragma endregion

#pragma region IControllerComponent operations

void $(name)::Start()
{
    // this operations is invoked only during system startup
    this->dataExchange.Start();
}

void $(name)::Stop()
{
    this->dataExchange.Stop();
    // this operations is invoked only during system shutdown
}

#pragma endregion

$(namespace.format.end) // end of namespace $(namespace)
