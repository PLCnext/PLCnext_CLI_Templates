#region Copyright
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) Phoenix Contact GmbH & Co KG
//  This software is licensed under Apache-2.0
//
///////////////////////////////////////////////////////////////////////////////
#endregion

using System;
using System.Iec61131Lib;
using System.Runtime.InteropServices;
using Eclr;
using Iec61131.Engineering.Prototypes.Types;
using Iec61131.Engineering.Prototypes.Variables;
using Iec61131.Engineering.Prototypes.Common;
using Iec61131.Engineering.Prototypes.Methods;
using Iec61131.Engineering.Prototypes.Pragmas;

namespace $(namespace)
{
    [Native]
    [Function$(returntype.toupper.format.datatypeattribute)]
    public static class $(name)
    {
        [Execution]
        public static $([if]$(returntype.format.isforcedreturnbyref)||$(returnbyref))void$([else])$(returntype.format.csharpdatatype)$([end-if]) __Process(
            $([if]$(returntype.format.isforcedreturnbyref)||$(returnbyref))[Output] ref $(returntype.format.csharpdatatype) $(name),
            $([end-if])[Input] short IN1,
            [Input, DataType("WORD")] ushort IN2)
        {
            // No implementation in C# part; implement in native method
$([if]$(returntype.format.isforcedreturnbyref.negate)&&$(returnbyref.negate))
            // Just return something to avoid errors from the C# compiler.
            return $(returntype.format.csharpdatatype.format.initvalue);
$([end-if])
        }
    }
}
