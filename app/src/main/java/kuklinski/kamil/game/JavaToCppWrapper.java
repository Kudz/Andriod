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
}
