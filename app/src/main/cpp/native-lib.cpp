#include <jni.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_BUFFER_SIZE 128

// Function to safely process a transaction-like buffer
void process_buffer(const char *input, size_t input_size) {

    // Ensure input size is within acceptable bounds
    if (input_size > MAX_BUFFER_SIZE) {
        fprintf(stderr, "Error: Input size exceeds the maximum allowed buffer size.\n");
        return;
    }

    // Allocate memory for the buffer
    char *buffer = (char *)malloc(input_size + 1);
    if (!buffer) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return;
    }

    // Safely copy input to the buffer
    snprintf(buffer, input_size + 1, "%s", input);

    // Process the buffer (example logic)
    printf("Processing buffer: %s\n", buffer);

    // Free the allocated memory
    free(buffer);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_rabbyx_andro_1myelitis_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    char buffer[MAX_BUFFER_SIZE] = {0};

    // Safely process buffer
    process_buffer("ExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExampleExample", 1280);

    // Prevent buffer overflow
    std::string largeMessage = "A very large string that is safely handled to prevent overflow.";
    snprintf(buffer, MAX_BUFFER_SIZE, "%s", largeMessage.c_str());

    std::cout<<largeMessage<<std::endl;

    return env->NewStringUTF(buffer);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_rabbyx_andro_1myelitis_MainActivity_00024JSInterface_receiveDataFromJNI(
        JNIEnv* env,
        jobject /* this */,
        jstring message) {
    if (message == nullptr) {
        return env->NewStringUTF("Error: Received null message.");
    }

    // Convert the Java string to a C++ string
    const char* nativeMessage = env->GetStringUTFChars(message, nullptr);
    if (!nativeMessage) {
        return env->NewStringUTF("Error: Unable to get message.");
    }

    char buffer[MAX_BUFFER_SIZE] = {0};

    // Safely copy message to buffer
    snprintf(buffer, MAX_BUFFER_SIZE, "%s", nativeMessage);

    std::cout << "Received from JavaScript: " << buffer << std::endl;

    // Secure file writing
    const char* sdCardPath = "/storage/emulated/0/testfile.txt";
    std::ofstream outFile(sdCardPath, std::ios::out | std::ios::trunc);

    if (outFile.is_open()) {
        outFile << "Message from Java/C++: " << buffer << std::endl;
        outFile.close();
        std::cout << "File created and written successfully!" << std::endl;
    } else {
        std::cerr << "Failed to open file for writing!" << std::endl;
    }

    // Release the string after using it
    env->ReleaseStringUTFChars(message, nativeMessage);

    // Safely create a response
    std::string response = "Message received: " + std::string(buffer);
    return env->NewStringUTF(response.c_str());
}

int main() {
    const char *data = "Sample transaction data";
    size_t data_size = strlen(data);

    // Test the function with safe input
    process_buffer(data, data_size);

    return 0;
}
