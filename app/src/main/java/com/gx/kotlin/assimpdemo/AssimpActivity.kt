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
        var width = 800
        var height = 600

        mRenderView = findViewById(R.id.render)
        var i = 1
        findViewById<Button>(R.id.rotate).setOnClickListener(View.OnClickListener {
            mRenderView.transform.setBearing(45.0 * i,width / 2.0f + width / 4.0f, height / 2.0f)
            i++
        })

        var j = 1
        findViewById<Button>(R.id.pitch).setOnClickListener(View.OnClickListener {
            mRenderView.transform.setPitch(20.0 * j)
        })

        findViewById<Button>(R.id.move).setOnClickListener(View.OnClickListener {
            mRenderView.transform.moveBy(width / 4.0, height / 4.0, 0)
        })

        findViewById<Button>(R.id.btn_zoom_in).setOnClickListener(View.OnClickListener {

        })

        findViewById<Button>(R.id.btn_zoom_out).setOnClickListener(View.OnClickListener {

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