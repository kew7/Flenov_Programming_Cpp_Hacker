using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Drawing;

namespace WindowsApplication1
{
	class PropertiesClass
	{
		#region DatabaseConnection

		private string serverName;

		[
		 Category("�����������"), 
		 Description("��� ������� ���� ������"),
		 DisplayName("������ ���� ������"),
		 DefaultValue("MyServer")
		]
		public string ServerName
		{
			get { return serverName; }
			set { serverName = value; }
		}

		#endregion DatabaseConnection

		private Color bakColor;

		[
		 Category("�����"),
		 DisplayName("���� ����"),
		 Description("���� �������� ������������� ���� ����")
		]
		public Color BakColor
		{
			get { return bakColor; }
			set { bakColor = value; }
		}
	}
}
