using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace L04.ParticleEmitterViewer
{
	public partial class MainForm : Form
	{
		Viewport viewport;

		public MainForm()
		{
			InitializeComponent();
		}

		private void MainForm_Load(object sender, EventArgs e)
		{
			refreshParticleList();
			initViewport();
		}

		private void initViewport()
		{
			viewport = new Viewport();
			viewport.Start(panelViewport.Handle);
		}

		private void MainForm_FormClosed(object sender, FormClosedEventArgs e)
		{
			viewport.Stop();
		}

		private void refreshParticleList()
		{
			listBoxParticleList.Items.Clear();

			string[] l = Directory.GetFiles("../media", "*particle*", SearchOption.TopDirectoryOnly);
			foreach (string f in l)
			{
				Image i = new Bitmap(f);

				ParticleInfo p = new ParticleInfo();
				p.FileName = f;
				p.Preview = i.GetThumbnailImage(128, 128, null, IntPtr.Zero);
				p.DisplayName = Path.GetFileName(f) + " (" + i.Width + "x" + i.Height + ")";

				listBoxParticleList.Items.Add(p);
			}

			if (listBoxParticleList.Items.Count > 0)
				listBoxParticleList.SelectedIndex = 0;
		}

		private void listBoxParticleList_SelectedIndexChanged(object sender, EventArgs e)
		{
			ParticleInfo p = listBoxParticleList.SelectedItem as ParticleInfo;
			if (p != null)
			{
				if (viewport != null)
					viewport.EnqueueCommand(CommandType.Particle, p);

				pictureBoxParticlePreview.Image = p.Preview;
			}
		}

		private void checkBoxAxes_CheckedChanged(object sender, EventArgs e)
		{
			viewport.EnqueueCommand(CommandType.Axes, checkBoxAxes.Checked);
		}

		private void checkBoxPlane_CheckedChanged(object sender, EventArgs e)
		{
			viewport.EnqueueCommand(CommandType.Plane, checkBoxPlane.Checked);
		}

		private void checkBoxEmitt_CheckedChanged(object sender, EventArgs e)
		{
			viewport.EnqueueCommand(CommandType.Emmit, checkBoxEmitt.Checked);
		}
	}
}
