
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
  JButton jButton4 = new JButton();
  JButton jButton5 = new JButton();
  JButton jButton6 = new JButton();
  JButton jButton7 = new JButton();
  JButton jButton8 = new JButton();
  JButton jButton9 = new JButton();
  JButton jButton10 = new JButton();

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
    jButton4.setBounds(new Rectangle(25, 48, 111, 26));
    jButton4.setText("ArrayList");
    jButton4.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton4_actionPerformed(e);
      }
    });
    jButton5.setBounds(new Rectangle(26, 86, 108, 28));
    jButton5.setText("TreeList");
    jButton5.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton5_actionPerformed(e);
      }
    });
    jButton6.setBounds(new Rectangle(28, 125, 109, 26));
    jButton6.setText("TreeMap");
    jButton6.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton6_actionPerformed(e);
      }
    });
    jButton7.setBounds(new Rectangle(175, 86, 112, 26));
    jButton7.setText("Comparator");
    jButton7.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton7_actionPerformed(e);
      }
    });
    jButton8.setBounds(new Rectangle(173, 45, 113, 26));
    jButton8.setText("Algo");
    jButton8.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton8_actionPerformed(e);
      }
    });
    jButton9.setBounds(new Rectangle(175, 125, 113, 28));
    jButton9.setText("Properties");
    jButton9.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton9_actionPerformed(e);
      }
    });
    jButton10.setBounds(new Rectangle(173, 164, 114, 26));
    jButton10.setEnabled(true);
    jButton10.setText("Load Prop");
    jButton10.addActionListener(new java.awt.event.ActionListener() {
      public void actionPerformed(ActionEvent e) {
        jButton10_actionPerformed(e);
      }
    });
    toolBar.add(jButton1);
    toolBar.add(jButton2);
    toolBar.add(jButton3);
    contentPane.add(jButton10, null);
    contentPane.add(jButton9, null);
    contentPane.add(jButton6, null);
    contentPane.add(jButton4, null);
    contentPane.add(jButton5, null);
    contentPane.add(jButton7, null);
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

  void jButton4_actionPerformed(ActionEvent e) {
    ArrayList list = new ArrayList();

    list.add("Это первый элемент");
    list.add(0, "Вставленный элемент");
    list.add(2, "Второй");

    for (int i=0; i<list.size(); i++)
      System.out.println(list.get(i));

    list.remove("Второй");

    System.out.println(list);
  }

  void jButton5_actionPerformed(ActionEvent e) {
    TreeSet tree = new TreeSet();

    tree.add("Один");
    tree.add("Два");
    tree.add("Три");
    tree.add("Четыре");
    tree.add("Пять");

    Iterator it = tree.iterator();

    while (it.hasNext())
      System.out.println(it.next());
  }

  void jButton6_actionPerformed(ActionEvent e) {
    TreeMap tMap = new TreeMap();

    tMap.put(new Integer(1), "Иванов");
    tMap.put(new Integer(2), "Петров");
    tMap.put(new Integer(3), "Сидоров");

    for (int i=1; i<=tMap.size(); i++)
      System.out.println(tMap.get(new Integer(i)));

    System.out.println(tMap.entrySet());
  }

  void jButton7_actionPerformed(ActionEvent e) {
    TreeMap tMap = new TreeMap(new DecComparator());

    tMap.put(new Integer(1), "Иванов");
    tMap.put(new Integer(2), "Петров");
    tMap.put(new Integer(3), "Сидоров");

    System.out.println(tMap.entrySet());

    TreeMap tMap2 = new TreeMap();

    tMap2.put(new Integer(1), "Иванов");
    tMap2.put(new Integer(2), "Петров");
    tMap2.put(new Integer(3), "Сидоров");

    System.out.println(tMap2.entrySet());
  }

  void jButton8_actionPerformed(ActionEvent e) {
    ArrayList tree = new ArrayList();

    tree.add("Один");
    tree.add("Два");
    tree.add("Три");
    tree.add("Четыре");
    tree.add("Пять");
    System.out.println(tree);

    Collections.shuffle(tree);
    System.out.println(tree);

    System.out.println(Collections.max(tree));

    Comparator r = Collections.reverseOrder();
    Collections.sort(tree, r);

    Collections.shuffle(tree);
    System.out.println(tree);
  }

  void jButton9_actionPerformed(ActionEvent e) {
    Properties p = new Properties();

    p.setProperty("1", "Январь");
    p.setProperty("2", "Февраль");
    p.setProperty("3", "Март");
    p.setProperty("4", "Апрель");
    p.put("5", "Май");

    System.out.println(p.getProperty("5"));
    System.out.println(p.getProperty("6", "Июнь"));

    try
    {
      FileOutputStream fo = new FileOutputStream("Months.txt");
      p.store(fo, "Месяца");
    }
    catch (Exception ee)
    {
    }
  }

  void jButton10_actionPerformed(ActionEvent e) {
    Properties p = new Properties();

    try
    {
      FileInputStream fi = new FileInputStream("Months.txt");
      p.load(fi);
    }
    catch (Exception ee)
    {
    }
    System.out.println(p.getProperty("5"));
    System.out.println(p.getProperty("6", "Июнь"));
  }
}

class DecComparator implements Comparator{
  public int compare(Object o1, Object o2){

    Integer a = (Integer) o1;
    Integer b = (Integer) o2;

    return b.compareTo(a);
  }
}