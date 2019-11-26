package awttest;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Frame1 extends JFrame {
  JPanel contentPane;
  JMenuBar jMenuBar1 = new JMenuBar();
  JMenu jMenuFile = new JMenu();
  JMenuItem jMenuFileExit = new JMenuItem();
  JMenu jMenuHelp = new JMenu();
  JMenuItem jMenuHelpAbout = new JMenuItem();
  JToolBar jToolBar = new JToolBar();
  JButton jButton1 = new JButton();
  JButton jButton2 = new JButton();
  JButton jButton3 = new JButton();
  ImageIcon image1;
  ImageIcon image2;
  ImageIcon image3;
  JLabel statusBar = new JLabel();
  JButton jStartThreadBtn = new JButton();
  JLabel jLabel1 = new JLabel();

  //Construct the frame
  public Frame1() {
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
    image1 = new ImageIcon(awttest.Frame1.class.getResource("openFile.png"));
    image2 = new ImageIcon(awttest.Frame1.class.getResource("closeFile.png"));
    image3 = new ImageIcon(awttest.Frame1.class.getResource("help.png"));
    contentPane = (JPanel) this.getContentPane();
    contentPane.setLayout(null);
    this.setSize(new Dimension(400, 300));
    this.setTitle("Frame Title");
    statusBar.setText(" ");
    statusBar.setBounds(new Rectangle(0, 284, 400, 16));
    jMenuFile.setText("File");
    jMenuFileExit.setText("Exit");
    jMenuFileExit.addActionListener(new Frame1_jMenuFileExit_ActionAdapter(this));
    jMenuHelp.setText("Help");
    jMenuHelpAbout.setText("About");
    jMenuHelpAbout.addActionListener(new Frame1_jMenuHelpAbout_ActionAdapter(this));
    jButton1.setIcon(image1);
    jButton1.setToolTipText("Open File");
    jButton2.setIcon(image2);
    jButton2.setToolTipText("Close File");
    jButton3.setIcon(image3);
    jButton3.setToolTipText("Help");
    jToolBar.setBounds(new Rectangle(0, 0, 400, 32));
    jStartThreadBtn.setBounds(new Rectangle(133, 140, 134, 26));
    jStartThreadBtn.setFont(new java.awt.Font("Dialog", 1, 12));
    jStartThreadBtn.setText("Start thread");
    jStartThreadBtn.addActionListener(new Frame1_jStartThreadBtn_actionAdapter(this));
    jLabel1.setText("jLabel1");
    jLabel1.setBounds(new Rectangle(173, 264, 41, 16));
    jToolBar.add(jButton1);
    jToolBar.add(jButton2);
    jToolBar.add(jButton3);
    jMenuFile.add(jMenuFileExit);
    jMenuHelp.add(jMenuHelpAbout);
    jMenuBar1.add(jMenuFile);
    jMenuBar1.add(jMenuHelp);
    this.setJMenuBar(jMenuBar1);
    contentPane.add(jToolBar, null);
    contentPane.add(statusBar, null);
    contentPane.add(jStartThreadBtn, null);
    contentPane.add(jLabel1, null);
  }
  //File | Exit action performed
  public void jMenuFileExit_actionPerformed(ActionEvent e) {
    System.exit(0);
  }
  //Help | About action performed
  public void jMenuHelpAbout_actionPerformed(ActionEvent e) {
  }
  //Overridden so we can exit when window is closed
  protected void processWindowEvent(WindowEvent e) {
    super.processWindowEvent(e);
    if (e.getID() == WindowEvent.WINDOW_CLOSING) {
      jMenuFileExit_actionPerformed(null);
    }
  }

  void jStartThreadBtn_actionPerformed(ActionEvent e) {
    String s1 = "Test";
    System.out.println(s1);

    char c[]={'T', 'e', 's', 't'};
    String s2 = new String(c);
    System.out.println(s2);

    String s3 = new String(c, 1, 2);
    System.out.println(s3);

    System.out.println("Длина строки s1 = "+s1.length());

    int l = "Test".length();

    String s = new String();
    for (int i=0; i<10; i++)
      s = s + i;
    System.out.println("s = "+s);

    String str = "В лему родилась елочка";
    int cstart = 5;
    int cend = 10;
    char buf[] = new char[cend-cstart];
    str.getChars(cstart, cend, buf,0);
    System.out.println(buf);

    if (s1 == "Test")
      System.out.println("s1 == 'Test' - Строки равны");
    else
      System.out.println("s1 == 'Test' - Строки не равны");

    if (s1.equals("тest"))
      System.out.println("s1.equals('Test') - Строки равны");
    else
      System.out.println("s1 == 'Test' - Строки не равны");

    if (s1.equalsIgnoreCase("test"))
      System.out.println("s1.equalsIgnoreCase('test') - Строки равны");
    else
      System.out.println("s1 == 'Test' - Строки не равны");

    String sort_arr[] = {
      "test", "rise", "man", "vr", "online", "horrific", "address", "sport"
    };

    for (int j = 0; j < sort_arr.length; j++) {
      for (int i = j + 1; i < sort_arr.length; i++) {
        if (sort_arr[i].compareTo(sort_arr[j]) < 0) {
          String t = sort_arr[j];
          sort_arr[j] = sort_arr[i];
          sort_arr[i] = t;
        }
      }
      System.out.println(sort_arr[j]);
    }

    StringBuffer sb = new StringBuffer("Тестовая строка буфера");
    System.out.println(sb);
  }
}

class Frame1_jMenuFileExit_ActionAdapter implements ActionListener {
  Frame1 adaptee;

  Frame1_jMenuFileExit_ActionAdapter(Frame1 adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jMenuFileExit_actionPerformed(e);
  }
}

class Frame1_jMenuHelpAbout_ActionAdapter implements ActionListener {
  Frame1 adaptee;

  Frame1_jMenuHelpAbout_ActionAdapter(Frame1 adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jMenuHelpAbout_actionPerformed(e);
  }
}

class Frame1_jStartThreadBtn_actionAdapter implements java.awt.event.ActionListener {
  Frame1 adaptee;

  Frame1_jStartThreadBtn_actionAdapter(Frame1 adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jStartThreadBtn_actionPerformed(e);
  }
}

