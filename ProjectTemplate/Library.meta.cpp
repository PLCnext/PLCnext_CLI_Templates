#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
$([no-duplicate-lines])
$([foreach]program[in]hierarchy[of-type]program)
#include "$(program.template.files.program.format.include)"
$([end-foreach])
$([foreach]struct[in]portAndTypeDefinitionStructs)
#include "$(struct.file.format.include)"
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
$([foreach]struct[in]portAndTypeDefinitionStructs)
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
$([foreach]program[in]hierarchy[of-type]program)
                {   // ProgramDefinition: $(program.fullName)
                    DataType::Program, CTN<$(program.fullName)>(), sizeof(::$(program.fullName)), alignof(::$(program.fullName)), StandardAttribute::None,
                    {
                        // FieldDefinitions:
$([foreach]port[in]program.ports)
                        { "$(port.name)", offsetof(::$(program.fullName), $(port.fieldName)), $(port.format.arpDataType), $(port.dataType.format.ctn), sizeof($(port.dataType.fullName)), alignof($(port.dataType.fullName)), { $(port.multiplicity.format.metaDimensions) }, $(port.attributes.format.standardAttributes) },
$([end-foreach])
                    }
                },
$([end-foreach])
            }
            // End TypeDefinitions
        );
    }

$(namespace.format.end) // end of namespace $(namespace)

