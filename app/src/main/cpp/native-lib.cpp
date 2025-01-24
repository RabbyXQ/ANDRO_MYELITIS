#include <jni.h>
#include <string>
#include <iostream>

extern "C" JNIEXPORT jstring JNICALL
Java_com_rabbyx_andro_1myelitis_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_rabbyx_andro_1myelitis_MainActivity_00024JSInterface_receiveDataFromJNI(
        JNIEnv* env,
        jobject /* this */,
        jstring message) {

    // Convert the Java string to a C++ string
    const char* nativeMessage = env->GetStringUTFChars(message, 0);

    // Print the message to the console
    std::cout << "Received from JavaScript: " << nativeMessage << std::endl;

    // Release the string once we're done with it
    env->ReleaseStringUTFChars(message, nativeMessage);

    // Return a response to Java/Kotlin
    std::string response = "Message received: " + std::string(nativeMessage);
    return env->NewStringUTF(response.c_str());
}
