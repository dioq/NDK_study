#include <jni.h>
#include <string>
#include "log.h"

static const char *JNI_REG_CLASS = "cn/my/jni/NativeUtils";


int func1(JNIEnv *env, jclass clazz, int p1, int p2) {
    return p1 + p2;
}

static JNINativeMethod g_methods[] = {
        {"func1", "(II)I", (void *) func1},
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

extern "C"
JNIEXPORT jint JNICALL
Java_cn_my_jni_NativeUtils_func2(JNIEnv *env, jclass clazz, jint p1, jint p2) {
    // TODO: implement func2()
    return p1 + p2;
}