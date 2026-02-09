///////////////////////////////////////////////////////////////////////////////
//
//  Copyright Phoenix Contact GmbH & Co. KG
//
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Commons/Threading/Mutex.hpp"
#include "Arp/Io/Commons/IoThread.hpp"
#include "Arp/Io/Commons/IoBuffer.hpp"
#include "Arp/Io/Commons/DataManager.hpp"
#include "Arp/Io/Commons/Configuration/TicConfiguration.hpp"
#include <vector>
#include <atomic>
#include <chrono>

#define USE_TIC_CONFIGURATION

$(namespace.format.start)
namespace Internal
{
    using namespace Arp;
    using namespace std::chrono_literals;

    /// <summary>This class manages the data exchange from the Gds to the IO component</summary>
    class DataExchange
    {
    public: // usings
        using IoBuffer = Arp::Io::Commons::IoBuffer;
        using IoThread = Arp::Io::Commons::IoThread;
        using DataManager = Arp::Io::Commons::DataManager;
        using TicConfiguration = Arp::Io::Commons::Configuration::TicConfiguration;
        using Mutex = Arp::System::Commons::Threading::Mutex;

    public: // construction
        explicit DataExchange(DataManager& dataManager);

    public: // operations
        void CreateIoBuffers(const TicConfiguration& ticConfiguration);
        void ResetIoBuffer(void);
        void Start(void);
        void Stop(void);

    private: // methods
        void IoUpdate(void);
        void UpdateH2F(void);
        void UpdateF2H(void);

    private: // fields
        mutable Mutex ioBufferLock;
        DataManager&      dataManager;
        IoThread          updateThread;   // Thread to update the update of the IO Data (IoBuffer <-> IO specific internal buffer)
        std::atomic<bool> updateData{ false };

        // TODO only inlcuded as example, these buffers have to be configured project dependent
        IoBuffer::Ptr inputBufferPtr;
        IoBuffer::Ptr outputBufferPtr;

        // internal buffer to simulate IO fieldbus driver
        std::vector<byte> internalBuffer;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // inline methods of class DataExchange
}
$(namespace.format.end) // end of namespace $(namespace)
