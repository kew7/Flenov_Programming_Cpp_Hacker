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
		 Category("Подключение"), 
		 Description("Имя сервера базы данных"),
		 DisplayName("Сервер базы данных"),
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
		 Category("Форма"),
		 DisplayName("Цвет фона"),
		 Description("Этот параметр устанавливает цвет фона")
		]
		public Color BakColor
		{
			get { return bakColor; }
			set { bakColor = value; }
		}
	}
}
