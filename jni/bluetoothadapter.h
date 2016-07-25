/*
 * bluetoothadapter.h
 *
 *  Created on: 2016Äê6ÔÂ7ÈÕ
 *      Author: a
 */
#include <jni.h>
#include <string>
#ifndef JNI_BLUETOOTHADAPTER_H_
#define JNI_BLUETOOTHADAPTER_H_
using namespace std;
class BluetoothAdapter {
private:
	jclass AdapterClass;
	jmethodID GetAddressMethod;
public:
	BluetoothAdapter();
	bool SetInit(JNIEnv * env);
	string getAddress(JNIEnv * env, jobject adapter);
};

#endif /* JNI_BLUETOOTHADAPTER_H_ */
