using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;

using IrrlichtLime.Core;
using IrrlichtLime.Video;
using IrrlichtLime.Scene;

namespace L16.SphereCamera
{
	class SpherePath
	{
		float height;
		List<Vector3Df> points = new List<Vector3Df>(); // we use this list only to simplify loading and saving routines
		VertexBuffer vertFront = VertexBuffer.Create();
		VertexBuffer vertBack = VertexBuffer.Create();
		IndexBuffer indBoth = IndexBuffer.Create(IndexType._16Bit); // same indices for both vertex buffers

		public Vector3Df Center { get; set; }
		public Color FrontColor { get; set; }
		public Color BackColor { get; set; }

		public int PointCount
		{
			get { return points.Count; }
		}

		public SpherePath(float height)
		{
			this.height = height;

			Center = new Vector3Df(0);
			FrontColor = Color.OpaqueCyan;
			BackColor = Color.OpaqueBlue;

			// we allocated once 64000 indices, initialize the sequence and never touch them in future... we will only use SetCount() method to set actual number of used indices
			indBoth.Reallocate(64000);
			for (int i = 0; i < indBoth.AllocatedCount - 1; i++)
				indBoth.Add(i);
		}

		public void Drop()
		{
			vertFront.Drop();
			vertBack.Drop();
			indBoth.Drop();
		}

		public void AddPoint(Vector3Df point)
		{
			points.Add(point);

			// add front line
			Vertex3D v1front = new Vertex3D(point, new Vector3Df(0), new Color(0));
			Vertex3D v2front = new Vertex3D((point - Center).Normalize() * height, new Vector3Df(0), FrontColor);
			vertFront.Add(v1front);
			vertFront.Add(v2front);

			// add back line
			Vertex3D v1back = v1front;
			Vertex3D v2back = new Vertex3D(v2front);
			v2back.Color = BackColor;
			vertBack.Add(v1back);
			vertBack.Add(v2back);

			// add connection line if possible (front and back)
			if (vertFront.Count >= 4)
			{
				vertFront.Add(vertFront.Get(vertFront.Count - 3));
				vertFront.Add(v2front);

				vertBack.Add(vertBack.Get(vertBack.Count - 3));
				vertBack.Add(v2back);
			}

			// update indices "used" count
			indBoth.SetCount(vertFront.Count);
		}

		public void Clear()
		{
			points.Clear();
			vertFront.Clear();
			vertBack.Clear();
			indBoth.SetCount(0); // we don't deallocate indices, we only set "used" count
		}

		public void Draw(VideoDriver driver)
		{
			driver.SetTransform(TransformationState.World, Matrix.Identity);

			// set material
			Material m = Material.IdentityNoLighting;
			m.Wireframe = true;
			m.BackfaceCulling = false;
			m.Type = MaterialType.TransparentVertexAlpha;
			m.ZWrite = false;

			// draw back lines
			m.ZBuffer = ComparisonFunc.Greater;
			driver.SetMaterial(m);
			driver.DrawVertexPrimitiveList(vertBack, indBoth, PrimitiveType.Lines);

			// draw front lines
			m.ZBuffer = ComparisonFunc.LessEqual;
			driver.SetMaterial(m);
			driver.DrawVertexPrimitiveList(vertFront, indBoth, PrimitiveType.Lines);

			// draw front points
			m.Thickness = 10;
			driver.SetMaterial(m);
			driver.DrawVertexPrimitiveList(vertFront, indBoth, PrimitiveType.Points);
		}

		public void Save(string filename)
		{
			XDocument d = new XDocument();
			d.Add(new XElement("path"));

			d.Root.Add(new XElement("center", new XAttribute("x", Center.X), new XAttribute("y", Center.Y), new XAttribute("z", Center.Z)));
			d.Root.Add(new XElement("frontColor", FrontColor.ARGB));
			d.Root.Add(new XElement("backColor", BackColor.ARGB));

			foreach (Vector3Df p in points)
				d.Root.Add(new XElement("point", new XAttribute("x", p.X), new XAttribute("y", p.Y), new XAttribute("z", p.Z)));

			d.Save(filename);
		}

		public void Load(string filename)
		{
			Clear();

			XDocument d = XDocument.Load(filename);

			Center.X = Convert.ToSingle(d.Root.Element("center").Attribute("x").Value);
			Center.Y = Convert.ToSingle(d.Root.Element("center").Attribute("y").Value);
			Center.Z = Convert.ToSingle(d.Root.Element("center").Attribute("z").Value);

			FrontColor.ARGB = Convert.ToUInt32(d.Root.Element("frontColor").Value);
			BackColor.ARGB = Convert.ToUInt32(d.Root.Element("backColor").Value);

			foreach (XElement e in d.Root.Elements("point"))
			{
				Vector3Df p = new Vector3Df(
					Convert.ToSingle(e.Attribute("x").Value),
					Convert.ToSingle(e.Attribute("y").Value),
					Convert.ToSingle(e.Attribute("z").Value));

				AddPoint(p);
			}
		}
	}
}
