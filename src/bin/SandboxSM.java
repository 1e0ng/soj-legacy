import java.security.Permission;
import java.security.SecurityPermission;
import java.util.PropertyPermission;
import java.io.FilePermission;
import java.net.NetPermission;
import java.lang.reflect.ReflectPermission;
import java.io.File;
public class SandboxSM extends SecurityManager{
    private String javahome=System.getenv("JAVA_HOME");
    public void checkWrite(String file){
    	File f1=new File("err");
    	if(!file.equals(f1.getAbsolutePath()))
    		super.checkWrite(file);
    }
    public void checkPermission(Permission perm) {
		if (perm instanceof SecurityPermission) {
            if (perm.getName().startsWith("getProperty")) {
                return;
            }
        } else if (perm instanceof PropertyPermission) {
            if (perm.getActions().equals("read")) {
                return;
            }
        } else if (perm instanceof FilePermission){
        	String name=Loader.path;
        
        	String action=perm.getActions();
        	if(action.indexOf("write")!=-1){
        		
        	}
        	if(action.indexOf("write")!=-1||action.indexOf("execute")!=-1||action.indexOf("delete")!=-1)
        		throw new SecurityException(perm.toString());
        	if(action.indexOf("../")!=-1)
        		throw new SecurityException(perm.toString());

        	String s=perm.getName();
        	if (s.startsWith(javahome))
        		return;
        }
        else if(perm instanceof NetPermission)
        	return;
        else if(perm instanceof RuntimePermission){
        	return;
        }
        else if(perm instanceof ReflectPermission){
        	return;
        }
        throw new SecurityException(perm.toString());
    }
}
