package cn.my.jni;

public class NativeApi {
    static {
        System.loadLibrary("study");
    }

    public static native int func1(int p1, int p2); // dynamic

    public static native int func2(int p1, int p2); // static
}
