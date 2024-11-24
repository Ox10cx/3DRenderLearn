package com.gx.kotlin.assimpdemo

import android.graphics.Point
import android.graphics.PointF
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Button
import com.gx.kotlin.scene.camera.CameraUpdateFactory
import com.gx.kotlin.scene.geometry.WayPoint
import com.gx.kotlin.scene.roam.DriveRoam
import com.gx.kotlin.scene.roam.RoamView
import kotlin.properties.Delegates

class AssimpActivity : BaseActivity() {
    lateinit var mRenderView : RoamView
    lateinit var mDriveRoam : DriveRoam
    var width by Delegates.notNull<Int>()
    var height by Delegates.notNull<Int>()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_assimp)
        mRenderView = findViewById(R.id.render)
        mRenderView.getRoamAsync { driveRoam ->
            this.mDriveRoam = driveRoam
            this.width = mRenderView.width
            this.height = mRenderView.height
        }


        var i = 1
        findViewById<Button>(R.id.rotate).setOnClickListener(View.OnClickListener {
////            mRenderView.transform.setBearing(45.0 * i,width / 2.0f + width / 4.0f, height / 2.0f + height / 4.0f)
//            mDriveRoam.setFocalBearing(45.0 * i,width / 2.0f + width / 4.0f, height / 2.0f + height / 4.0f, 100)
            mDriveRoam.easeCamera(CameraUpdateFactory.bearingTo(45.0 * i))

            i++
        })

        var j = 1
        findViewById<Button>(R.id.pitch).setOnClickListener(View.OnClickListener {
            mDriveRoam.easeCamera(CameraUpdateFactory.tiltTo(20.0 * j))
//            mRenderView.transform.setPitch(20.0 * j)
        })

        findViewById<Button>(R.id.move).setOnClickListener(View.OnClickListener {
//            mRenderView.transform.moveBy(width / 4.0, height / 4.0, 0)
//            mDriveRoam.easeCamera(CameraUpdateFactory.newWayPoint(WayPoint(256 / 2.0, 256 / 2.0)))
            mDriveRoam.easeCamera(CameraUpdateFactory.newWayPointZoom(WayPoint(-64.0, 0.0), 1.0))
        })

        findViewById<Button>(R.id.btn_zoom_in).setOnClickListener(View.OnClickListener {
//            mDriveRoam.zoomBy(1.0, PointF(width / 2.0f + 64 , height / 2.0f))
            mDriveRoam.easeCamera(CameraUpdateFactory.zoomBy(1.0, Point(width / 2 + 64, height / 2)))
        })

        findViewById<Button>(R.id.btn_zoom_out).setOnClickListener(View.OnClickListener {
//            mDriveRoam.zoomBy(-0.5, PointF(width / 2.0f + 64 , height / 2.0f))
            mDriveRoam.easeCamera(CameraUpdateFactory.zoomBy(2.0, Point(width / 2 - 128 , height / 2)))
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