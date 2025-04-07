namespace FileModifierWinForms
{
    partial class Form1
    {
        /// <summary>
        /// Обов’язкова змінна конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        private System.Windows.Forms.Label lblSource;
        private System.Windows.Forms.TextBox txtSource;
        private System.Windows.Forms.Button btnBrowseSource;
        private System.Windows.Forms.Label lblTarget;
        private System.Windows.Forms.TextBox txtTarget;
        private System.Windows.Forms.Button btnBrowseTarget;
        private System.Windows.Forms.Button btnModify;

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
            lblSource = new Label();
            txtSource = new TextBox();
            btnBrowseSource = new Button();
            lblTarget = new Label();
            txtTarget = new TextBox();
            btnBrowseTarget = new Button();
            btnModify = new Button();
            SuspendLayout();
            // 
            // lblSource
            // 
            lblSource.AutoSize = true;
            lblSource.Location = new Point(12, 15);
            lblSource.Name = "lblSource";
            lblSource.Size = new Size(115, 20);
            lblSource.TabIndex = 0;
            lblSource.Text = "Файл-джерело:";
            // 
            // txtSource
            // 
            txtSource.Location = new Point(133, 12);
            txtSource.Name = "txtSource";
            txtSource.Size = new Size(264, 27);
            txtSource.TabIndex = 1;
            // 
            // btnBrowseSource
            // 
            btnBrowseSource.Location = new Point(403, 10);
            btnBrowseSource.Name = "btnBrowseSource";
            btnBrowseSource.Size = new Size(75, 29);
            btnBrowseSource.TabIndex = 2;
            btnBrowseSource.Text = "Огляд...";
            btnBrowseSource.UseVisualStyleBackColor = true;
            btnBrowseSource.Click += btnBrowseSource_Click;
            // 
            // lblTarget
            // 
            lblTarget.AutoSize = true;
            lblTarget.Location = new Point(12, 50);
            lblTarget.Name = "lblTarget";
            lblTarget.Size = new Size(117, 20);
            lblTarget.TabIndex = 3;
            lblTarget.Text = "Цільовий файл:";
            // 
            // txtTarget
            // 
            txtTarget.Location = new Point(133, 47);
            txtTarget.Name = "txtTarget";
            txtTarget.Size = new Size(264, 27);
            txtTarget.TabIndex = 4;
            // 
            // btnBrowseTarget
            // 
            btnBrowseTarget.Location = new Point(403, 45);
            btnBrowseTarget.Name = "btnBrowseTarget";
            btnBrowseTarget.Size = new Size(75, 29);
            btnBrowseTarget.TabIndex = 5;
            btnBrowseTarget.Text = "Огляд...";
            btnBrowseTarget.UseVisualStyleBackColor = true;
            btnBrowseTarget.Click += btnBrowseTarget_Click;
            // 
            // btnModify
            // 
            btnModify.Location = new Point(97, 85);
            btnModify.Name = "btnModify";
            btnModify.Size = new Size(150, 30);
            btnModify.TabIndex = 6;
            btnModify.Text = "Модифікувати файл";
            btnModify.UseVisualStyleBackColor = true;
            btnModify.Click += btnModify_Click;
            // 
            // Form1
            // 
            ClientSize = new Size(491, 118);
            Controls.Add(btnModify);
            Controls.Add(btnBrowseTarget);
            Controls.Add(txtTarget);
            Controls.Add(lblTarget);
            Controls.Add(btnBrowseSource);
            Controls.Add(txtSource);
            Controls.Add(lblSource);
            Name = "Form1";
            Text = "Модифікація файлу";
            Load += Form1_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion
    }
}
