package to.msn.wings.mamoruapplication2;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import androidx.annotation.Nullable;

import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

/*
緊急通知のブロードキャスト設定用クラス
 */

public class EmergencyBroadcast extends Service {

    private final String TAG = "EmergencyBroadcast";
    private ScheduledExecutorService schedule;
    public static final String ACTION = "EmergencyBroadcast Action";

    @Override
    public void onCreate() {
        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        schedule = Executors.newSingleThreadScheduledExecutor();
        schedule.scheduleAtFixedRate(() -> {
            Intent i = new Intent(ACTION);
            sendBroadcast(i);},
                0,
                10, //仮（10秒に１回）
                TimeUnit.SECONDS
                );
        return START_STICKY;
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        schedule.shutdown();
    }

}
