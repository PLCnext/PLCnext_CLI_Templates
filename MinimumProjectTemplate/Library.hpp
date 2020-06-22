#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/System/Core/AppDomain.hpp"
#include "Arp/System/Core/Singleton.hxx"
#include "Arp/System/Core/Library.h"
#include "Arp/System/Acf/LibraryBase.hpp"

$(namespace.format.start)

using namespace Arp;
using namespace Arp::System::Acf;

class $(name.format.lastNamespacePart.format.escapeProjectName)Library : public LibraryBase, public Singleton<$(name.format.lastNamespacePart.format.escapeProjectName)Library>
{
public: // typedefs
    typedef Singleton<$(name.format.lastNamespacePart.format.escapeProjectName)Library> SingletonBase;

public: // construction/destruction
    $(name.format.lastNamespacePart.format.escapeProjectName)Library(AppDomain& appDomain);
    virtual ~$(name.format.lastNamespacePart.format.escapeProjectName)Library() = default;

public: // static operations (called through reflection)
    static void Main(AppDomain& appDomain);

private: // deleted methods
    $(name.format.lastNamespacePart.format.escapeProjectName)Library(const $(name.format.lastNamespacePart.format.escapeProjectName)Library& arg) = delete;
    $(name.format.lastNamespacePart.format.escapeProjectName)Library& operator= (const $(name.format.lastNamespacePart.format.escapeProjectName)Library& arg) = delete;
};

extern "C" ARP_CXX_SYMBOL_EXPORT ILibrary& ArpDynamicLibraryMain(AppDomain& appDomain);

$(namespace.format.end) // end of namespace $(namespace)
