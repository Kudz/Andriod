package kuklinski.kamil.game;

/**
 * Created by kamil7 on 2017-03-28.
 */

import android.content.Context;
import android.app.Activity;
//import android.opengl.GLSurfaceView;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;
import android.graphics.Point;
import android.view.Display;

import java.io.File;
import java.io.IOException;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

public class IntroActivity extends Activity
{
    private static String TAG = "IntroActivity";

//    public static native void loadAssetManager(AssetManager mgr);
//    public static native void displayString(String mgr);
    private AssetManager assetManager;

    MyView mView;

    @Override protected void onCreate(Bundle icicle)
    {
        super.onCreate(icicle);
        mView = new MyView(getApplication());
        setContentView(mView);

        //delete that

        assetManager = getResources().getAssets();
//        try {
//            String[] listOfAsset = assetManager.list("Shaders");
//            Log.w(TAG, String.format("ArrayLength = %s", listOfAsset.length));
//            Log.w(TAG, String.format("listOfAsset = %s", listOfAsset[0]));
//        } catch (IOException e) {
//            Log.e(TAG, e.getMessage());
//        }
//        JavaToCppWrapper.loadAssetManager(assetManager);
    }

    @Override protected void onStart()
    {
        super.onStart();

        // initialize scene cpp, dosen't work opengl es 2 context not loaded
//        Display display = getWindowManager().getDefaultDisplay();
//        Point size = new Point();
//        display.getSize(size);
//        int width = size.x;
//        int height = size.y;
//        JavaToCppWrapper.initializeScene(width, height);
//        mView.onPause();
    }

    @Override protected void onPause()
    {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume()
    {
        super.onResume();
        mView.onResume();
    }

    @Override protected void onDestroy()
    {
        super.onDestroy();
        //cleaning cpp stuff
        JavaToCppWrapper.cleanScene();
    }
}

