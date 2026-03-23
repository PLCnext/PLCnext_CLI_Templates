///////////////////////////////////////////////////////////////////////////////
//
//  Copyright Phoenix Contact GmbH & Co. KG
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Arp/Base/Core/Arp.hpp"
#include "Arp/Base/Acf/Commons/IControllerComponent.hpp"
#include "Arp/System/Commons/Logging.h"
#include "Arp/Io/Commons/IoComponentBase.hpp"
#include "Arp/Plc/Domain/Commons/DualDomain.hxx"
#include "Internal/DataExchange.hpp"
#include "Internal/FieldbusData.hpp"
#include "Internal/Settings/FieldbusSettings.hpp"

$(namespace.format.start)

using namespace Arp;
using namespace Arp::Base::Acf::Commons;
using namespace Arp::Io::Commons;
using namespace Arp::Plc::Domain::Commons;

/// <summary>Demo fieldbus component.</summary>
/// <remarks>
/// <para>
/// This example component demonstrates the basic design pattern to implement a basic IO component based on <see cref="IoComponentBase"/>.
/// </para>
/// <para>
/// This component is not connected to an underlying IO driver and therefore transfers no data. In and out data is stored in a byte buffer instead.
/// The buffer layout is defined in project dependent tic files. If the data layout is independet of the current project, the layout should be defined directly
///  in the component and registered with <see cref="DataManager::CreateSystemFrame"/>
/// </para>
/// </remarks>
//$(settings.AttributePrefix)fieldbuscomponent
class $(name) : public IoComponentBase, public IControllerComponent, private Loggable<$(name)>
{
public: // usings
    using Settings = Internal::Settings::FieldbusSettings;
    using FieldbusDomain = DualDomain<Internal::FieldbusData>;
    using DataExchange = Internal::DataExchange;
    
public: // construction/destruction

    $(name)(ILibrary& library, const String& name);
    ~$(name)(void) override = default;

public: // IComponent operations
    void InitializeInternal(void)override;
    void SubscribeServicesInternal(void)override;
    void LoadSettingsInternal(const String& settingsPath)override;
    void SetupSettingsInternal(void)override;
    void PublishServicesInternal(void)override;
    void LoadConfigInternal(void)override;
    void SetupConfigInternal(void)override;
    void ResetConfigInternal(void)override;
    void DisposeInternal(void)override;
    void PowerDownInternal(void)override;
    
public: // IPlcComponent operations
    DcgResultInfo   LoadPlcInternal(bool isChanging)override;
    DcgResultInfo   SetupPlcInternal(bool isChanging, PlcStartKind startKind)override;
    void            StartPlcInternal(PlcStartKind startKind)override;
    void            StopPlcInternal(void)override;
    void            ResetPlcInternal(bool isChanging, bool onError)override;
    void            UnloadPlcInternal(bool isChanging, bool onError)override;

public: // IControllerComponent operations
    void Start(void)override;
    void Stop(void)override;

private: // fields
    Settings        settings;
    FieldbusDomain  domain;
    DataExchange    dataExchange{ this->GetDataManager() };

    // example status variable
    uint32* pStatusVariable{ nullptr };
};

///////////////////////////////////////////////////////////////////////////////
// inline methods of Class FieldbusComponent

$(namespace.format.end) // end of namespace $(namespace)
