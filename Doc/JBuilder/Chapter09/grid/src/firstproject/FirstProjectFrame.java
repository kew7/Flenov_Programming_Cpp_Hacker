
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
  ImageIcon image1;
  ImageIcon image2;
  ImageIcon image3;
  JLabel jLabel1 = new JLabel();
  JLabel jLabel2 = new JLabel();
  JTextField jTextField1 = new JTextField();
  JTextField jTextField2 = new JTextField();
  JLabel jLabel3 = new JLabel();
  JTextField jTextField3 = new JTextField();
  JLabel jLabel4 = new JLabel();
  JTextField jTextField4 = new JTextField();
  JLabel jLabel5 = new JLabel();
  JTextField jTextField5 = new JTextField();
  GridLayout gridLayout1 = new GridLayout();

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
    contentPane.setLayout(gridLayout1);
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
    jLabel1.setHorizontalAlignment(SwingConstants.CENTER);
    jLabel1.setText("jLabel1");
    contentPane.setDebugGraphicsOptions(0);
    jLabel2.setHorizontalAlignment(SwingConstants.CENTER);
    jLabel2.setText("jLabel2");
    jTextField1.setText("jTextField1");
    jTextField2.setText("jTextField2");
    jLabel3.setHorizontalAlignment(SwingConstants.CENTER);
    jLabel3.setText("jLabel3");
    jTextField3.setText("jTextField3");
    jLabel4.setHorizontalAlignment(SwingConstants.CENTER);
    jLabel4.setText("jLabel4");
    jTextField4.setText("jTextField4");
    jLabel5.setHorizontalAlignment(SwingConstants.CENTER);
    jLabel5.setText("jLabel5");
    jTextField5.setText("jTextField5");
    gridLayout1.setColumns(2);
    gridLayout1.setHgap(10);
    gridLayout1.setRows(5);
    gridLayout1.setVgap(10);
    menuFile.add(menuFileExit);
    menuHelp.add(menuHelpAbout);
    menuBar1.add(menuFile);
    menuBar1.add(menuHelp);
    contentPane.add(jLabel1, null);
    contentPane.add(jTextField1, null);
    contentPane.add(jLabel2, null);
    contentPane.add(jTextField2, null);
    contentPane.add(jLabel3, null);
    contentPane.add(jTextField3, null);
    contentPane.add(jLabel4, null);
    contentPane.add(jTextField4, null);
    contentPane.add(jLabel5, null);
    contentPane.add(jTextField5, null);
    this.setJMenuBar(menuBar1);
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
}