# Irrlicht Engine

* Source: https://sourceforge.net/p/irrlicht/code/HEAD/tree/trunk/
* Revision: `5824`

### `IrrCompileConfig.h`

* Enable `_IRR_WCHAR_FILESYSTEM`

### `Irrlicht15.0.vcxproj`

* Advanced / Character Set set to `Use Unicode Character Set`
* VC++ Directories / Include Directories append `;..\..\..\dx9sdk\Include`
* VC++ Directories / Library Directories append `;..\..\..\dx9sdk\Lib\x86` / `;..\..\..\dx9sdk\Lib\x64`
* C/C++ / Code Generation / Runtime Library set to `Multi-threaded Debug DLL` / `Multi-threaded DLL`
