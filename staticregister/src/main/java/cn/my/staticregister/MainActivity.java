package cn.my.staticregister;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import cn.my.jni.NativeApi;

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
        int result = NativeApi.func1(a, b);
        String msg = String.format("add(%d,%d) = %d", a, b, result);
        Log.d(TAG, msg);
        tv.setText(msg);
    }

    @SuppressLint("DefaultLocale")
    public void click2(View view) {
        NativeApi nativeApi = new NativeApi();
        int result = nativeApi.func2(a, b);
        String msg = String.format("add(%d,%d) = %d", a, b, result);
        Log.d(TAG, msg);
        tv.setText(msg);
    }

    @SuppressLint("DefaultLocale")
    public void click3(View view) {
        String param = "This is message from java method!";
        String msg = NativeApi.func3(param);
        Log.d(TAG, msg);
        tv.setText(msg);
    }
}