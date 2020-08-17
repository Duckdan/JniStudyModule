package jni;

public class JniTest {

    static {
        System.loadLibrary("native_lib");
    }

    public native void definePrint(String msg);

    public native String getStringFromJni();
}
