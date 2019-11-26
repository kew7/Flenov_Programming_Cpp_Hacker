import java.net.*;
import java.lang.*;
import java.util.*;
import java.awt.*;
import java.applet.*;
import javax.swing.*;

/**
 * <center><BR><H2><font color=#AA1B1B><B>CyD Software Labs</B></font></H2></center>
 * <center><font color=#AA1B1B><B>The best software for WEB designers and developers</B></font></center>
 * <BR><B>Title:</B>........Scinable Vertical Menu
 * <BR><B>Version:</B>........1.0
 * <BR><B>Description:</B>........A menu like interface for website navigational purpose
 * <BR><B>Copyright:</B>........Copyright (c) 2003
 * <BR><B>Company:</B>......CyD Software Labs
 * <BR><B>WWW:</B>......<a href="http://www.cydsoft.com">www.cydsoft.com</a>
 * <BR><B>E-mail:</B>......<a href="MailTo:info@cydsoft.com">info@cydsoft.com</a>

 * <P><B>Parameters:</B>
 * <LI>tips.............is the message of the day
 * <LI>img..............is the background image
 * <LI>menu1 - menuN....are the menu items
 * <LI>link1 - linkN....are the URLs
 * <LI>icon1 - iconN....are item icon
 * <P><B>Note:</B> This is a freeware but if you want to source code, visit our site <a href="http://www.cydsoft.com">www.cydsoft.com</a>
 */

public class ScinableVerticalMenu extends Applet
{
  // ========== Main variables =========== //
  Frame f;
  Image wallpaper;
  Image buffer=null;

  // ========== Menu variables =========== //
  Vector items=new Vector();
  Vector hrefs=new Vector();
  Vector Imgs=new Vector();
  Dimension d=getSize();
  boolean pop=true;
  int MenuWidth=100;
  int itemCount=0;
  int mouseX=0,mouseY=0;
  int menuY=0,menuEY=0;
  int fheight=0;

  // ========== Add menu item =========== //
  public void addItem(Image img, String caption, String href)
  {
    items.addElement(caption);
    hrefs.addElement(href);
    Imgs.addElement(img);
    itemCount++;
  }

  // ========== Mouse move =========== //
  public boolean mouseMove(Event e,int x,int y)
  {
    int tempY=0;
    mouseX=x;
    mouseY=y;
    repaint();
    return true;
  }

  // ========== Mouse up =========== //
  public boolean mouseUp(Event e,int x,int y)
  {
    int tempY=0,i=0,ix=0,iy=0,iex=0;
    mouseX=x;
    mouseY=y;
    if(pop&&(0<=mouseX)&&(menuY<mouseY)&&(MenuWidth>=mouseX)&&(menuEY>mouseY))
    {
       for(tempY=menuY;tempY<menuEY;tempY+=fheight,i++)
        if((tempY+8<mouseY)&&(tempY+fheight+8>mouseY))
        {
           repaint(0,tempY+8,MenuWidth,tempY+fheight+8);
           showStatus("Select "+i+" is "+items.elementAt(i)+" Link To "+hrefs.elementAt(i));
           break;
        }
       do_menu(i);
    }
   return true;
  }

  // ========== Update =========== //
  public void update(Graphics g)
  {
    paint(g);
  }

  // ========== Image Update =========== //
  public boolean imageUpdate(Image img,int flags,int x,int y, int w,int h)
  {
  if((flags&SOMEBITS)!=0){repaint(x,y,w,h);
  } else if((flags&ABORT)!=0)
  {repaint();}
  return(flags&(ALLBITS|ABORT))==0;
  }

  // ========== Paint =========== //
  public void paint(Graphics g)
  {
    Graphics screengc=null;
    screengc=g;
    g=buffer.getGraphics();
    int i=0;
    String str;
    int y=0;
    int ix=0,iy=0,iex=0;

    d=getSize();
    MenuWidth=(int)d.getWidth();

    fheight = (int)(d.getHeight()/itemCount);

    if(wallpaper!=null) g.drawImage(wallpaper,0,0,d.width,d.height-8,this);

    if(pop&&(itemCount>0))
    {
      y=d.height-8;
      menuEY=y;
      for(i=itemCount-1;i>=0;i--)
      {
        g.setColor(Color.blue);

        if ((0<=mouseX) && (y-fheight+8<=mouseY) && (MenuWidth>=mouseX) && (y+8>=mouseY))
          g.fill3DRect(1, y-fheight+9, MenuWidth-2, fheight-2, false);
        else
          g.fill3DRect(0, y-fheight+8, MenuWidth, fheight, true);

        Image ItemIcon = (Image) Imgs.elementAt(i);
        if(ItemIcon!=null)
          g.drawImage(ItemIcon,8, y-(int)((fheight)/2), 16, 16, this);

        g.setColor(Color.white);
        g.drawString((String) items.elementAt(i), 32, y+4-(int)((fheight-g.getFontMetrics().getHeight())/2));
        y-=fheight;
      }
      menuY=y;
    }
    screengc.drawImage(buffer,0,0,null);
 }

 // ========== Menu Handler =========== //
 public void do_menu(int i)
 {
   String link=(String)hrefs.elementAt(i);

   if(link.startsWith("popup:"))
   {
   f=new MsgWnd("ScinableVerticalMenu message",link.substring(6));
   f.show();
   }else
   {
    try{getAppletContext().showDocument(new URL(link));}
    catch(MalformedURLException er)
    {
    f=new MsgWnd("ScinableVerticalMenu error","page not found:\n"+link);
    f.show();
    }
   }
 }

 // ========== Initialization =========== //
 public void init()
 {
   int i=0;
   setBackground(Color.cyan);
   d=getSize();
   buffer=createImage(d.width,d.height);

   if(getParameter("tips")!=null)
   {
     f=new MsgWnd("Tips of the day..!",getParameter("tips"));
     f.show();
   }

   if(getParameter("img")!=null)
     wallpaper=getImage(getDocumentBase(),getParameter("img"));

  for(i=1;getParameter("menu"+i)!=null;i++)
    addItem(getImage(getDocumentBase(),getParameter("icon"+i)),
     getParameter("menu"+i),
     (getParameter("link"+i)!=null)?getParameter("link"+i):"none"
    );
 }
}
