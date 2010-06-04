import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
public class Loader{
	public static void main(String[] args){
		try{
			Class<?> c=null;
			Method m=null;
			Object[] arguments = new Object[] { new String[0] };
			try{
				c=Class.forName("Main");
			}catch(ClassNotFoundException e){
				System.err.println(e);
			}
			try{
				m=c.getMethod("main",String[].class);
			}catch(NoSuchMethodException e){
				System.err.println(e);
			}

			try{
				SandboxSM sm=new SandboxSM();
				System.setSecurityManager(sm);
			}catch(SecurityException e){
				System.err.println(e);
			}

			try{
				m.invoke(null,arguments);
			}
			catch(IllegalAccessException e){
				System.err.println(e);
			}
			catch(InvocationTargetException e){
				System.err.println(e);
			}
		}catch(Throwable t){
			System.err.println("Unpredicated Error!!");
			System.err.println(t);
		}
	}
}
