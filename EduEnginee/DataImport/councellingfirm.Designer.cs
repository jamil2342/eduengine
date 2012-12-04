namespace DataImport
{
    partial class CouncellingFirm
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
            this.label1 = new System.Windows.Forms.Label();
            this.plusBtn = new System.Windows.Forms.Button();
            this.minusBtn = new System.Windows.Forms.Button();
            this.EndIdTb = new System.Windows.Forms.TextBox();
            this.OutputTb = new System.Windows.Forms.TextBox();
            this.StartIdTb = new System.Windows.Forms.TextBox();
            this.SubmitTb = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.label1.Location = new System.Drawing.Point(86, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(92, 20);
            this.label1.TabIndex = 14;
            this.label1.Text = "progressLbl";
            // 
            // plusBtn
            // 
            this.plusBtn.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.plusBtn.Location = new System.Drawing.Point(320, 111);
            this.plusBtn.Name = "plusBtn";
            this.plusBtn.Size = new System.Drawing.Size(41, 36);
            this.plusBtn.TabIndex = 13;
            this.plusBtn.Text = "+";
            this.plusBtn.UseVisualStyleBackColor = true;
            // 
            // minusBtn
            // 
            this.minusBtn.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.minusBtn.Location = new System.Drawing.Point(379, 111);
            this.minusBtn.Name = "minusBtn";
            this.minusBtn.Size = new System.Drawing.Size(41, 36);
            this.minusBtn.TabIndex = 12;
            this.minusBtn.Text = "-";
            this.minusBtn.UseVisualStyleBackColor = true;
            // 
            // EndIdTb
            // 
            this.EndIdTb.Location = new System.Drawing.Point(468, 62);
            this.EndIdTb.Name = "EndIdTb";
            this.EndIdTb.Size = new System.Drawing.Size(100, 26);
            this.EndIdTb.TabIndex = 11;
            this.EndIdTb.Text = "4060";
            // 
            // OutputTb
            // 
            this.OutputTb.Location = new System.Drawing.Point(35, 207);
            this.OutputTb.Multiline = true;
            this.OutputTb.Name = "OutputTb";
            this.OutputTb.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.OutputTb.Size = new System.Drawing.Size(588, 239);
            this.OutputTb.TabIndex = 10;
            // 
            // StartIdTb
            // 
            this.StartIdTb.Location = new System.Drawing.Point(320, 62);
            this.StartIdTb.Name = "StartIdTb";
            this.StartIdTb.Size = new System.Drawing.Size(100, 26);
            this.StartIdTb.TabIndex = 9;
            this.StartIdTb.Text = "4050";
            // 
            // SubmitTb
            // 
            this.SubmitTb.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.SubmitTb.Location = new System.Drawing.Point(493, 138);
            this.SubmitTb.Name = "SubmitTb";
            this.SubmitTb.Size = new System.Drawing.Size(75, 36);
            this.SubmitTb.TabIndex = 8;
            this.SubmitTb.Text = "Submit";
            this.SubmitTb.UseVisualStyleBackColor = true;
            this.SubmitTb.Click += new System.EventHandler(this.SubmitTb_Click);
            // 
            // CouncellingFirm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(783, 493);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.plusBtn);
            this.Controls.Add(this.minusBtn);
            this.Controls.Add(this.EndIdTb);
            this.Controls.Add(this.OutputTb);
            this.Controls.Add(this.StartIdTb);
            this.Controls.Add(this.SubmitTb);
            this.Name = "CouncellingFirm";
            this.Text = "CouncellingFirm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button plusBtn;
        private System.Windows.Forms.Button minusBtn;
        private System.Windows.Forms.TextBox EndIdTb;
        private System.Windows.Forms.TextBox OutputTb;
        private System.Windows.Forms.TextBox StartIdTb;
        private System.Windows.Forms.Button SubmitTb;
    }
}