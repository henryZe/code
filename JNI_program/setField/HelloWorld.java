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

	public native Person createPerson(int age, String name);

	public static void main(String[] args)
	{
		Person p = new HelloWorld().createPerson(23, "Henry");
		System.out.println(p);
	}

	static
	{
		System.loadLibrary("Hello");
	}
}
