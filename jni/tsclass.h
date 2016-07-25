/*
 * tsclass.h
 *
 *  Created on: 2016Äê5ÔÂ18ÈÕ
 *      Author: a
 */
#include <base64.h>
#include <bluetoothadapter.h>
#include <bluetoothsocket.h>
#include <convert.h>
#include <jni.h>
#include <RSA.h>
#include <stringutil.h>
#include <tscmd.h>
#include <thread>
#include <string>
#include <vector>

#ifndef TSCLASS_H_
#define TSCLASS_H_
using std::string;
using std::vector;
class TsMeasure {
private:
	JNIEnv * Env;
	BluetoothAdapter bluetoothAdapter;
	BluetoothSocket bluetoothSocket;
	jobject Socket;
	bool Write(string cmd, string operation, string* const error);
	bool CheckDeviceType(string src, string cmp[], int cmpsize);
	bool CheckDoMeasure(const char* src);
	string CheckGetCoordData(const char* src);
	string CheckGetDeviceNo(const char*);
	string ReadWait(int times, int waitMilliseconds, string error);
public:
	TsMeasure();
	void SetInit(JNIEnv * env, jobject socket);
	bool VerifyDeviceType(string* const error);
	bool DoMeasure(string* const error);
	const string GetCoordData(jint waitMilliseconds);
	string GetDeviceNo();
	bool VerifyDeviceNo(JNIEnv * env, jstring src);
	bool VerifyBlueToothMac(JNIEnv * env, jstring src, jobject adapter);
};

#endif /* TSCLASS_H_ */
