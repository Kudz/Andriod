package kuklinski.kamil.game;

import android.content.res.AssetManager;

/**
 * Created by kamil7 on 2017-03-28.
 */

public class SmasherCPP
{
    static
    {
        System.loadLibrary("smasher");
    }

    /**
     * @param width the current view width
     * @param height the current view height
     */
    public static native void init(int width, int height);
    public static native void step();
    public static native void moveBoard(float x, float y);
//    public static native void assetLoad(AssetManager mgr);
//    public static native void displayString(String mgr);
//    public static native void loadTriangleShader();

}
