## Changes in 1.6 (23-Jun-2019)

- Updated Irrlicht SDK to trunk r5824.
- Moved to Visual Studio 2019 (Community Edition is free).
- Updated output dir for x86 builds to "Debug-x86" (was "Debug") and "Release-x86" (was "Release").
- Updated AssemblyDescription attribute for IrrlichtLime.dll to state exaclty what build and what platform it is.
- Updated documentation support approach:
    - Removed docs/IrrlchtLime.xml and docs dir
    - IrrlichtLime.xml now generated at build time from source files using XML comments
- Added GetMatrixFast() to Quaternion.
- Added IntersectsWithBox(), IntersectsWithLine() and IsValid; renamed Empty to IsEmpty in AABBox.
- Added zClipFromZero flag to BuildProjectionMatrix*() methods in Matrix.
- Added Size in Rect*.
- Updated Interpolate(), Invert(), Normalize() and RotateBy() in Vector2D*/3D* to return self vector (was new vector).
- Updated GetIntersectionWithLine(), GetIntersectionWithLimitedLine() and GetIntersectionWithPlanes() to return Vector3Df of the intersection and null if none in Plane3Df. Instead of returning bool and having out arg.
- Added TextureCubemapSeamless to VideoDriverFeature.
- Added RotateLeft and RotateRight to KeyAction.
- Renamed MultiRenderTexture to MultiRenderTextures in RenderTarget to match native API.
- Removed deprecated PolygonOffset enum.
- Removed deprecated PolygonOffsetDirection and PolygonOffsetFactor; added PolygonOffsetDepthBias and PolygonOffsetSlopeScale to Material.
- Deprecated B3D_TexturePath, CSM_TexturePath, DMF_TexturePath, LMTS_TexturePath, MY3D_TexturePath and OBJ_TexturePath in SceneParameters.
- Renamed Opaque* to Solid* in Color.
- Fixed camera gravity value in 07.Collision.
- Fixed room specular color in 08.SpecialFX.
- Fixed crash (for Direct3D9) and console error spam (for OpenGL) when don't using high level shaders in 10.Shaders.
- Added BulletSharp.dll files (x86 and x64) version 2.87. Now you can build L11.BulletSharpTest straight from Lime SDK.
- Fixed rare crashes with accessing removed textures in L13.FractalBrowser.
- Added more interactivity to L15.AbstractTrace: ability to show/hide generator; ability to pause/resume trace.
- Fixed Earth rotation with mouse left button in L16.SphereCamera.
- Added showing all bombs when game is lost in L17.Minesweeper.
- Removed 20.ManagedLights, 24.CursorControl and L19.CustomSceneNodeAnimator due to lack of support.
- Removed unused media: d3d8.psh and d3d8.vsh.

## Changes in r538 (final commit on SF)

- Updated Irrlicht SDK to trunk rev. 5538
- Example 24.CursorControl added
- Changes to TexturePainter due to API changes of Irrlicht
- Changes to L01.TexturePainting due to API changes + bug workaround
- GUIFontBitmap class wrapped. Can be cast from GUIFont.
- little Code cleanup:
    - moved VertexArray and IndexArray classes from .cpp to header
    - use copy constructor in NativeIterator to init the ConstIterator
- SceneNode and SceneNodeAnimator: check for user scene node type only, if the type is ESNT_UNKNOWN. This solves SEHExceptions that were sometimes logged
- Many maths functions replaced to calls to new LimeMath class.
- StreamReadFile class added: Allows Irrlicht to read from .NET Streams
    - Updated StreamReadFileNative to work with size_t internally
- Image: CopyToBitmap now only supports R8G8B8 and A8R8G8B8. Others are untested.
    - Also R8G8B8 now works correctly (formerly, it had the wrong byte order)
    - GetData() method added.
- Added Create method to DynamicMeshBuffer
- Added ExistFile to FileSystem
- Added GetTab(int) to GUITabControl
- Wrapped new CollisionHit class and added corresponding methods to SceneCollisionManager
- Wrapped new CreateTriangleSelector methods in SceneManager
- Wrapped new CollisionTriangleRange struct and added corresponding methods to TriangleSelector
- Wrapped OctreeSceneNode
- VideoDriver: added QueryTextureFormat function
- Vector2D: added NearlyParallel and CheckOrientation functions
- TextSceneNode: added GetText, GetColor and Font setting
- SceneManager: GetMesh() now has an extra parameter for cache name
- Quaternion: added GetMatrixFast() function
- MeshBuffer: added PrimitiveType and PrimitiveCount properties
- Matrix: added alternative constructor
- UserEvent now takes two IntPtrs instead of two ints
- CameraFPSSceneNodeAnimator: added RotateSpeedKeyboard property
- BillboardTextSceneNode: added GetText function and Font property
- BillboardSceneNode: added GetTransformedBillboardBoundingBox function

## Changes in 1.5 (05-Mar-2016)

- Updated Irrlicht SDK to trunk rev. 5269
- Added x64 support
- AABBox: Intersect(AABBox^ other) added
- CursorControl: RelativePosition::set(...) removed
- FileArchive: ArchiveName::get() added
- Enum FocusFlag added
- GeometryCreator: AddGeoplaneMesh(...) added 
- GUIButton: SetNormalImage(...) renamed to setImage(...), SetImage(GUIButtonImageState state, ...) added
- Enum GUIButtonImageState added
- Enum GUIButtonState modified: ButtonDisabled added
- GUIColorSelectDialog: properties Color and ColorHSL added
- Enum GUIDefaultSize modified: ButtonPressedSpriteOffsetX and ButtonPressedSpriteOffsetY added
- GUIElement: GetNextElement(..., bool includeDisabled) added
- GUIEnvironment: GetNextElement(...) added
- GUIImage: properties DrawBounds and SourceRect added
- GUISpriteBank: only a comment, will be continued in the future
- IrrlichtDevice: property DoubleClickTime added, WindowSize added
- Matrix: GetRotationDegrees(Vector3Df scale) added
- MeshLoader: property MeshTextureLoader added
- Class MeshTextureLoader added
- ParticleAttractionAffector: property Speed added
- Enum ParticleBehavior added
- ParticleSystemSceneNode: property ParticleBehavior added
- SceneManager: property CurrentRenderPass added
- SceneNodeAnimator: SetEnabled(...) and SetStartTime(...) added, properties Enabled and StartTime added
- Texture: property Source added
- Enum TextureSource added
- Crash with software drivers solved in example 10.Shaders
- Crash with low level shaders in example 10.Shaders solved
- Example 10.Shaders crash with DX9 with CG-Shaders fixed
- SceneNodeAnimator can be inherited
- New Examples: L18.LightningShots and L19.CustomSceneNodeAnimator
- Enum GUIElementType modifier: Profiler added
- GUIEnvironment: AddProfilerDisplay(...) added
- Enum MaterialFlag: BlendFactor added
- SceneNodeAnimator: PostEvent(...) added
- Enum VideoDriverFeature: BlendSeperate added
- Class GUIProfiler added
- GUITable: added properties ActiveFont and OverrideFont
- SceneManager: property LightManager added
- Class LightManager added, can be inherited
- Example 20.ManagedLights added
- GUIListBox: added property VerticalScrollBar
- GUITable: added property VerticalScrollBar, HorizontalScrollBar and ItemHeight
- GUITreeView: added propery VerticalScrollBar and HorizontalScrollBar
- Material: Pack(...), PackSeparate(...), Unpack(...) and UnpackSeparate(...) added
- Enum CursorIcon added
- CursorControl: properties ActiveIcon and SupportedIconSize added
- Custom SceneNodes and SceneNodeAnimators: Dispose is called if available.
- VideoDriver: ushort and uint arrays are passed with pin_ptrs in Draw(2D)VertexPrimitiveList(...)
- Example L11.BulletSharpTest: Thread is reused instead of recreated.
- Example 03.CustomSceneNode: Node shows message when disposed in debug mode.
- Example L19.CustomSceneNodeAnimator: Animator shows message when disposed in debug mode.
- MaterialRendererServices: float and int arrays are passed with pin_ptrs in Set|Vertex/Pixel|ShaderConstant(List)(...)
- Some classes are now structs: Color, Vector3Di/f/d, Vertex3D(TTCoords/Tangents), Line3Df, Triangle3Df, Quaternion
    - Every class and example has been updated to use them correctly, but not all of them have been tested.
- Line3Df: Operator + and - Vector3Df added
- Vector2/3D now inherits IComparable<T>, can be sorted, etc
- Vector2/3D and Quaternion inherit IEquatable<T>, makes comparing consistent
- SceneCollisionManager.GetCollisionPoint() now optionally doesn't return a SceneNode.
- Class ReadFileStream added: Allows .Net like reading from ReadFiles. Can be used with XMLReaders, etc.
- Color: Bug in GetInterpolated solved (wrong channel order)
- SceneManager: CreateFollowSplineAnimator and CreateTextureAnimator now take ICollections instead of Lists
- Material is now IEquatable
- Color is now IEquatable
- Quaternion: static Lerp and Slerp added, virtual Lerp and Slerp now interpolate between "this" and another quaternion (instead of two independent quaternions)
- ViewFrustum: properties BoundingCenter and BoundingRadius added, SetFarNearDistance added
- GUIElement.Children is now a NativeCollection
- GUIProfiler: SetFilters, DrawBackground, Frozen and ShowGroups together added, IgnoreUncalled property rempved
- GUITable.DrawBackground property added
- NativeValue template now overrides the GetHashCode method, so two equal native objects (e.g. Material) return the same hash code
- MeshBuffer:
    - Indices property split up into two methods: GetIndices16Bit and GetIndices32Bit, both return NativeArray<>s
    - Vertices property changed to a generic method, returns a NativeArray<>
    - UpdateIndices and UpdateVertices methods removed
    - GetVertex returns a IVertex3D
    - Append methods aren't generic anymore, old overloadings are back
- ParticleSystemSceneNode.AffectorList returns a NativeCollection now
- ReferenceCounted: now IEquatable, GetHashCode returns the first four bytes of the pointer (so two References to the same object have the same hash)
- SceneNode: AnimatorList and Children properties return NativeCollections now
- NativeArray, NativeCollection and NativeList classes added
- Vector3D/2D: static equals method removed, rewritten Equals(Object^/Vector*D) and CompareTo
- IVertex3D: added Position, Normal, Color and TCoords properties
- Vertex3D(TTCoords/Tangents): implement IVertex3D and IEquatable
- Mesh class split up into Mesh and StaticMesh
- New ColorFormats added
- Image: IsDepthFormat added
- Matrix: GetTextureScale and GetTextureTranslate added
- Mesh: return type of MeshBuffers is now a NativeArray
- MeshManipulator: CreateMeshCopy returns a StaticMesh
- Rect: new constructor added
- VideoDriver: SetRenderTarget overloading added
- Direct3D8 removed, DriverType.Direct3D8 is marked obsolete
- Examples updated
- RenderTarget enum renamed to RenderTargetType
- RenderTarget class added
- MeshType property moved from AnimatedMesh to Mesh
- AnimatedMeshType: 'Static' added
- Material: ZWriteFineControl property added
- VideoDriver: AddRenderTarget, RemoveRenderTarget, RemoveAllRenderTargets and ClearBuffers added. ClearZBuffer marked obsolete.
- GUISpriteBank, GUISprite and GUISpriteFrame classes added
- GUITreeView: ActiveFont and OverrideFont properties added
- Warnings 4238 and 4714 disabled. One of them mentioned that some methods could not be inlined, the other is explained in Lime.h
- MeshWriter class + MeshWriterFlag and MeshWriterType enums added
- Rect: now a struct instead of a class
- SceneManager: CreateMeshWriter(...) method added
- Triangle is now IEquatable
- Vector3Di now has separate implementations for some methods like in native Irrlicht
- CameraMayaSceneNodeAnimator: TargetMinDistance method added
- ClearBufferFlag enum added
- new ColorFormats added
- ContextManager class added
- GUIFileOpenDialog now uses wchar_t instead of path internally
- ImageLoader: LoadImages added
- IrrlichtDevice: ContextManager property added
- MaterialLayer: TextureWrapW property added
- Read-only NativeArray class added (internally)
- RenderTarget: GetTexture() and GetDepthStencil() methods added
- Texture: Type property added
- TextureCreationFlag "AllowMemoryCopy" added
- TextureType enum added
- VideoDriver: AddCubemap, CreateImagesFromFile and setRenderTargetEx added. Added Overloadings to use ClearBufferFlags
- new VideoDriverFeatures added
- WriteFile: Flush method added
- Changed the way setting up ShaderCallBacks:
    - Add*ShaderMaterial now returns a ShaderCallBack, which provides the events and the MaterialType
- CursorControl: AddIcon and ChangeIcon added.
- Examples updated to work with API changes

## Changes in 1.4 (19-May-2013)

- Added examples L16.SphereCamera and L17.Minesweeper.
- Updated Irrlicht SDK to trunk rev. 4527.
- Fixed bug in SceneNode when OnGetMaterial event was not fired when internal getMaterial() was actually called by the Irrlicht.
- Fixed bug when you couldn't actually pass null as string where you might need it (until now it was treated as an empty line, not null). For example now GUIContextMenu.AddItem(null) will add a separator instead of blank menu item.
- Added Intellisense documentation to all members of Scene and GUI namespaces. Now Lime' Intellisence file should contain all wrapped classes and members.
- Extended IndexBuffer and VertexBuffer (added new stuff and renamed old). Added static methods Create() to each class. Added additional overloadings to VideoDriver's DrawVertexPrimitiveList() and Draw2DVertexPrimitiveList() with arguments of VertexBuffer and IndexBuffer.
- Changed assertion check in Draw*VertexPrimitiveList()s, now if count of vertices or indices is zero, the method will do nothing (was assertion failure).
- Changed Texture class: removed GetTexturePainter() method and added Painter prop. Fixed bug when having more than one TexturePainter per Texture may lead to inconsistency with texture lock state.
- Changed argument order in AddTabControl() in GUIEnvironment. Now id follows parent argument (similar to other "add" methods).
- Changed argument timeForceLost, now it has type of uint and assumes milliseconds (was float in seconds) in ParticleSystemSceneNode.CreateGravityAffector() method.
- Added MipMapLevelData to TexturePainter.
- Added CreateClone() to SceneNodeAnimator.
- Added OSOperator to GUIEnvironment.
- Added Edges and Radius props to AABBox.
- Added WindowPosition to IrrlichtDevice and IrrlichtCreationParameters.
- Added checkSubElements argument to GUIEnvironment.Focused().
- Added TrulyVisible to GUIElement.
- Added UpdateMatrices() to CameraSceneNode.
- Added HeightmapOptimizeMesh() to MeshManipulator.
- Added Compressed, MipMaps props and IsCompressedFormat() static method to Image. Added DXT1-5 values to ColorFormat enum.
- Added overloadings for VideoDriver.Draw2DRectangle(), Draw2DRectangleOutline() and Draw3DLine() which takes separate coordinates directly (e.g. x, y and z).
- Added overloading for VideoDriver.Draw2DPolygon() which takes x and y directly.
- Added overloading for VideoDriver.CreateImage() with single texture argument; it uses all the texture to create software image.
- Added overloading for Rect{i|f|d}.IsPointInside() which takes x and y arguments directly.
- Added TextureCompressedDXT value to VideoDriverFeature enum.
- Added LMTS value to AnimatedMeshType enum.

## Changes in 1.3 (20-Jan-2013)

- Added examples L14.Pathfinding and L15.AbstractTrace.
- Updated Irrlicht SDK to trunk rev. 4446.
- MaterialRendererServices changes: added GetPixelShaderConstantID and GetVertexShaderConstantID. Updated methods to take index instead of name. Renamed SetPixelShaderConstant (and "Vertex") which took argument "startRegisterIndex" to SetPixelShaderConstantList (and "Vertex"). Removed SetPixelShaderConstant (and "Vertex") with "bool" argument.
- GUIEditBox changes: added get-set props CursorBlinkTime, CursorChar, DrawBackground and DrawBorder. Removed SetDrawBorder method.
- Added DrawBackground and DrawBorder props to GUICheckBox.
- Added ValidateOn prop to GUISpinBox. Added GUISpinBoxValidation enum.
- Added AddShadowVolumeSceneNode to MeshSceneNode.
- Added BoundingBoxTransformedEdges to SceneNode.
- Added ButtonPressedImageOffsetX, ButtonPressedImageOffsetY, ButtonPressedTextOffsetX and ButtonPressedTextOffsetY to GUIDefaultSize enum.
- Added Disabled to ComparisonFunc enum.

## Changes in 1.2 (21-Aug-2012)

- Added examples L11.BulletSharpTest, L12.StencilShadows and L13.FractalBrowser.
- Updated Irrlicht SDK to trunk rev. 4295.
- MaterialRendererServices changes: renamed SetPixelShaderRegisters() and SetPixelShaderVariable() to SetPixelShaderConstant(); renamed SetVertexShaderRegisters() and SetVertexShaderVariable() to SetVertexShaderConstant(); added 2 more overloadings to Set*ShaderConstant() which takes int array and 2 more overloadings for bool arrays.
- Added "double" versions for common types: Vector2Dd, Vector3Dd, Dimension2Dd and Rectd.
- Replaced SetRotationAxisRadiansLH() and SetRotationAxisRadiansRH() with SetRotationAxisRadians() in Matrix, which assumes left handed rotation.
- Removed assert check for !Locked in Lock() in TexturePainter, since Lock() returns bool, and it is OK to receive "false" and check it at runtime.
- Added Draw2DImageBatch() to VideoDriver.
- Added DeviceContext, RenderingContext, WindowID props and public constructor to ExposedVideoData.
- Added CursorPlatformBehavior enum. Added PlatformBehavior prop to CursorControl.
- Removed SetLoopMode() and added LoopMode prop (getter and setter) to AnimatedMeshSceneNode.
- Added overloading to DrawStencilShadow() which takes single color of the shadow in VideoDriver.
- Added DriverMultithreaded prop to IrrlichtCreationParameters.
- Added useAlphaChannel argument to AddImage() to GUIEnvironment.
- Added Name prop to GUIElement.

## Changes in 1.1 (09-Mar-2012)

- Added example L10.ImageBrowser.
- Updated Irrlicht SDK to trunk rev. 4098.
- Added setter for LightSceneNode.LightData. Changes in Light class: CastShadows, Direction, Position, Radius and Type now can be set.
- Added SceneParameters static class.
- Updated 10.Shaders example: ported usage of Cg shaders. (Note: Lime's Irrlicht.dll currently compiled without Cg support.)
- Added GPUShadingLanguage enum. Added shadingLang argument to AddHighLevelShaderMaterial() and AddHighLevelShaderMaterialFromFiles() to GPUProgrammingServices.
- Updated 09.Meshviewer example: ported bug fix: while modal dialog is open, pressing hot keys lead to unexpected application behavior for the user.
- Added some OEM keys to KeyCode.
- Added CreateForsythOptimizedMesh() to MeshManipulator.
- Added threshold argument to Quaternion.Slerp().
- Added HoveredElement prop to GUIEnvironment.
- Added SetRotationAxisRadiansLH() and SetRotationAxisRadiansRH() to Matrix.
- Added more overloads for AddHighLevelShaderMaterial() and for AddHighLevelShaderMaterialFromFiles() in GPUProgrammingServices.
- Added GetVertex() to MeshBuffer.
- Added DrawMeshBufferNormals() and TextureList prop to VideoDriver.
- Added IdentityRedWireframe static prop to Material.
- Fixed mistype in AddHighLevelShaderMaterial() when it used shader program text as a filename.
- Added Inflate() to Dimension2Di/f, Recti/f. Added Offset() and Adjust() to Recti/f.
- Added handling of OnAnimate event in custom scene node.

## Changes in 1.0 (22-Dec-2011)

- Added example L09.SimpleLOD.
- Updated Irrlicht SDK to trunk rev. 4021.
- Added Clear(), RemoveTab(), InsertTab() and GetTabAt() to GUITabControl. Added DoParticleSystem() to ParticleSystemSceneNode.
- Added props ActiveFont and OverrideFont to GUIButton, GUIEditBox and GUIStaticText.
- SetDrawBackground() and SetDrawBorder() replaced with get-and-set props DrawBackgroundEnabled and DrawBorderEnabled in GUIStaticText.
- Added TextureMatrix value to VideoDriverFeature. Added SceneManager value to SceneNodeType.
- Added OnAnimate protected event to SceneNode.
- Added ability to inherit from GUIElement. Added protected members: OnDraw and OnEvent events; Environment prop.
- Added Randomizer class. Added CreateRandomizer() and prop Randomizer to IrrlichtDevice.
- Added MaxSelectionRows to GUIComboBox.
- Added overloadings to GUIEnvironment.AddFileOpenDialog() with arguments restoreCurrentWorkingDir and startDir.
- SetKeyMap() replaced with get-and-set prop KeyMap in CameraFPSSceneNodeAnimator.
- Image class changes: added GetPixelFormat() and CopyToBitmap(); fixed bug with CopyToScaling(), now it returns byte array and it is correctly filled in; added CopyTo() overloading which returns byte array.
- BillboardSceneNode class chnages: added SetSize(), GetSize(), BottomColor, TopColor, BottomWidth, TopWidth, Height and removed Size prop.
- Added IdentityNoLighting (static get-only prop) to Material.
- Added AnimationSpeed prop to AnimatedMesh.
- Added Distance prop to CameraMayaSceneNodeAnimator.
- Added Vector2Df type support to Attributes.

## Changes in 0.9.1 (30-May-2011)

- Updated Irrlicht SDK to trunk rev. 3767: fixed bug with "blend oparations" which causes all the objects to be transparent under OpenGL renderer.
- Added overloadings to MakePlanarTextureMapping(), RecalculateTangents(), SetVertexColorAlpha() and SetVertexColors() to MeshManipulator.
- Added overloadings to VideoDriver.CreateScreenShot() with color format and render target arguments.
- Added HandleSRGB to IrrlichtCreationParameters.
- Added CreateMeshCopy() to MeshManipulator.

## Changes in 0.9 (19-May-2011)

- Added examples 23.MeshHandling, 26.OcclusionQuery, L06.AnalogueClock, L07.FastStaticRenderin and L08.WPFWindow.
- Updated Irrlicht SDK to trunk rev. 3727: added GetItemAt() to GUIListBox. Added GetSelector() and SelectorCount to TriangleSelector. Added BlendOperation and PolygonOffset to MaterialFlag enum. Added BlendOperations and PolygonOffset to VideoDriverFeature enum. Added BlendOperation, PolygonOffsetDirection and PolygonOffsetFactor to Material. Added VideoDriver.CreateAttributesFromMaterial overloading with AttributeReadWriteOptions argument. Renamed CreateOcclusionQuery to AddOcclusionQuery in VideoDriver.
- Moved to VS2010 and .NET Framework 4.0. Reorganized build process: now building is done into sub folders of the bin folder: Debug and Release (so it is possible to batch build IrrlichtLime).
- Added FeatureList prop to VideoDriver.
- Added ColorHSL class.
- Added enums: AlphaSource, BlendFactor, BlendOperation, ModulateFunc and PolygonOffset. Renamed enum ZBufferCompFunc to ComparisonFunc.
- Added Lerp to Quaternion.
- 12.TerrainRendering updated: now it reacts on 'X' key which toggles debug information.
- Added GetColumnWidth to GUITable.
- Added MeshBuffers (get-only prop) to Mesh. ChildList replaced with Children array (get-only prop) in SceneNode and GUIElement.
- Added Mesh.RemoveMeshBuffer().
- Added Create() (static), AddMeshBuffer() and RecalculateBoundingBox() methods to Mesh.
- Added MeshBuffer.Append() overloadings which handles 32-bit indices. Added MeshBuffer.UpdateIndices() overloading which handles 32-bit indices.
- MeshBuffer changes: 1) added Create() static method; 2) optimized copying of indices from managed to unmanaged buffers in Append() methods.
- DrawVertexPrimitiveList() and Draw2DVertexPrimitiveList() changes: 1) now takes arrays (was Lists); 2) optimized copying of indices from managed to unmanaged buffers.
- Added constructors with transition, rotation and scale vectors to Matrix.
- Added method SetMaterial() to SceneNode and MeshBuffer classes. Added static prop Material.Identity.
- Renamed RemoveAll() to RemoveChildren() in SceneNode.
- Added "==" and "!=" operators to Color/f. Added named colors as static props to Color.
- Added copy constructors to Line3Df, Triangle3Df, Plane3Df and Matrix.
- Added more constructors and Set()s to AABBox.
- Added SetProjectionMatrix() to CameraSceneNode.

## Changes in 0.8 (03-Mar-2011)

- Added examples 19.MouseAndJoystick and L05.ScreenshotToTexture.
- Updated Irrlicht SDK to trunk rev. 3601: added new items to GUIDefaultColor; added MaxAngleDegrees, MaxLifeTime and MinLifeTime to ParticleEmitter; ParticleFadeOutAffector.FadeOutTime now has int type; added AffectorList to ParticleSystemSceneNode. GUIElement.BringToBack renamed to SendToBack. BoneSceneNode.BoneName renamed to Name.
- Added JoystickInfo class. Added ActivateJoysticks() to IrrlichtDevice.
- Added Attributes class and AttributeType enum. Added Attributes prop to VideoDriver and SceneManager.
- Added AttributeReadWriteOptions class and AttributeReadWriteFlag enum.
- Added CreateAttributesFromMaterial() and GetMaterialFromAttributes() to VideoDriver.
- Added SerializeAttributes() and DeserializeAttributes() to AttributeExchangingObject, GUIEnvironment and SceneNode.
- Added CreateAttributes() to FileSystem. FileSystem methods renaming: CreateFileList => CreateFileListFromWorkingDirectory, CreateEmptyFileList => CreateFileList.
- Added class Quaternion.
- Added class ViewFrustum and CameraSceneNode.ViewFrustum prop.
- Added class SceneLoader. Added AddExternalSceneLoader(), GetSceneLoader() and SceneLoaderCount prop to SceneManager.
- Added class MeshLoader. Added AddExternalMeshLoader(), GetMeshLoader() and MeshLoaderCount prop to SceneManager.
- Added ClearParticles() to ParticleSystemSceneNode.
- Added overloadings to SaveScene() and LoadScene() with node argument to SceneManager.
- Added CreateSceneNodeAnimator() to SceneManager.
- Added overloading to SceneCollisionManager.GetScreenCoordinatesFrom3DPosition() with useViewPort argument.
- Added RemoveFont() and renamed ClearFocus() to RemoveFocus() in GUIEnvironment. Added GUIElementType.Root.
- Added class ArchiveLoader. Added AddArchiveLoader(), GetArchiveLoader(), ArchiveLoaderCount and GetRelativeFilename() to FileSystem.
- Added FileSystem.AddFileArchive() overloadings with ReadFile argument.
- Added TextRestrainedInside and RightToLeft props to GUIStaticText; added overloadings to GeometryCreator.CreatePlaneMesh().
- Added enum TextureLockMode.
- Changes in TexturePainter: Lock() now takes TextureLockMode (was "bool readOnly"); ReadOnly prop removed; LockMode prop added.
- GUIImage changes: added props Color and Image (get and set); removed SetColor() and SetImage() methods.
- Added classes CameraFPSSceneNodeAnimator and CameraMayaSceneNodeAnimator.

## Changes in 0.7 (12-Oct-2010)

- Added examples 10.Shaders, L03.RGBSwirl and L04.ParticleEmitterViewer.
- Updated Irrlicht SDK to trunk rev. 3427: added Timer.RealTimeAndDate prop, Timer.RealTimeDate class, Timer.WeekDay enum, IrrlichtCreationParameters.UsePerformanceTimer prop. Also some bugs were fixed (see Irrlicht Engine svn trunk logs for details).
- Added Visual Studio' IntelliSense xml doc file for IrrlichtLime.dll. Currently fully documented next namespaces: IrrlichtLime (root), Core, IO and Video.
- Added methods CopyTo(), CopyToScaling(), CopyToScalingBoxFilter() and CopyToWithAlpha() to Image.
- Added methods UpdateIndices, UpdateVertices, overloading of Append method (operates with arrays of vertices and indices), added get-only props Indicies and Vertices to MeshBuffer.
- Added classes Vertex3DTTCoords and Vertex3DTangents.
- Added correct type solving for all derived classes from ParticleAffector and ParticleEmitter.
- Added method IrrlichtDevice.PostEvent. Added method ResizeNotify to VideoDriver.
- Added enum VideoModeAspectRatio. Added static method GetAspectRatio, property Wide, field AspectRatio to VideoMode.
- Added class OSOperator and prop IrrlichtDevice.OSOperator.
- Added methods LoadGUI and SaveGUI to GUIEnvironment; additional overloading of SaveScene and LoadScene to SceneManager; additional overloading of CreateImage and WriteImage to VideoDriver.
- Added methods CreateLimitReadFile, CreateMemoryReadFile, CreateReadFile, CreateWriteFile and CreateMemoryWriteFile to FileSystem. Added class WriteFile.
- Added class GPUProgrammingServices, enums GeometryShaderType, PixelShaderType and VertexShaderType. Added prop VideoDriver.GPUProgrammingServices. Changed return type of Video.AddMaterialRenderer() to MaterialType (was int).
- Added method ToArray to class Colorf. Method GetElementArray renamed to ToArray in class Matrix. Added copy-constructor to Material.
- Added class Logger. Added prop IrrlichtDevice.Logger.
- Added class MaterialRendererServices.
- Added class SkinnedMesh, enum InterpolationMode. Added method SceneManager.CreateSkinnedMesh.
- Added class ImageLoader. Added prop ImageLoaderCount and method GetImageLoader to VideoDriver.

## Changes in 0.6 (25-Jul-2010)

- Added examples 12.TerrainRendering, 13.RenderToTexture, 15.LoadIrrFile, 18.SplitScreen, L01.TexturePainting and L02.WinFormsWindow.
- Updated Irrlicht SDK to trunk rev. 3368. Added AnimatedMeshType.MDL_HalfLife, FileArchiveType.WAD, FileList.GetFileOffset() and GUIElement.BringToBack().
- Added class GeometryCreator. Added prop SceneManager.GeometryCreator.
- Added class MeshCache and prop SceneManager.MeshCache.
- Added methods LoadHeightMap and LoadHeightMapRAW to TerrainSceneNode.
- Added class ReadFile, method FileArchive.CreateAndOpenFile.
- Added class IrrlichtCreationParameters and proper overloading for method IrrlichtDevice.CreateDevice.
- Class VideoDriver extended with methods Draw2DPolygon, Draw2DRectangleOutline, Draw2DVertexPrimitiveList, DrawStencilShadow, DrawStencilShadowVolume, FindTexture, GetTextureCreationFlag, SetClipPlane; props MaxClipPlanes (static), ColorFormat, MeshManipulator; CreateImageFromFile renamed into CreateImage (additional overloading to CreateImage).
- Added method SetLine to class TexturePainter.
- Added comparison operators ("==" and "!=") to ReferenceCounted.
- Class Matrix improved: added most of methods and operators; added static property Identity.
- Removed class Line2Di.

## Changes in 0.5 (04-Jul-2010)

- Added examples 09.Meshviewer and 11.PerPixelLighting.
- Updated Irrlicht SDK to trunk rev. 3330. Added LogLevel.Debug; GUIEditBox changes: removed method SetOverrideColor; added props OverrideColor, OverrideColorEnabled.
- Added comparison operators ("== " and "!=") to AABBox, Line2Di, Line3Df, Matrix, Plane3Df and Triangle3Df.
- Added class MaterialRenderer. Class VideoDriver extended with methods AddDynamicLight, AddMaterialRenderer, GetDynamicLight, GetMaterialRenderer, GetMaterialRendererName and SetMaterialRendererName.
- Changed usage of "unsigned int" to "int" in classes FileList, FileSystem, Image, IrrlichtDevice, Texture, VideoDriver, AnimatedMesh, AnimatedMeshSceneNode, BoneSceneNode, GUIComboBox, GUIEditBox, GUITable, Mesh, MeshBuffer, MeshManipulator, ParticleEmitter, ParticleSystemSceneNode, SceneNode and VolumeLightSceneNode. Renamed method "GetTextureByIndex" to "GetTexture" in VideoDriver. Changed return type of SceneManager.RegisterNodeForRendering from "uint" to "bool".
- Removed class Dimension2Du; made changes to use Dimension2Di instead.
- Renamed classes Coloru => Color, Matrix4f => Matrix and AABBox3Df => AABBox. Also renamed prop Color.Color => Color.ARGB, method Colorf.ToColoru => Colorf.ToColor.
- Added classes NamedPath and TexturePainter. Class Texture extended with methods GetTexturePainter, RegenerateMipMapLevels; props AlphaChannel, ColorFormat, DriverType, MipMaps, Name, OriginalSize, Pitch, RenderTarget and Size.
- Added ability to compile Lime in Release mode. Added release version of Irrlicht.dll. Made proper changes to proj files. Updated AssemblyInfo' AssemblyDescriptionAttribute to indicate debug build.
- Added class BillboardTextSceneNode. Class SceneManager extended with methods AddArrowMesh, AddBillboardTextSceneNode, AddMeshSceneNode, AddSceneNode, CreateTerrainTriangleSelector, CreateTriangleSelectorFromBoundingBox, GetSceneNodesFromType, IsCulled and PostEvent.
- Added classes DynamicMeshBuffer, IndexBuffer, MetaTriangleSelector, TerrainSceneNode, TextSceneNode, VertexBuffer; enum TerrainPatchSize. Class SceneManager extended with methods AddTerrainSceneNode, AddTextSceneNode and CreateMetaTriangleSelector. Changed type of index-related arguments from "unsigned int" to "int" in TriangleSelector.
- Added class DummyTransformationSceneNode. Added method CreateImageFromFile to VideoDriver. Class SceneManager extended methods AddDummyTransformationSceneNode, AddEmptySceneNode, AddSkyDomeSceneNode, AddSphereMesh, AddTerrainMesh, AddToDeletionQueue, AddVolumeLightMesh, CreateDeleteAnimator, CreateFollowSplineAnimator and CreateNewSceneManager.
- Added classes GUITreeView, GUITreeViewNode. Added methods GUIEnvironment.AddTreeView, GUITable.Get/SetCellData.
- Added enums GUIColumnOrdering, GUIOrderingMode, GUITableDrawFlag; classes GUIImageList, GUISpinBox and GUITable. Class GUIEnvironment extended with methods AddEmptySpriteBank, AddFont, AddGUIElement, AddModalScreen, AddSpinBox, AddTable, Clear, ClearFocus, CreateImageList, CreateSkin, Focused, GetSpriteBank, PostEvent; props FileSystem, Focus, VideoDriver. Added constructors to class Event. Added static props ButtonCount and AxisCount to Event.JoystickEvent. Added class Dimension2Di (currently it is used in GUIImageList.ImageSize only).
- Added classes GUICheckBox, GUIColorSelectDialog, GUIInOutFader and GUIMeshViewer. Added methods AddCheckBox, AddColorSelectDialog, AddInOutFader and AddMeshViewer to GUIEnvironment.
- Added proper class wrapping to SceneNode, now it wraps correct type and can be type-casted safely to more specific XXXSceneNode type.
- Changed type of index values from "unsigned int" to "int" in GUIComboBox, GUIContextMenu, GUIListBox and GUISkin.
- Added classes GUITab, GUITabControl. Added methods AddTab, AddTabControl to GUIEnvironment.
- Added classes GUIComboBox, GUIContextMenu, GUIToolBar; enum GUIContextMenuClose. Class GUIEnvironment extended with methods AddComboBox, AddContextMenu, AddMenu and AddToolBar.
- Added enum FileSystemType. Added classes FileArchive and FileList. Class FileSystem extended with methods CreateEmptyFileList, CreateFileListFromWorkingDirectory, GetFileArchive and SetFileSystemType. Class SceneManager extended with methods AddCameraSceneNodeMaya and AddSkyBoxSceneNode.
- Added enums FogType, GUIMessageBoxFlag and TextureCreationFlag. Added class Fog for holding fog data. Class VideoDriver extended with methods SetMinHardwareBufferVertexCount, SetTextureCreationFlag, TurnLight and WriteImageToFile; prop Fog.
- Added enum GUIMessageBoxFlag, method GUIEnvironment.AddMessageBox. Class GUIElement extended with methods AddChild, BringToFront, Draw, GetNextElement, Move, Remove, RemoveChild, SetAlignment, SetMaxSize, SetMinSize, SetRelativePositionProportional and UpdateAbsolutePosition; props ChildList, Parent, SubElement, TabGroup, TabGroupElement and TypeName.
- Added prop GUIEnvironment.RootElement. Renamed prop SceneManager.RootSceneNode to RootNode. Changed argument order in GUISkin class for methods SetColor, SetText, SetFont, SetIcon, SetSize; added overloading for SetFont with only 1 argument - a font. Updated examples to this changes.

## Changes in 0.4 (19-Jun-2010)

- Added and completly ported examples 07.Collision and 08.SpecialFX.
- Added class VolumeLightSceneNode. Added methods AddVolumeLightSceneNode and CreateTextureAnimator to SceneManager.
- Added classes ParticleMeshEmitter, ParticleRingEmitter, ParticleRotationAffector and ParticleSphereEmitter. Class ParticleSystemSceneNode extended with methods: CreateMeshEmitter, CreatePointEmitter, CreateRingEmitter, CreateRotationAffector, CreateScaleParticleAffector and CreateSphereEmitter.
- Added classes ParticleAnimatedMeshSceneNodeEmitter, ParticleAttractionAffector, ParticleBoxEmitter, ParticleCylinderEmitter, ParticleFadeOutAffector, ParticleGravityAffector. Class ParticleSystemSceneNode extended with methods: CreateAnimatedMeshSceneNodeEmitter, CreateAttractionAffector, CreateBoxEmitter, CreateCylinderEmitter, CreateFadeOutParticleAffector and CreateGravityAffector.
- Added enums BoneAnimationMode, BoneSkinningSpace, CullingType and JointUpdateOnRender. Added class BoneSceneNode. Changed ISceneNode.AutomaticCulling prop: now it operates with CullingType values. Class AnimatedMeshSceneNode extended with methods: AddShadowVolumeSceneNode, AnimateJoints, Clone, GetJointNode, SetJointMode, SetLoopMode, SetRenderFromIdentity, SetTransitionTime and prop JointCount.
- Added class ShadowVolumeSceneNode.
- Updated Irrlicht SDK to trunk rev. 3313.
- Added enums ParticleAffectorType and ParticleEmitterType. Added classes Particle, ParticleAffector, ParticleEmitter and ParticleSystemSceneNode. Added method AddParticleSystemSceneNode to SceneManager.
- Added methods AddHillPlaneMesh and AddWaterSurfaceSceneNode to SceneManager.
- Added enum IndexType. MeshBuffer extended with methods Append, GetNormal, GetPosition, GetTCoords, RecalculateBoundingBox, SetDirty, SetHardwareMappingHint; props BoundingBox, HardwareMappingHintForIndex, HardwareMappingHintForVertex, IndexCount, IndexType, Material, VertexCount, VertexType.
- Added enums HardwareBufferType and HardwareMappingHint. Mesh extended with methods GetMeshBuffer, SetDirty, SetHardwareMappingHint, SetMaterialFlag; props BoundingBox, MeshBufferCount.
- Added class MeshManipulator; added prop SceneManager.MeshManipulator.
- Added overloads to GUIFont.Draw(): now position can be specified as Recti, Vector2Di or two int values (x and y).
- Rect improved; now available int and float versions.
- Dimension2D improved; now available unsigned int and float versions.
- Vector2D improved; now available int and float versions.
- VideoDriver has been extended with new methods: ClearZBuffer, CreateScreenShot, DeleteAllDynamicLights, Draw2DLine, Draw3DBox, Draw3DLine, Draw3DTriangle, DrawMeshBuffer, DrawPixel, EnableClipPlane. Changed argument order of some VideoDriver.DrawXXX methods to be same structured: now color follows at the end (or before clip if present) and it became mandatory.
- Vector3D class has been improved: all native functionality wrapped (including operators). Templates imitation has been implemented and now there are two classes for 3d vectors: Vector3Df and Vector3Di.
- Added class SceneCollisionManager, prop SceneManager.SceneCollisionManager and default constructor to Matrix4f.
- Added class CollisionResponseSceneNodeAnimator and method SceneManager.CreateCollisionResponseAnimator.
- Added classes Line3Df, Plane3Df, Triangle3Df and TriangleSelector; prop SceneNode.TriangleSelector; added methods CreateOctreeTriangleSelector and CreateTriangleSelector to SceneManager.
- Added classes Dimension2Df and BillboardSceneNode; added SceneManager.AddBillboardSceneNode().
- Added enum LightType, classes LightSceneNode, Light and Colorf. Normalized argument list of RGBA values in constructors and Set() methods of Coloru/f classes: for constructors: R, G, B, A = 255 or 1.0f, for Set(): R, G, B, A? (if A not set, than it will not be changed). All the examples updated to this change, since there is no need to specify alpha value all the time now (if its 255).
- Added props AspectRatio, FarValue, FOV, InputReceiverEnabled, NearValue, Orthogonal, ProjectionMatrix, Rotation (setter overridden), Target, TargetAndRotationBinding, UpVector, ViewMatrix and ViewMatrixAffector to CameraSceneNode.

## Changes in 0.3 (05-Jun-2010)

- Added and completly ported examples 05.UserInterface and 06.2DGraphics.
- Changes in IrrlichtDevice class: prop WindowResizable became SetWindowResizable method, prop WindowCaption became SetWindowCaption method (since they both had only setters).
- Added class GUIListBox, enum GUIListBoxColor, method GUIEnvironment.AddListBox.
- Renamed property in GUIElement: "NotClipped" => "Clipped" (the meaning also inverted).
- Added class GUIEditBox. Added method GUIEnvironment.AddEditBox.
- Added class GUIFileOpenDialog. Added method GUIEnvironment.AddFileOpenDialog.
- Added class GUIWindow. Added method GUIEnvironment.AddWindow.
- Made changes in wrapping technique and various classes' ToString() formatting.
- Added class GUIScrollBar. Added method GUIEnvironment.AddScrollBar.
- GUIStaticText extended with methods: SetBackgroundColor, SetDrawBackground, SetDrawBorder, SetTextAlignment; props: OverrideColor, OverrideColorEnabled, OverrideFont, TextHeight, TextWidth, WordWrap.
- Added class GUIButton, enum GUIButtonState, method GUIEnvironment.AddButton.
- Added patch which avoids small bug described at http://irrlicht.sourceforge.net/phpBB2/viewtopic.php?t=38669.
- Added enums GUIAlignment, GUIDefaultColor, GUIDefaultFont, GUIDefaultIcon, GUIDefaultSize, GUIDefaultText, GUIFontType and GUISkinType. Added classes GUIFont, GUISkin and GUISpriteBank. Added to GUIEnvironment: GetFont(), BuiltInFont, Skin. Added IrrlichtDevice.Close().
- Fixed bug when IrrlichtDevice::createDevice() returns null, IrrlichtLime fails.

## Changes in 0.2 (29-May-2010)

- Added and completly ported examples 03.CustomSceneNode and 04.Movement.
- Added classes Event, GUIEvent, MouseEvent, KeyEvent, JoystickEvent, LogEvent, UserEvent. Added enums EventType, GUIEventType, MouseEventType, LogLevel. Added event IrrlichtDevice.OnEvent.
- Added classes VideoModeList, VideoMode; enum DeviceType; IrrlichtDevice extended with methods IsDriverSupported, ClearSystemMessages, MaximizeWindow, MinimizeWindow, RestoreWindow and properties ColorFormat, Type, VideoModeList.
- Added class GUIImage. Added method GUIEnvironment.AddImage.
- Added class Timer. Added property IrrlichtDevice.Timer.
- Added method SetFrameLoop and properties AnimationSpeed, CurrentFrame, EndFrame, Mesh, StartFrame, ReadOnlyMaterials to AnimatedMeshSceneNode.
- Added methods CreateFlyCircleAnimator and CreateFlyStraightAnimator to SceneManager.
- Added methods AddCubeSceneNode and AddSphereSceneNode to SceneManager.
- Added overloading for VideoDriver.DrawVertexPrimitiveList() with 32bit indices.
- Added classes AttributeExchangingObject, ReferenceCounted. All inherited classes from ReferenceCounted got Drop(), Grab(), ReferenceCount and DebugName.
- Added enum PrimitiveType; added VideoDriver.DrawVertexPrimitiveList(), SceneManager.CreateRotationAnimator().
- SceneNode extended, added events OnGetBoundingBox, OnGetMaterialCount, OnGetMaterial, OnRegisterSceneNode.
- Added classes Image, SceneNodeAnimator, MeshBuffer; enums DebugSceneType, RenderTarget. VideoDriver extended with methods AddRenderTargetTexture, AddTexture, CreateOcclusionQuery, GetOcclusionQueryResult, MakeColorKeyTexture, MakeNormalMapTexture, RemoveAllHardwareBuffers, RemoveAllOcclusionQueries, RemoveAllTextures, RemoveHardwareBuffer, RemoveOcclusionQuery, RemoveTexture, RunAllOcclusionQueries, RunOcclusionQuery, SetRenderTarget, UpdateAllOcclusionQueries, UpdateOcclusionQuery. SceneNode extended with methods AddAnimator, GetMaterial, RemoveAnimator, RemoveAnimators, SetMaterialType; properties AbsoluteTransformation, AnimatorList, BoundingBox, BoundingBoxTransformed, ChildList, DebugDataVisible, MaterialCount, RelativeTransformation.
- Added enums ColorFormat, ExposedVideoData, TransformationState, VideoDriverFeature; VideoDriver class extended with methods CheckDriverReset, DisableFeature, GetExposedVideoData, GetTextureByIndex, GetTransform, QueryFeature, RenameTexture, SetMaterial, SetTransform; property TextureCount.
- Added enums SceneNodeRenderPass, SceneNodeAnimatorType; SceneManager extended with methods: Clear, GetSceneNodeFromId, GetSceneNodeFromName, GetSceneNodeFromType, GetAnimatorTypeName, GetSceneNodeTypeName, RegisterNodeForRendering, SaveScene, LoadScene; properties: ActiveCamera, FileSystem, GUIEnvironment, SceneNodeRenderPass, ShadowColor, VideoDriver.
- Added classes Matrix, Material; enums AntiAliasingMode, ColorMaterial, ColorPlane, MaterialType, ZBufferCompFunc.
- Added Vertex3D class; VertexType enum.
- Added AABBox3Df class.
- Added protected constructor for SceneNode. Added SceneNode.OnRender event.
- Added Dimension2Di class.
- Added CursorControl.ReferenceRect property.

## Changes in 0.1 (19-May-2010)

- Added and completly ported examples 01.HelloWorld and 02.Quake3Map.
- Added classes Coloru, Texture and VideoDriver; enums DriverType and MaterialFlag.
- Added classes AnimatedMesh, AnimatedMeshSceneNode, CameraSceneNode, Mesh, MeshSceneNode, SceneManager and SceneNode; enums AnimatedMeshType, AnimationTypeMD2 and SceneNodeType.
- Added class FileSystem and FileArchiveType enum.
- Added classes CursorControl, GUIElement, GUIEnvironment and GUIStaticText; GUIElementType enum.
- Added classes Dimension2Du, Recti, Vector2Df, Vector2Di and Vector3Df.
- Added class KeyMap, enums KeyCode and KeyAction.
- Added class IrrlichtDevice, and its methods: CreateDevice, Drop, Run, Sleep, Yield, GetGammaRamp, SetGammaRamp; properties: CursorControl, FileSystem, FullScreen, GUIEnvironment, SceneManager, Version, VideoDriver, WindowActive, WindowCaption, WindowFocused, WindowMinimized, WindowResizable.
- Added class Lime - wrapper core class.
