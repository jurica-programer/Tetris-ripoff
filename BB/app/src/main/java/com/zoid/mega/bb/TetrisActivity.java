package com.zoid.mega.bb;

import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.os.Build;
import android.os.Bundle;
import android.app.Activity;
import android.graphics.Color;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;


public class TetrisActivity extends Activity {

    private static final String TAG = TetrisActivity.class.getSimpleName();

    public static boolean doubletap = false;
    private static int button = -1;
    public static TetrisActivity instance;
    public static TetrisActivity getInstance() {
        return instance;
    }

    //TODO napravi više viewa za manu
    private TetrisView mTetrisView;

    Thread threadNative = new Thread(){
        public void run(){
            Native.startThread();
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        instance = this;
        /** INIT GAME RES */
        try {
            Native.initGameRes();
        } catch (Exception e) {
            e.printStackTrace();
        }

        /** INIT VIEW */
        setContentView(R.layout.activity_main);
        //TODO napravi za mijenjanje ekrana vertikalno i horizontalno
        //this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);

        mTetrisView = new TetrisView(this);

        int mUIFlag = View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                | View.SYSTEM_UI_FLAG_LOW_PROFILE
                | View.SYSTEM_UI_FLAG_FULLSCREEN
                | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY;

        getWindow().getDecorView().setSystemUiVisibility(mUIFlag);

        setContentView(mTetrisView);

        mTetrisView.setBackgroundColor(Color.BLACK);
        mTetrisView.setClickable(true);
        mTetrisView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if (event.getAction() == MotionEvent.ACTION_DOWN) {//TODO napravi ovo da ti sam napravi akciju a ne na akciju da radi
                    button = mTetrisView.getAButton(event.getX(), event.getY());
                    if(doubletap){
                        Native.startButton(3);
                    } else {
                        Native.startButton(1);
                    }
                }

                if ((event.getAction() == MotionEvent.ACTION_UP) && !doubletap) {
                    Native.startButton(2);
                }

                return true;
            }
        });
        //Start game
        threadNative.start();
        //TODO postavi ovo kao defaultne vrijednosti za mobitele
        Log.e(TAG, "jurica size = " + getResources().getDisplayMetrics().heightPixels
                + " x " + getResources().getDisplayMetrics().widthPixels);
        mTetrisView.clickButton(0, false);
    }

    public void clickOnView(boolean longClick){ //TODO ovo još sredi i u native prebaci =)
        mTetrisView.clickButton(button, longClick);
    }

    @Override
    protected void onDestroy(){
        super.onDestroy();

        try {
            threadNative.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        /** TERMINATE GAME RES */
        Native.terminateGameRes();

        //Exit from app
        if (Build.VERSION.SDK_INT >= 21) { //Is the user running Lollipop or above?
            finishAndRemoveTask(); //If yes, run the new fancy function to end the app and remove it from the Task Manager.
        } else {
            finish(); //If not, then just end the app (without removing the task completely).
        }
    }

    @Override
    protected void onStop(){
        super.onStop();
        if(!mTetrisView.pauseState){mTetrisView.clickButton(0, false);}
    }

    public void redrawScreen(){
        mTetrisView.postInvalidate();
    }

    //TODO ovo stavi u poseban java calass
    public void checkHighscore(int tempScore) {
        SharedPreferences pref = getApplicationContext().getSharedPreferences("MyPref", MODE_PRIVATE);
        SharedPreferences.Editor editor = pref.edit();
        if (tempScore > pref.getInt("highscore", 0)) {
            editor.putInt("highscore",tempScore);
            editor.apply();
            //editor.commit(); /* was before */
        }
    }

    public int getHighScore(){
        SharedPreferences pref = getApplicationContext().getSharedPreferences("MyPref", MODE_PRIVATE);
        return pref.getInt("highscore", 0);
    }

    //TODO napravi disable rotacije
    public void setScreenRotation(int state){
        switch (state)
        {
            case 0:
                setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LOCKED);
                break;
            case 1:
                setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
                break;
            case 2:
                setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
                break;
            default:
                break;
        }
    }

    public boolean getScreenOrientation(){
        if( getRequestedOrientation() == ActivityInfo.SCREEN_ORIENTATION_PORTRAIT){
            return true;
        }
        return false;
    }

    public void setDoubletap(boolean state){doubletap = state;}

}
