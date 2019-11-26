package testservlet;

import javax.servlet.http.*;
import java.io.*;
import javax.servlet.*;
import java.util.*;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2006</p>
 * <p>Company: </p>
 * @author not attributable
 * @version 1.0
 */

public class CookieServletTest extends HttpServlet {
  public void doPost(HttpServletRequest request,
                     HttpServletResponse response){
    // �������� ������� Cookie
    Cookie[] cookies = request.getCookies();
    try{
      PrintWriter pw = response.getWriter();
      pw.println("<B>Old data:</B> ");
      for(int i = 0; i < cookies.length; i++) {
        String name = cookies[i].getName();
        String value = cookies[i].getValue();
        pw.println("name = " + name +" value = " + value);
      }

      String data = request.getParameter("data");
      Cookie cookie = new Cookie("MyCookie", data);

      // �������� Cookie
      response.addCookie(cookie);

      response.setContentType("text/html");
      pw.println("<BR><B>New data:</B> "+data);

      // ��������� ������
      HttpSession hs = request.getSession(true);
      Date date = (Date)hs.getValue("date");
      if(date != null) {
        pw.print("<BR><B>Last visit:</B> " + date);
      }

      // ���������� ������� ����
      date = new Date();
      hs.putValue("date", date);
      pw.println("<BR><B>Current date:</B> " + date);
    }
    catch(IOException ee){}
  }
}