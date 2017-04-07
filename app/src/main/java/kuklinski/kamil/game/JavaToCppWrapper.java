package kuklinski.kamil.game;

/**
 * Created by kamil7 on 2017-03-30.
 */

import android.content.res.AssetManager;

public class JavaToCppWrapper
{
    static
    {
        System.loadLibrary("cppToJava");
    }

    public static native void loadAssetManager(AssetManager mgr);
    public static native void initializeScene(int width, int height);
    public static native void cleanScene();
    public static native void makeStep();
    public static native void initializeShader();
    public static native void initializeMatrices();
    public static native void setTouchMovement(boolean isMoving, float xPosition, float yPosition);
}
