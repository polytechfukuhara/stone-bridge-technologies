package to.msn.wings.mamoruapplication2;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.PersistableBundle;
import android.widget.Button;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

/*
緊急通知のポップアップクリック時の設定用クラス
 */

public class EmergencyCall extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_emergency_notification);

        //「電話をかける」ボタンをクリック時処理
        Button btnCallOn = findViewById(R.id.btnCallon);
        btnCallOn.setOnClickListener(view -> {
            Uri uri = Uri.parse("tel:03-000-0000");
            Intent i = new Intent(Intent.ACTION_VIEW, uri);
            startActivity(i);
        });
        //「電話をかけない」ボタンをクリック時処理
        Button btnCallOff = findViewById(R.id.btnCalloff);
        btnCallOff.setOnClickListener(view -> {
            finish();
        });
    }
}
