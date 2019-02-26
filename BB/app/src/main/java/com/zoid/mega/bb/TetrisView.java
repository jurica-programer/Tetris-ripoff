package com.zoid.mega.bb;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.util.Log;
import android.view.SurfaceView;


/**
 * Created by Jura on 8.4.2016..
 */
public class TetrisView extends SurfaceView {

    private static final String TAG = TetrisView.class.getSimpleName();

    private GameplayData mGameplayData;

    public boolean pauseState = false;

    //TODO place in FSM and store with highscore as user settings
    /**
    * menu item options
    **/
    private boolean slamDunk     = false;
    private boolean enableRotate = false;
    private boolean colorblind   = false;
    private boolean doubletap    = false;

    public int   screenMaxX = 0;
    public int   screenMaxY = 0;

    private float xButton;
    private float yButton;
    private float sizeButton;
    private int   textSize    = 65;      // Text size
    private float blockSize   = 65;      // Block size
    private float yOffset     = 75;
    private float xOffset     = 75;

    private Paint paint;                 // The paint (e.g. style, color) used for drawing
    private int orange = android.graphics.Color.rgb(32, 162, 64);

    // Bitmaps
    Bitmap GameFieldBackground;
    Bitmap Left;
    Bitmap Down;
    Bitmap Rotate;
    Bitmap Right;
    Bitmap Block;
    Bitmap VoidBlock;
    Bitmap NextBlock;
    //TODO probaj prozirne bitmape

    // Constructor
    public TetrisView(Context context) {
        super(context);
        mGameplayData = new GameplayData();

        screenMaxX = getResources().getDisplayMetrics().widthPixels;
        screenMaxY = getResources().getDisplayMetrics().heightPixels;

        paint      = new Paint();

        xButton    = mGameplayData.getButtonX();          // This view's bounds
        sizeButton = mGameplayData.getButtonSize();
        yButton    = mGameplayData.getButtonY();

        // Setting up bitmaps
        //GameFieldBackground = BitmapFactory.decodeResource(getResources(), R.drawable.template2);
        //GameFieldBackground = Bitmap.createScaledBitmap(GameFieldBackground, (int) ((10 * blockSize) + 20), (int) ((20 * blockSize) + 40), false);

        Left      = BitmapFactory.decodeResource(getResources(), R.drawable.left);
        Left      = Bitmap.createScaledBitmap(Left, (int) sizeButton, (int) sizeButton, false);

        Down      = BitmapFactory.decodeResource(getResources(), R.drawable.down);
        Down      = Bitmap.createScaledBitmap(Down, (int) sizeButton, (int) sizeButton, false);

        Rotate    = BitmapFactory.decodeResource(getResources(), R.drawable.rotate);
        Rotate    = Bitmap.createScaledBitmap(Rotate, (int) sizeButton, (int) sizeButton, false);

        Right     = BitmapFactory.decodeResource(getResources(), R.drawable.right);
        Right     = Bitmap.createScaledBitmap(Right, (int) sizeButton, (int) sizeButton, false);

        Block     = BitmapFactory.decodeResource(getResources(), R.drawable.block);
        Block     = Bitmap.createScaledBitmap(Block, (int)blockSize, (int)blockSize, false);

        VoidBlock = BitmapFactory.decodeResource(getResources(), R.drawable.void_block);
        VoidBlock = Bitmap.createScaledBitmap(VoidBlock, (int)blockSize, (int)blockSize, false);

    }

    // Called back to draw the view. Also called by invalidate() when Java is refreshing the screen.
    @Override
    protected void onDraw(Canvas canvas) {
        drawScreen(canvas);

        // If using Java to refresh screen, otherwise game loop will refresh it.
        if(GameplayData.isJavaRefreshScreen()){
            invalidate();
            try {
                Thread.sleep(30);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * TODO NAPravi da je ovo skalabilno po ekranu i tako to da nije apsolutni pikseli, to radi ovdje
     */
    // Called back when the view is first created or its size changes.
    @Override //TODO
    public void onSizeChanged(int w, int h, int oldW, int oldH) {
        // Set the movement bounds for the ball
        //screenMaxX = w-1;
        //screenMaxY = h-1;
    }

    private void drawScreen(Canvas canvas){

        //TODO switch case sa nekim global vrijednostima FSM-a

        //TODO napravi custom font za brojeve
        //score
        paint.setColor(orange);
        paint.setTextSize(textSize);
        canvas.drawText("Next:", xOffset + 30 + (10 * blockSize), yOffset + 50, paint);
        //TODO ovo zamijeni sa očitanjem pravog nexta koji se treba nacrtati, da nije sa slike očitano
        switch (Native.getNext())
        {
            case 0:NextBlock = BitmapFactory.decodeResource(getResources(), R.drawable.i_block);break;
            case 1:NextBlock = BitmapFactory.decodeResource(getResources(), R.drawable.t_block);break;
            case 2:NextBlock = BitmapFactory.decodeResource(getResources(), R.drawable.n_block);break;
            case 3:NextBlock = BitmapFactory.decodeResource(getResources(), R.drawable.z_block);break;
            case 4:NextBlock = BitmapFactory.decodeResource(getResources(), R.drawable.l_block);break;
            case 5:NextBlock = BitmapFactory.decodeResource(getResources(), R.drawable.j_block);break;
            case 6:NextBlock = BitmapFactory.decodeResource(getResources(), R.drawable.s_block);break;
            default:
                break;
        }
        NextBlock = Bitmap.createScaledBitmap(NextBlock, (int)(blockSize * 4) + 3, (int)(blockSize * 4) + 3, false);
        canvas.drawBitmap(NextBlock, xOffset + 30 + (10 * blockSize), yOffset + textSize, paint);

        canvas.drawText("Highscore:", xOffset + 30 + (10 * blockSize), yOffset + textSize + (5 * blockSize) + 1, paint);
        canvas.drawText(Integer.toString(TetrisActivity.getInstance().getHighScore()), xOffset + 30 + (10 * blockSize), (7 * blockSize) + textSize + 20, paint);

        canvas.drawText("Score:", xOffset + 30 + (10 * blockSize), yOffset + (3 * textSize) + (5 * blockSize) + 10, paint);
        canvas.drawText(Integer.toString(mGameplayData.getScoreLocal()), xOffset + 30 + (10 * blockSize), yOffset + (4 * textSize) + (5 * blockSize) + 10, paint);

        //playground background
        //canvas.drawBitmap(GameFieldBackground, 10, 10, paint);
        //TODO napravi cjelokupnu pozadinu za igru neki kamen kao warcraft probaj

        //buttons
        canvas.drawBitmap(Left, xButton, yButton, paint);
        canvas.drawBitmap(Down, xButton + sizeButton, yButton, paint);
        canvas.drawBitmap(Rotate,  xButton + (2 * sizeButton), yButton, paint);
        canvas.drawBitmap(Right,  xButton + (3 * sizeButton), yButton, paint);

        drawPlayfield(canvas);
    }

    public void setScreenState(){pauseState =!pauseState;}

    private void drawPlayfield(Canvas canvas){

        if(pauseState)
        {
            for(int row = 0; row < 20; row++){
                for(int column = 0; column < 10; column++) {
                    canvas.drawBitmap(VoidBlock, (column * blockSize) + (column * 2) + xOffset, (row * blockSize) + (row * 2) + yOffset, paint);
                }
            }
            canvas.drawText("Resume", xOffset + (3 * (blockSize + 1)), yOffset + (3  * (blockSize + 1)), paint);

            canvas.drawText("Slam dunk?", xOffset + (2 * (blockSize + 1)), yOffset + (6  * (blockSize + 1)), paint);
            if(slamDunk) {
                canvas.drawText("Yes", xOffset + (7 * (blockSize + 1)) + 20, yOffset + (6 * (blockSize + 1)), paint);
            } else {
                canvas.drawText("No", xOffset + (7 * (blockSize + 1)) + 20, yOffset + (6  * (blockSize + 1)), paint);
            }

            canvas.drawText("Enable rotation?", xOffset + (1 * (blockSize + 1)), yOffset + (9  * (blockSize + 1)), paint);
            if(enableRotate) {
                canvas.drawText("Yes", xOffset + (8 * (blockSize + 1)) + 20, yOffset + (9 * (blockSize + 1)), paint);
            } else {
                canvas.drawText("No", xOffset + (8 * (blockSize + 1)) + 20, yOffset + (9  * (blockSize + 1)), paint);
            }

            canvas.drawText("Colorblind?", xOffset + (2 * (blockSize + 1)), yOffset + (12  * (blockSize + 1)), paint);
            if(colorblind) {
                canvas.drawText("Yes", xOffset + (7 * (blockSize + 1)) + 20, yOffset + (12 * (blockSize + 1)), paint);
            } else {
                canvas.drawText("No", xOffset + (7 * (blockSize + 1)) + 20, yOffset + (12  * (blockSize + 1)), paint);
            }

            canvas.drawText("Doubletap?", xOffset + (2 * (blockSize + 1)), yOffset + (15  * (blockSize + 1)), paint);
            if(doubletap) {
                canvas.drawText("Yes", xOffset + (7 * (blockSize + 1)) + 20, yOffset + (15 * (blockSize + 1)), paint);
            } else {
                canvas.drawText("No", xOffset + (7 * (blockSize + 1)) + 20, yOffset + (15  * (blockSize + 1)), paint);
            }

            //canvas.drawText("Pause", xOffset + (2 * (blockSize + 1)), yOffset + (18 * (blockSize + 1)), paint);

        }
        else
        {
            for(int row = 0; row < 20; row++){
                for(int column = 0; column < 10; column++) {
                    if (Native.getField(row, column)){
                        canvas.drawBitmap(Block, (column * blockSize) + (column * 2) + xOffset, (row * blockSize) + (row * 2) + yOffset, paint);
                    } else {
                        canvas.drawBitmap(VoidBlock, (column * blockSize) + (column * 2) + xOffset, (row * blockSize) + (row * 2) + yOffset, paint);
                    }
                }
            }
        }
    }

    //TODO dodaj tipke ovdje, sa generičkim vrijednostima
    public int clickButton(int button, boolean longClick) {

        switch (button)
        {
            case 0:
                setScreenState();
                Native.pauseContinue();
                return 1;
            case 1:
                if( longClick ){Native.buttonAlong();}
                else{Native.buttonA();}
                break;
            case 2:
                if( longClick || slamDunk ){Native.buttonBlong();}
                else{Native.buttonB();}
                break;
            case 3:
                Native.buttonC();
                break;
            case 4:
                if( longClick ){Native.buttonDlong();}
                else{Native.buttonD();}
                break;
            case 5:
                slamDunk = !slamDunk;
                postInvalidate();
                break;
            case 6:
                enableRotate = !enableRotate;
                postInvalidate();
                break;
            case 7:
                if(colorblind) {
                    VoidBlock = BitmapFactory.decodeResource(getResources(), R.drawable.void_block);
                } else {
                    VoidBlock = BitmapFactory.decodeResource(getResources(), R.drawable.void_block_cb);
                }
                VoidBlock = Bitmap.createScaledBitmap(VoidBlock, (int) blockSize, (int) blockSize, false);
                colorblind = !colorblind;
                postInvalidate();
                break;
            case 8:
                doubletap = !doubletap;
                TetrisActivity.getInstance().setDoubletap(doubletap);
                postInvalidate();
                break;
            case 9:
                postInvalidate();
                break;
            default:
                break;
        }
        return 0;
    }

    public int getAButton(float x, float y){
        if((x > xButton) && (x < (xButton + sizeButton)) && (y > yButton) && (y < (yButton + sizeButton))){
            return 1;
        }
        if((x > xButton + sizeButton) && (x < (xButton + (2 * sizeButton))) && (y > yButton) && (y < (yButton + sizeButton))){
            return 2;
        }
        if((x > xButton + (2 * sizeButton)) && (x < xButton + (3 * sizeButton)) && (y > yButton) && (y < (yButton + sizeButton))){
            return 3;
        }
        if((x > xButton + (3 * sizeButton)) && (x < xButton + (4 * sizeButton)) && (y > yButton) && (y < (yButton + sizeButton))) {
            return 4;
        }
        if(pauseState)
        {
            if((x > xOffset) && (x < xOffset + (10 * (blockSize + 1))) && (y > yOffset + (4  * (blockSize + 1)))
                    && (y < yOffset + (7  * (blockSize + 1)))){
                return 5;
            }
            if((x > xOffset) && (x < xOffset + (10 * (blockSize + 1))) && (y > yOffset + (7  * (blockSize + 1)))
                    && (y < yOffset + (11  * (blockSize + 1)))){
                return 6;
            }
            if((x > xOffset) && (x < xOffset + (10 * (blockSize + 1))) && (y > yOffset + (11  * (blockSize + 1)))
                    && (y < yOffset + (14  * (blockSize + 1)))){
                return 7;
            }
            if((x > xOffset) && (x < xOffset + (10 * (blockSize + 1))) && (y > yOffset + (14  * (blockSize + 1)))
                    && (y < yOffset + (17  * (blockSize + 1)))){
                return 8;
            }
            if((x > xOffset) && (x < xOffset + (10 * (blockSize + 1))) && (y > yOffset + (17  * (blockSize + 1)))
                    && (y < yOffset + (20  * (blockSize + 1)))){
                return 9;
            }
        }

        if((x >= 0) && (x < (xButton + 4* sizeButton)) && (y >= 0) && (y < (yButton - 100) )){
            return 0;
        }
        return -1;
    }
}

//TODO dodaj ovdje više wievova ovisno o state mašini

