package com.gx.kotlin.assimpdemo

import android.content.Intent
import android.os.Bundle
import android.widget.TextView

class MainActivity : BaseActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        findViewById<TextView>(R.id.tv_title).setOnClickListener {
            startActivity(Intent(
                applicationContext,
                AssimpActivity::class.java)
            )
        }
    }
}