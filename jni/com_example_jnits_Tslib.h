/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_example_jnits_Tslib */

#ifndef _Included_com_example_jnits_Tslib
#define _Included_com_example_jnits_Tslib
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_example_jnits_Tslib
 * Method:    Measure
 * Signature: (Landroid/bluetooth/BluetoothAdapter;Landroid/bluetooth/BluetoothSocket;IILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_jnits_Tslib_Measure
  (JNIEnv *, jobject, jobject, jobject, jint, jint, jstring);

/*
 * Class:     com_example_jnits_Tslib
 * Method:    GetDeviceNo
 * Signature: (Landroid/bluetooth/BluetoothSocket;I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_example_jnits_Tslib_GetDeviceNo
  (JNIEnv *, jobject, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif