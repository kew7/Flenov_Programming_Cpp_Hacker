
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
import java.net.*;
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
  JButton jButton8 = new JButton();
  JButton jButton4 = new JButton();
  JButton jButton5 = new JButton();

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
    this.setSize(new Dimension(374, 286));
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
    jButton8.setBounds(new Rectangle(26, 46, 113, 26));
    jButton8.setText("Address");
    jButton8.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton8_actionPerformed(e);
      }
    });
    jButton4.setBounds(new Rectangle(24, 85, 113, 25));
    jButton4.setText("URL");
    jButton4.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton4_actionPerformed(e);
      }
    });
    jButton5.setBounds(new Rectangle(24, 119, 112, 27));
    jButton5.setText("URLConnection");
    jButton5.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton5_actionPerformed(e);
      }
    });
    toolBar.add(jButton1);
    toolBar.add(jButton2);
    toolBar.add(jButton3);
    contentPane.add(jButton4, null);
    contentPane.add(jButton5, null);
    contentPane.add(jButton8, null);
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

  void jButton8_actionPerformed(ActionEvent e) {
    try{
      InetAddress ia = InetAddress.getLocalHost();
      System.out.println(ia);

      InetAddress iaAll[] = InetAddress.getAllByName("www.vr-online.ru");
    }
    catch (Exception ee){}
  }

  void jButton4_actionPerformed(ActionEvent e) {
    try{
      URL uCon = new URL("http://www.vr-online.ru/");
      System.out.println(uCon.getDefaultPort());
    }
    catch(Exception ee){}
  }

  void jButton5_actionPerformed(ActionEvent e) {
    try {
      URL url = new URL("http://www.vr-online.ru/index.php");
      URLConnection urlCon = url.openConnection();

      System.out.println("Date: " + new Date(urlCon.getDate()));
      System.out.println("Type: " + urlCon.getContentType());
      System.out.println("Modified: " + new Date(urlCon.getLastModified()));
      System.out.println("Length: " + urlCon.getContentLength());
      if (urlCon.getContentLength() > 0) {
        System.out.println("Content:");
        InputStream input = urlCon.getInputStream();
        int i = urlCon.getContentLength();
        int c;
        while (((c = input.read()) != -1) && (--i > 0)) {
          System.out.print((char) c);
        }
        input.close();
      }
    }
    catch(Exception ee){}
  }
}
