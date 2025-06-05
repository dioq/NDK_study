#include <jni.h>
#include <string>
#include "log.h"

static const char *JNI_REG_CLASS = "cn/my/dynamicregister/NativeUtils";

static int add(int a, int b) {
    return a + b;
}

static int mul(int a, int b) {
    return a * b;
}

// static native 传入 NativeUtils 类 Class
int func1(JNIEnv *env, jclass clazz, int p1, int p2) {
    return add(p1, p2);
}

// native 传入 NativeUtils 对象 this
int func2(JNIEnv *env, jobject thiz, int p1, int p2) {
    return mul(p1, p2);
}

JNIEXPORT jstring JNICALL
func3(JNIEnv *env, jclass clazz, jstring msg) {
    //获取字符串指针，必须使用指针，不能使用char strContent[],因为GetStringUTFChars()返回值为const char *;
    const char *strContent = env->GetStringUTFChars(msg, JNI_FALSE);
    char str[] = "欢迎你的到来！";

    //字符串拼接,实现strContent+str1,因为strcat的第一个参数必须为非const类型(可变)，所以不能直接使用strcat()
    //创建一个新的字符串指针
    char *strTemp = (char *) malloc(strlen(strContent) + strlen(str) + 1);
    //拷贝常量到字符串指针
    strcpy(strTemp, strContent);
    //拼接str1到strTemp
    strcat(strTemp, str);
    //返回一个utf的jstring
    return env->NewStringUTF(strTemp);
}

static JNINativeMethod g_methods[] = {
        {"func1", "(II)I",                                  (void *) func1},
        {"func2", "(II)I",                                  (void *) func2},
        {"func3", "(Ljava/lang/String;)Ljava/lang/String;", (void *) func3},
};

// must define this function
JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }

    jclass javaClass = env->FindClass(JNI_REG_CLASS);
    if (javaClass == nullptr) {
        return JNI_ERR;
    }

    int method_count = sizeof(g_methods) / sizeof(g_methods[0]);
    if (env->RegisterNatives(javaClass, g_methods, method_count) < 0) {
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}
