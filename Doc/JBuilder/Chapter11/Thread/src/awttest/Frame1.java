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
  JButton jButton4 = new JButton();
  TestThread2 tt2;

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
    this.addWindowListener(new Frame1_this_windowAdapter(this));
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
    jStartThreadBtn.setBounds(new Rectangle(80, 108, 238, 26));
    jStartThreadBtn.setText("Start thread (Runnable interface)");
    jStartThreadBtn.addActionListener(new Frame1_jStartThreadBtn_actionAdapter(this));
    jLabel1.setText("jLabel1");
    jLabel1.setBounds(new Rectangle(19, 44, 366, 21));
    jButton4.setBounds(new Rectangle(77, 164, 241, 27));
    jButton4.setAlignmentY((float) 0.5);
    jButton4.setText("Start thread (Thread extends)");
    jButton4.addActionListener(new Frame1_jButton4_actionAdapter(this));
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
    contentPane.add(jLabel1, null);
    contentPane.add(jStartThreadBtn, null);
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
    // Start thread
    Thread t = Thread.currentThread();

    ThreadTest tt = new ThreadTest();
    try {
      for (int i=0; i<5; i++){
        System.out.println("First thread");
        t.sleep(1000);
      }
    } catch (InterruptedException ee){
      jLabel1.setText("Îøèáêà");
    }
  }

  void jButton4_actionPerformed(ActionEvent e) {
    tt2 = new TestThread2("Test Thread");
  }

  void this_windowClosing(WindowEvent e) {
    tt2.setPriority(tt2.getPriority()+1);
    if (tt2.isAlive())
      try {
        tt2.join();
      } catch (InterruptedException ee){
      }
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

class Frame1_jButton4_actionAdapter implements java.awt.event.ActionListener {
  Frame1 adaptee;

  Frame1_jButton4_actionAdapter(Frame1 adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jButton4_actionPerformed(e);
  }
}

class ThreadTest implements Runnable{
  Thread t;

  ThreadTest(){
    t = new Thread(this);
    t.start();
  }

  public void run(){
    try {
      for (int i=0; i<5; i++){
        System.out.println("Second thread " + i);
        t.sleep(1000);
      }
    }
    catch (InterruptedException ee){
      System.out.println("Îøèáêà");
    }
  }
}

class TestThread2 extends Thread{
  TestThread2(String s){
    super(s);
    start();
  }

  public void run(){
    try {
      for (int i=0; i<5; i++){
        System.out.println("Second thread " + i);
        sleep(1000);
      }
    }
    catch (InterruptedException ee){
      System.out.println("Îøèáêà");
    }
  }
}

class Frame1_this_windowAdapter extends java.awt.event.WindowAdapter {
  Frame1 adaptee;

  Frame1_this_windowAdapter(Frame1 adaptee) {
    this.adaptee = adaptee;
  }
  public void windowClosing(WindowEvent e) {
    adaptee.this_windowClosing(e);
  }
}
