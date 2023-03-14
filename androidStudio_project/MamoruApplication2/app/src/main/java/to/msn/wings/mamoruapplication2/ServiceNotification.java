package to.msn.wings.mamoruapplication2;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.os.Build;
import android.os.IBinder;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.annotation.RequiresApi;
import androidx.core.app.NotificationCompat;

/*
サービス開始と終了ポップアップ設定用クラス
 */

public class ServiceNotification extends Service {

    //フィールド
    private static final int NOTIFY_ID = 0;
    private NotificationManager manager;
    private NotificationChannel channel;

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    public void onCreate() {
        super.onCreate();
        //チャンネル設定
        channel = new NotificationChannel("service_status", "サービス状況",
                NotificationManager.IMPORTANCE_DEFAULT);
        long[] pattern = {1000L, 500L, 1000L, 500L, 2000L, 500L};
        channel.setVibrationPattern(pattern);
    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Toast.makeText(this, "サービス開始しました", Toast.LENGTH_SHORT).show();

        //ノーティフィケーションの準備
        NotificationCompat.Builder builder = new NotificationCompat.Builder(this, "service_status");
        builder.setContentTitle("守サービス");
        builder.setContentText("サービス起動中");
        //todo アイコンは後で設定
        builder.setSmallIcon(R.drawable.wings_logo);
        builder.setWhen(System.currentTimeMillis());

        //pendingIntentの準備
        PendingIntent pending = PendingIntent.getActivity(this, 1,
                new Intent(this, MainActivity.class),
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
        Toast.makeText(this, "サービス終了しました", Toast.LENGTH_SHORT).show();
        manager.cancel(NOTIFY_ID);
    }
}
