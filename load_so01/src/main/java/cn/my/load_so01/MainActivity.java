package cn.my.load_so01;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import java.io.File;

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
        String so_name = "libstudy.so";
        File file = new File(context.getCacheDir(), so_name);
        if (!file.exists()) {
            Log.d(TAG, file.getPath() + " not exist!");
            return;
        }
        System.load(file.getPath());
//        System.load("/system/lib64/libhook.so");
        int a = 10, b = 20;
        int result = NativeUtils.func1(a, b);
        String msg = String.format("add(%d,%d) = %d", a, b, result);
        Log.d(TAG, msg);
    }

}