#include <jni.h>
#include <string>
#include <iostream>
#include "log.h"

static const char *JNI_REG_CLASS = "cn/my/nativecallback/NativeUtils";

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

static JNINativeMethod g_methods[] = {
        {"callStaticFunc", "(II)I",                   (void *) callStaticFunc},
        {"callFunc",       "(Ljava/lang/Object;II)I", (void *) callFunc},
//        {"func3", "(Ljava/lang/String;)Ljava/lang/String;", (void *) func3},
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

jobject convert(JNIEnv *env, jobject param) {
    // 检查参数是否为 null
    if (param == nullptr) {
        return nullptr;
    }

    // 获取参数的类
    jclass paramClass = env->GetObjectClass(param);
    if (paramClass == nullptr) {
        std::cerr << "Failed to get parameter class." << std::endl;
        return nullptr;
    }

    // 获取类名
    jclass classClass = env->FindClass("java/lang/Class");
    jmethodID getNameMethod = env->GetMethodID(classClass, "getName", "()Ljava/lang/String;");
    jstring className = (jstring) env->CallObjectMethod(paramClass, getNameMethod);
    const char *classNameCStr = env->GetStringUTFChars(className, nullptr);

    jobject resultObject = nullptr;

    // 根据类名判断类型并转换
    if (strcmp(classNameCStr, "java.lang.Integer") == 0) {
        resultObject = param;
    } else if (strcmp(classNameCStr, "java.lang.Float") == 0) {
        resultObject = param;
    } else if (strcmp(classNameCStr, "java.lang.Boolean") == 0) {
        resultObject = param;
    } else if (strcmp(classNameCStr, "java.lang.String") == 0) {
        resultObject = param;
    } else if (strcmp(classNameCStr, "java.lang.Double") == 0) {
        resultObject = param;
    } else if (strcmp(classNameCStr, "java.lang.Long") == 0) {
        resultObject = param;
    } else if (strcmp(classNameCStr, "java.lang.Short") == 0) {
        resultObject = param;
    } else if (strcmp(classNameCStr, "java.lang.Byte") == 0) {
        resultObject = param;
    } else {
        std::cerr << "Unsupported type: " << classNameCStr << std::endl;
    }

    // 释放局部引用
    env->ReleaseStringUTFChars(className, classNameCStr);

    return resultObject;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_cn_my_nativecallback_NativeUtils_callAny(JNIEnv *env, jclass clazz, jstring class_path,
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
        return nullptr;
    }

    jint *arrayElements = env->GetIntArrayElements(args, nullptr);
    int p1 = arrayElements[0];
    int p2 = arrayElements[1];

    jint result = env->CallIntMethod(this_object, methodID, p1, p2);

    jclass integerClass = env->FindClass("java/lang/Integer");

    // 接下来，找到Integer类的构造函数
    jmethodID integerConstructor = env->GetMethodID(integerClass, "<init>", "(I)V");

    // 使用构造函数创建一个新的Integer对象
    jobject integerObject = env->NewObject(integerClass, integerConstructor, result);

    return integerObject;
}