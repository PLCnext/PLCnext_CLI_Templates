#pragma once
#include "Arp/System/Core/Arp.h"

$(namespace.format.start)

using namespace Arp;

class $(name)Class
{
public: // typedefs
    typedef std::shared_ptr<$(name)Class> Ptr;

public: // construction/destruction
    /// <summary>Constructs an <see cref="$(name)Class" /> instance.</summary>
    $(name)Class(void) = default;
    /// <summary>Copy constructor.</summary>
    $(name)Class(const $(name)Class& arg) = default;
    /// <summary>Assignment operator.</summary>
    $(name)Class& operator=(const $(name)Class& arg) = default;
    /// <summary>Destructs this instance and frees all resources.</summary>
    ~$(name)Class(void) = default;

public: // operators

public: // static operations

public: // setter/getter operations

public: // operations

protected: // operations

private: // static methods

private: // methods

public: // fields

private: // static fields

};

$(namespace.format.end) // end of namespace $(namespace)