
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
  Button button1 = new Button();
  Button button4 = new Button();
  JLabel jLabel1 = new JLabel();
  JLabel jLabel2 = new JLabel();
  JRadioButton jRadioButton1 = new JRadioButton();
  GridBagLayout gridBagLayout1 = new GridBagLayout();

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
    contentPane.setLayout(gridBagLayout1);
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
    button1.setActionCommand("button1");
    button1.setLabel("button1");
    button4.setLabel("button4");
    jLabel1.setText("jLabel1");
    jLabel2.setText("jLabel2");
    jRadioButton1.setText("jRadioButton1");
    toolBar.add(jButton1);
    toolBar.add(jButton2);
    toolBar.add(jButton3);
    contentPane.add(button1,  new GridBagConstraints(1, 1, 2, 1, 0.0, 0.0
            ,GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets(69, 10, 0, 21), 0, 6));
    contentPane.add(button4,  new GridBagConstraints(3, 2, 1, 1, 0.0, 0.0
            ,GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets(36, 10, 0, 28), 35, 14));
    contentPane.add(jLabel1,  new GridBagConstraints(0, 1, 1, 1, 0.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(76, 75, 9, 0), 0, 0));
    contentPane.add(jLabel2,  new GridBagConstraints(2, 2, 1, 1, 0.0, 0.0
            ,GridBagConstraints.WEST, GridBagConstraints.NONE, new Insets(49, 32, 11, 0), 0, 0));
    contentPane.add(jRadioButton1,  new GridBagConstraints(0, 3, 2, 1, 0.0, 0.0
            ,GridBagConstraints.CENTER, GridBagConstraints.NONE, new Insets(7, 47, 45, 0), 0, 0));
    menuFile.add(menuFileExit);
    menuHelp.add(menuHelpAbout);
    menuBar1.add(menuFile);
    menuBar1.add(menuHelp);
    this.setJMenuBar(menuBar1);
    contentPane.add(toolBar,  new GridBagConstraints(0, 0, 4, 1, 1.0, 0.0
            ,GridBagConstraints.CENTER, GridBagConstraints.HORIZONTAL, new Insets(0, 0, 0, 0), 269, 0));
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