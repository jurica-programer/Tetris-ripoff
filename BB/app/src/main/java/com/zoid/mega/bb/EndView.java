package com.zoid.mega.bb;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.View;

/**
 * Created by Jura on 10.5.2016..
 */
public class EndView extends View{
    private Paint paint;
    private int textSize = 70;      // Text size
    private int orange = android.graphics.Color.rgb(32, 162, 64);

    // Constructor
    public EndView(Context context) {
        super(context);
        paint = new Paint();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        //score
        paint.setColor(orange);
        paint.setTextSize(textSize);
        canvas.drawText("GameOver", 140, 140, paint);
        canvas.drawText(Integer.toString(GameplayData.getScore()), 200, 200, paint);
    }
}
