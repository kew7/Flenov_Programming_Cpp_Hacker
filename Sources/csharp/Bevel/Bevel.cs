using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace heaparessential.Controls
{
    public enum BevelStyle { Lowered, Raised };
    public enum BevelShape { Box, Frame, TopLine, BottomLine, LeftLine, RightLine, VerticalLine, HorizontalLine };

    [ToolboxBitmap(typeof(Bevel))]
    [System.ComponentModel.DesignerCategory("code")]
    public partial class Bevel : UserControl
    {
        Pen pen1, pen2;

        public Bevel()
        {
            InitializeComponent();
            Style = BevelStyle.Lowered;
            Shape = BevelShape.Box;
            Width = 40;
            Height = 40;
        }

        [Category("Style"), Description("Bevel style property")]
        BevelStyle style;
        public BevelStyle Style
        {
            get { return style; }
            set { style = value; Invalidate(); }
        }

        // Bevel shape property
        [Category("Style"), Description("Bevel shape")]
        BevelShape shape;
        public BevelShape Shape
        {
            get { return shape; }
            set { shape = value; Invalidate(); }
        }

        /// <summary>
        /// Paint bevel
        /// </summary>
        /// <param name="g"></param>
        /// <param name="rect"></param>
        void BevelRect(Graphics g, Rectangle rect)
        {
            g.DrawLine(pen1, new Point(rect.Left, rect.Top), new Point(rect.Left, rect.Bottom));
            g.DrawLine(pen1, new Point(rect.Left, rect.Top), new Point(rect.Right, rect.Top));

            g.DrawLine(pen2, new Point(rect.Right, rect.Top), new Point(rect.Right, rect.Bottom));
            g.DrawLine(pen2, new Point(rect.Right, rect.Bottom), new Point(rect.Left, rect.Bottom));
        }

        /// <summary>
        /// Paint control
        /// </summary>
        /// <param name="e"></param>
        protected override void OnPaint(PaintEventArgs e)
        {
            if (style == BevelStyle.Lowered)
            {
                pen1 = SystemPens.ButtonShadow;
                pen2 = SystemPens.ButtonHighlight;
            }
            else
            {
                pen1 = SystemPens.ButtonHighlight;
                pen2 = SystemPens.ButtonShadow;
            }

            // draw bevel
            switch (shape)
            {
                case BevelShape.Box:
                    BevelRect(e.Graphics, new Rectangle(0, 0, Width-1, Height-1));
                    break;
                case BevelShape.Frame:
                    Pen temp = pen1;
                    pen1 = pen2;
                    BevelRect(e.Graphics, new Rectangle(1, 1, Width-1, Height-1));
                    pen1 = temp;
                    pen2 = temp;
                    BevelRect(e.Graphics, new Rectangle(0, 0, Width-2, Height-2));
                    break;
                case BevelShape.TopLine:
                    e.Graphics.DrawLine(pen1, new Point(0, 0), new Point(Width - 1, 0));
                    e.Graphics.DrawLine(pen2, new Point(0, 1), new Point(Width - 1, 1));
                    break;
                case BevelShape.BottomLine:
                    e.Graphics.DrawLine(pen1, new Point(0, Height - 2), new Point(Width - 1, Height - 2));
                    e.Graphics.DrawLine(pen2, new Point(0, Height - 1), new Point(Width - 1, Height - 1));
                    break;
                case BevelShape.LeftLine:
                    e.Graphics.DrawLine(pen1, new Point(0, 0), new Point(0, Height - 1));
                    e.Graphics.DrawLine(pen2, new Point(1, 0), new Point(1, Height - 1));
                    break;
                case BevelShape.RightLine:
                    e.Graphics.DrawLine(pen1, new Point(Width - 2, 0), new Point(Width - 2, Height - 1));
                    e.Graphics.DrawLine(pen2, new Point(Width - 1, 0), new Point(Width - 1, Height - 1));
                    break;
                case BevelShape.VerticalLine:
                    e.Graphics.DrawLine(pen1, new Point(Width / 2, 0), new Point(Width / 2, Height - 1));
                    e.Graphics.DrawLine(pen2, new Point(Width / 2+1, 0), new Point(Width / 2+1, Height - 1));
                    break;
                case BevelShape.HorizontalLine:
                    e.Graphics.DrawLine(pen1, new Point(0, Height / 2), new Point(Width - 1, Height / 2));
                    e.Graphics.DrawLine(pen2, new Point(0, Height / 2+1), new Point(Width - 1, Height / 2+1));
                    break;
            }           
        }
    }
}
