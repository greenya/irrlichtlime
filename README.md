# The Irrlicht Lime SDK version 1.6

The Irrlicht Lime (or simply "Lime") is a .NET wrapper for the [Irrlicht Engine](http://irrlicht.sourceforge.net). It wraps most of the API available in native library, easily allowing you to use 2D/3D graphics in your application, written in C#, VB.NET or other .NET language.

Currently Lime is being develop under Visual Studio 2019 with .NET Framework 4.0. It includes bunch of examples and IntelliSense documentation.

Lime is not a distinct "engine", it is a wrapper with almost the same architecture whitch native Irrlicht Engine has. You do not need to download/compile Irrlicht Engine, as wrapper already has it and ready to be used straight from the box.

#### Table of Contents

* [How to Start](#how-to-start)
* [Directory Structure Overview](#directory-structure-overview)
* [Release Notes](#release-notes)
* [License](#license)
* [Links](#links)

## How to Start

To see wrapper in action, go to `bin` folder and run some examples.

To start developing your own applications, all you need is to add a reference on `IrrlichtLime.dll` to your .NET project.
When running your application, make sure that `IrrlichtLime.dll` and `Irrlicht.dll` are placed near your executable.
Please note `Irrlicht.dll` will not be copied to output folder automatically, as it is native DLL.

The wrapper requires [Microsoft .NET Framework 4.0](https://www.microsoft.com/en-us/download/details.aspx?id=17851) to be installed.
Also if you get `FileNotFoundException` while running any example, you need to install
[Microsoft Visual C++ Redistributable Package](https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads).

The solution file `IrrlichtLime.sln` can be opened using [Visual Studio 2019](https://visualstudio.microsoft.com/vs/)
Community Edition (its free).

## Directory Structure Overview

Directory | Description
--- | ---
`bin` | This is the output directory. When you compile Lime and its examples, it fills with binaries.
`examples` | Directory with examples of usage. The examples starting straight with a number are examples from Irrlicht Engine SDK ported from C++ to C#. Other ones (starting with `L`) are Lime native examples.
`irrlicht` | Contains Irrlicht Engine SDK used for compiling Lime. It has `README.md` file describing which exact version of the Irrlicht Engine SDK is used. Sub folders stores necessary files: `lib`, `include` and `dll`.
`media` | Media resources for the examples.
`source` | Source code of the Irrlicht Lime.

## Release Notes

Informations about changes can be found in `CHANGES.md`.

Please note that the textures, 3D models and levels are copyright by their authors and not covered by the Irrlicht Lime license.

## License

The license of the Irrlicht Lime is based on the zlib/libpng license.
Even though this license does not require you to mention that you are using the Irrlicht Lime in your product,
an acknowledgement would be highly appreciated.

See `LICENSE` file.

## Links

* [Project on GitHub](https://github.com/greenya/irrlichtlime)
* [Issues, bugs, feature requests](https://github.com/greenya/irrlichtlime/issues)
* [Discussion thread on official Irrlicht Engine forum](http://irrlicht.sourceforge.net/forum/viewtopic.php?f=6&t=38512)
* [Playlist on YouTube](https://www.youtube.com/playlist?list=PL6AFEBCA167138B03)
* [Old project on SourceForge](https://sourceforge.net/projects/irrlichtlime/) (with previous releases)
