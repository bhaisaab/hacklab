/*
jar cfe fibjthread.jar fibjthread fibjthread.class fib.class calculate_fib.class 
java -jar fibjthread.jar
*/
import java.util.*;
import java.io.*;

class fib
{
	int size;
	public fib(int size)
	{
		this.size=size;
	}
	long arr[]=new long[500];
	
	public void print_fib()
	{
		String output="Fibonacci numbers of size "+size+" are : ";
		for(int i=0;i<size;i++)
			output+=(arr[i]+" ");
		System.out.println(output);
	}
}

class calculate_fib implements Runnable
{
	fib f;
	public calculate_fib(fib f)
	{
		this.f=f;
	}
	public void run()
	{
		f.arr[0]=0;
		f.arr[1]=1;
		for(int i=2;i<f.size;i++)
			f.arr[i]=f.arr[i-1]+f.arr[i-2];
		f.print_fib();
		System.out.println();
	}
}
public class fibjthread
{
	public static void main(String[] args) throws FileNotFoundException
	{
		int m;
		Scanner in = new Scanner(new File("/home/rohit/input"));
		m = in.nextInt();
		fib obj=new fib(m);
		Thread thread=new Thread(new calculate_fib(obj));
		thread.start();
		try
		{
		  	thread.join();
         	}
     	catch(InterruptedException ie){}
	}
}
