///////////////////////////////////////////////////////////////////////////////
//
//  Copyright Phoenix Contact GmbH & Co. KG
//
///////////////////////////////////////////////////////////////////////////////
#include "Internal/DataExchange.hpp"
#include "Arp/System/Commons/Threading/LockGuard.hpp"
#include "Arp/Io/Commons/Data/BufferInfo.hpp"


$(namespace.format.start)
 
namespace Internal
{
    using namespace Arp::Io::Commons;
    using namespace Arp::Io::Commons::Data;
    using Arp::System::Commons::Threading::LockGuard;

    DataExchange::DataExchange(DataManager& dataManager)
        : dataManager(dataManager)
        , updateThread("DemoFieldbusThread", 90, 10ms, 1, make_delegate(this, &DataExchange::IoUpdate))
    {
    }

    void DataExchange::CreateIoBuffers(const TicConfiguration& ticConfiguration)
    {
        // In this example the buffer IN and OUT are hardcoded known to the Firmware. If the count of buffers is project dependent, all frame info objects can be
        // obtained with TicConfiguration::GetBufferInfos().
        // If the layout of the IoBuffer is known at runtime, the BufferInfo objects can be initalized directly without the use of the TicConfiguration as
        // system frames.

#ifdef USE_TIC_CONFIGURATION

        const auto& inBufferInfo = ticConfiguration.GetBufferInfo("IN");
        const auto& outBufferInfo = ticConfiguration.GetBufferInfo("OUT");

#else // Define buffer information by Api (same content as from TIC files)

        constexpr size_t BufferSize { 10 };
        BufferInfo inBufferInfo{ "IN", BufferSize, BufferType::Data, Endianness::BigEndian };
        BufferInfo outBufferInfo{ "OUT", BufferSize, BufferType::Data, Endianness::BigEndian };

#endif // !USE_TIC_CONFIGURATION

        // initialize the internal transfer buffer (only for demonstration)
        size_t bufferSize = std::min(inBufferInfo.GetSize(), outBufferInfo.GetSize());
        this->internalBuffer = std::vector<byte>(bufferSize);

        // Create IOBuffer
        LockGuard lock{ this->ioBufferLock };
        this->inputBufferPtr = this->dataManager.CreatePlcIoBuffer(inBufferInfo, false);
        this->outputBufferPtr = this->dataManager.CreatePlcIoBuffer(outBufferInfo, false);
        this->updateData = true;
    }

    void DataExchange::ResetIoBuffer()
    {
        this->updateData = false;
        LockGuard lock{ this->ioBufferLock };
        this->inputBufferPtr.reset();
        this->outputBufferPtr.reset();
    }

    void DataExchange::Start()
    {
        this->updateThread.Start();
    }

    void DataExchange::Stop()
    {
        this->updateThread.Join();
    }

    void DataExchange::IoUpdate()
    {
        // Update method triggered in example by rate-monotonic based thread (IoThread)
        this->UpdateH2F();
        this->UpdateF2H();
    }

    void DataExchange::UpdateH2F()
    {
        if (this->updateData)
        {
            LockGuard lock{ this->ioBufferLock };
            byte* buffer = nullptr;
            this->outputBufferPtr->BeginRead(buffer);
            if (this->dataManager.IsPlcRunning())
            {
                std::copy_n(buffer, this->internalBuffer.size(), this->internalBuffer.begin());
            }
            else
            {
                // Plc currenlty stopped or in debug mode: set output data to subsitute values
                std::fill_n(buffer, this->internalBuffer.size(), 0_b);
            }
            this->outputBufferPtr->EndRead();
        }
    }

    void DataExchange::UpdateF2H()
    {
        if (this->updateData)
        {
            LockGuard lock{ this->ioBufferLock };
            byte* buffer = nullptr;
            this->inputBufferPtr->BeginWrite(buffer);
            // example IN and OUT buffer layout is equal, therefore data is mirrored
            std::copy(this->internalBuffer.cbegin(), this->internalBuffer.cend(), buffer);
            this->inputBufferPtr->EndWrite();
        }
    }
}
$(namespace.format.end) // end of namespace $(namespace)
