package firstproject;

public class NativeDemoClass {
  int number;

  public static void main(String args[]) {
    NativeDemoClass ob = new NativeDemoClass();

    ob.number = 1;
    ob.test(); // ����� native ������
    System.out.println("number = " + ob.number);
  }

  public native void test() ;

  // ��������� ���������� � native �������
  static {
    System.loadLibrary("NativeTest");
  }
}
