package cn.my.load_so02;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import cn.my.jni.NativeUtils;


public class MainActivity extends AppCompatActivity {
    private static final String TAG = "dlog";
    private TextView tv;

    private Context context = null;

    @SuppressLint("MissingInflatedId")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        tv = findViewById(R.id.textViewId);

        context = MainActivity.this;
    }

    @SuppressLint({"SetTextI18n", "DefaultLocale", "UnsafeDynamicallyLoadedCode"})
    public void load1(View view) {
        int a = 10, b = 20;
        int result = NativeUtils.func1(a, b);
        String msg = String.format("add(%d,%d) = %d", a, b, result);
        Log.d(TAG, msg);
    }

    @SuppressLint({"SetTextI18n", "DefaultLocale"})
    public void load2(View view) {
        int a = 11, b = 22;
        int result = NativeUtils.func2(a, b);
        String msg = String.format("func2(%d,%d) = %d", a, b, result);
        Log.d(TAG, msg);
    }
}