using System;
using System.IO;
using System.Windows.Forms;

namespace VirusDetectionApp
{
    public partial class Form1 : Form
    {
        // Каталог для карантину (заражені файли будуть переміщені сюди)
        private string quarantineFolder = "";

        public Form1()
        {
            InitializeComponent();
        }

        // Обробник кнопки "Огляд..." для вибору каталогу файлів
        private void btnBrowse_Click(object sender, EventArgs e)
        {
            using (FolderBrowserDialog folderDlg = new FolderBrowserDialog())
            {
                if (folderDlg.ShowDialog() == DialogResult.OK)
                {
                    txtDirectory.Text = folderDlg.SelectedPath;
                }
            }
        }

        // Обробник кнопки "Сканувати файли"
        // Процедура шукає заданий рядок (вірусний код) у всіх текстових файлах обраного каталогу.
        // У разі виявлення зараженого файлу, він переміщується до каталогу карантину.
        private void btnScan_Click(object sender, EventArgs e)
        {
            string dirPath = txtDirectory.Text;
            string virusSignature = txtVirusSignature.Text;

            if (string.IsNullOrEmpty(dirPath) || string.IsNullOrEmpty(virusSignature))
            {
                MessageBox.Show("Будь ласка, вкажіть каталог та рядок вірусного коду.");
                return;
            }

            if (!Directory.Exists(dirPath))
            {
                MessageBox.Show("Вказаний каталог не існує.");
                return;
            }

            // Створення каталогу карантину всередині обраного каталогу
            quarantineFolder = System.IO.Path.Combine(dirPath, "Quarantine");
            if (!Directory.Exists(quarantineFolder))
            {
                Directory.CreateDirectory(quarantineFolder);
            }

            // Отримання всіх текстових файлів (*.txt) у обраному каталозі
            string[] textFiles = Directory.GetFiles(dirPath, "*.txt");
            int infectedCount = 0;

            foreach (var file in textFiles)
            {
                try
                {
                    // Зчитування вмісту файлу
                    string content = File.ReadAllText(file);

                    // Якщо вміст містить заданий рядок вірусного коду, файл вважається зараженим
                    if (content.Contains(virusSignature))
                    {
                        // Формування шляху для переміщення файлу до карантину
                        string destFile = Path.Combine(quarantineFolder, Path.GetFileName(file));

                        // Переміщення файлу (як "лікування")
                        File.Move(file, destFile);
                        infectedCount++;
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Помилка при обробці файлу " + file + ": " + ex.Message);
                }
            }

            MessageBox.Show("Пошук завершено. Заражено " + infectedCount + " файлів, переміщено до карантину.");
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
