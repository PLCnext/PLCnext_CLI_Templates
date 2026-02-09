///////////////////////////////////////////////////////////////////////////////
//
//  Copyright Phoenix Contact GmbH & Co. KG
//
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Commons/Xml/IXmlSerializable.hpp"

$(namespace.format.start)
namespace Internal
{
    namespace Settings
    {
        using namespace Arp;
        using namespace Arp::System::Commons::Xml;

        class FieldbusSettings : public IXmlSerializable
        {
        public: // typedefs
            using Ptr = FieldbusSettings*;

        public: // construction
            FieldbusSettings(void) = default;

        public: // setter/getter operations
            const String& GetLinksFilePath(void)const;

        public: // operations
            void ReadXml(XmlReader& reader, XmlSerializationContext& context)override;
            void WriteXml(XmlWriter& writer, XmlSerializationContext& context)override;

        private: // fields
            String linksFilePath;
        };

        ///////////////////////////////////////////////////////////////////////////////
        // inline methods of class FieldbusSettings

        inline const String& FieldbusSettings::GetLinksFilePath()const
        {
            return this->linksFilePath;
        }
    }
}    
$(namespace.format.end) // end of namespace $(namespace)
