using System;
using System.Data;
using System.IO;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Management;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace ZIKS_Lab2
{
    public partial class Form1 : Form
    {
        private ManagementObjectSearcher usbSearcher; 
        private string savedSerial = null; 

       
        public Form1()
        {
            InitializeComponent();
            LoadSavedSerial(); 
            LoadUSBDevices(); 
        }

        // Завантаження збереженого серійного номера з файлу
        private void LoadSavedSerial()
        {
            if (System.IO.File.Exists("id.pas")) 
            {
                savedSerial = File.ReadAllText("id.pas").Trim();
                VerifyUSBSerial();
            }
        }

        // Завантажує підключені USB пристрої в комбобокс
        private void LoadUSBDevices()
        {
            comboBox1.Items.Clear();
            // Створюємо запит для пошуку USB пристроїв
            usbSearcher = new ManagementObjectSearcher("SELECT * FROM Win32_DiskDrive WHERE InterfaceType='USB'"); 
            var usbDevices = usbSearcher.Get().Cast<ManagementObject>().ToList(); // Отримуємо всі підключені USB пристрої

            // Перевіряємо, чи є підключені пристрої
            if (usbDevices.Count == 0)
            {
                MessageBox.Show("Не знайдено підключених USB пристроїв!");
                return;
            }
            foreach (ManagementObject usb in usbDevices) 
            {
                comboBox1.Items.Add(usb["DeviceID"].ToString()); 
            }
            if (comboBox1.Items.Count > 0)
                comboBox1.SelectedIndex = 0;
        }

        // Перевірка на серійний номер з файлу
        private void VerifyUSBSerial()
        {
            if (string.IsNullOrEmpty(savedSerial)) return;

            int count = 0;

            // Створюємо запит для пошуку USB пристроїв з відповідним серійним номером
            usbSearcher = new ManagementObjectSearcher("SELECT * FROM Win32_DiskDrive WHERE InterfaceType='USB'");
            foreach (ManagementObject usb in usbSearcher.Get())
            {
                string serialNumber = GetSerialNumber(usb["DeviceID"].ToString());

                // Перевіряємо чи серійний номер з файлу співпадає з серійним номером підключеного пристрою
                if (serialNumber == savedSerial)
                {
                    count++;
                    break;  // Якщо знайдений відповідний серійний номер, виходимо з циклу
                }
            }

            // Якщо знайдено відповідний пристрій, повідомляємо про успішну перевірку
            if (count != 0)
            {
                MessageBox.Show("Ваш цифровий пароль прийнято!");
            }
            else
            {
                // Якщо серійний номер не знайдено, завершуємо процес
                MessageBox.Show("Цифровий пароль не прийнято. Завершення роботи.");
                Process.GetCurrentProcess().Kill();
            }
        }
        private void button2_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(savedSerial)) // Якщо серійний номер не збережений
            {
                MessageBox.Show("Немає збереженого серійного номера!"); 
                return;
            }

            // Пошук відповідного USB пристрою за серійним номером
            foreach (ManagementObject usb in usbSearcher.Get())
            {
                string serial = GetSerialNumber(usb["DeviceID"].ToString()); // Отримуємо серійний номер пристрою
                if (serial == savedSerial) 
                {
                    MessageBox.Show("USB-ключ знайдено і підтверджено!"); 
                    return;
                }
            }

            MessageBox.Show("USB-ключ не знайдено!"); 
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string selectedDevice = comboBox1.SelectedItem?.ToString();
            if (string.IsNullOrEmpty(selectedDevice))
            {
                MessageBox.Show("Не вибрано жодного пристрою.");
                return;
            }

            string serial = GetSerialNumber(selectedDevice); // Отримуємо серійний номер вибраного пристрою

            if (string.IsNullOrEmpty(serial) || serial == "Не знайдено") // Перевірка на успішність отримання серійного номера
            {
                MessageBox.Show("Серійний номер не знайдено! ");
                return;
            }

            File.WriteAllText("id.pas", serial);
            MessageBox.Show("Серійний номер збережено!");
        }


        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            string selectedDevice = comboBox1.SelectedItem.ToString();
            foreach (ManagementObject usb in usbSearcher.Get()) // Перебираємо всі знайдені пристрої
            {
                if (usb["DeviceID"].ToString() == selectedDevice) // Якщо знайдений вибраний пристрій
                {
                    string serial = GetSerialNumber(selectedDevice); // Отримуємо серійний номер
                    label1.Text = "Модель: " + usb["Model"]; // Виводимо модель пристрою
                    label2.Text = "Тип: " + usb["Description"]; // Виводимо тип пристрою
                    label3.Text = "Серійний номер: " + serial; // Виводимо серійний номер
                    label4.Text = "Розмір: " + Math.Round(Convert.ToDouble(usb["Size"]) / 1073741824, 1) + " ГБ"; // Виводимо розмір пристрою в ГБ
                    textBox1.Text = serial; // Виводимо серійний номер в текстове поле

                    break; 
                }
            }
        }

        // Отримує серійний номер для заданого пристрою
        private string GetSerialNumber(string deviceId)
        {
            foreach (ManagementObject disk in new ManagementObjectSearcher(
                "SELECT * FROM Win32_LogicalDisk WHERE DriveType=2").Get()) 
            {
                string driveLetter = disk["DeviceID"].ToString(); 
                uint serialNumber;
                uint maxComponentLength;
                uint fileSystemFlags;
                StringBuilder fileSystemName = new StringBuilder(256);
                StringBuilder volumeName = new StringBuilder(256);

                bool success = GetVolumeInformation(driveLetter + "\\", volumeName, (uint)volumeName.Capacity,
                    out serialNumber, out maxComponentLength, out fileSystemFlags, fileSystemName, (uint)fileSystemName.Capacity); // Отримуємо інформацію про том

                if (success) 
                {
                    return $"{serialNumber}"; 
                }
            }

            return "Не знайдено";
        }

        // функція отримує інформацію про файлову систему та серійний номер
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern bool GetVolumeInformation(
            string lpRootPathName,
            StringBuilder lpVolumeNameBuffer,
            uint nVolumeNameSize,
            out uint lpVolumeSerialNumber,
            out uint lpMaximumComponentLength,
            out uint lpFileSystemFlags,
            StringBuilder lpFileSystemNameBuffer,
            uint nFileSystemNameSize);
    }
}
