using System;
using System.IO;
using System.Windows.Forms;

namespace FileModifierWinForms
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        // Обробник кнопки для вибору файлу-джерела
        private void btnBrowseSource_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                // Відкриття діалогового вікна для вибору файлу-джерела
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    txtSource.Text = openFileDialog.FileName; // Запис обраного шляху у текстове поле
                }
            }
        }

        // Обробник кнопки для вибору цільового файлу
        private void btnBrowseTarget_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                // Відкриття діалогового вікна для вибору цільового файлу
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    txtTarget.Text = openFileDialog.FileName; // Запис обраного шляху у текстове поле
                }
            }
        }

        // Обробник кнопки, що виконує модифікацію файлу
        private void btnModify_Click(object sender, EventArgs e)
        {
            // Отримання шляхів файлів з текстових полів
            string sourceFile = txtSource.Text;
            string targetFile = txtTarget.Text;

            // Перевірка, чи існують файли
            if (!File.Exists(sourceFile) || !File.Exists(targetFile))
            {
                MessageBox.Show("Будь ласка, оберіть існуючі файли.");
                return;
            }

            try
            {
                // Зчитування вмісту файлу-джерела та цільового файлу
                string sourceContent = File.ReadAllText(sourceFile);
                string targetContent = File.ReadAllText(targetFile);

                // Визначення випадкової позиції вставки у цільовому файлі
                Random rand = new Random();
                int insertPosition = rand.Next(0, targetContent.Length);

                // Вставка вмісту файлу-джерела у вказану позицію цільового файлу
                string modifiedContent = targetContent.Insert(insertPosition, sourceContent);

                // Формування імені нового файлу (з префіксом "Modified_")
                string outputFile = Path.Combine(Path.GetDirectoryName(targetFile), "Modified_" + Path.GetFileName(targetFile));

                // Запис модифікованого вмісту у новий файл
                File.WriteAllText(outputFile, modifiedContent);

                MessageBox.Show("Модифікований файл збережено: " + outputFile);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Помилка: " + ex.Message);
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
