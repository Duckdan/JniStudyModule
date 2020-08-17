package jni;

import android.content.Context;
import android.widget.Toast;

public class JniTest {

    static {
        System.loadLibrary("native_lib");
    }

    public native void definePrint(String msg);

    public native String getStringFromJni();

    /**
     * Jni中的引用
     */
    public native void jniRef();


    /**
     * 通过本地展示Toast
     *
     * @param context
     * @param toastContent
     */
    public native void showToastFromCOrCPlusPlus(Context context, String toastContent);

    /**
     * 显示Toast
     */
    public void showToast(Context context, String toastContent) {
        Toast.makeText(context, "C/C++调用java显示吐司：：" + toastContent, Toast.LENGTH_SHORT).show();
    }
}
