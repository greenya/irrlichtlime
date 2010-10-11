#include "stdafx.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

[assembly:AssemblyTitleAttribute("Irrlicht Lime")];

#if _DEBUG
[assembly:AssemblyDescriptionAttribute("The Irrlicht Lime is a .NET wrapper for the Irrlicht Engine. (DEBUG)")];
#else
[assembly:AssemblyDescriptionAttribute("The Irrlicht Lime is a .NET wrapper for the Irrlicht Engine.")];
#endif

[assembly:AssemblyConfigurationAttribute("")];
[assembly:AssemblyCompanyAttribute("")];
[assembly:AssemblyProductAttribute("Irrlicht Lime")];
[assembly:AssemblyCopyrightAttribute("Copyright (c) Yuriy Grinevich 2010")];
[assembly:AssemblyTrademarkAttribute("")];
[assembly:AssemblyCultureAttribute("")];

[assembly:AssemblyVersionAttribute("0.7.*")];

[assembly:ComVisible(false)];
[assembly:CLSCompliantAttribute(true)];
[assembly:SecurityPermission(SecurityAction::RequestMinimum, UnmanagedCode = true)];