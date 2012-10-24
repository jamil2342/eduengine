namespace DataImport
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
            this.inputTb = new System.Windows.Forms.TextBox();
            this.submitBtn = new System.Windows.Forms.Button();
            this.outputTb = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // inputTb
            // 
            this.inputTb.Location = new System.Drawing.Point(24, 33);
            this.inputTb.Multiline = true;
            this.inputTb.Name = "inputTb";
            this.inputTb.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.inputTb.Size = new System.Drawing.Size(796, 230);
            this.inputTb.TabIndex = 0;
            // 
            // submitBtn
            // 
            this.submitBtn.Location = new System.Drawing.Point(745, 285);
            this.submitBtn.Name = "submitBtn";
            this.submitBtn.Size = new System.Drawing.Size(75, 23);
            this.submitBtn.TabIndex = 1;
            this.submitBtn.Text = "SubmitBtn";
            this.submitBtn.UseVisualStyleBackColor = true;
            this.submitBtn.Click += new System.EventHandler(this.submitBtn_Click);
            // 
            // outputTb
            // 
            this.outputTb.Location = new System.Drawing.Point(24, 351);
            this.outputTb.Multiline = true;
            this.outputTb.Name = "outputTb";
            this.outputTb.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.outputTb.Size = new System.Drawing.Size(796, 266);
            this.outputTb.TabIndex = 2;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(845, 629);
            this.Controls.Add(this.outputTb);
            this.Controls.Add(this.submitBtn);
            this.Controls.Add(this.inputTb);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox inputTb;
        private System.Windows.Forms.Button submitBtn;
        private System.Windows.Forms.TextBox outputTb;
    }
}

