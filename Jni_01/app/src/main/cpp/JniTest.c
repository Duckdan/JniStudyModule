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