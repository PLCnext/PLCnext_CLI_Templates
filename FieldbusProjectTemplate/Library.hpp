///////////////////////////////////////////////////////////////////////////////
//
//  Copyright Phoenix Contact GmbH & Co. KG
//
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Arp/System/Core/Arp.h"
#include "Arp/Io/Commons/IoLibraryBase.hpp"

$(namespace.format.start)

using Arp::Io::Commons::IoLibraryBase;

class $(name.format.lastNamespacePart.format.escapeProjectName)Library : public IoLibraryBase

{
public: // construction/destruction 
    $(name.format.lastNamespacePart.format.escapeProjectName)Library(void);

public: // static singleton operations
    static $(name.format.lastNamespacePart.format.escapeProjectName)Library& GetInstance();

};

$(namespace.format.end) // end of namespace $(namespace)
