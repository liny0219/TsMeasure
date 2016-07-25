/*
 * bluetoothsocket.cpp
 *
 *  Created on: 2016Äê5ÔÂ17ÈÕ
 *      Author: a
 */
#include <bluetoothsocket.h>
BluetoothSocket::BluetoothSocket() {
}

bool BluetoothSocket::SetInit(JNIEnv * env) {
	this->SocketClass = env->FindClass("android/bluetooth/BluetoothSocket");

	this->GetoutputsteamMethod = env->GetMethodID(this->SocketClass,
			"getOutputStream", "()Ljava/io/OutputStream;");

	this->GetInputsteamMethod = env->GetMethodID(this->SocketClass,
			"getInputStream", "()Ljava/io/InputStream;");

	this->CloseMethod = env->GetMethodID(this->SocketClass, "close", "()V");

	this->InputsteamClass = env->FindClass("java/io/InputStream");

	this->OutputsteamClass = env->FindClass("java/io/OutputStream");

	this->OutputWriteMethod = env->GetMethodID(this->OutputsteamClass, "write",
			"([B)V");

	this->InputReadMethod = env->GetMethodID(this->InputsteamClass, "read",
			"([B)I");
}

bool BluetoothSocket::OutputWrite(JNIEnv * env, jobject socket,
		jbyteArray data) {
	jobject output = env->CallObjectMethod(socket, this->GetoutputsteamMethod);
	env->CallVoidMethod(output, this->OutputWriteMethod, data);
	return true;
}

int BluetoothSocket::InputRead(JNIEnv * env, jobject socket,
		jbyteArray buffer) {
	jobject input = env->CallObjectMethod(socket, this->GetInputsteamMethod);
	return env->CallIntMethod(input, this->InputReadMethod, buffer);
}
