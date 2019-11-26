package firstproject;

public class NativeDemoClass {
  int number;

  public static void main(String args[]) {
    NativeDemoClass ob = new NativeDemoClass();

    ob.number = 1;
    ob.test(); // Вызов native метода
    System.out.println("number = " + ob.number);
  }

  public native void test() ;

  // Загрузить библиотеку с native методом
  static {
    System.loadLibrary("NativeTest");
  }
}
