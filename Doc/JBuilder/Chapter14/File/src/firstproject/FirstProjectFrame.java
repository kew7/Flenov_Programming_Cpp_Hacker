
/**
 * Title:        First project<p>
 * Description:  <p>
 * Copyright:    Copyright (c) Flenov Mikhail<p>
 * Company:      CyD Software Labs<p>
 * @author Flenov Mikhail
 * @version 1.0
 */
package firstproject;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;
import java.io.*;

public class FirstProjectFrame extends JFrame {
  JPanel contentPane;
  JMenuBar menuBar1 = new JMenuBar();
  JMenu menuFile = new JMenu();
  JMenuItem menuFileExit = new JMenuItem();
  JMenu menuHelp = new JMenu();
  JMenuItem menuHelpAbout = new JMenuItem();
  JToolBar toolBar = new JToolBar();
  JButton jButton1 = new JButton();
  JButton jButton2 = new JButton();
  JButton jButton3 = new JButton();
  ImageIcon image1;
  ImageIcon image2;
  ImageIcon image3;
  JButton jButton5 = new JButton();
  JButton jButton4 = new JButton();
  JButton jButton6 = new JButton();
  JButton jButton7 = new JButton();
  JButton jButton8 = new JButton();
  JButton jButton9 = new JButton();
  JButton jButton10 = new JButton();
  JButton jButton11 = new JButton();

  //Construct the frame
  public FirstProjectFrame() {
    enableEvents(AWTEvent.WINDOW_EVENT_MASK);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }

  //Component initialization
  private void jbInit() throws Exception  {
    image1 = new ImageIcon(FirstProjectFrame.class.getResource("openFile.gif"));
    image2 = new ImageIcon(FirstProjectFrame.class.getResource("closeFile.gif"));
    image3 = new ImageIcon(FirstProjectFrame.class.getResource("help.gif"));
    contentPane = (JPanel) this.getContentPane();
    contentPane.setLayout(null);
    this.setSize(new Dimension(374, 310));
    this.setTitle("My First Project");
    menuFile.setText("File");
    menuFileExit.setText("Exit");
    menuFileExit.addActionListener(new ActionListener()  {
      public void actionPerformed(ActionEvent e) {
        fileExit_actionPerformed(e);
      }
    });
    menuHelp.setText("Help");
    menuHelpAbout.setText("About");
    menuHelpAbout.addActionListener(new ActionListener()  {
      public void actionPerformed(ActionEvent e) {
        helpAbout_actionPerformed(e);
      }
    });
    jButton1.setIcon(image1);
    jButton1.setToolTipText("Open File");
    jButton2.setIcon(image2);
    jButton2.setToolTipText("Close File");
    jButton3.setIcon(image3);
    jButton3.setToolTipText("Help");
    contentPane.setMaximumSize(new Dimension(2147483647, 2147483647));
    toolBar.setBounds(new Rectangle(0, 0, 374, 33));
    jButton5.setBounds(new Rectangle(23, 65, 125, 29));
    jButton5.setText("Файл");
    jButton5.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton5_actionPerformed(e);
      }
    });
    jButton4.setBounds(new Rectangle(23, 104, 125, 29));
    jButton4.setText("Директория");
    jButton4.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton4_actionPerformed(e);
      }
    });
    jButton6.setBounds(new Rectangle(23, 142, 125, 29));
    jButton6.setText("Фильтр");
    jButton6.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton6_actionPerformed(e);
      }
    });
    jButton7.setBounds(new Rectangle(23, 180, 125, 29));
    jButton7.setOpaque(true);
    jButton7.setToolTipText("");
    jButton7.setText("FileInputStream");
    jButton7.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton7_actionPerformed(e);
      }
    });
    jButton8.setBounds(new Rectangle(23, 219, 125, 29));
    jButton8.setText("FileOutputStream");
    jButton8.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton8_actionPerformed(e);
      }
    });
    jButton9.setBounds(new Rectangle(188, 65, 113, 29));
    jButton9.setToolTipText("");
    jButton9.setText("BufferedInput");
    jButton9.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton9_actionPerformed(e);
      }
    });
    jButton10.setBounds(new Rectangle(187, 105, 115, 30));
    jButton10.setText("Serializable");
    jButton10.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton10_actionPerformed(e);
      }
    });
    jButton11.setBounds(new Rectangle(188, 145, 115, 30));
    jButton11.setText("Deserializable");
    jButton11.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton11_actionPerformed(e);
      }
    });
    toolBar.add(jButton1);
    toolBar.add(jButton2);
    toolBar.add(jButton3);
    contentPane.add(jButton11, null);
    contentPane.add(jButton10, null);
    contentPane.add(jButton9, null);
    contentPane.add(jButton8, null);
    contentPane.add(jButton7, null);
    contentPane.add(jButton4, null);
    contentPane.add(jButton5, null);
    contentPane.add(jButton6, null);
    menuFile.add(menuFileExit);
    menuHelp.add(menuHelpAbout);
    menuBar1.add(menuFile);
    menuBar1.add(menuHelp);
    this.setJMenuBar(menuBar1);
    contentPane.add(toolBar, null);
  }

  //File | Exit action performed
  public void fileExit_actionPerformed(ActionEvent e) {
    System.exit(0);
  }

  //Help | About action performed
  public void helpAbout_actionPerformed(ActionEvent e) {
    FirstProjectFrame_AboutBox dlg = new FirstProjectFrame_AboutBox(this);
    Dimension dlgSize = dlg.getPreferredSize();
    Dimension frmSize = getSize();
    Point loc = getLocation();
    dlg.setLocation((frmSize.width - dlgSize.width) / 2 + loc.x, (frmSize.height - dlgSize.height) / 2 + loc.y);
    dlg.setModal(true);
    dlg.show();
  }

  //Overridden so we can exit when window is closed
  protected void processWindowEvent(WindowEvent e) {
    super.processWindowEvent(e);
    if (e.getID() == WindowEvent.WINDOW_CLOSING) {
      fileExit_actionPerformed(null);
    }
  }

  void jButton5_actionPerformed(ActionEvent e) {
    File f = new File("c:\\autoexec.bat");
    System.out.println("Name:  "+f.getName());
    System.out.println("Parent:"+f.getParent());
    System.out.println("Read:  "+f.canRead());
    System.out.println("Write: "+f.canWrite());
  }

  void jButton4_actionPerformed(ActionEvent e) {
    File f = new File("c:\\");

    String s[] = f.list();
    for (int i=0; i<s.length; i++)
    {
      File ff = new File("c:\\"+s[i]);
      if (ff.isDirectory())
        System.out.println(s[i]+" - директория");
      else
        System.out.println(s[i]+" - файл");
    }
  }

  void jButton6_actionPerformed(ActionEvent e) {
    File f = new File("c:\\");

    FileFilt filter = new FileFilt();

    String s[] = f.list(filter);

    for (int i=0; i<s.length; i++)
    {
      File ff = new File("c:\\"+s[i]);
      if (ff.isDirectory())
        System.out.println(s[i]+" - директория");
      else
        System.out.println(s[i]+" - файл");
    }
  }

  void jButton7_actionPerformed(ActionEvent e) {
    try{
      FileInputStream is = new FileInputStream("c:\\1.txt");
      while (is.available()>0)
        System.out.print((char)is.read());
    }
    catch (Exception ee){}
  }

  void jButton8_actionPerformed(ActionEvent e) {
    try{
      FileOutputStream is = new FileOutputStream("c:\\1.txt");
      String s = "Hello";
      is.write(s.getBytes());
      is.close();
    }
    catch (Exception ee){}
  }

  void jButton9_actionPerformed(ActionEvent e) {
    String s = "This is a [bold] symbol. This is a [bo ld] error";
    byte buf[] = s.getBytes();
    ByteArrayInputStream in = new ByteArrayInputStream(buf);
    BufferedInputStream f = new BufferedInputStream(in);
    boolean bMarked = false;

    int ch;
    try{
      while ((ch = f.read()) != -1) {
        switch(ch) {
        case '[':
          if (!bMarked) {
            f.mark(32);
            bMarked = true;
          }
          else
            bMarked = false;
          break;
        case ']':
          if (bMarked) {
            bMarked = false;
            System.out.print("<b>");
          }
          else
            System.out.print((char) ch);
          break;
        case ' ':
          if (bMarked) {
            bMarked = false;
            f.reset();
            System.out.print("[");
          }
          else
            System.out.print((char) ch);
          break;
       default:
         if (!bMarked)
             System.out.print((char) ch);
         break;
        }
      }
    }
    catch (Exception eee){}
  }

  void jButton10_actionPerformed(ActionEvent e) {
    // Создать объект
    ObjectSave os = new ObjectSave();
    os.setINumber(10);
    os.setSName("Michael");
    os.setSTrans("Trans");

    try{
      // Создать потоки
      FileOutputStream fOut = new FileOutputStream("object.data");
      ObjectOutputStream oOut = new ObjectOutputStream(fOut);

      // Сохранить объект
      oOut.writeObject(os);
      oOut.flush();

      oOut.close();
      fOut.close();
    }
    catch(Exception ee){}
  }

  void jButton11_actionPerformed(ActionEvent e) {
    try{
      // Создать потоки
      FileInputStream fIn = new FileInputStream("object.data");
      ObjectInputStream oIn = new ObjectInputStream(fIn);

      // Загрузить объект
      ObjectSave os = (ObjectSave)oIn.readObject();

      System.out.println(os.getINumber());
      System.out.println(os.getSName());
      System.out.println(os.getSTrans());

      oIn.close();
      fIn.close();
    }
    catch(Exception ee){}
  }
}

class FileFilt implements FilenameFilter{
  public boolean accept(File d, String n){
    File f = new File(d, n);
    if (f.isDirectory())
      return false;

    return n.endsWith(".txt");
  }
}

class ObjectSave implements Serializable{
  int iNumber=0;
  String sName = "";
  transient String sTrans="Default";

  public void setINumber(int v){
   iNumber = v;
  }

  public void setSName(String s){
   sName = s;
  }

  public int getINumber(){
   return iNumber;
  }

  public String getSName(){
   return sName;
  }

  public void setSTrans(String s){
   sTrans = s;
  }

  public String getSTrans(){
   return sTrans;
  }
}
