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
  Label label1 = new Label();
  Button button1 = new Button();
  Checkbox checkbox1 = new Checkbox();
  CheckboxGroup checkboxGroup1 = new CheckboxGroup();
  Checkbox checkbox2 = new Checkbox();
  Checkbox checkbox3 = new Checkbox();
  Choice choice1 = new Choice();
  List list1 = new List();
  Scrollbar scrollbar1 = new Scrollbar();
  Label label2 = new Label();
  TextArea textArea1 = new TextArea();
  TextField textField1 = new TextField();
  Panel panel1 = new Panel();
  ScrollPane scrollPane1 = new ScrollPane();
  MenuBar menuBar1 = new MenuBar();
  Menu menuItemFile = new Menu();
  Menu menuItemHelp = new Menu();
  MenuItem menuItem1 = new MenuItem();

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
  private void jbInit() throws Exception {
    image1 = new ImageIcon(awttest.Frame1.class.getResource("openFile.png"));
    image2 = new ImageIcon(awttest.Frame1.class.getResource("closeFile.png"));
    image3 = new ImageIcon(awttest.Frame1.class.getResource("help.png"));
    contentPane = (JPanel) this.getContentPane();
    contentPane.setLayout(null);
    this.setFont(new java.awt.Font("SansSerif", 2, 12));
    this.setSize(new Dimension(550, 300));
    this.setTitle("Frame Title");
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
    label1.setAlignment(Label.LEFT);
    label1.setFont(new java.awt.Font("Dialog", 2, 12));
    label1.setForeground(Color.black);
    label1.setLocale(java.util.Locale.getDefault());
    label1.setText("label1");
    label1.setBounds(new Rectangle(27, 52, 54, 16));
    button1.setLabel("button1");
    button1.setBounds(new Rectangle(24, 83, 77, 26));
    button1.addActionListener(new Frame1_button1_actionAdapter(this));
    checkbox1.setLabel("checkbox1");
    checkbox1.setLocale(java.util.Locale.getDefault());
    checkbox1.setState(false);
    checkbox1.setBounds(new Rectangle(27, 131, 88, 24));
    checkbox2.setCheckboxGroup(checkboxGroup1);
    checkbox2.setLabel("checkbox2");
    checkbox2.setState(true);
    checkbox2.setBounds(new Rectangle(27, 175, 88, 24));
    checkbox3.setCheckboxGroup(checkboxGroup1);
    checkbox3.setLabel("checkbox3");
    checkbox3.setBounds(new Rectangle(27, 202, 88, 24));
    contentPane.setBackground(SystemColor.control);
    choice1.setBounds(new Rectangle(26, 243, 162, 22));
    list1.setBounds(new Rectangle(213, 52, 162, 64));
    scrollbar1.setBlockIncrement(10);
    scrollbar1.setLocale(java.util.Locale.getDefault());
    scrollbar1.setOrientation(0);
    scrollbar1.setUnitIncrement(5);
    scrollbar1.setValue(10);
    scrollbar1.setBounds(new Rectangle(208, 141, 166, 20));
    scrollbar1.addAdjustmentListener(new Frame1_scrollbar1_adjustmentAdapter(this));
    label2.setText("label2");
    label2.setBounds(new Rectangle(211, 123, 91, 16));
    textArea1.setText("textArea1");
    textArea1.setBounds(new Rectangle(212, 176, 162, 71));
    textField1.setText("textField1");
    textField1.setBounds(new Rectangle(211, 257, 162, 20));
    panel1.setBounds(new Rectangle(395, 55, 132, 59));
    scrollPane1.setBounds(new Rectangle(395, 135, 133, 65));
    menuItemFile.setLabel("File");
    menuItemHelp.setLabel("Help");
    menuItem1.setLabel("New");
    jToolBar.add(jButton1);
    jToolBar.add(jButton2);
    jToolBar.add(jButton3);
    jMenuFile.add(jMenuFileExit);
    jMenuHelp.add(jMenuHelpAbout);
    jMenuBar1.add(jMenuFile);
    jMenuBar1.add(jMenuHelp);
    this.setJMenuBar(jMenuBar1);
    contentPane.add(jToolBar, null);
    contentPane.add(label1, null);
    contentPane.add(button1, null);
    contentPane.add(checkbox1, null);
    contentPane.add(checkbox2, null);
    contentPane.add(checkbox3, null);
    contentPane.add(choice1, null);
    contentPane.add(label2, null);
    contentPane.add(scrollbar1, null);
    contentPane.add(list1, null);
    contentPane.add(textArea1, null);
    contentPane.add(textField1, null);
    contentPane.add(panel1, null);
    contentPane.add(scrollPane1, null);
    choice1.add("Один");
    choice1.addItem("Два");
    choice1.addItem("Три");

    list1.add("Один");
    list1.add("Два");
    list1.add("Три");
    menuBar1.add(menuItemFile);
    menuBar1.add(menuItemHelp);
    menuItemFile.add(menuItem1);

    label1.getBounds();
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

  void button1_actionPerformed(ActionEvent e) {
    label1.setText(choice1.getSelectedItem());
  }

  void scrollbar1_adjustmentValueChanged(AdjustmentEvent e) {
    label2.setText("Значение: "+scrollbar1.getValue());
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

class Frame1_button1_actionAdapter implements java.awt.event.ActionListener {
  Frame1 adaptee;

  Frame1_button1_actionAdapter(Frame1 adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.button1_actionPerformed(e);
  }
}

class Frame1_scrollbar1_adjustmentAdapter implements java.awt.event.AdjustmentListener {
  Frame1 adaptee;

  Frame1_scrollbar1_adjustmentAdapter(Frame1 adaptee) {
    this.adaptee = adaptee;
  }
  public void adjustmentValueChanged(AdjustmentEvent e) {
    adaptee.scrollbar1_adjustmentValueChanged(e);
  }
}