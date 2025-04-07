using System;
using System.IO;
using System.Management;
using System.Security.Cryptography;
using System.Text;
using System.Windows.Forms;
using Microsoft.Win32;
using Microsoft.VisualBasic.Devices;
using System.Diagnostics;

namespace Lab4_ZIKS
{
    public partial class Form1 : Form
    {
        private string publicKey;

        public Form1()
        {
            InitializeComponent();
            CheckSignatureOnStartup(); // Перевірка цифрового підпису при запуску
        }

        private void button1_Click(object sender, EventArgs e)
        {
            using (FolderBrowserDialog folderBrowser = new FolderBrowserDialog()) // Відкриття діалогового вікна для вибору папки
            {
                if (folderBrowser.ShowDialog() == DialogResult.OK) // Перевірка, чи вибрана папка
                {
                    installDirTextBox.Text = folderBrowser.SelectedPath; // Запис вибраного шляху в текстове поле
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string installPath = installDirTextBox.Text; // Отримання шляху встановлення

            if (string.IsNullOrWhiteSpace(installPath) || !Directory.Exists(installPath)) // Перевірка, чи шлях коректний
            {
                MessageBox.Show("Будь ласка, оберіть коректну папку для встановлення.");
                return;
            }

            try
            {
                // Копіюємо файл програми у вибрану папку
                File.Copy("C:\\Users\\Ростислав\\Desktop\\Univercity\\ЗИКС\\Lab1\\Lab1\\bin\\Debug\\net8.0-windows\\Lab1.exe",
                          Path.Combine(installPath, "InProgram.exe"), true);

                string computerInfo = CollectComputerInfo(installPath); // Отримання інформації про систему
                infoTextBox.Text = computerInfo; // Відображення інформації у вікні

                RSACryptoServiceProvider rsa = new RSACryptoServiceProvider(); // Створення об'єкта RSA
                string privateKey = rsa.ToXmlString(true); // Отримання закритого ключа
                publicKey = rsa.ToXmlString(false); // Отримання відкритого ключа

                string hashedData = ComputeHash(computerInfo); // Хешування інформації
                string signature = SignData(hashedData, privateKey); // Підписування хешу
                WriteSignatureToRegistry(signature); // Збереження підпису в реєстрі

                MessageBox.Show("Програма успішно встановлена та підпис збережено.");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Помилка: " + ex.Message); // Вивід помилки
            }
        }


        private string CollectComputerInfo(string installPath)
        {
            var sb = new StringBuilder();
            var computerInfo = new ComputerInfo();
            // Основна інформація про систему
            sb.AppendLine("Ім'я користувача: " + Environment.UserName);
            sb.AppendLine("Ім'я комп'ютера: " + Environment.MachineName);
            sb.AppendLine("Папка Windows: " + Environment.GetFolderPath(Environment.SpecialFolder.Windows));
            sb.AppendLine("Системна папка: " + Environment.GetFolderPath(Environment.SpecialFolder.System));
            sb.AppendLine("Тип клавіатури: " + InputLanguage.CurrentInputLanguage.LayoutName);
            sb.AppendLine("Тип і підтип клавіатури: " + InputLanguage.CurrentInputLanguage.LayoutName);
            sb.AppendLine("Ширина екрану: " + Screen.PrimaryScreen.Bounds.Width);
            sb.AppendLine("Набір дискових пристроїв:");

            try
            {
                ManagementObjectSearcher searcher = new ManagementObjectSearcher("SELECT Model FROM Win32_DiskDrive");
                foreach (ManagementObject obj in searcher.Get())
                {
                    sb.AppendLine(" - " + obj["Model"]);
                }
            }
            catch (Exception ex)
            {
                sb.AppendLine("Помилка отримання дискових пристроїв: " + ex.Message);
            }

            try
            {
                DriveInfo cDrive = new DriveInfo("C");
                sb.AppendLine("Мітка тому диска C: " + cDrive.VolumeLabel);
            }
            catch (Exception ex)
            {
                sb.AppendLine("Помилка отримання мітки тому: " + ex.Message);
            }
            try
            {
                ManagementObjectSearcher searcher = new ManagementObjectSearcher("SELECT * FROM Win32_ComputerSystem");

                foreach (ManagementObject obj in searcher.Get())
                {
                    sb.AppendLine("Виробник: " + obj["Manufacturer"]);
                    sb.AppendLine("Модель: " + obj["Model"]);
                }
            }
            catch (Exception ex)
            {
                sb.AppendLine("Помилка отримання інформації про систему: " + ex.Message);
            }
            return sb.ToString();
        }

         private string ComputeHash(string data)
        {
            using (SHA256 sha256 = SHA256.Create()) // Створення об'єкта SHA256
            {
                byte[] hashBytes = sha256.ComputeHash(Encoding.UTF8.GetBytes(data)); // Обчислення хешу
                return Convert.ToBase64String(hashBytes); // Перетворення в Base64
            }
        }

        private string SignData(string data, string privateKey)
        {
            using (RSACryptoServiceProvider rsa = new RSACryptoServiceProvider()) // Створення RSA
            {
                rsa.FromXmlString(privateKey); // Відновлення закритого ключа
                byte[] dataBytes = Encoding.UTF8.GetBytes(data);
                byte[] signatureBytes = rsa.SignData(dataBytes, new SHA256CryptoServiceProvider()); // Підписування даних
                return Convert.ToBase64String(signatureBytes);
            }
        }


        private void WriteSignatureToRegistry(string signature)
        {
            using (RegistryKey key = Registry.CurrentUser.CreateSubKey("Software\\Ростислав")) // Відкриття розділу реєстру
            {
                key.SetValue("Signature", signature); // Збереження підпису
                key.SetValue("PublicKey", publicKey); // Збереження відкритого ключа
            }
        }

        // Метод для зчитування цифрового підпису та публічного ключа з реєстру
        private (string, string) ReadSignatureFromRegistry()
        {
            // Відкриваємо розділ реєстру за вказаним шляхом (поточний користувач)
            using (RegistryKey key = Registry.CurrentUser.OpenSubKey("Software\\Ростислав"))
            {
                // Якщо розділ знайдено
                if (key != null)
                {
                    // Отримуємо значення підпису з реєстру
                    string signature = key.GetValue("Signature") as string;
                    // Отримуємо значення публічного ключа з реєстру
                    string publicKey = key.GetValue("PublicKey") as string;
                    // Повертаємо кортеж з підписом та публічним ключем
                    return (signature, publicKey);
                }
            }
            // Якщо розділ не знайдено, повертаємо кортеж з null значеннями
            return (null, null);
        }

        // Метод для перевірки цифрового підпису
        private bool VerifySignature(string originalData, string signature, string publicKey)
        {
            // Створюємо екземпляр криптографічного провайдера RSA
            using (RSACryptoServiceProvider rsa = new RSACryptoServiceProvider())
            {
                // Завантажуємо публічний ключ з XML-рядка
                rsa.FromXmlString(publicKey);
                // Перетворюємо вхідний рядок даних в масив байтів з використанням кодування UTF8
                byte[] dataBytes = Encoding.UTF8.GetBytes(originalData);
                // Перетворюємо рядкове представлення підпису (Base64) в масив байтів
                byte[] signatureBytes = Convert.FromBase64String(signature);
                // Перевіряємо відповідність даних та підпису з використанням алгоритму SHA256
                return rsa.VerifyData(dataBytes, new SHA256CryptoServiceProvider(), signatureBytes);
            }
        }

        // Метод, що виконує перевірку підпису під час запуску програми
        private void CheckSignatureOnStartup()
        {
            // Зчитуємо підпис та публічний ключ з реєстру
            var (signature, publicKey) = ReadSignatureFromRegistry();

            // Якщо підпис або публічний ключ не знайдено (null або порожній рядок)
            if (string.IsNullOrEmpty(signature) || string.IsNullOrEmpty(publicKey))
            {
                // Виводимо повідомлення про помилку
                MessageBox.Show("Не вдалося знайти підпис або публічний ключ у реєстрі.");
                // Примусово завершуємо процес програми
                Process.GetCurrentProcess().Kill();
            }

            // Збираємо інформацію про поточний стан комп'ютера або програми (наприклад, шлях запуску)
            string currentInfo = CollectComputerInfo(Application.StartupPath);
            // Обчислюємо хеш від зібраної інформації
            string currentHash = ComputeHash(currentInfo);

            // Якщо перевірка підпису не пройшла
            if (!VerifySignature(currentHash, signature, publicKey))
            {
                // Виводимо повідомлення про невдалу перевірку підпису
                MessageBox.Show("Невдала перевірка підпису. Програма буде завершена.");
                // Примусово завершуємо процес програми
                Process.GetCurrentProcess().Kill();
            }
        }
    }
}
