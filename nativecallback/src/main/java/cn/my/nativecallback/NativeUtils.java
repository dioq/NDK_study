package cn.my.nativecallback;

public class NativeUtils {
    static {
        System.loadLibrary("study");
    }

    // C++ 调用 java 静态方法
    public static native int callStaticFunc(int p1, int p2);

    // C++ 调用 java 非静态方法
    public static native int callFunc(Object thisObj, int p1, int p2);

    // C++ 处理可变参数
    public static native int callFuncWithArgs(String classPath, String methodName, String methodSig, Object thisObject, int... args);
}
