#include <jni.h>
#include <string>
#include "log.h"

static const char *JNI_REG_CLASS = "cn/my/jni/NativeApi";

int add(int a, int b) {
    return a + b;
}

static int mul(int a, int b) {
    return a * b;
}

int func1(JNIEnv *env, jclass clazz, int p1, int p2) {
    return add(p1, p2);
}

int func2(JNIEnv *env, jobject thiz, int p1, int p2) {
    return mul(p1, p2);
}

JNIEXPORT jstring JNICALL
func3(JNIEnv *env, jclass clazz, jstring msg) {
    char str[] = "This is a string from so!";

//    std::string str1 = "This is C++ string";
    //获取字符串指针
    const char *strContent = env->GetStringUTFChars(msg, JNI_FALSE);

    //创建一个新的字符串指针
    char *buff = (char *) malloc(0x100);
    memset(buff, 0, 0x100);
    //拷贝常量到字符串指针
    strcpy(buff, strContent);
    //拼接str1到strTemp
    strcat(buff, str);
    jstring jstring1 = env->NewStringUTF(buff);
    free(buff);
    return jstring1;
}

static JNINativeMethod g_methods[] = {
        {"func1", "(II)I",                                  (void *) func1},
        {"func2", "(II)I",                                  (void *) func2},
        {"func3", "(Ljava/lang/String;)Ljava/lang/String;", (void *) func3},
};

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
