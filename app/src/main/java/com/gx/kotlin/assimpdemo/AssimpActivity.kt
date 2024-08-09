package com.gx.kotlin.assimpdemo

import android.content.res.AssetManager
import android.os.Bundle
import com.gx.kotlin.scene.NativeRenderScene
import com.gx.kotlin.scene.gesture.Gesture
import com.gx.kotlin.scene.view.SceneRenderGLSurfaceView

class AssimpActivity : BaseActivity() {
    lateinit var mRenderView : SceneRenderGLSurfaceView
    lateinit var mGesture : Gesture


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_assimp)

        mRenderView = findViewById(R.id.render)
        var assetManager = assets
        var path = filesDir.absolutePath
        NativeRenderScene.onModelCreated(assetManager, path)

        mGesture = Gesture(this)
        mRenderView.setOnTouchListener(mGesture.TwoFingerGestureListener)
    }

    override fun onResume() {
        super.onResume()
        mRenderView.onResume()
    }

    override fun onPause() {
        super.onPause()
        mRenderView.onPause()
    }

    override fun onDestroy() {
        super.onDestroy()
    }
}