package com.zoid.mega.bb;

/**
 * Created by Jura on 10.4.2016..
 */
public class GameplayData {

    public int   screenMaxX = 1080;//getResources().getDisplayMetrics().widthPixels;
    public int   screenMaxY = 1776;//getResources().getDisplayMetrics().heightPixels;

    public float ButtonSize = screenMaxX / 4;
    public float ButtonX = 0;
    public float ButtonY = screenMaxY - ButtonSize;

    private int scoreLocal = 0;
    public static int score = 0;

    public static boolean JavaRefreshScreen = false;//true //c radi refresh ekrana zasad

    public static int getScore(){
        return score;
    }
    public static int setScore(int score) {
        //System.out.println("setScore " + score);
        TetrisActivity.getInstance().checkHighscore(score);
        GameplayData.score = score;
        return 0;
    }
    public float getButtonX() {
        return ButtonX;
    }
    public float getButtonY() {
        return ButtonY;
    }
    public float getButtonSize() {
        return ButtonSize;
    }
    public int getScoreLocal() {
        scoreLocal = GameplayData.score;
        return scoreLocal;
    }
    public static boolean isJavaRefreshScreen() {
        return JavaRefreshScreen;
    }
}
