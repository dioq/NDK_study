package cn.my.frida_gadget;

import android.annotation.SuppressLint;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import cn.my.target.Target;

import java.io.File;


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
    public void load(View view) {
        String so_name = "libgadget.so";
        File file = new File(context.getCacheDir(), so_name);
        if (!file.exists()) {
            Log.d(TAG, file.getPath() + " not exist!");
            return;
        }
        System.load(file.getPath());
    }

    @SuppressLint({"SetTextI18n", "DefaultLocale"})
    public void test(View view) {
        Target target = new Target();
        String result = target.methodForTest("Dio", "wonam", 20);
        Log.d(TAG, "result:" + result);
    }

}