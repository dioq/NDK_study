package cn.my.dynamicregister;

public class NativeUtils {
    static {
        System.loadLibrary("study");
    }

    public static native int func1(int p1, int p2); // static

    public native int func2(int p1, int p2);        // no static

    public static native String func3(String msg);
}
