#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
$([no-duplicate-lines])
$([foreach]struct[in]portAndTypeInformationStructs)
#include "$(struct.file.format.include)"
$([end-foreach])
$([foreach]enum[in]portEnums)
#include "$(enum.file.format.include)"
$([end-foreach])
#include "$(template.files.library.format.include)"
$([end-no-duplicate-lines])

$(namespace.format.start)

using namespace Arp::Plc::Commons::Meta;
    
    void $(name.format.lastNamespacePart.format.escapeProjectName)Library::InitializeTypeDomain()
    {
        this->typeDomain.AddTypeDefinitions
        (
            // Begin TypeDefinitions
            {
$([foreach]struct[in]portAndTypeInformationStructs)
                {   // TypeDefinition: $(struct.fullName)
                    DataType::Struct, CTN<$(struct.fullName)>(), sizeof(::$(struct.fullName)), alignof(::$(struct.fullName)), $(struct.attributes.format.standardAttributes),
                    {
                        // FieldDefinitions:
$([foreach]field[in]struct.fields)
                        { "$(field.name)", offsetof(::$(struct.fullName), $(field.fieldName)), $(field.format.arpDataType), $(field.dataType.format.ctn), sizeof($(field.dataType.fullName)), alignof($(field.dataType.fullName)), { $(field.multiplicity.format.metaDimensions) }, $(field.attributes.format.standardAttributes) },
$([end-foreach])
                    }
                },
$([end-foreach])
            }
            // End TypeDefinitions
        );
$([foreach]enum[in]portEnums)
        {
            TypeDefinition typeDefinition{DataType::Enum | DataType::$(enum.baseType.name.format.knownDataTypes.format.stringMacroReplace.format.convertStaticString), CTN<$(enum.fullName)>(), sizeof($(enum.fullName)), alignof($(enum.fullName)), $(enum.attributes.format.standardAttributes), {}};
$([foreach]symbol[in]enum.symbols)
            {
                FieldDefinition field{"$(symbol.name)", 0, DataType::Enum | DataType::$(enum.baseType.name.format.knownDataTypes.format.stringMacroReplace.format.convertStaticString), String::Empty, sizeof($(enum.fullName)), alignof($(enum.fullName)), {}, StandardAttribute::None};
                field.GetChildTypeInfo().AddCustomAttribute("Value", static_cast<std::underlying_type<$(enum.fullName)>::type>($(enum.fullName)::$(symbol.name)));
                typeDefinition.AddField(std::move(field));
            }
$([end-foreach])
            typeDomain.AddTypeDefinition(std::move(typeDefinition));
        }
$([end-foreach])
    }

$(namespace.format.end) // end of namespace $(namespace)

