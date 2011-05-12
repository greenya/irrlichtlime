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

			string[] l = Directory.GetFiles("../../media", "*particle*", SearchOption.TopDirectoryOnly);
			foreach (string f in l)
				addImageToParticleList(f, false);

			if (listBoxParticleList.Items.Count > 0)
				listBoxParticleList.SelectedIndex = 0;
		}

		private void addImageToParticleList(string f, bool makeThisImageSelected)
		{
			Image i = new Bitmap(f);

			ParticleInfo p = new ParticleInfo();
			p.FileName = f;
			p.Preview = i.GetThumbnailImage(128, 128, null, IntPtr.Zero);
			p.DisplayName = Path.GetFileName(f) + " (" + i.Width + "x" + i.Height + ")";

			int s = listBoxParticleList.Items.Add(p);

			if (makeThisImageSelected)
				listBoxParticleList.SelectedIndex = s;
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

		private void buttonBrowseForTexture_Click(object sender, EventArgs e)
		{
			OpenFileDialog f = new OpenFileDialog();
			f.Filter = "Image files (*.bmp;*.jpg;*.png;*.tga)|*.bmp;*.jpg;*.png;*.tga|All files (*.*)|*.*";
			DialogResult r = f.ShowDialog();

			if (r == DialogResult.OK)
				addImageToParticleList(f.FileName, true);
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
			viewport.EnqueueCommand(CommandType.Rate, checkBoxEmitt.Checked ? trackBarRate.Value : 0);
		}

		private void MainForm_Resize(object sender, EventArgs e)
		{
			viewport.EnqueueCommand(CommandType.Resize, new int[3] {
				panelViewport.ClientSize.Width,
				panelViewport.ClientSize.Height,
				checkBoxKeepAspect.Checked ? 1 : 0
			});
		}

		private void trackBarPosition_Scroll(object sender, EventArgs e)
		{
			viewport.EnqueueCommand(CommandType.Position, new float[3] { trackBarPosition.Value, 0, 0 });
		}

		private void trackBarRadius_Scroll(object sender, EventArgs e)
		{
			viewport.EnqueueCommand(CommandType.Radius, (float)trackBarRadius.Value);
		}

		private void trackBarCameraView_Scroll(object sender, EventArgs e)
		{
			viewport.EnqueueCommand(CommandType.CameraView, (float)trackBarCameraView.Value);
		}

		private void trackBarRate_Scroll(object sender, EventArgs e)
		{
			if (checkBoxEmitt.Checked)
				viewport.EnqueueCommand(CommandType.Rate, trackBarRate.Value);
		}

		private void trackBarSize_Scroll(object sender, EventArgs e)
		{
			viewport.EnqueueCommand(CommandType.Size, trackBarSize.Value);
		}

		private void trackBarDirection_Scroll(object sender, EventArgs e)
		{
			viewport.EnqueueCommand(CommandType.Direction, new float[3] {
				trackBarDirectionX.Value / 100.0f,
				trackBarDirectionY.Value / 100.0f,
				trackBarDirectionZ.Value / 100.0f
			});
		}

		private void checkBoxAffectorFadeOut_CheckedChanged(object sender, EventArgs e)
		{
			viewport.EnqueueCommand(CommandType.FadeOut, checkBoxAffectorFadeOut.Checked);
		}

		private void checkBoxAffectorRotation_CheckedChanged(object sender, EventArgs e)
		{
			viewport.EnqueueCommand(CommandType.Rotation, checkBoxAffectorRotation.Checked);
		}

		private void checkBoxAffectorGravity_CheckedChanged(object sender, EventArgs e)
		{
			viewport.EnqueueCommand(CommandType.Gravity, checkBoxAffectorGravity.Checked);
		}
	}
}
