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
  JToggleButton jToggleButton1 = new JToggleButton();
  JTextArea jTextArea1 = new JTextArea();
  JButton jButton4 = new JButton();

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
    this.setSize(new Dimension(666, 337));
    this.setTitle("Start & Wait");
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
    jToolBar.setBounds(new Rectangle(-1, 0, 400, 32));
    jStartThreadBtn.setBounds(new Rectangle(17, 48, 134, 26));
    jStartThreadBtn.setFont(new java.awt.Font("Dialog", 1, 12));
    jStartThreadBtn.setActionCommand("Start thread");
    jStartThreadBtn.setText("Start calc");
    jStartThreadBtn.addActionListener(new Frame1_jStartThreadBtn_actionAdapter(this));
    jToggleButton1.setText("Start & Wait");
    jToggleButton1.setBounds(new Rectangle(19, 91, 132, 31));
    jToggleButton1.addActionListener(new Frame1_jToggleButton1_actionAdapter(this));
    jTextArea1.setToolTipText("");
    jTextArea1.setText("");
    jTextArea1.setLineWrap(true);
    jTextArea1.setWrapStyleWord(true);
    jTextArea1.setBounds(new Rectangle(164, 41, 494, 293));
    jButton4.setBounds(new Rectangle(21, 139, 129, 29));
    jButton4.setText("Properties");
    jButton4.addActionListener(new Frame1_jButton4_actionAdapter(this));
    jToolBar.add(jButton1);
    jToolBar.add(jButton2);
    jToolBar.add(jButton3);
    contentPane.add(jToolBar, null);
    jMenuFile.add(jMenuFileExit);
    jMenuHelp.add(jMenuHelpAbout);
    jMenuBar1.add(jMenuFile);
    jMenuBar1.add(jMenuHelp);
    this.setJMenuBar(jMenuBar1);
    contentPane.add(statusBar, null);
    contentPane.add(jStartThreadBtn, null);
    contentPane.add(jToggleButton1, null);
    contentPane.add(jTextArea1, null);
    contentPane.add(jButton4, null);
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
    Runtime r = Runtime.getRuntime();
    try{
      r.exec("calc");
    }
    catch(Exception ee){
    }
  }

  void jToggleButton1_actionPerformed(ActionEvent e) {
    Runtime r = Runtime.getRuntime();
    try{
      Process p = r.exec("calc");
      p.waitFor();
    }
    catch(Exception ee){
    }
  }

  void jButton4_actionPerformed(ActionEvent e) {
    System.out.println("file.separator "+System.getProperty("file.separator"));
    System.out.println("file.separator "+System.getProperty("file.separator"));
    System.out.println("line.separator "+System.getProperty("line.separator"));
    System.out.println("java.home "+System.getProperty("java.home"));
    System.out.println("java.vm.name "+System.getProperty("java.vm.name"));
    System.out.println("java.vm.vendor "+System.getProperty("java.vm.vendor"));
    System.out.println("java.vm.version "+System.getProperty("java.vm.version"));
    System.out.println("java.vendor "+System.getProperty("java.vendor"));
    System.out.println("java.version "+System.getProperty("java.version"));
    System.out.println("user.dir "+System.getProperty("user.dir"));
    System.out.println("user.home "+System.getProperty("user.home"));
    System.out.println("user.name "+System.getProperty("user.name"));
    System.out.println("os.name "+System.getProperty("os.name"));
    System.out.println("os.version "+System.getProperty("os.version"));
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

class Frame1_jToggleButton1_actionAdapter implements java.awt.event.ActionListener {
  Frame1 adaptee;

  Frame1_jToggleButton1_actionAdapter(Frame1 adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jToggleButton1_actionPerformed(e);
  }
}

class Frame1_jButton4_actionAdapter implements java.awt.event.ActionListener {
  Frame1 adaptee;

  Frame1_jButton4_actionAdapter(Frame1 adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jButton4_actionPerformed(e);
  }
}

