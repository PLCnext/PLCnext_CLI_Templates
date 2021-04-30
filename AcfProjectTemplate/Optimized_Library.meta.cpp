#include "Arp/System/Core/Arp.h"
#include "Arp/Plc/Commons/Meta/TypeSystem/TypeSystem.h"
$([no-duplicate-lines])
$([foreach]struct[in]portAndTypeDefinitionStructs)
#include "$(struct.file.format.include)"
$([end-foreach])
#include "$(template.files.library.format.include)"
$([end-no-duplicate-lines])

$(namespace.format.start)

using namespace Arp::Plc::Commons::Meta;
    
namespace { // anonymous namespace
$([foreach]struct[in]portAndTypeDefinitionStructs)
$([foreach]chunk[in]struct.fields[split]8)
    void AddFieldDefinitions_$(struct.name)_$(chunk.start)_$(chunk.end)(TypeDefinition& typeDefinition)
    {
$([foreach]field[in]chunk)
        typeDefinition.AddField({ "$(field.name)", offsetof(::$(struct.fullName), $(field.fieldName)), $(field.format.arpDataType), $(field.dataType.format.ctn), sizeof($(field.dataType.fullName)), alignof($(field.dataType.fullName)), { $(field.multiplicity) }, $(field.attributes.format.standardAttributes) });
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
} // anonymous namespace

$(namespace.format.start)

    void $(name.format.lastNamespacePart.format.escapeProjectName)Library::InitializeTypeDomain()
    {
$([foreach]struct[in]portAndTypeDefinitionStructs)
        this->typeDomain.AddTypeDefinition(GetTypeDefinition$(struct.name)());
$([end-foreach])
    }

$(namespace.format.end) // end of namespace $(namespace)

