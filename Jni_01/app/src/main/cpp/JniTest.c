//
// Created by 72088102 on 2020/8/14.
//
#include <jni.h>
#include <stdio.h>
#include "JniTest.h"
#include <android/log.h>

#define TAG "jni-log-jni" // 这个是自定义的LOG的标识
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型


//printf打印不出日志，所以替换成Android的Log

JNIEXPORT void JNICALL Java_jni_JniTest_definePrint(JNIEnv *env, jobject job, jstring jstr) {
    const char *c_str = NULL;
    char buf[128] = {0};
    jboolean iscopy;
    c_str = (*env)->GetStringUTFChars(env, jstr, &iscopy);
    LOGD("isCopy:%d\n", iscopy);

    LOGD("C_str: %s \n", c_str);
    sprintf(buf, "Hello, 你好 %s", c_str);
    LOGD("C_str: %s \n", buf);
    (*env)->ReleaseStringUTFChars(env, jstr, c_str);
}

JNIEXPORT jstring JNICALL Java_jni_JniTest_getStringFromJni(JNIEnv *env, jobject thiz) {
    const char *hello = "111Hello from c";
    LOGD("==========CCCC======================\n");
    return (*env)->NewStringUTF(env, hello);
}

/**
 * jni引用（野指针）
 */
JNIEXPORT void JNICALL Java_jni_JniTest_jniRef(JNIEnv *env, jobject thiz) {
    jcharArray elemArray;
    jchar *chars = NULL;
    jstring jStr = NULL;
    //定义静态的局部变量,该变量的值没有被释放的时候，二次运行的时不会再次被赋值。同时再取值的时候
    //也会报错
    static jclass jStringClass = NULL;
    LOGE("this is a jStringClass -------------%s--------\n", jStringClass);
    static jmethodID stringConstructor = NULL;
    LOGE("this is a stringConstructor ----------%s-----------\n", stringConstructor);
    //1.jni中创建Java字符串

    //找到String的字节码
    if (jStringClass == NULL) {
        LOGE("jStringClass is null\n");
        jStringClass = (*env)->FindClass(env, "java/lang/String");
        if (jStringClass == NULL) {
            return;
        }
    }

    //找到String(char[] array)的构造函数
    if (stringConstructor == NULL) {
        LOGE("stringConstructor is null\n");
        stringConstructor = (*env)->GetMethodID(env, jStringClass, "<init>", "([C)V");
        if (stringConstructor == NULL) {
            return;
        }
    }

    LOGE("this is a line1 ---------------------\n");

    elemArray = (*env)->NewCharArray(env, 1024);
    LOGE("this is a line2 ---------------------\n");
    LOGE("this is every variable,jStringClass is::%d,stringConstructor is::%d,elemArray is::%d",
         jStringClass, stringConstructor, elemArray);
    //局部引用
    jStr = (*env)->NewObject(env, jStringClass, stringConstructor, elemArray);
    LOGE("this is a line3 ---------------------\n");
    //释放引用，否则将导致野指针
    (*env)->DeleteLocalRef(env, elemArray);
    elemArray = NULL;

    (*env)->DeleteLocalRef(env, jStringClass);
    jStringClass = NULL;

    stringConstructor = NULL;
    LOGE("end of function ---------------------\n");
}

JNIEXPORT void JNICALL
Java_jni_JniTest_showToastFromCOrCPlusPlus(JNIEnv *env, jobject thiz, jobject context,
                                           jstring toast_content) {
    //获取JniTest的Class对象
    jclass jniTestClazz = (*env)->GetObjectClass(env, thiz);
    //获取showToast方法的MethodId
    jmethodID showToast_Id = (*env)->GetMethodID(env, jniTestClazz, "showToast",
                                                 "(Landroid/content/Context;Ljava/lang/String;)V");
    //调用没有返回值的java方法使用CallVoidMethod
    (*env)->CallVoidMethod(env, thiz, showToast_Id, context, toast_content);
}
