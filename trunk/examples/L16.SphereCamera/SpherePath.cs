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
		const int MAX_LINE_COUNT = 32000;

		float height;
		List<Vector3Df> points = new List<Vector3Df>(); // we use this list only to simplify loading and saving routines
		VertexPrimitive primFront = new VertexPrimitive(MAX_LINE_COUNT * 2, MAX_LINE_COUNT * 2, PrimitiveType.Lines);
		VertexPrimitive primBack = new VertexPrimitive(MAX_LINE_COUNT * 2, MAX_LINE_COUNT * 2, PrimitiveType.Lines);
		int primUsed = 0;

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

			// init all at once indices here
			System.Diagnostics.Debug.Assert(primFront.IndexCount == primBack.IndexCount);
			for (int i = 0; i < primFront.IndexCount; i++)
			{
				primFront.SetIndex(i, i);
				primBack.SetIndex(i, i);
			}
		}

		public void Drop()
		{
			primFront.Drop();
			primBack.Drop();
		}

		public void AddPoint(Vector3Df point)
		{
			points.Add(point);

			// add front line
			Vertex3D v1front = new Vertex3D(point, new Vector3Df(0), new Color(0));
			Vertex3D v2front = new Vertex3D((point - Center).Normalize() * height, new Vector3Df(0), FrontColor);
			primFront.SetVertex(primUsed + 0, v1front);
			primFront.SetVertex(primUsed + 1, v2front);

			// add back line
			Vertex3D v1back = v1front;
			Vertex3D v2back = new Vertex3D(v2front);
			v2back.Color = BackColor;
			primBack.SetVertex(primUsed + 0, v1back);
			primBack.SetVertex(primUsed + 1, v2back);

			primUsed += 2;

			// add connection line if possible (front and back)
			if (primUsed >= 4)
			{
				primFront.SetVertex(primUsed + 0, primFront.GetVertex(primUsed - 3));
				primFront.SetVertex(primUsed + 1, v2front);

				primBack.SetVertex(primUsed + 0, primBack.GetVertex(primUsed - 3));
				primBack.SetVertex(primUsed + 1, v2back);

				primUsed += 2;
			}
		}

		public void Clear()
		{
			points.Clear();
			primUsed = 0;
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
			primBack.Draw(driver, primUsed / 2);

			// draw front lines
			m.ZBuffer = ComparisonFunc.LessEqual;
			driver.SetMaterial(m);
			primFront.Draw(driver, primUsed / 2);

			// draw front points
			m.Thickness = 10;
			driver.SetMaterial(m);
			primFront.Draw(driver, primUsed, PrimitiveType.Points);
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
