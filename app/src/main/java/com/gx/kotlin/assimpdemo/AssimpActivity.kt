package com.gx.kotlin.assimpdemo

import android.os.Bundle
import com.gx.kotlin.scene.roam.RoamView

class AssimpActivity : BaseActivity() {
    lateinit var mRenderView : RoamView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_assimp)

        mRenderView = findViewById(R.id.render)
//        var assetManager = assets
//        var path = filesDir.absolutePath
//        NativeRenderScene.onModelCreated(assetManager, path)
//
//        mGesture = Gesture(this)
//        mRenderView.setOnTouchListener(mGesture.TwoFingerGestureListener)
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
        mRenderView.onDestroy()
    }
}