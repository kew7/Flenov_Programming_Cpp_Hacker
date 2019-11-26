
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
import javax.swing.border.*;

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
  JButton jButton5 = new JButton();
  JButton jButton6 = new JButton();
  JButton jButton7 = new JButton();
  JButton jButton8 = new JButton();
  TitledBorder titledBorder1;
  Border border1;
  JToggleButton jToggleButton1 = new JToggleButton();
  JFormattedTextField jFormattedTextField1 = new JFormattedTextField();

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
    border1 = BorderFactory.createCompoundBorder(titledBorder1,BorderFactory.createEmptyBorder(2,2,2,2));
    contentPane.setLayout(borderLayout1);
    this.setSize(new Dimension(450, 400));
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
    jButton4.setText("Etched");
    jButton4.setBounds(new Rectangle(18, 13, 94, 27));
    jButton4.setBorder(BorderFactory.createEtchedBorder());
    jButton5.setBounds(new Rectangle(18, 52, 94, 27));
    jButton5.setBorder(BorderFactory.createLineBorder(Color.black));
    jButton5.setText("Line");
    jButton6.setBounds(new Rectangle(18, 91, 94, 27));
    jButton6.setBorder(BorderFactory.createLoweredBevelBorder());
    jButton6.setText("LoweredBevel");
    jButton7.setBounds(new Rectangle(18, 125, 94, 27));
    jButton7.setBorder(BorderFactory.createRaisedBevelBorder());
    jButton7.setText("RaisedBavel");
    jButton8.setBounds(new Rectangle(18, 164, 94, 27));
    jButton8.setEnabled(true);
    titledBorder1 = new TitledBorder(BorderFactory.createLineBorder(Color.red,2),"");
    jButton8.setBorder(border1);
    jButton8.setDisabledIcon(image3);
    jButton8.setFocusPainted(true);
    jButton8.setHorizontalAlignment(SwingConstants.RIGHT);
    jButton8.setHorizontalTextPosition(SwingConstants.LEFT);
    jButton8.setIcon(image1);
    jButton8.setSelected(true);
    jButton8.setText("Titled");
    jToggleButton1.setText("jToggleButton1");
    jToggleButton1.setBounds(new Rectangle(150, 11, 123, 30));
    jToggleButton1.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jToggleButton1_actionPerformed(e);
      }
    });
    jFormattedTextField1.setText("jFormattedTextField1");
    jFormattedTextField1.setBounds(new Rectangle(153, 58, 119, 20));
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
    jPanel1.add(jButton5, null);
    jPanel1.add(jButton6, null);
    jPanel1.add(jButton7, null);
    jPanel1.add(jButton8, null);
    jPanel1.add(jToggleButton1, null);
    jPanel1.add(jFormattedTextField1, null);
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

  void jToggleButton1_actionPerformed(ActionEvent e) {
    if (jToggleButton1.isSelected())
      jToggleButton1.setText("Pressed");
    else
      jToggleButton1.setText("Unpressed");
  }
}