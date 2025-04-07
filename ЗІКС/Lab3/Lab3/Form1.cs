using System;
using System.Diagnostics;
using System.IO;
using System.Threading;
using System.Windows.Forms;


namespace ZIKS_Lab3
{
    public partial class Form1 : Form
    {
        private string path = null, file = null;
        private int count = 9;  // Кількість дозволених запусків програми після створення файлу
        private DateTime validDate = new DateTime(1992, 12, 22);  // Дата, яка повинна бути встановлена для службового файлу
        private readonly string protectedFileName = "id.pas";  // Назва службового файлу, який не можна редагувати

        public Form1()
        {
            InitializeComponent();
            LoadFile();  // Завантаження та перевірка службового файлу
        }

        private void LoadFile()
        {
            // Вибір файлу для редагування через діалогове вікно
            OpenFileDialog st = new OpenFileDialog();
            if (st.ShowDialog() == DialogResult.OK)
            {
                path = st.FileName;

                // Якщо службовий файл не існує, створити його та задати необхідні параметри
                if (!File.Exists(protectedFileName))
                {
                    using (StreamWriter write = new StreamWriter(protectedFileName))
                    {
                        file = new string('0', 100);
                        file = file.Remove(8, 1).Insert(8, count.ToString());
                        write.Write(file);
                    }
                    File.SetLastWriteTime(protectedFileName, validDate);
                    File.SetCreationTime(protectedFileName, validDate);
                }

                // Перевірка, чи файл не редагувався (перевірка дати зміни)
                if (File.GetLastWriteTime(protectedFileName) != validDate)
                {
                    MessageBox.Show("Службовий файл програми редагували. Відкриття неможливе!");
                    Process.GetCurrentProcess().Kill();
                }

                // Читання лічильника спроб із службового файлу
                using (StreamReader read = new StreamReader(protectedFileName))
                {
                    string content = read.ReadLine();
                    if (content != null && content.Length >= 9)
                    {
                        count = int.Parse(content[8].ToString()) - 1; // Зменшуємо лічильник на 1
                    }
                }

                // Якщо кількість спроб закінчилась, програма завершується
                if (count <= 0)
                {
                    MessageBox.Show("Пробний період завершений. Запуск програми неможливий");
                    Process.GetCurrentProcess().Kill();
                }

                label1.Text = count.ToString();  // Відображення кількості залишених спроб

                // Оновлення службового файлу з новим значенням лічильника
                using (StreamWriter write = new StreamWriter(protectedFileName))
                {
                    file = new string('0', 100);
                    file = file.Remove(8, 1).Insert(8, count.ToString());
                    write.Write(file);
                }

                // Зміна дати створення та зміни службового файлу на початкову дату
                File.SetLastWriteTime(protectedFileName, validDate);
                File.SetCreationTime(protectedFileName, validDate);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                // Перевірка на спробу змінити службовий файл
                if (path.Contains(protectedFileName))
                {
                    MessageBox.Show("Файл 'id.pas' захищений та не може бути змінений програмою!");
                    return;
                }

                // Зміна дати обраного файлу користувачем
                DateTime selectedDate = new DateTime(Convert.ToInt32(textBox1.Text), (int)numericUpDown2.Value, (int)numericUpDown1.Value);
                File.SetLastWriteTime(path, selectedDate);
                File.SetCreationTime(path, selectedDate);

                MessageBox.Show("Дату файлу змінено!");
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Помилка: {ex.Message}");
            }
        }
        //відволікаюча функція для маскування  дій
        private void distractFunction()
        {

            int i = 0;
        start:
            while (i < 999999999)
            {
                i++;
                goto start;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            // Дозволяє вибрати новий файл для зміни дати
            OpenFileDialog fileDialog = new OpenFileDialog();
            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                path = fileDialog.FileName;
                MessageBox.Show($"Новий файл обраний: {path}");
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            distractFunction();
        }

        private void Form1_Load_1(object sender, EventArgs e)
        {

        }
    }
}
