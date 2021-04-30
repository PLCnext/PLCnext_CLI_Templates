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

using namespace Arp::Plc::Commons::Meta;

namespace { // anonymous namespace
$([foreach]struct[in]portAndTypeDefinitionStructs)
$([foreach]chunk[in]struct.fields[split]8)
    void AddFieldDefinitions_$(struct.name)_$(chunk.start)_$(chunk.end)(TypeDefinition& typeDefinition)
    {
$([foreach]field[in]chunk)
        typeDefinition.AddField({ "$(field.name)", offsetof(::$(struct.fullName), $(field.fieldName)), $(field.format.arpDataType), $(field.dataType.format.ctn), sizeof($(field.dataType.fullName)), alignof($(field.dataType.fullName)), { $(field.multiplicity.format.metaDimensions) }, $(field.attributes.format.standardAttributes) });
$([end-foreach])
    }

$([end-foreach])

    void AddFieldDefinitions_$(struct.name)(TypeDefinition& typeDefinition)
    {
$([foreach]chunk[in]struct.fields[split]8)
    AddFieldDefinitions_$(struct.name)_$(chunk.start)_$(chunk.end)(typeDefinition);
$([end-foreach])
    }

    TypeDefinition GetTypeDefinition$(struct.name)()
    {
        TypeDefinition result{ DataType::Struct, $(struct.format.ctn), sizeof(::$(struct.fullName)), alignof(::$(struct.fullName)), $(struct.attributes.format.standardAttributes), {} };
        result.ReserveFields($(struct.fields.count));
        AddFieldDefinitions_$(struct.name)(result);
        return result;
    }
$([end-foreach])

$([foreach]program[in]hierarchy[of-type]program)
$([foreach]chunk[in]program.ports[split]8)
    void AddFieldDefinitions_$(program.name)_$(chunk.start)_$(chunk.end)(TypeDefinition& typeDefinition)
    {
$([foreach]port[in]chunk)
        typeDefinition.AddField({ "$(port.name)", offsetof(::$(program.fullName), $(port.fieldName)), $(port.format.arpDataType), $(port.dataType.format.ctn), sizeof($(port.dataType.fullName)), alignof($(port.dataType.fullName)), { $(port.multiplicity.format.metaDimensions) }, $(port.attributes.format.standardAttributes) });
$([end-foreach])
    }

$([end-foreach])

    void AddFieldDefinitions_$(program.name)(TypeDefinition& typeDefinition)
    {
$([foreach]chunk[in]program.ports[split]8)
    AddFieldDefinitions_$(program.name)_$(chunk.start)_$(chunk.end)(typeDefinition);
$([end-foreach])
    }

    TypeDefinition GetTypeDefinition$(program.name)()
    {
        TypeDefinition result{ DataType::Program, $(program.format.ctn), sizeof(::$(program.fullName)), alignof(::$(program.fullName)), StandardAttribute::None, {} };
        result.ReserveFields($(program.ports.count));
        AddFieldDefinitions_$(program.name)(result);
        return result;
    }
$([end-foreach])
        

} // anonymous namespace


$(namespace.format.start)

    void $(name.format.lastNamespacePart.format.escapeProjectName)Library::InitializeTypeDomain()
    {
$([foreach]struct[in]portAndTypeDefinitionStructs)
        this->typeDomain.AddTypeDefinition(GetTypeDefinition$(struct.name)());
$([end-foreach])

$([foreach]program[in]hierarchy[of-type]program)
        this->typeDomain.AddTypeDefinition(GetTypeDefinition$(program.name)());
$([end-foreach])
    }

$(namespace.format.end) // end of namespace $(namespace)
