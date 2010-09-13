using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace L04.ParticleEmitterViewer
{
	/// <summary>
	/// Describes particle image file.
	/// </summary>
	class ParticleInfo
	{
		public string DisplayName;
		public string FileName;
		public Image Preview;

		public override string ToString()
		{
			return DisplayName;
		}
	}
}
