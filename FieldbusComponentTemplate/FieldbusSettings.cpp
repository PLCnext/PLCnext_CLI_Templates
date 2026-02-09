///////////////////////////////////////////////////////////////////////////////
//
//  Copyright Phoenix Contact GmbH & Co. KG
//
///////////////////////////////////////////////////////////////////////////////
#include "Internal/Settings/FieldbusSettings.hpp"

$(namespace.format.start)
namespace Internal
{
    namespace Settings
    {
        using namespace Arp;

        void FieldbusSettings::ReadXml(XmlReader& reader, XmlSerializationContext& context)
        {
            const char* linksFileXmlName = "Links";

            String elementName;
            while (reader.TryReadStartElement(elementName))
            {
                if (elementName == XmlSerializationContext::IncludesXmlName)
                {
                    context.ReadIncludesElement(reader);
                }
                else if (elementName == linksFileXmlName)
                {
                    this->linksFilePath = context.ResolvePath(reader.GetAttributeValue<String>("path"));

                }
                else
                {
                    context.InvalidXmlElementOccurs(reader, elementName);
                    reader.SkipElementContent();
                }
                reader.ReadEndElement();
            }
        }

        void FieldbusSettings::WriteXml(XmlWriter& /*writer*/, XmlSerializationContext& /*context*/)
        {
            throw NotSupportedException("Write of FieldbusSettings not supported");
        }
    }
}    
$(namespace.format.end) // end of namespace $(namespace)