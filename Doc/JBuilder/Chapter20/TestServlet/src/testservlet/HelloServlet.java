package testservlet;

import javax.servlet.*;
import java.io.*;
import java.util.Enumeration;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2006</p>
 * <p>Company: </p>
 * @author not attributable
 * @version 1.0
 */

public class HelloServlet extends GenericServlet{
  public void service(ServletRequest req, ServletResponse resp)
      throws ServletException {
    resp.setContentType("text/html");
    try{
      PrintWriter pw = resp.getWriter();
      pw.print("<h2>Hello from Servlet</h2>");

      Enumeration e = req.getParameterNames();

      while (e.hasMoreElements()) {
        String param = (String)e.nextElement();
        pw.print("<LI>"+param + " = ");
        String value = req.getParameter(param);
        pw.print(value);
        pw.print("<BR>");
      }

      pw.close();
    }
    catch (Exception ee){}
  }
}
