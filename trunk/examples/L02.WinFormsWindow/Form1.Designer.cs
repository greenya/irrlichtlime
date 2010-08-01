namespace L02.WinFormsWindow
{
	partial class Form1
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
			this.panelRenderingWindow = new System.Windows.Forms.Panel();
			this.labelRenderingStatus = new System.Windows.Forms.Label();
			this.backgroundRendering = new System.ComponentModel.BackgroundWorker();
			this.comboBoxVideoDriver = new System.Windows.Forms.ComboBox();
			this.checkBoxUseSeparateWindow = new System.Windows.Forms.CheckBox();
			this.comboBoxAntiAliasing = new System.Windows.Forms.ComboBox();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.comboBoxBackground = new System.Windows.Forms.ComboBox();
			this.label4 = new System.Windows.Forms.Label();
			this.checkBoxUseVSync = new System.Windows.Forms.CheckBox();
			this.SuspendLayout();
			// 
			// panelRenderingWindow
			// 
			this.panelRenderingWindow.Location = new System.Drawing.Point(12, 85);
			this.panelRenderingWindow.Name = "panelRenderingWindow";
			this.panelRenderingWindow.Size = new System.Drawing.Size(540, 400);
			this.panelRenderingWindow.TabIndex = 0;
			// 
			// labelRenderingStatus
			// 
			this.labelRenderingStatus.AutoSize = true;
			this.labelRenderingStatus.Font = new System.Drawing.Font("Tahoma", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.labelRenderingStatus.Location = new System.Drawing.Point(12, 64);
			this.labelRenderingStatus.Name = "labelRenderingStatus";
			this.labelRenderingStatus.Size = new System.Drawing.Size(187, 18);
			this.labelRenderingStatus.TabIndex = 1;
			this.labelRenderingStatus.Text = "Select video driver to use...";
			// 
			// backgroundRendering
			// 
			this.backgroundRendering.WorkerReportsProgress = true;
			this.backgroundRendering.WorkerSupportsCancellation = true;
			this.backgroundRendering.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundRendering_DoWork);
			this.backgroundRendering.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.backgroundRendering_RunWorkerCompleted);
			this.backgroundRendering.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.backgroundRendering_ProgressChanged);
			// 
			// comboBoxVideoDriver
			// 
			this.comboBoxVideoDriver.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboBoxVideoDriver.FormattingEnabled = true;
			this.comboBoxVideoDriver.Location = new System.Drawing.Point(12, 32);
			this.comboBoxVideoDriver.Name = "comboBoxVideoDriver";
			this.comboBoxVideoDriver.Size = new System.Drawing.Size(130, 21);
			this.comboBoxVideoDriver.TabIndex = 2;
			this.comboBoxVideoDriver.SelectedIndexChanged += new System.EventHandler(this.initializeIrrlichtDevice);
			// 
			// checkBoxUseSeparateWindow
			// 
			this.checkBoxUseSeparateWindow.AutoSize = true;
			this.checkBoxUseSeparateWindow.Location = new System.Drawing.Point(349, 38);
			this.checkBoxUseSeparateWindow.Name = "checkBoxUseSeparateWindow";
			this.checkBoxUseSeparateWindow.Size = new System.Drawing.Size(128, 17);
			this.checkBoxUseSeparateWindow.TabIndex = 3;
			this.checkBoxUseSeparateWindow.Text = "Use separate window";
			this.checkBoxUseSeparateWindow.UseVisualStyleBackColor = true;
			this.checkBoxUseSeparateWindow.CheckedChanged += new System.EventHandler(this.initializeIrrlichtDevice);
			// 
			// comboBoxAntiAliasing
			// 
			this.comboBoxAntiAliasing.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboBoxAntiAliasing.FormattingEnabled = true;
			this.comboBoxAntiAliasing.Items.AddRange(new object[] {
            "No",
            "2x",
            "4x",
            "8x",
            "16x"});
			this.comboBoxAntiAliasing.Location = new System.Drawing.Point(158, 32);
			this.comboBoxAntiAliasing.Name = "comboBoxAntiAliasing";
			this.comboBoxAntiAliasing.Size = new System.Drawing.Size(80, 21);
			this.comboBoxAntiAliasing.TabIndex = 4;
			this.comboBoxAntiAliasing.SelectedIndexChanged += new System.EventHandler(this.initializeIrrlichtDevice);
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point(12, 16);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(63, 13);
			this.label2.TabIndex = 5;
			this.label2.Text = "Video driver";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point(155, 16);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(61, 13);
			this.label3.TabIndex = 6;
			this.label3.Text = "AntiAliasing";
			// 
			// comboBoxBackground
			// 
			this.comboBoxBackground.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboBoxBackground.FormattingEnabled = true;
			this.comboBoxBackground.Items.AddRange(new object[] {
            "Skybox",
            "Black",
            "White"});
			this.comboBoxBackground.Location = new System.Drawing.Point(253, 32);
			this.comboBoxBackground.Name = "comboBoxBackground";
			this.comboBoxBackground.Size = new System.Drawing.Size(80, 21);
			this.comboBoxBackground.TabIndex = 7;
			this.comboBoxBackground.SelectedIndexChanged += new System.EventHandler(this.initializeIrrlichtDevice);
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point(250, 16);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(65, 13);
			this.label4.TabIndex = 6;
			this.label4.Text = "Background";
			// 
			// checkBoxUseVSync
			// 
			this.checkBoxUseVSync.AutoSize = true;
			this.checkBoxUseVSync.Location = new System.Drawing.Point(349, 15);
			this.checkBoxUseVSync.Name = "checkBoxUseVSync";
			this.checkBoxUseVSync.Size = new System.Drawing.Size(79, 17);
			this.checkBoxUseVSync.TabIndex = 8;
			this.checkBoxUseVSync.Text = "Use VSync";
			this.checkBoxUseVSync.UseVisualStyleBackColor = true;
			this.checkBoxUseVSync.CheckedChanged += new System.EventHandler(this.initializeIrrlichtDevice);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(564, 497);
			this.Controls.Add(this.checkBoxUseVSync);
			this.Controls.Add(this.comboBoxBackground);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.comboBoxAntiAliasing);
			this.Controls.Add(this.checkBoxUseSeparateWindow);
			this.Controls.Add(this.comboBoxVideoDriver);
			this.Controls.Add(this.labelRenderingStatus);
			this.Controls.Add(this.panelRenderingWindow);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
			this.MaximizeBox = false;
			this.Name = "Form1";
			this.Text = "WinForms window example - Irrlicht Engine";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Panel panelRenderingWindow;
		private System.Windows.Forms.Label labelRenderingStatus;
		private System.ComponentModel.BackgroundWorker backgroundRendering;
		private System.Windows.Forms.ComboBox comboBoxVideoDriver;
		private System.Windows.Forms.CheckBox checkBoxUseSeparateWindow;
		private System.Windows.Forms.ComboBox comboBoxAntiAliasing;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.ComboBox comboBoxBackground;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.CheckBox checkBoxUseVSync;
	}
}

