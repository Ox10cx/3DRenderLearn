package com.gx.kotlin.assimpdemo

import android.Manifest
import android.content.pm.PackageManager
import android.os.Build
import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat


open class BaseActivity : AppCompatActivity() {
    val mRequestCode = 100
    lateinit var mPermissions : Array<String>
    lateinit var mPermissionList : ArrayList<String>


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        mPermissions = arrayOf(
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.READ_EXTERNAL_STORAGE)
        mPermissionList = arrayListOf();
    }

    override fun onResume() {
        super.onResume()
        initPermission()
    }

    fun initPermission()  {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            mPermissionList.clear()
            for (permission in mPermissions) {
                if (ContextCompat.checkSelfPermission(this, permission) != PackageManager.PERMISSION_GRANTED) {
                    mPermissionList.add(permission)
                }
            }
            if (mPermissionList.size > 0) {
                ActivityCompat.requestPermissions(this, mPermissions, mRequestCode)
            }
        }
    }


    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        var hasPermissionDismiss = false
        if (mRequestCode == requestCode) {
            for (result in grantResults) {
                if (result == -1) {
                    hasPermissionDismiss = true
                }
            }
        }
        if (hasPermissionDismiss) {
            Toast.makeText(this, "请开启权限", Toast.LENGTH_SHORT).show()
        }
    }
}