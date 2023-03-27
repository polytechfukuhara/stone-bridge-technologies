package to.msn.wings.mamoruapplication2;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

/*
緊急通知のブロードキャスト受信時の設定用クラス
 */

public class EmergencyReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
        Toast.makeText(context, "振動緊急通知がきました", Toast.LENGTH_SHORT).show();
        Intent i = new Intent(context, EmergencyNotification.class);
        context.startService(i);
    }
}
