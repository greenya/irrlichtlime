using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace L04.ParticleEmitterViewer
{
	enum CommandType
	{
		/// <summary>
		/// Abort request.
		/// Param: N/A
		/// </summary>
		Abort,

		/// <summary>
		/// Axes visibility on/off.
		/// Param: bool
		/// </summary>
		Axes,

		/// <summary>
		/// Plane visibility on/off.
		/// Param: bool
		/// </summary>
		Plane,

		/// <summary>
		/// New particle.
		/// Param: ParticleInfo
		/// </summary>
		Particle,

		/// <summary>
		/// Viewport resize.
		/// Param: int[3] (Width, Height and KeepAspect? (1 == keep))
		/// </summary>
		Resize,

		/// <summary>
		/// Emitter position.
		/// Param: float[3] (X, Y and Z coords)
		/// </summary>
		Position,

		/// <summary>
		/// Emitter radius.
		/// Param: float
		/// </summary>
		Radius,

		/// <summary>
		/// Camera look-at Y coord.
		/// Param: float
		/// </summary>
		CameraView,

		/// <summary>
		/// Particle rate.
		/// Param: int
		/// </summary>
		Rate,

		/// <summary>
		/// Particle size.
		/// Param: int
		/// </summary>
		Size,

		/// <summary>
		/// Particle emitting direction.
		/// Param: float[3] (X, Y and Z coords)
		/// </summary>
		Direction,

		/// <summary>
		/// On/off fade out affector.
		/// Param: bool
		/// </summary>
		FadeOut,

		/// <summary>
		/// On/off rotation affector.
		/// Param: bool
		/// </summary>
		Rotation,

		/// <summary>
		/// On/off gravity affector.
		/// Param: bool
		/// </summary>
		Gravity,
	}

	/// <summary>
	/// Command info for sending to rendering thread.
	/// </summary>
	class Command
	{
		/// <summary>
		/// Type of command.
		/// </summary>
		public CommandType Type;

		/// <summary>
		/// Command parameter.
		/// </summary>
		public object Param;
	}
}
