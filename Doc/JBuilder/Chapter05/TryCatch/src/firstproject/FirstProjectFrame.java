
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
  JLabel statusBar = new JLabel();
  BorderLayout borderLayout1 = new BorderLayout();
  JPanel jPanel1 = new JPanel();
  JButton jButton4 = new JButton();
  JLabel jLabel1 = new JLabel();

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
    contentPane.setLayout(borderLayout1);
    this.setSize(new Dimension(374, 286));
    this.setTitle("My First Project");
    statusBar.setText(" ");
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
    jPanel1.setBackground(Color.white);
    jPanel1.setBorder(BorderFactory.createLineBorder(Color.black));
    jPanel1.setLayout(null);
    jButton4.setText("jButton4");
    jButton4.setBounds(new Rectangle(214, 33, 81, 27));
    jButton4.addActionListener(new java.awt.event.ActionListener() {

      public void actionPerformed(ActionEvent e) {
        jButton4_actionPerformed(e);
      }
    });
    jLabel1.setText("jLabel1");
    jLabel1.setBounds(new Rectangle(16, 10, 338, 16));
    toolBar.add(jButton1);
    toolBar.add(jButton2);
    toolBar.add(jButton3);
    menuFile.add(menuFileExit);
    menuHelp.add(menuHelpAbout);
    menuBar1.add(menuFile);
    menuBar1.add(menuHelp);
    this.setJMenuBar(menuBar1);
    contentPane.add(toolBar, BorderLayout.NORTH);
    contentPane.add(statusBar, BorderLayout.WEST);
    contentPane.add(jPanel1, BorderLayout.CENTER);
    jPanel1.add(jButton4, null);
    jPanel1.add(jLabel1, null);
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

  int TryExcept(int x, int y) throws ArithmeticException{
    if (y==0)
      throw new ArithmeticException();
    else
      return x/y;
  }

  void TryArray(){
    try {
      int a[] = new int[10];
      a[11]=12;
      throw new ArithmeticException();
    }
    catch (ArithmeticException ex){
      jLabel1.setText(ex.toString());
    }
  }

  void jButton4_actionPerformed(ActionEvent e) {
    try{
      int i=1;
      int j=10/i;

      TryArray();
    }
    catch(ArithmeticException ex){
      jLabel1.setText(ex.toString());
    }
    catch (ArrayIndexOutOfBoundsException ex){
      jLabel1.setText(ex.toString());
    }

    try{
      TryExcept(10, 0);
    }
    catch (ArithmeticException ex){

    }
  }
}
