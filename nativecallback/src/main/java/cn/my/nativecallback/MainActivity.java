package cn.my.nativecallback;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import java.lang.reflect.Method;


public class MainActivity extends AppCompatActivity {
    final private String TAG = "dlog";

    private TextView tv;

    int a = 10, b = 20;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        tv = findViewById(R.id.textViewId);
    }

    @SuppressLint("DefaultLocale")
    public void click1(View view) {
        int result = NativeUtils.callStaticFunc(a, b);
        String msg = String.format("add(%d,%d) = %d", a, b, result);
        Log.d(TAG, msg);
        tv.setText(msg);
    }

    @SuppressLint("DefaultLocale")
    public void click2(View view) {
        MethodUtils methodUtils = new MethodUtils();
        methodUtils.num = 100;

        int result = NativeUtils.callFunc(methodUtils, a, b);
        String msg = String.format("add(%d,%d) = %d", a, b, result);
        Log.d(TAG, msg);
        tv.setText(msg);
    }

    @SuppressLint("DefaultLocale")
    public void click3(View view) throws NoSuchMethodException {
        MethodUtils methodUtils = new MethodUtils();
        methodUtils.num = 100;
//        Method method = MethodUtils.class.getDeclaredMethod("method2", int.class, int.class);

        String classPath = "cn/my/nativecallback/MethodUtils";
        String methodName = "method2";
        String methodSig = "(II)I";
        Object thisObject = methodUtils;
        int[] args = new int[]{a,b};

//        int result = NativeUtils.callbackup(method, methodUtils, a, b);
        Object result = NativeUtils.callAny(classPath,methodName,methodSig,thisObject,args);
        String msg = String.format("add(%d,%d) = %d", a, b, (int)result);
        Log.d(TAG, msg);
        tv.setText(msg);


//        int num2 = 100;
//        Object object = num2;
//        Log.d(TAG,"obj:" + object);
    }
}