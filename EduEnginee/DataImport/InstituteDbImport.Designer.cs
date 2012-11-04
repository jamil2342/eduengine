namespace DataImport
{
    partial class InstituteDbImport
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
            this.SubmitTb = new System.Windows.Forms.Button();
            this.StartIdTb = new System.Windows.Forms.TextBox();
            this.OutputTb = new System.Windows.Forms.TextBox();
            this.EndIdTb = new System.Windows.Forms.TextBox();
            this.minusBtn = new System.Windows.Forms.Button();
            this.plusBtn = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // SubmitTb
            // 
            this.SubmitTb.Location = new System.Drawing.Point(637, 138);
            this.SubmitTb.Name = "SubmitTb";
            this.SubmitTb.Size = new System.Drawing.Size(75, 36);
            this.SubmitTb.TabIndex = 0;
            this.SubmitTb.Text = "Submit";
            this.SubmitTb.UseVisualStyleBackColor = true;
            this.SubmitTb.Click += new System.EventHandler(this.SubmitTb_Click);
            // 
            // StartIdTb
            // 
            this.StartIdTb.Location = new System.Drawing.Point(464, 62);
            this.StartIdTb.Name = "StartIdTb";
            this.StartIdTb.Size = new System.Drawing.Size(100, 26);
            this.StartIdTb.TabIndex = 1;
            this.StartIdTb.Text = "4050";
            // 
            // OutputTb
            // 
            this.OutputTb.Location = new System.Drawing.Point(124, 192);
            this.OutputTb.Multiline = true;
            this.OutputTb.Name = "OutputTb";
            this.OutputTb.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.OutputTb.Size = new System.Drawing.Size(588, 239);
            this.OutputTb.TabIndex = 2;
            // 
            // EndIdTb
            // 
            this.EndIdTb.Location = new System.Drawing.Point(612, 62);
            this.EndIdTb.Name = "EndIdTb";
            this.EndIdTb.Size = new System.Drawing.Size(100, 26);
            this.EndIdTb.TabIndex = 4;
            this.EndIdTb.Text = "4060";
            // 
            // minusBtn
            // 
            this.minusBtn.Location = new System.Drawing.Point(523, 111);
            this.minusBtn.Name = "minusBtn";
            this.minusBtn.Size = new System.Drawing.Size(41, 36);
            this.minusBtn.TabIndex = 5;
            this.minusBtn.Text = "-";
            this.minusBtn.UseVisualStyleBackColor = true;
            this.minusBtn.Click += new System.EventHandler(this.minusBtn_Click);
            // 
            // plusBtn
            // 
            this.plusBtn.Location = new System.Drawing.Point(464, 111);
            this.plusBtn.Name = "plusBtn";
            this.plusBtn.Size = new System.Drawing.Size(41, 36);
            this.plusBtn.TabIndex = 6;
            this.plusBtn.Text = "+";
            this.plusBtn.UseVisualStyleBackColor = true;
            this.plusBtn.Click += new System.EventHandler(this.button2_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(230, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(92, 20);
            this.label1.TabIndex = 7;
            this.label1.Text = "progressLbl";
            // 
            // InstituteDbImport
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(831, 570);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.plusBtn);
            this.Controls.Add(this.minusBtn);
            this.Controls.Add(this.EndIdTb);
            this.Controls.Add(this.OutputTb);
            this.Controls.Add(this.StartIdTb);
            this.Controls.Add(this.SubmitTb);
            this.Name = "InstituteDbImport";
            this.Text = "InstituteDbImport";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button SubmitTb;
        private System.Windows.Forms.TextBox StartIdTb;
        private System.Windows.Forms.TextBox OutputTb;
        private System.Windows.Forms.TextBox EndIdTb;
        private System.Windows.Forms.Button minusBtn;
        private System.Windows.Forms.Button plusBtn;
        private System.Windows.Forms.Label label1;
    }
}