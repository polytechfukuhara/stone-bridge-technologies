package to.msn.wings.mamoruapplication2;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.os.Build;
import android.os.IBinder;

import androidx.annotation.Nullable;
import androidx.annotation.RequiresApi;
import androidx.core.app.NotificationCompat;

/*
緊急通知のポップアップ設定用クラス
 */

public class EmergencyNotification extends Service {
    //フィールド
    private static final int NOTIFY_ID = 1;
    private NotificationManager manager;
    private NotificationChannel channel;

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    public void onCreate() {
        super.onCreate();
        //チャンネル設定
        channel = new NotificationChannel("emergency_status", "振動検知通知",
                NotificationManager.IMPORTANCE_HIGH);
        long[] pattern = {1000L, 500L, 1000L, 500L, 2000L, 500L};
        channel.setVibrationPattern(pattern);
    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        //ノーティフィケーションの準備
        NotificationCompat.Builder builder = new NotificationCompat.Builder(this, "emergency_status");
        builder.setContentTitle("守サービス");
        builder.setContentText("振動を検知しました");
        //todo アイコンは後で設定
        builder.setSmallIcon(R.drawable.wings_logo);
        builder.setWhen(System.currentTimeMillis());

        //pendingIntentの準備(EmergencyCallへ移動)
        PendingIntent pending = PendingIntent.getActivity(this, 1,
                new Intent(this, EmergencyCall.class),
                PendingIntent.FLAG_CANCEL_CURRENT);
        builder.setContentIntent(pending);
        Notification notif = builder.build();

        //ノーティフィケーションの登録
        manager = (NotificationManager) getSystemService(NOTIFICATION_SERVICE);
        manager.createNotificationChannel(channel);
        manager.notify(NOTIFY_ID, notif);

        return super.START_STICKY;
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        manager.cancel(NOTIFY_ID);
    }
}

