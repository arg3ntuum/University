using System;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace Laba1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        // Метод шифрування тексту
        private string EncryptText(string text, string key, out int step)
        {
            // Перевірка на текст і ключ
            if (string.IsNullOrEmpty(text) || string.IsNullOrEmpty(key))
                throw new ArgumentException("Текст і ключ не можуть бути порожні!");

            Random rand = new Random();
            step = rand.Next(2, 6); // Генерація випадкового кроку вставки ключа (від 2 до 5)

            StringBuilder encrypted = new StringBuilder();
            int keyIndex = 0;

            for (int i = 0; i < text.Length; i++)
            {
                // Шифрування тексту з відповідним ключем
                char encryptedChar = (char)(text[i] ^ key[keyIndex % key.Length]);
                encrypted.Append(encryptedChar);

                // Вставка символів ключа через крок
                if ((i + 1) % step == 0)
                {
                    encrypted.Append(key[keyIndex % key.Length]);
                    keyIndex++;
                }
            }

            return encrypted.ToString();
        }

        // Метод розшифрування тексту
        private string DecryptText(string encryptedText, string key, int step)
        {
            // Перевірка на зашифрований текст і ключ
            if (string.IsNullOrEmpty(encryptedText) || string.IsNullOrEmpty(key))
                throw new ArgumentException("Зашифрований текст і ключ не можуть бути порожні!");

            StringBuilder decrypted = new StringBuilder();
            int keyIndex = 0;
            int count = 0;

            for (int i = 0; i < encryptedText.Length; i++)
            {
                // Пропускаємо ключ
                if ((count + 1) % (step + 1) == 0)
                {
                    keyIndex++; 
                }
                else
                {
                    // Дешифрування
                    char decryptedChar = (char)(encryptedText[i] ^ key[keyIndex % key.Length]);
                    decrypted.Append(decryptedChar);
                }
                count++;
            }

            return decrypted.ToString();
        }

        // Метод для запису зашифрованого тексту у файл
        private void SaveToFile(string encryptedText, string key, int step)
        {
            using (StreamWriter writer = new StreamWriter("code.txt"))
            {
                writer.WriteLine(key.Length); // Записуємо довжину ключа
                writer.WriteLine(step);       // Записуємо крок вставки ключа
                writer.WriteLine(encryptedText); // Записуємо зашифрований текст
            }
        }

        // Метод для зчитування даних із файлу
        private (int, int, string) ReadFromFile()
        {
            using (StreamReader reader = new StreamReader("code.txt"))
            {
                int keyLength = int.Parse(reader.ReadLine()); // Зчитуємо довжину ключа
                int step = int.Parse(reader.ReadLine());      // Зчитуємо крок вставки ключа
                string encryptedText = reader.ReadLine();     // Зчитуємо сам зашифрований текст
                return (keyLength, step, encryptedText);
            }
        }

        // Метод обробки кнопки "Зашифрувати"
        private void buttonEncrypt_Click(object sender, EventArgs e)
        {
            try
            {
                string text = textBoxIn.Text;  // Отримуємо введений текст
                string key = textBoxKey.Text;  // Отримуємо введений ключ

                string encryptedText = EncryptText(text, key, out int step); // Шифруємо текст
                textBoxResult.Text = encryptedText; // Відображаємо результат шифрування

                // Одразу записуємо зашифрований текст у файл
                SaveToFile(encryptedText, key, step);
                MessageBox.Show($"Файл успішно збережено! (Крок ключа = {step})", "Успіх", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Помилка під час шифрування", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        // Метод обробки кнопки "Розшифрувати"
        private void buttonUnEcrypt_Click(object sender, EventArgs e)
        {
            try
            {
                // Читаємо зашифровані дані з файлу
                (int keyLength, int step, string encryptedText) = ReadFromFile();
                string key = textBoxKey.Text;

                // Відображаємо зашифрований текст
                textBoxIn.Text = encryptedText;

                // Перевіряємо довжину ключа
                if (key.Length != keyLength)
                {
                    MessageBox.Show("Невірний ключ!", "Помилка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                // Розшифровуємо текст
                string decryptedText = DecryptText(encryptedText, key, step);
                textBoxResult.Text = decryptedText; // Відображаємо результат
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Помилка під час розшифрування", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }
}