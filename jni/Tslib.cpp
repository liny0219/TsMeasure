#include <com_example_jnits_Tslib.h>
#include <jni.h>

#include <tsclass.h>

using namespace std;

extern "C" {
JNIEXPORT jstring JNICALL Java_com_example_jnits_Tslib_Measure(JNIEnv * env,
		jobject o, jobject adapter, jobject socket, jint waitMilliseconds,
		jint validateType, jstring code) {
	try {
		string error = "";
		if (socket == 0) {
			error = "socket is null";
			return env->NewStringUTF(error.c_str());
		}

		if (adapter == 0) {
			error = "adapter is null";
			return env->NewStringUTF(error.c_str());
		}

		TsMeasure measure = TsMeasure();
		measure.SetInit(env, socket);

//		if (measure.VerifyDeviceNo(env, code) == false) {
//			error = "verification code error";
//			return env->NewStringUTF(error.c_str());
//		}

		if (measure.VerifyBlueToothMac(env, code, adapter) == false) {
			error = "verification code error";
			return env->NewStringUTF(error.c_str());
		}

		if (measure.VerifyDeviceType(&error) == false) {
			return env->NewStringUTF(error.c_str());
		}

		if (measure.DoMeasure(&error) == false) {
			return env->NewStringUTF(error.c_str());
		}
		string data = measure.GetCoordData(waitMilliseconds);
		return env->NewStringUTF(data.c_str());
	} catch (char *mes) {
		return env->NewStringUTF(mes);
	}
}

JNIEXPORT jstring JNICALL Java_com_example_jnits_Tslib_GetDeviceNo(JNIEnv * env,
		jobject o, jobject socket, jint validateType) {
	try {
		string error = "";
		if (socket == 0) {
			error = "socket is null";
			return env->NewStringUTF(error.c_str());
		}
		TsMeasure measure = TsMeasure();
		measure.SetInit(env, socket);
		string mes = measure.GetDeviceNo();
		return env->NewStringUTF(mes.c_str());
	} catch (char *mes) {
		return env->NewStringUTF(mes);
	}
}
}

