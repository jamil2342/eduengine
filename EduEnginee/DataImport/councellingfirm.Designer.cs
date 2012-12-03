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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(InstituteDbImport));
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
            resources.ApplyResources(this.SubmitTb, "SubmitTb");
            this.SubmitTb.Name = "SubmitTb";
            this.SubmitTb.UseVisualStyleBackColor = true;
            this.SubmitTb.Click += new System.EventHandler(this.SubmitTb_Click);
            // 
            // StartIdTb
            // 
            resources.ApplyResources(this.StartIdTb, "StartIdTb");
            this.StartIdTb.Name = "StartIdTb";
            // 
            // OutputTb
            // 
            resources.ApplyResources(this.OutputTb, "OutputTb");
            this.OutputTb.Name = "OutputTb";
            // 
            // EndIdTb
            // 
            resources.ApplyResources(this.EndIdTb, "EndIdTb");
            this.EndIdTb.Name = "EndIdTb";
            // 
            // minusBtn
            // 
            resources.ApplyResources(this.minusBtn, "minusBtn");
            this.minusBtn.Name = "minusBtn";
            this.minusBtn.UseVisualStyleBackColor = true;
            this.minusBtn.Click += new System.EventHandler(this.minusBtn_Click);
            // 
            // plusBtn
            // 
            resources.ApplyResources(this.plusBtn, "plusBtn");
            this.plusBtn.Name = "plusBtn";
            this.plusBtn.UseVisualStyleBackColor = true;
            this.plusBtn.Click += new System.EventHandler(this.button2_Click);
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
            // 
            // InstituteDbImport
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.label1);
            this.Controls.Add(this.plusBtn);
            this.Controls.Add(this.minusBtn);
            this.Controls.Add(this.EndIdTb);
            this.Controls.Add(this.OutputTb);
            this.Controls.Add(this.StartIdTb);
            this.Controls.Add(this.SubmitTb);
            this.Name = "InstituteDbImport";
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