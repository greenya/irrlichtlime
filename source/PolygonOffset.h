#pragma once

#include "stdafx.h"

using namespace irr;
using namespace video;
using namespace System;

namespace IrrlichtLime {
namespace Video {

	[Obsolete("Deprecated. Will be removed after Irrlicht 1.9.")]
	/// <summary>
	/// Flags for the definition of the polygon offset feature. These flags define whether the offset should be into the screen, or towards the eye.
	/// </summary>
	public enum class PolygonOffset
	{
		/// <summary>
		/// Push pixel towards the far plane, away from the eye.
		/// This is typically used for rendering inner areas.
		/// </summary>
		Back = EPO_BACK,

		/// <summary>
		/// Pull pixels towards the camera.
		/// This is typically used for polygons which should appear on top of other elements, such as decals.
		/// </summary>
		Front = EPO_FRONT
	};

} // end namespace Video
} // end namespace IrrlichtLime
