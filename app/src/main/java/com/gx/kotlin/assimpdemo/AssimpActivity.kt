package com.gx.kotlin.assimpdemo

import android.os.Bundle
import android.view.View
import android.widget.Button
import com.gx.kotlin.scene.roam.RoamView

class AssimpActivity : BaseActivity() {
    lateinit var mRenderView : RoamView


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_assimp)

        mRenderView = findViewById(R.id.render)
        var i = 1
        findViewById<Button>(R.id.rotate).setOnClickListener(View.OnClickListener {
            var a = 0
//            mRenderView.transform.setPitch(20.0);
//            mRenderView.transform.setBearing(45.0,1920 / 2.0f + 1920 / 4.0f, 1016 / 2.0f)
//            mRenderView.transform.setBearing(45.0,1920 / 2.0f, 1016 / 2.0f)
            mRenderView.transform.moveBy(100.0, 75.0, 0)
            i++
        })


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