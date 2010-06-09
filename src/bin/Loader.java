import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.io.*;
public class Loader{
	static String path;
	public static void main(String[] args){
		
		try{
			PrintStream fout;
			try{
				fout=new PrintStream(new FileOutputStream("err"));
			}catch(IOException e){
				System.out.println("Open 'err' File Error.");
				return;
			}
			
			Class<?> c=null;
			Method m=null;
			Object[] arguments = new Object[] { new String[0] };
			System.gc();
			try{
				c=Class.forName("Main");
			}catch(ClassNotFoundException e){
				fout.println("CE");
				return;
			}
			try{
				m=c.getMethod("main",String[].class);
			}catch(NoSuchMethodException e){
				fout.println("CE");
				return;
			}
			System.gc();

			try{
				SandboxSM sm=new SandboxSM();
				System.setSecurityManager(sm);
			}catch(SecurityException e){
				fout.println("Inner Error");
			}
			System.gc();

			try{
				m.invoke(null,arguments);
			}
			catch(IllegalAccessException e){
				fout.println(e);
			}
			
			catch(InvocationTargetException e){
				if(e.getCause() instanceof java.lang.OutOfMemoryError){
					System.out.println("MLE");
					fout.println("MLE");
				}
				else{
					fout.println(e.getCause());
				}
			}
			fout.close();
			System.gc();
		}catch(Throwable t){
			System.out.println("Unpredicated Error!!");
			System.out.println(t);
		}
	}
}
