
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
  JButton jButton8 = new JButton();
  JButton jButton4 = new JButton();
  JButton jButton5 = new JButton();
  JButton jButton6 = new JButton();
  JButton jButton7 = new JButton();

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
    jButton8.setBounds(new Rectangle(155, 112, 113, 26));
    jButton8.setText("Разбор");
    jButton8.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton8_actionPerformed(e);
      }
    });
    jButton4.setBounds(new Rectangle(154, 65, 114, 29));
    jButton4.setText("Битовый массив");
    jButton4.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton4_actionPerformed(e);
      }
    });
    jButton5.setBounds(new Rectangle(27, 65, 112, 30));
    jButton5.setText("Дата");
    jButton5.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton5_actionPerformed(e);
      }
    });
    jButton6.setBounds(new Rectangle(27, 108, 113, 32));
    jButton6.setText("Календарь");
    jButton6.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton6_actionPerformed(e);
      }
    });
    jButton7.setBounds(new Rectangle(28, 163, 112, 26));
    jButton7.setText("Random");
    jButton7.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton7_actionPerformed(e);
      }
    });
    toolBar.add(jButton1);
    toolBar.add(jButton2);
    toolBar.add(jButton3);
    contentPane.add(jButton7, null);
    contentPane.add(jButton4, null);
    contentPane.add(jButton8, null);
    contentPane.add(jButton6, null);
    contentPane.add(jButton5, null);
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
    String options = "1032;742;-4;-4;0;";
    StringTokenizer tokens = new StringTokenizer(options, ";");
    while (tokens.hasMoreTokens()){
      System.out.println(tokens.nextToken());
    }
  }

  void jButton4_actionPerformed(ActionEvent e) {
    BitSet b = new BitSet();
    b.set(1, true);
    b.set(4, true);
    System.out.println(b);
  }

  void jButton5_actionPerformed(ActionEvent e) {
    Date d = new Date();
    System.out.println(d);
  }

  void jButton6_actionPerformed(ActionEvent e) {
    Calendar c = Calendar.getInstance();

    System.out.println("Число: "+c.get(Calendar.DAY_OF_MONTH));
    System.out.println("Время: "+c.get(Calendar.HOUR)+":"+c.get(Calendar.MINUTE));
  }

  void jButton7_actionPerformed(ActionEvent e) {
    Random r = new Random();
    for (int i=0; i<10; i++)
      System.out.println(r.nextInt());
  }
}
