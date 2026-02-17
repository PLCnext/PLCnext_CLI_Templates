///////////////////////////////////////////////////////////////////////////////
//
//  Copyright Phoenix Contact GmbH & Co. KG
//
///////////////////////////////////////////////////////////////////////////////
#include "$(template.files.library.format.include)"

$([foreach]component[in]related[of-type]basecomponent)
#include "$(component.template.files.component.format.include)"
$([end-foreach])

$(namespace.format.start)

$(name.format.lastNamespacePart.format.escapeProjectName)Library::$(name.format.lastNamespacePart.format.escapeProjectName)Library()
    : IoLibraryBase(ARP_VERSION_BUILT)
    {
#if ARP_ABI_VERSION_MAJOR >= 3 || (ARP_ABI_VERSION_MAJOR >= 2 && ARP_ABI_VERSION_MINOR >= 1)
    this->SetSdkBuildInfo(ARP_VERSION_BUILT, ARP_ABI_VERSION_NAME, ARP_TARGET_IDENTIFIER);
#endif
$([foreach]component[in]related[of-type]basecomponent) 
        this->AddComponentType<::$(component.fullName)>();
$([end-foreach])
    }                                                  

$(name.format.lastNamespacePart.format.escapeProjectName)Library& $(name.format.lastNamespacePart.format.escapeProjectName)Library::GetInstance()
{
    static $(name.format.lastNamespacePart.format.escapeProjectName)Library instance;
    return instance;
}              

$(namespace.format.end) // end of namespace $(namespace)
extern "C" ARP_EXPORT Arp::Base::Acf::Commons::ILibrary& $(name.format.escapeDotProjectName)_MainEntry()
{
    return  $(namespace.format.cppFullName)::$(name.format.lastNamespacePart.format.escapeProjectName)Library::GetInstance();
}                       
