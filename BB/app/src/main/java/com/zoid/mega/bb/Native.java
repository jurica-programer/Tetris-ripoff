package com.zoid.mega.bb;

import android.util.Log;

/**
 * Created by Jura on 8.4.2016..
 */
public class Native {

    static {
        System.loadLibrary("MyLib");
    }
    /** GAME FUNCTIONS */
    public native static int initGameRes();
    public native static int terminateGameRes();
    public native static int startThread();
    public native static int startButton(int state);

    public native static int buttonA();
    public native static int buttonB();
    public native static int buttonC();
    public native static int buttonD();

    public native static int buttonAlong();
    public native static int buttonBlong();
    //public native static int buttonClong();
    public native static int buttonDlong();

    public native static boolean getField(int row, int column);
    public native static int getScore();
    public native static int getNext();
    public native static int getView();
    public native static int resetGame();
    public native static int pauseContinue();

    /** CALLBACK FUNCTIONS */
    public static void callback(int command){
        //System.out.println("Native command " + command);
        switch (command)
        {
            case 0:
                GameplayData.setScore(getScore());
                break;
            case 1:
                if(!GameplayData.isJavaRefreshScreen())
                {
                    TetrisActivity.getInstance().redrawScreen();
                }
                break;
            case 2:
                {
                    //TetrisActivity.getInstance().changeView(2);
                }
                break;
            default:
                break;
        }

    }

    public static void callbackButton(boolean longClick){
        TetrisActivity.getInstance().clickOnView(longClick);
    }

}
