package to.msn.wings.mamoruapplication2;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import android.content.Intent;
import android.content.IntentFilter;
import android.os.BatteryManager;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //各インスタンス
        Button btnUpdate = findViewById(R.id.btnGo);
        Button btnWifi = findViewById(R.id.btnWifi);
        Button btnBth = findViewById(R.id.btnBth);
        Button btnStart = findViewById(R.id.btnStart);
        Button btnStop = findViewById(R.id.btnStop);
        Button btnOpen = findViewById(R.id.btnOpen);
        Button btnClose = findViewById(R.id.btnClose);
        TextView txtOpenClose = findViewById(R.id.txtOpenClose);
        TextView txtBthOnOff = findViewById(R.id.txtBthOnOff);

        //レシーバーの登録（緊急通知）
        EmergencyReceiver r = new EmergencyReceiver();
        IntentFilter f = new IntentFilter();
        f.addAction(EmergencyBroadcast.ACTION);
        registerReceiver(r,f);

        //「更新」ボタンのクリック時処理
        btnUpdate.setOnClickListener(view -> {
            //バッテリーフラグメント処理
            BatteryFragment B1 = new BatteryFragment("本体");
            BatteryFragment B2 = new BatteryFragment("キー");
            FragmentManager m = getSupportFragmentManager();
            FragmentTransaction t = m.beginTransaction();
            t.replace(R.id.frame1, B1);
            t.replace(R.id.frame2, B2);
            t.commit();

            //施錠開錠状況の処理
            txtOpenClose.setText(R.string.txtOpen);

            //Blutoothの接続状況処理
            txtBthOnOff.setText(R.string.btnOk);
        });

        //「WIFI接続」ボタンのクリック時処理
        btnWifi.setOnClickListener(view -> {
            Intent i = new Intent(MainActivity.this, WifiActivity.class);
            startActivity(i);
        });

        //「Blutooth接続」ボタンのクリック時処理
        btnBth.setOnClickListener(view -> {
            Toast.makeText(this, "Bluetooth接続開始", Toast.LENGTH_SHORT).show();
        });

        Intent i = new Intent(MainActivity.this, ServiceNotification.class); //サービス開始通知
        Intent i2 = new Intent(MainActivity.this, EmergencyBroadcast.class); //緊急通知
        //「サービス開始」ボタンのクリック時処理
        btnStart.setOnClickListener(view -> {
            startService(i);
            startService(i2);
        });

        //「サービス終了」ボタンのクリック時処理
        btnStop.setOnClickListener(view -> {
            stopService(i);
            stopService(i2);
        });

        //「開錠」ボタンのクリック時処理
        btnOpen.setOnClickListener(view -> {
            Toast.makeText(MainActivity.this, "開錠しました", Toast.LENGTH_SHORT).show();
            txtOpenClose.setText(R.string.txtOpen);
        });

        //「施錠」ボタンのクリック時処理
        btnClose.setOnClickListener(view -> {
            Toast.makeText(MainActivity.this, "施錠しました", Toast.LENGTH_SHORT).show();
            txtOpenClose.setText(R.string.txtClose);
        });
    }
}