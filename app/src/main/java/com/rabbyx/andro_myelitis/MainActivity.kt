package com.rabbyx.andro_myelitis

import android.Manifest
import android.content.pm.PackageManager
import android.os.Bundle
import android.webkit.JavascriptInterface
import android.webkit.WebView
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import com.rabbyx.andro_myelitis.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    // Permission request code
    private val REQUEST_STORAGE_PERMISSION = 1

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Check and request storage permissions
        checkStoragePermissions()

        // Set up the WebView
        val webView: WebView = binding.webView
        webView.settings.javaScriptEnabled = true
        webView.addJavascriptInterface(JSInterface(), "Android")

        // Load a sample HTML or JavaScript
        webView.loadUrl("file:///android_asset/index.html")
    }


    // Check if storage permissions are granted
    private fun checkStoragePermissions() {
        val writePermission = ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE)
        val readPermission = ContextCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE)

        if (writePermission != PackageManager.PERMISSION_GRANTED || readPermission != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(
                this,
                arrayOf(Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.READ_EXTERNAL_STORAGE),
                REQUEST_STORAGE_PERMISSION
            )
        }
    }

    // Handling permission result
    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<String>, grantResults: IntArray) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)

        when (requestCode) {
            REQUEST_STORAGE_PERMISSION -> {
                if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED &&
                    grantResults[1] == PackageManager.PERMISSION_GRANTED) {
                    println("Storage permission granted")
                } else {
                    println("Storage permission denied")
                }
            }
        }
    }



    // Create the interface for JavaScript to call Android
    class JSInterface {
        @JavascriptInterface
        fun sendDataToNative(message: String) {
            // Call the C++ function or handle the message
            val response = receiveDataFromJNI(message)
            println("Response from C++: $response")
        }

        external fun receiveDataFromJNI(message: String): String
    }

    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'andro_myelitis' library on application startup.
        init {
            System.loadLibrary("andro_myelitis")
        }
    }
}
