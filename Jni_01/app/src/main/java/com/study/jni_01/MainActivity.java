package com.study.jni_01;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import jni.JniTest;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native_lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text_cplusplus);
        tv.setText(stringFromJNI());
        final JniTest jniTest = new JniTest();
        TextView tv1 = findViewById(R.id.sample_text_c);
        tv1.setText("C语言::" + jniTest.getStringFromJni());
        tv1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                jniTest.jniRef();
            }
        });

        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                System.out.println("java我要学习JNI");
                jniTest.definePrint("我要学习JNI");

                jniTest.showToastFromCOrCPlusPlus(MainActivity.this, "C/C++调用java");
            }
        });
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
