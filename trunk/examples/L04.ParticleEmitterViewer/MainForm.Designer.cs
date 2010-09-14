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
			this.label3 = new System.Windows.Forms.Label();
			this.checkBoxPlane = new System.Windows.Forms.CheckBox();
			this.checkBoxAxes = new System.Windows.Forms.CheckBox();
			this.trackBarCameraView = new System.Windows.Forms.TrackBar();
			this.panelViewport = new System.Windows.Forms.Panel();
			this.groupBox3 = new System.Windows.Forms.GroupBox();
			this.label6 = new System.Windows.Forms.Label();
			this.label5 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.trackBarDirectionZ = new System.Windows.Forms.TrackBar();
			this.trackBarDirectionY = new System.Windows.Forms.TrackBar();
			this.trackBarDirectionX = new System.Windows.Forms.TrackBar();
			this.trackBarSize = new System.Windows.Forms.TrackBar();
			this.label1 = new System.Windows.Forms.Label();
			this.trackBarRate = new System.Windows.Forms.TrackBar();
			this.trackBarRadius = new System.Windows.Forms.TrackBar();
			this.trackBarPosition = new System.Windows.Forms.TrackBar();
			this.checkBoxEmitt = new System.Windows.Forms.CheckBox();
			this.groupBox4 = new System.Windows.Forms.GroupBox();
			this.checkBoxAffectorRotation = new System.Windows.Forms.CheckBox();
			this.checkBoxAffectorGravity = new System.Windows.Forms.CheckBox();
			this.checkBoxAffectorFadeOut = new System.Windows.Forms.CheckBox();
			this.checkBoxKeepAspect = new System.Windows.Forms.CheckBox();
			this.label7 = new System.Windows.Forms.Label();
			this.buttonBrowseForTexture = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBoxParticlePreview)).BeginInit();
			this.groupBox2.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBarCameraView)).BeginInit();
			this.groupBox3.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBarDirectionZ)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarDirectionY)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarDirectionX)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarSize)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarRate)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarRadius)).BeginInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarPosition)).BeginInit();
			this.groupBox4.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)));
			this.groupBox1.Controls.Add(this.buttonBrowseForTexture);
			this.groupBox1.Controls.Add(this.label7);
			this.groupBox1.Controls.Add(this.pictureBoxParticlePreview);
			this.groupBox1.Controls.Add(this.listBoxParticleList);
			this.groupBox1.Location = new System.Drawing.Point(12, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(140, 380);
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
			this.listBoxParticleList.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)));
			this.listBoxParticleList.FormattingEnabled = true;
			this.listBoxParticleList.IntegralHeight = false;
			this.listBoxParticleList.Location = new System.Drawing.Point(6, 153);
			this.listBoxParticleList.Name = "listBoxParticleList";
			this.listBoxParticleList.Size = new System.Drawing.Size(128, 80);
			this.listBoxParticleList.TabIndex = 0;
			this.listBoxParticleList.SelectedIndexChanged += new System.EventHandler(this.listBoxParticleList_SelectedIndexChanged);
			// 
			// groupBox2
			// 
			this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox2.Controls.Add(this.label3);
			this.groupBox2.Controls.Add(this.checkBoxPlane);
			this.groupBox2.Controls.Add(this.checkBoxKeepAspect);
			this.groupBox2.Controls.Add(this.checkBoxAxes);
			this.groupBox2.Controls.Add(this.trackBarCameraView);
			this.groupBox2.Controls.Add(this.panelViewport);
			this.groupBox2.Location = new System.Drawing.Point(158, 12);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(412, 380);
			this.groupBox2.TabIndex = 1;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Viewport";
			// 
			// label3
			// 
			this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(141, 332);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(69, 13);
			this.label3.TabIndex = 2;
			this.label3.Text = "Camera View";
			// 
			// checkBoxPlane
			// 
			this.checkBoxPlane.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
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
			// checkBoxAxes
			// 
			this.checkBoxAxes.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.checkBoxAxes.AutoSize = true;
			this.checkBoxAxes.Location = new System.Drawing.Point(65, 325);
			this.checkBoxAxes.Name = "checkBoxAxes";
			this.checkBoxAxes.Size = new System.Drawing.Size(49, 17);
			this.checkBoxAxes.TabIndex = 1;
			this.checkBoxAxes.Text = "Axes";
			this.checkBoxAxes.UseVisualStyleBackColor = true;
			this.checkBoxAxes.CheckedChanged += new System.EventHandler(this.checkBoxAxes_CheckedChanged);
			// 
			// trackBarCameraView
			// 
			this.trackBarCameraView.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.trackBarCameraView.AutoSize = false;
			this.trackBarCameraView.LargeChange = 10;
			this.trackBarCameraView.Location = new System.Drawing.Point(6, 348);
			this.trackBarCameraView.Maximum = 250;
			this.trackBarCameraView.Minimum = -100;
			this.trackBarCameraView.Name = "trackBarCameraView";
			this.trackBarCameraView.Size = new System.Drawing.Size(204, 26);
			this.trackBarCameraView.TabIndex = 1;
			this.trackBarCameraView.TickFrequency = 10;
			this.trackBarCameraView.Value = 80;
			this.trackBarCameraView.Scroll += new System.EventHandler(this.trackBarCameraView_Scroll);
			// 
			// panelViewport
			// 
			this.panelViewport.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
						| System.Windows.Forms.AnchorStyles.Left)
						| System.Windows.Forms.AnchorStyles.Right)));
			this.panelViewport.Location = new System.Drawing.Point(6, 19);
			this.panelViewport.Name = "panelViewport";
			this.panelViewport.Size = new System.Drawing.Size(400, 300);
			this.panelViewport.TabIndex = 0;
			// 
			// groupBox3
			// 
			this.groupBox3.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox3.Controls.Add(this.label6);
			this.groupBox3.Controls.Add(this.label5);
			this.groupBox3.Controls.Add(this.label4);
			this.groupBox3.Controls.Add(this.label2);
			this.groupBox3.Controls.Add(this.trackBarDirectionZ);
			this.groupBox3.Controls.Add(this.trackBarDirectionY);
			this.groupBox3.Controls.Add(this.trackBarDirectionX);
			this.groupBox3.Controls.Add(this.trackBarSize);
			this.groupBox3.Controls.Add(this.label1);
			this.groupBox3.Controls.Add(this.trackBarRate);
			this.groupBox3.Controls.Add(this.trackBarRadius);
			this.groupBox3.Controls.Add(this.trackBarPosition);
			this.groupBox3.Controls.Add(this.checkBoxEmitt);
			this.groupBox3.Location = new System.Drawing.Point(576, 12);
			this.groupBox3.Name = "groupBox3";
			this.groupBox3.Size = new System.Drawing.Size(216, 274);
			this.groupBox3.TabIndex = 2;
			this.groupBox3.TabStop = false;
			this.groupBox3.Text = "Emitter";
			// 
			// label6
			// 
			this.label6.AutoSize = true;
			this.label6.Location = new System.Drawing.Point(6, 223);
			this.label6.Name = "label6";
			this.label6.Size = new System.Drawing.Size(91, 13);
			this.label6.TabIndex = 2;
			this.label6.Text = "Direction (X, Y, Z)";
			// 
			// label5
			// 
			this.label5.AutoSize = true;
			this.label5.Location = new System.Drawing.Point(6, 178);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(27, 13);
			this.label5.TabIndex = 2;
			this.label5.Text = "Size";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(6, 133);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(30, 13);
			this.label4.TabIndex = 2;
			this.label4.Text = "Rate";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(6, 88);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(40, 13);
			this.label2.TabIndex = 2;
			this.label2.Text = "Radius";
			// 
			// trackBarDirectionZ
			// 
			this.trackBarDirectionZ.AutoSize = false;
			this.trackBarDirectionZ.LargeChange = 20;
			this.trackBarDirectionZ.Location = new System.Drawing.Point(148, 239);
			this.trackBarDirectionZ.Maximum = 50;
			this.trackBarDirectionZ.Minimum = -50;
			this.trackBarDirectionZ.Name = "trackBarDirectionZ";
			this.trackBarDirectionZ.Size = new System.Drawing.Size(62, 26);
			this.trackBarDirectionZ.TabIndex = 1;
			this.trackBarDirectionZ.TickFrequency = 10;
			this.trackBarDirectionZ.Scroll += new System.EventHandler(this.trackBarDirection_Scroll);
			// 
			// trackBarDirectionY
			// 
			this.trackBarDirectionY.AutoSize = false;
			this.trackBarDirectionY.LargeChange = 20;
			this.trackBarDirectionY.Location = new System.Drawing.Point(78, 239);
			this.trackBarDirectionY.Maximum = 50;
			this.trackBarDirectionY.Minimum = -50;
			this.trackBarDirectionY.Name = "trackBarDirectionY";
			this.trackBarDirectionY.Size = new System.Drawing.Size(62, 26);
			this.trackBarDirectionY.TabIndex = 1;
			this.trackBarDirectionY.TickFrequency = 10;
			this.trackBarDirectionY.Value = 10;
			this.trackBarDirectionY.Scroll += new System.EventHandler(this.trackBarDirection_Scroll);
			// 
			// trackBarDirectionX
			// 
			this.trackBarDirectionX.AutoSize = false;
			this.trackBarDirectionX.LargeChange = 20;
			this.trackBarDirectionX.Location = new System.Drawing.Point(10, 239);
			this.trackBarDirectionX.Maximum = 50;
			this.trackBarDirectionX.Minimum = -50;
			this.trackBarDirectionX.Name = "trackBarDirectionX";
			this.trackBarDirectionX.Size = new System.Drawing.Size(62, 26);
			this.trackBarDirectionX.TabIndex = 1;
			this.trackBarDirectionX.TickFrequency = 10;
			this.trackBarDirectionX.Scroll += new System.EventHandler(this.trackBarDirection_Scroll);
			// 
			// trackBarSize
			// 
			this.trackBarSize.AutoSize = false;
			this.trackBarSize.LargeChange = 10;
			this.trackBarSize.Location = new System.Drawing.Point(5, 194);
			this.trackBarSize.Maximum = 200;
			this.trackBarSize.Minimum = 5;
			this.trackBarSize.Name = "trackBarSize";
			this.trackBarSize.Size = new System.Drawing.Size(205, 26);
			this.trackBarSize.TabIndex = 1;
			this.trackBarSize.TickFrequency = 10;
			this.trackBarSize.Value = 40;
			this.trackBarSize.Scroll += new System.EventHandler(this.trackBarSize_Scroll);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(7, 43);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(60, 13);
			this.label1.TabIndex = 2;
			this.label1.Text = "Position (X)";
			// 
			// trackBarRate
			// 
			this.trackBarRate.AutoSize = false;
			this.trackBarRate.LargeChange = 100;
			this.trackBarRate.Location = new System.Drawing.Point(5, 149);
			this.trackBarRate.Maximum = 2000;
			this.trackBarRate.Minimum = 50;
			this.trackBarRate.Name = "trackBarRate";
			this.trackBarRate.Size = new System.Drawing.Size(205, 26);
			this.trackBarRate.TabIndex = 1;
			this.trackBarRate.TickFrequency = 50;
			this.trackBarRate.Value = 300;
			this.trackBarRate.Scroll += new System.EventHandler(this.trackBarRate_Scroll);
			// 
			// trackBarRadius
			// 
			this.trackBarRadius.AutoSize = false;
			this.trackBarRadius.LargeChange = 10;
			this.trackBarRadius.Location = new System.Drawing.Point(5, 104);
			this.trackBarRadius.Maximum = 100;
			this.trackBarRadius.Minimum = 1;
			this.trackBarRadius.Name = "trackBarRadius";
			this.trackBarRadius.Size = new System.Drawing.Size(205, 26);
			this.trackBarRadius.TabIndex = 1;
			this.trackBarRadius.TickFrequency = 10;
			this.trackBarRadius.Value = 20;
			this.trackBarRadius.Scroll += new System.EventHandler(this.trackBarRadius_Scroll);
			// 
			// trackBarPosition
			// 
			this.trackBarPosition.AutoSize = false;
			this.trackBarPosition.LargeChange = 10;
			this.trackBarPosition.Location = new System.Drawing.Point(6, 59);
			this.trackBarPosition.Maximum = 100;
			this.trackBarPosition.Minimum = -100;
			this.trackBarPosition.Name = "trackBarPosition";
			this.trackBarPosition.Size = new System.Drawing.Size(204, 26);
			this.trackBarPosition.TabIndex = 1;
			this.trackBarPosition.TickFrequency = 10;
			this.trackBarPosition.Scroll += new System.EventHandler(this.trackBarPosition_Scroll);
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
			// groupBox4
			// 
			this.groupBox4.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
			this.groupBox4.Controls.Add(this.checkBoxAffectorRotation);
			this.groupBox4.Controls.Add(this.checkBoxAffectorGravity);
			this.groupBox4.Controls.Add(this.checkBoxAffectorFadeOut);
			this.groupBox4.Location = new System.Drawing.Point(576, 292);
			this.groupBox4.Name = "groupBox4";
			this.groupBox4.Size = new System.Drawing.Size(216, 100);
			this.groupBox4.TabIndex = 3;
			this.groupBox4.TabStop = false;
			this.groupBox4.Text = "Affectors";
			// 
			// checkBoxAffectorRotation
			// 
			this.checkBoxAffectorRotation.AutoSize = true;
			this.checkBoxAffectorRotation.Checked = true;
			this.checkBoxAffectorRotation.CheckState = System.Windows.Forms.CheckState.Checked;
			this.checkBoxAffectorRotation.Location = new System.Drawing.Point(6, 42);
			this.checkBoxAffectorRotation.Name = "checkBoxAffectorRotation";
			this.checkBoxAffectorRotation.Size = new System.Drawing.Size(66, 17);
			this.checkBoxAffectorRotation.TabIndex = 0;
			this.checkBoxAffectorRotation.Text = "Rotation";
			this.checkBoxAffectorRotation.UseVisualStyleBackColor = true;
			this.checkBoxAffectorRotation.CheckedChanged += new System.EventHandler(this.checkBoxAffectorRotation_CheckedChanged);
			// 
			// checkBoxAffectorGravity
			// 
			this.checkBoxAffectorGravity.AutoSize = true;
			this.checkBoxAffectorGravity.Location = new System.Drawing.Point(6, 65);
			this.checkBoxAffectorGravity.Name = "checkBoxAffectorGravity";
			this.checkBoxAffectorGravity.Size = new System.Drawing.Size(59, 17);
			this.checkBoxAffectorGravity.TabIndex = 0;
			this.checkBoxAffectorGravity.Text = "Gravity";
			this.checkBoxAffectorGravity.UseVisualStyleBackColor = true;
			this.checkBoxAffectorGravity.CheckedChanged += new System.EventHandler(this.checkBoxAffectorGravity_CheckedChanged);
			// 
			// checkBoxAffectorFadeOut
			// 
			this.checkBoxAffectorFadeOut.AutoSize = true;
			this.checkBoxAffectorFadeOut.Checked = true;
			this.checkBoxAffectorFadeOut.CheckState = System.Windows.Forms.CheckState.Checked;
			this.checkBoxAffectorFadeOut.Location = new System.Drawing.Point(6, 19);
			this.checkBoxAffectorFadeOut.Name = "checkBoxAffectorFadeOut";
			this.checkBoxAffectorFadeOut.Size = new System.Drawing.Size(68, 17);
			this.checkBoxAffectorFadeOut.TabIndex = 0;
			this.checkBoxAffectorFadeOut.Text = "Fade out";
			this.checkBoxAffectorFadeOut.UseVisualStyleBackColor = true;
			this.checkBoxAffectorFadeOut.CheckedChanged += new System.EventHandler(this.checkBoxAffectorFadeOut_CheckedChanged);
			// 
			// checkBoxKeepAspect
			// 
			this.checkBoxKeepAspect.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
			this.checkBoxKeepAspect.AutoSize = true;
			this.checkBoxKeepAspect.Checked = true;
			this.checkBoxKeepAspect.CheckState = System.Windows.Forms.CheckState.Checked;
			this.checkBoxKeepAspect.Location = new System.Drawing.Point(297, 325);
			this.checkBoxKeepAspect.Name = "checkBoxKeepAspect";
			this.checkBoxKeepAspect.Size = new System.Drawing.Size(109, 17);
			this.checkBoxKeepAspect.TabIndex = 1;
			this.checkBoxKeepAspect.Text = "Keep aspect ratio";
			this.checkBoxKeepAspect.UseVisualStyleBackColor = true;
			this.checkBoxKeepAspect.CheckedChanged += new System.EventHandler(this.MainForm_Resize);
			// 
			// label7
			// 
			this.label7.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.label7.Enabled = false;
			this.label7.Location = new System.Drawing.Point(6, 236);
			this.label7.Name = "label7";
			this.label7.Size = new System.Drawing.Size(128, 80);
			this.label7.TabIndex = 2;
			this.label7.Text = "Above listed files with the \"particle\" word in its name from \"media\" folder only." +
				" Use button below to add your own texture to the list.";
			this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// buttonBrowseForTexture
			// 
			this.buttonBrowseForTexture.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
			this.buttonBrowseForTexture.Location = new System.Drawing.Point(6, 322);
			this.buttonBrowseForTexture.Name = "buttonBrowseForTexture";
			this.buttonBrowseForTexture.Size = new System.Drawing.Size(128, 52);
			this.buttonBrowseForTexture.TabIndex = 3;
			this.buttonBrowseForTexture.Text = "Browse for own texture...";
			this.buttonBrowseForTexture.UseVisualStyleBackColor = true;
			this.buttonBrowseForTexture.Click += new System.EventHandler(this.buttonBrowseForTexture_Click);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(804, 404);
			this.Controls.Add(this.groupBox4);
			this.Controls.Add(this.groupBox3);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.MinimumSize = new System.Drawing.Size(820, 442);
			this.Name = "MainForm";
			this.Text = "Particle Emitter Viewer - Irrlicht Lime";
			this.Load += new System.EventHandler(this.MainForm_Load);
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MainForm_FormClosed);
			this.Resize += new System.EventHandler(this.MainForm_Resize);
			this.groupBox1.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.pictureBoxParticlePreview)).EndInit();
			this.groupBox2.ResumeLayout(false);
			this.groupBox2.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBarCameraView)).EndInit();
			this.groupBox3.ResumeLayout(false);
			this.groupBox3.PerformLayout();
			((System.ComponentModel.ISupportInitialize)(this.trackBarDirectionZ)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarDirectionY)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarDirectionX)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarSize)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarRate)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarRadius)).EndInit();
			((System.ComponentModel.ISupportInitialize)(this.trackBarPosition)).EndInit();
			this.groupBox4.ResumeLayout(false);
			this.groupBox4.PerformLayout();
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
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TrackBar trackBarPosition;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TrackBar trackBarRadius;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TrackBar trackBarCameraView;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.TrackBar trackBarRate;
		private System.Windows.Forms.Label label5;
		private System.Windows.Forms.TrackBar trackBarSize;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.TrackBar trackBarDirectionX;
		private System.Windows.Forms.TrackBar trackBarDirectionZ;
		private System.Windows.Forms.TrackBar trackBarDirectionY;
		private System.Windows.Forms.GroupBox groupBox4;
		private System.Windows.Forms.CheckBox checkBoxAffectorFadeOut;
		private System.Windows.Forms.CheckBox checkBoxAffectorGravity;
		private System.Windows.Forms.CheckBox checkBoxAffectorRotation;
		private System.Windows.Forms.CheckBox checkBoxKeepAspect;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.Button buttonBrowseForTexture;
	}
}

