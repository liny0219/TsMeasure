/*
 * bluetoothadapter.cpp
 *
 *  Created on: 2016Äê6ÔÂ7ÈÕ
 *      Author: a
 */

#include <bluetoothadapter.h>
BluetoothAdapter::BluetoothAdapter() {
}

bool BluetoothAdapter::SetInit(JNIEnv * env) {
	this->AdapterClass = env->FindClass("android/bluetooth/BluetoothAdapter");

	this->GetAddressMethod = env->GetMethodID(this->AdapterClass, "getAddress",
			"()Ljava/lang/String;");
}

string BluetoothAdapter::getAddress(JNIEnv * env, jobject adapter) {
	jstring jmac = (jstring) env->CallObjectMethod(adapter,
			this->GetAddressMethod);
	const char* cmac;
	cmac = env->GetStringUTFChars(jmac, (jboolean*) false);
	string mac(cmac);
	env->ReleaseStringUTFChars(jmac, cmac);
	return mac;
}
