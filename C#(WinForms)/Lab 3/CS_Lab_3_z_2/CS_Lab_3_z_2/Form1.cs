﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CS_Lab_3_z_2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // добавляем новый элемент в список
            listView1.Items.Add(textBox1.Text);

        }

        private void button2_Click(object sender, EventArgs e)
        {
            // получаем выделенный узел
            TreeNode node = treeView1.SelectedNode;
            // если выделенного узла нет
            if (node == null)
            {   // добавляем новый элемент
                // в корень основного дерева
                treeView1.Nodes.Add(textBox1.Text);
            }
            // если имеется выделенный узел
            else
            {   // добавляем новый элемент
                // как вложенный в выделенный узел
                node.Nodes.Add(textBox1.Text);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            foreach (ListViewItem item in listView1.SelectedItems)
            {
                listView1.Items.Remove(item);
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (treeView1.SelectedNode != null)
            {
                treeView1.Nodes.Remove(treeView1.SelectedNode);
            }
        }
        

        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {

        }
    }
}
