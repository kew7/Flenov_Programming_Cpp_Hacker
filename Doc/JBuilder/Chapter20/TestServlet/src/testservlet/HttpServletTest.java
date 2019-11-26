package testservlet;

import javax.servlet.http.*;
import java.io.PrintWriter;
import java.io.IOException;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2006</p>
 * <p>Company: </p>
 * @author not attributable
 * @version 1.0
 */


public class HttpServletTest extends HttpServlet {
 // Пример показывает перехват GET запросов
  public void doGet(HttpServletRequest req,
                    HttpServletResponse resp){
    String Name = req.getParameter("firstName");
    resp.setContentType("text/html");
    try{
      PrintWriter pw = resp.getWriter();
      pw.println("<B>Your name is:  ");
      pw.println(Name);
      pw.close();
    }
    catch(IOException ee){}
  }

 // Пример показывает перехват POST запросов
  public void doPost(HttpServletRequest req,
                    HttpServletResponse resp){
    String Name = req.getParameter("firstName");
    resp.setContentType("text/html");
    try{
      PrintWriter pw = resp.getWriter();
      pw.println("<B>Your name is:  ");
      pw.println(Name);
      pw.close();
    }
    catch(IOException ee){}
  }
}