package com.gx.kotlin.assimpdemo

import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.view.MotionEvent
import android.widget.TextView
import com.gx.kotlin.scene.gesture.AndroidGesturesManager
import com.gx.kotlin.scene.gesture.MoveGestureDetector
import com.gx.kotlin.scene.gesture.MoveGestureDetector.OnMoveGestureListener

class MainActivity : BaseActivity() {
    lateinit var mAndroidGesturesManager: AndroidGesturesManager

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        mAndroidGesturesManager = AndroidGesturesManager(this);


        mAndroidGesturesManager.setMoveGestureListener(object :
            MoveGestureDetector.OnMoveGestureListener {
            override fun onMoveBegin(detector: MoveGestureDetector): Boolean {
                Log.d("MoveGesture", "onMoveBegin");
                return true;
            }

            override fun onMove(
                detector: MoveGestureDetector,
                distanceX: Float,
                distanceY: Float
            ): Boolean {
                Log.d("MoveGesture", "onMove");
                return true;
            }

            override fun onMoveEnd(
                detector: MoveGestureDetector,
                velocityX: Float,
                velocityY: Float
            ) {
                Log.d("MoveGesture", "onMoveEnd");
            }
        });

        findViewById<TextView>(R.id.tv_title).setOnClickListener {
            startActivity(Intent(
                applicationContext,
                AssimpActivity::class.java)
            )
        }
    }

    override fun onTouchEvent(event: MotionEvent?): Boolean {
        return mAndroidGesturesManager.onTouchEvent(event) || super.onTouchEvent(event)
    }

//    private val onMoveGestureListener: OnMoveGestureListener = object : MoveGestureDetector.OnMoveGestureListener() {
//        fun onMoveBegin(detector: MoveGestureDetector): Boolean {
//            return true
//        }
//
//        fun onMove(detector: MoveGestureDetector, distanceX: Float, distanceY: Float): Boolean {
//            return true
//        }
//
//        fun onMoveEnd(detector: MoveGestureDetector, velocityX: Float, velocityY: Float) {
//        }
//    }


}