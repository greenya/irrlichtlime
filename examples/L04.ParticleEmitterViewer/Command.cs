using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace L04.ParticleEmitterViewer
{
	enum CommandType
	{
		Abort,
		Axes,
		Plane,
		Particle,
		Emmit
	}

	class Command
	{
		public CommandType Type;
		public object Param;
	}
}
