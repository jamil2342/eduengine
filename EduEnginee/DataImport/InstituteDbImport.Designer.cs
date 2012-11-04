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
            this.StartIdTb.Text = "4052";
            // 
            // OutputTb
            // 
            this.OutputTb.Location = new System.Drawing.Point(124, 192);
            this.OutputTb.Multiline = true;
            this.OutputTb.Name = "OutputTb";
            this.OutputTb.Size = new System.Drawing.Size(588, 239);
            this.OutputTb.TabIndex = 2;
            // 
            // EndIdTb
            // 
            this.EndIdTb.Location = new System.Drawing.Point(612, 62);
            this.EndIdTb.Name = "EndIdTb";
            this.EndIdTb.Size = new System.Drawing.Size(100, 26);
            this.EndIdTb.TabIndex = 4;
            this.EndIdTb.Text = "4052";
            // 
            // InstituteDbImport
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(831, 570);
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
    }
}