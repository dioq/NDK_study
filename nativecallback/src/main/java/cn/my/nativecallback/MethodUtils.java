package cn.my.nativecallback;

import android.util.Log;

public class MethodUtils {
    final private static String TAG = "dlog";

    public int num = 10;

    public static int method1(int a, int b) {
        Log.d(TAG, "a = " + a);
        Log.d(TAG, "b = " + b);
        return a + b;
    }

    public int method2(int a, int b) {
        Log.d(TAG, "className:" + this.getClass().getName());
        Log.d(TAG, "a = " + a);
        Log.d(TAG, "b = " + b);

        return a + b + num;
    }
}
