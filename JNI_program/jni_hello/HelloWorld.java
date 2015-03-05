public class HelloWorld{

	public native void printContext();

	public static void main(String[] args)
	{
		new HelloWorld().printContext();
	}

	static
	{
		System.loadLibrary("Hello");
	}
}
