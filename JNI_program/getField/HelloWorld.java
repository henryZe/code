public class HelloWorld{

	public int a = 30;

	public static void JavaSystem()
	{
		System.out.println("static class function");
	}

	public void JavaPrint()
	{
		System.out.println("object function");
	}

	public native String printContext(String str);

	public static void main(String[] args)
	{
		String str = new HelloWorld().printContext("welcome to JAVA");
		System.out.println(str);
	}

	static
	{
		System.loadLibrary("Hello");
	}
}
