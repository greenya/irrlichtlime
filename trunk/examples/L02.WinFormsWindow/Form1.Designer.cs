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
			this.panel1 = new System.Windows.Forms.Panel();
			this.label1 = new System.Windows.Forms.Label();
			this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
			this.comboBox1 = new System.Windows.Forms.ComboBox();
			this.checkBoxUseSeparateWindow = new System.Windows.Forms.CheckBox();
			this.SuspendLayout();
			// 
			// panel1
			// 
			this.panel1.Location = new System.Drawing.Point(12, 62);
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size(540, 400);
			this.panel1.TabIndex = 0;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Font = new System.Drawing.Font("Tahoma", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
			this.label1.Location = new System.Drawing.Point(12, 41);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(187, 18);
			this.label1.TabIndex = 1;
			this.label1.Text = "Select video driver to use...";
			// 
			// backgroundWorker1
			// 
			this.backgroundWorker1.WorkerReportsProgress = true;
			this.backgroundWorker1.WorkerSupportsCancellation = true;
			this.backgroundWorker1.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker1_DoWork);
			this.backgroundWorker1.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.backgroundWorker1_RunWorkerCompleted);
			this.backgroundWorker1.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.backgroundWorker1_ProgressChanged);
			// 
			// comboBox1
			// 
			this.comboBox1.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Location = new System.Drawing.Point(12, 14);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new System.Drawing.Size(133, 21);
			this.comboBox1.TabIndex = 2;
			this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.initializeIrrlichtDevice);
			// 
			// checkBoxUseSeparateWindow
			// 
			this.checkBoxUseSeparateWindow.AutoSize = true;
			this.checkBoxUseSeparateWindow.Location = new System.Drawing.Point(160, 16);
			this.checkBoxUseSeparateWindow.Name = "checkBoxUseSeparateWindow";
			this.checkBoxUseSeparateWindow.Size = new System.Drawing.Size(128, 17);
			this.checkBoxUseSeparateWindow.TabIndex = 3;
			this.checkBoxUseSeparateWindow.Text = "Use separate window";
			this.checkBoxUseSeparateWindow.UseVisualStyleBackColor = true;
			this.checkBoxUseSeparateWindow.CheckedChanged += new System.EventHandler(this.initializeIrrlichtDevice);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(564, 474);
			this.Controls.Add(this.checkBoxUseSeparateWindow);
			this.Controls.Add(this.comboBox1);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.panel1);
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

		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.Label label1;
		private System.ComponentModel.BackgroundWorker backgroundWorker1;
		private System.Windows.Forms.ComboBox comboBox1;
		private System.Windows.Forms.CheckBox checkBoxUseSeparateWindow;
	}
}

