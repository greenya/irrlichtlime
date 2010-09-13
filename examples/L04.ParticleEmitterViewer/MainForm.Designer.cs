namespace L04.ParticleEmitterViewer
{
	partial class MainForm
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.pictureBoxParticlePreview = new System.Windows.Forms.PictureBox();
			this.listBoxParticleList = new System.Windows.Forms.ListBox();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.panelViewport = new System.Windows.Forms.Panel();
			this.groupBox3 = new System.Windows.Forms.GroupBox();
			this.checkBoxAxes = new System.Windows.Forms.CheckBox();
			this.checkBoxPlane = new System.Windows.Forms.CheckBox();
			this.checkBoxEmitt = new System.Windows.Forms.CheckBox();
			this.groupBox1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBoxParticlePreview)).BeginInit();
			this.groupBox2.SuspendLayout();
			this.groupBox3.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.pictureBoxParticlePreview);
			this.groupBox1.Controls.Add(this.listBoxParticleList);
			this.groupBox1.Location = new System.Drawing.Point(12, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(140, 234);
			this.groupBox1.TabIndex = 0;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Particle Texture";
			// 
			// pictureBoxParticlePreview
			// 
			this.pictureBoxParticlePreview.Location = new System.Drawing.Point(6, 19);
			this.pictureBoxParticlePreview.Name = "pictureBoxParticlePreview";
			this.pictureBoxParticlePreview.Size = new System.Drawing.Size(128, 128);
			this.pictureBoxParticlePreview.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
			this.pictureBoxParticlePreview.TabIndex = 1;
			this.pictureBoxParticlePreview.TabStop = false;
			// 
			// listBoxParticleList
			// 
			this.listBoxParticleList.FormattingEnabled = true;
			this.listBoxParticleList.IntegralHeight = false;
			this.listBoxParticleList.Location = new System.Drawing.Point(6, 153);
			this.listBoxParticleList.Name = "listBoxParticleList";
			this.listBoxParticleList.Size = new System.Drawing.Size(128, 75);
			this.listBoxParticleList.TabIndex = 0;
			this.listBoxParticleList.SelectedIndexChanged += new System.EventHandler(this.listBoxParticleList_SelectedIndexChanged);
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.checkBoxPlane);
			this.groupBox2.Controls.Add(this.checkBoxAxes);
			this.groupBox2.Controls.Add(this.panelViewport);
			this.groupBox2.Location = new System.Drawing.Point(158, 12);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(412, 380);
			this.groupBox2.TabIndex = 1;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Viewport";
			// 
			// panelViewport
			// 
			this.panelViewport.Location = new System.Drawing.Point(6, 19);
			this.panelViewport.Name = "panelViewport";
			this.panelViewport.Size = new System.Drawing.Size(400, 300);
			this.panelViewport.TabIndex = 0;
			// 
			// groupBox3
			// 
			this.groupBox3.Controls.Add(this.checkBoxEmitt);
			this.groupBox3.Location = new System.Drawing.Point(576, 12);
			this.groupBox3.Name = "groupBox3";
			this.groupBox3.Size = new System.Drawing.Size(216, 380);
			this.groupBox3.TabIndex = 2;
			this.groupBox3.TabStop = false;
			this.groupBox3.Text = "Emitter";
			// 
			// checkBoxAxes
			// 
			this.checkBoxAxes.AutoSize = true;
			this.checkBoxAxes.Location = new System.Drawing.Point(65, 325);
			this.checkBoxAxes.Name = "checkBoxAxes";
			this.checkBoxAxes.Size = new System.Drawing.Size(49, 17);
			this.checkBoxAxes.TabIndex = 1;
			this.checkBoxAxes.Text = "Axes";
			this.checkBoxAxes.UseVisualStyleBackColor = true;
			this.checkBoxAxes.CheckedChanged += new System.EventHandler(this.checkBoxAxes_CheckedChanged);
			// 
			// checkBoxPlane
			// 
			this.checkBoxPlane.AutoSize = true;
			this.checkBoxPlane.Checked = true;
			this.checkBoxPlane.CheckState = System.Windows.Forms.CheckState.Checked;
			this.checkBoxPlane.Location = new System.Drawing.Point(6, 325);
			this.checkBoxPlane.Name = "checkBoxPlane";
			this.checkBoxPlane.Size = new System.Drawing.Size(53, 17);
			this.checkBoxPlane.TabIndex = 2;
			this.checkBoxPlane.Text = "Plane";
			this.checkBoxPlane.UseVisualStyleBackColor = true;
			this.checkBoxPlane.CheckedChanged += new System.EventHandler(this.checkBoxPlane_CheckedChanged);
			// 
			// checkBoxEmitt
			// 
			this.checkBoxEmitt.AutoSize = true;
			this.checkBoxEmitt.Checked = true;
			this.checkBoxEmitt.CheckState = System.Windows.Forms.CheckState.Checked;
			this.checkBoxEmitt.Location = new System.Drawing.Point(6, 19);
			this.checkBoxEmitt.Name = "checkBoxEmitt";
			this.checkBoxEmitt.Size = new System.Drawing.Size(49, 17);
			this.checkBoxEmitt.TabIndex = 0;
			this.checkBoxEmitt.Text = "Emitt";
			this.checkBoxEmitt.UseVisualStyleBackColor = true;
			this.checkBoxEmitt.CheckedChanged += new System.EventHandler(this.checkBoxEmitt_CheckedChanged);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(804, 404);
			this.Controls.Add(this.groupBox3);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.Name = "MainForm";
			this.Text = "Particle Emitter Viewer - Irrlicht Lime";
			this.Load += new System.EventHandler(this.MainForm_Load);
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainForm_FormClosed);
			this.groupBox1.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.pictureBoxParticlePreview)).EndInit();
			this.groupBox2.ResumeLayout(false);
			this.groupBox2.PerformLayout();
			this.groupBox3.ResumeLayout(false);
			this.groupBox3.PerformLayout();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.GroupBox groupBox1;
		private System.Windows.Forms.PictureBox pictureBoxParticlePreview;
		private System.Windows.Forms.ListBox listBoxParticleList;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.Panel panelViewport;
		private System.Windows.Forms.GroupBox groupBox3;
		private System.Windows.Forms.CheckBox checkBoxAxes;
		private System.Windows.Forms.CheckBox checkBoxPlane;
		private System.Windows.Forms.CheckBox checkBoxEmitt;
	}
}

