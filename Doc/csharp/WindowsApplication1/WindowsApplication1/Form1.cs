using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Reflection;

namespace WindowsApplication1
{
	class Form1
	{
	}
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
			PropertiesClass tempClass = new PropertiesClass();
			propertyGrid1.SelectedObject = tempClass;

			Type type = tempClass.GetType();
			PropertyInfo[] pi = type.GetProperties();

			for (int i=0; i<pi.Length; i++)
			{
				foreach (Attribute attr in
					Attribute.GetCustomAttributes(pi[i]))
				{
					if (attr.GetType() == typeof(CategoryAttribute))
						MessageBox.Show(pi[i].Name+" находиться в категории "+((CategoryAttribute)attr).Category.ToString());
				}
			}
		}
	}
}