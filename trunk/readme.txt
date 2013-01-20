==========================================================================
The Irrlicht Lime SDK
==========================================================================

  Irrlicht Lime (or simply "Lime") is a .NET wrapper for Irrlicht Engine.

  Contents:

  1. How to Start
  2. Directory Structure Overview
  3. Release Notes
  4. License
  5. Contact



==========================================================================
1. How to Start
==========================================================================

  To see wrapper in action, go to \bin folder and run couple examples.

  To start developing your own applications, all you need is to add a
  reference on IrrlichtLime.dll to your .NET project. When running your
  application, make sure that IrrlichtLime.dll and Irrlicht.dll are
  placed near your executable.

  Also make sure you have installed Microsoft .NET Framework 4.0.

  If you get FileNotFoundException while running any example, you need
  to install Microsoft Visual C++ 2010 Redistributable Package (x86),
  which can be easily found at http://www.microsoft.com/downloads/.

  Examples in \bin\Release should run just fine; to run examples from
  \bin\Debug you need Visual Studio 2010 installed.



==========================================================================
2. Directory Structure Overview
==========================================================================

  \bin         This is the output directory. When you compile Lime and
               its examples, it fills with binaries.
  \doc         Contains documentation related files.
  \examples    Directory with examples of usage. This examples are ports
               from real Irrlicht Engine SDK examples written on C++.
  \irrlicht    Contains Irrlicht Engine SDK used for compiling Lime.
               It has version.txt file that describes which certain
               version of Irrlicht Engine SDK is used. Sub folders stores
               necessary files: lib, include and dll. dll\Irrlicht.dll
               is copying into \bin folder each time you compile Lime.
  \media       Media resources for the examples.
  \source      Source code of the Irrlicht Lime.



==========================================================================
3. Release Notes
==========================================================================

  Informations about changes can be found in changes.txt.

  Please note that the textures, 3D models and levels are copyright
  by their authors and not covered by the Irrlicht Lime license.



==========================================================================
4. License
==========================================================================

  The license of the Irrlicht Lime is based on the zlib/libpng license.
  Even though this license does not require you to mention that you are
  using the Irrlicht Lime in your product, an acknowledgement would be
  highly appreciated.


  The Irrlicht Lime License
  =========================

  Copyright (C) 2010-2013 Yuriy Grinevich

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgement in the product documentation would
     be appreciated but is not required.

  2. Altered source versions must be clearly marked as such, and must not
     be misrepresented as being the original software.

  3. This notice may not be removed or altered from any source
     distribution.



==========================================================================
5. Contact
==========================================================================

  Email:
  greenya@users.sourceforge.net

  The official homepage:
  http://irrlichtlime.sourceforge.net

  Additional information (discussion thread):
  English: http://irrlicht.sourceforge.net/phpBB2/viewtopic.php?t=38512
  Russian: http://www.irrlicht.ru/forum/viewtopic.php?f=3&t=118

  If you found bug, please sumbit it at:
  http://sourceforge.net/tracker/?atid=1355121&group_id=322499&func=browse

  If you have feature request, please submit it at:
  http://sourceforge.net/tracker/?atid=1355124&group_id=322499&func=browse
