namespace VirusDetectionApp
{
    partial class Form1
    {
        private System.ComponentModel.IContainer components = null;
        private System.Windows.Forms.Label lblDirectory;
        private System.Windows.Forms.TextBox txtDirectory;
        private System.Windows.Forms.Button btnBrowse;
        private System.Windows.Forms.Label lblVirusSignature;
        private System.Windows.Forms.TextBox txtVirusSignature;
        private System.Windows.Forms.Button btnScan;

        /// <summary>
        /// Вивільнення всіх використовуваних ресурсів.
        /// </summary>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматично створений конструктором форм Windows

        /// <summary>
        /// Метод, необхідний для підтримки конструктора – не змінюйте 
        /// вміст цього методу за допомогою редактора коду.
        /// </summary>
        private void InitializeComponent()
        {
            lblDirectory = new Label();
            txtDirectory = new TextBox();
            btnBrowse = new Button();
            lblVirusSignature = new Label();
            txtVirusSignature = new TextBox();
            btnScan = new Button();
            SuspendLayout();
            // 
            // lblDirectory
            // 
            lblDirectory.AutoSize = true;
            lblDirectory.Location = new Point(12, 15);
            lblDirectory.Name = "lblDirectory";
            lblDirectory.Size = new Size(117, 20);
            lblDirectory.TabIndex = 0;
            lblDirectory.Text = "Каталог файлів:";
            // 
            // txtDirectory
            // 
            txtDirectory.Location = new Point(108, 12);
            txtDirectory.Name = "txtDirectory";
            txtDirectory.Size = new Size(300, 27);
            txtDirectory.TabIndex = 1;
            // 
            // btnBrowse
            // 
            btnBrowse.Location = new Point(414, 10);
            btnBrowse.Name = "btnBrowse";
            btnBrowse.Size = new Size(75, 23);
            btnBrowse.TabIndex = 2;
            btnBrowse.Text = "Огляд...";
            btnBrowse.UseVisualStyleBackColor = true;
            btnBrowse.Click += btnBrowse_Click;
            // 
            // lblVirusSignature
            // 
            lblVirusSignature.AutoSize = true;
            lblVirusSignature.Location = new Point(12, 50);
            lblVirusSignature.Name = "lblVirusSignature";
            lblVirusSignature.Size = new Size(159, 20);
            lblVirusSignature.TabIndex = 3;
            lblVirusSignature.Text = "Рядок вірусного коду:";
            // 
            // txtVirusSignature
            // 
            txtVirusSignature.Location = new Point(128, 47);
            txtVirusSignature.Name = "txtVirusSignature";
            txtVirusSignature.Size = new Size(280, 27);
            txtVirusSignature.TabIndex = 4;
            // 
            // btnScan
            // 
            btnScan.Location = new Point(108, 85);
            btnScan.Name = "btnScan";
            btnScan.Size = new Size(150, 30);
            btnScan.TabIndex = 5;
            btnScan.Text = "Сканувати файли";
            btnScan.UseVisualStyleBackColor = true;
            btnScan.Click += btnScan_Click;
            // 
            // Form1
            // 
            ClientSize = new Size(510, 130);
            Controls.Add(btnScan);
            Controls.Add(txtVirusSignature);
            Controls.Add(lblVirusSignature);
            Controls.Add(btnBrowse);
            Controls.Add(txtDirectory);
            Controls.Add(lblDirectory);
            Name = "Form1";
            Text = "Виявлення вірусного коду";
            Load += Form1_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
    }
}
