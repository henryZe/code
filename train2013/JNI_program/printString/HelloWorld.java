public class HelloWorld{

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
