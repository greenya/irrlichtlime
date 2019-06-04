#include "stdafx.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

[assembly:AssemblyTitleAttribute("Irrlicht Lime")];

#if _DEBUG
#if WIN64
[assembly:AssemblyDescriptionAttribute("The Irrlicht Lime is a .NET wrapper for the Irrlicht Engine. (This is Debug-x64 build.)")];
#else
[assembly:AssemblyDescriptionAttribute("The Irrlicht Lime is a .NET wrapper for the Irrlicht Engine. (This is Debug-x86 build.)")];
#endif
#else
#if WIN64
[assembly:AssemblyDescriptionAttribute("The Irrlicht Lime is a .NET wrapper for the Irrlicht Engine. (This is Release-x64 build.)")];
#else
[assembly:AssemblyDescriptionAttribute("The Irrlicht Lime is a .NET wrapper for the Irrlicht Engine. (This is Release-x86 build.)")];
#endif
#endif

[assembly:AssemblyConfigurationAttribute("")];
[assembly:AssemblyCompanyAttribute("")];
[assembly:AssemblyProductAttribute("Irrlicht Lime")];
[assembly:AssemblyCopyrightAttribute("Copyright (c) Yuriy Grynevych 2010-2019")];
[assembly:AssemblyTrademarkAttribute("")];
[assembly:AssemblyCultureAttribute("")];

[assembly:AssemblyVersionAttribute("1.6")];

[assembly:ComVisible(false)];
[assembly:CLSCompliantAttribute(true)];
