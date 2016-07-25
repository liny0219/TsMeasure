/*
 * bluetoothsocket.h
 *
 *  Created on: 2016Äê5ÔÂ17ÈÕ
 *      Author: a
 */
#include <jni.h>
#ifndef BLUETOOTHSOCKET_H_
#define BLUETOOTHSOCKET_H_
using namespace std;
class BluetoothSocket {
private:
	jclass SocketClass;
	jmethodID GetInputsteamMethod;
	jmethodID GetoutputsteamMethod;
	jclass InputsteamClass;
	jclass OutputsteamClass;
	jmethodID OutputWriteMethod;
	jmethodID InputReadMethod;
	jmethodID CloseMethod;
public:
	BluetoothSocket();
	bool SetInit(JNIEnv * env);
	bool OutputWrite(JNIEnv * env, jobject socket, jbyteArray data);
	int InputRead(JNIEnv * env, jobject socket, jbyteArray buffer);
};

#endif /* BLUETOOTHSOCKET_H_ */
