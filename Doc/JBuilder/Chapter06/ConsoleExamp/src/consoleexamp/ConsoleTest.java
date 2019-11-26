package consoleexamp;

public class ConsoleTest {
  public static void main(String[] args) {
    System.out.println("Console Test");

    if (args.length==0)
      System.out.println("Program needs parameters");

    for (int i=0; i<args.length; i++)
      System.out.println(args[i]);
  }
}
