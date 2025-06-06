#include <jni.h>
#include <string>
#include "log.h"

static const char *JNI_REG_CLASS = "cn/my/jni/NativeApi";

int callStaticFunc(JNIEnv *env, jclass clazz, int p1, int p2) {
    LOGD("%s", __FUNCTION__);
    jclass methodClass = env->FindClass("cn/my/nativecallback/MethodUtils");

    // 获取方法的名称和签名（需要根据实际情况调整）
    const char *methodName = "method1"; // 方法名
    const char *methodSig = "(II)I"; // 方法签名

    jmethodID methodid = env->GetStaticMethodID(methodClass, methodName, methodSig);
    int resutl = env->CallStaticIntMethod(methodClass, methodid, p1, p2);

    return resutl;
}

int callFunc(JNIEnv *env, jclass clazz, jobject thisObj, int p1, int p2) {
    LOGD("%s", __FUNCTION__);
    jclass methodClass = env->GetObjectClass(thisObj);

    // 获取方法的名称和签名（需要根据实际情况调整）
    const char *methodName = "method2"; // 方法名
    const char *methodSig = "(II)I"; // 方法签名

    // 获取方法 ID
    jmethodID methodID = env->GetMethodID(methodClass, methodName, methodSig);
    if (methodID == nullptr) {
        LOGD("methodID == nullptr");
        return -1;
    }

    int result = env->CallIntMethod(thisObj, methodID, p1, p2);

    return result;
}

int call_func_args(JNIEnv *env, jclass clazz, jstring class_path,
                   jstring method_name, jstring method_sig,
                   jobject this_object, jintArray args) {
    LOGD("%s", __FUNCTION__);
    const char *class_path_str = env->GetStringUTFChars(class_path, JNI_FALSE);
    const char *method_name_str = env->GetStringUTFChars(method_name, JNI_FALSE);
    const char *method_sig_str = env->GetStringUTFChars(method_sig, JNI_FALSE);

    jclass methodClass = env->FindClass(class_path_str);
    // 获取方法 ID
    jmethodID methodID = env->GetMethodID(methodClass, method_name_str, method_sig_str);

    if (methodID == nullptr) {
        LOGD("methodID == nullptr");
        return -1;
    }

    // 获取参数并转换类型
    // 获取 jintArray 的长度
    jsize length = env->GetArrayLength(args);

    // 获取 jintArray 的元素
    jint *arrayElements = env->GetIntArrayElements(args, nullptr);
    if (arrayElements == nullptr) {
        return -1; // 获取元素失败
    }

    // 创建 jvalue 数组
    jvalue *params = new jvalue[length];
    // 将 jintArray 的元素复制到 jvalue 数组中
    for (jsize i = 0; i < length; ++i) {
        params[i].i = arrayElements[i];
    }

    // 调用 java 方法
    int result = env->CallIntMethodA(this_object, methodID, params);
    LOGD("result:%d", result);

    return result;
}

static JNINativeMethod g_methods[] = {
        {"callStaticFunc",   "(II)I",                                                                         (void *) callStaticFunc},
        {"callFunc",         "(Ljava/lang/Object;II)I",                                                       (void *) callFunc},
        {"callFuncWithArgs", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/Object;[I)I", (void *) call_func_args},
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
