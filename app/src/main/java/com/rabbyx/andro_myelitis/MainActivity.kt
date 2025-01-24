package com.rabbyx.andro_myelitis

import android.os.Bundle
import android.webkit.JavascriptInterface
import android.webkit.WebView
import android.widget.WebView
import com.rabbyx.andro_myelitis.databinding.ActivityMainBinding
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Set up the WebView
        val webView: WebView = binding.webView
        webView.settings.javaScriptEnabled = true
        webView.addJavascriptInterface(JSInterface(), "Android")

        // Load a sample HTML or JavaScript
        webView.loadUrl("file:///android_asset/index.html")
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
