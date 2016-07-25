/*
 * tsclass.cpp
 *
 *  Created on: 2016Äê5ÔÂ18ÈÕ
 *      Author: a
 */
#include <tsclass.h>
TsMeasure::TsMeasure() {

}

void TsMeasure::SetInit(JNIEnv * env, jobject socket) {
	this->Env = env;
	this->Socket = socket;
	this->bluetoothSocket = BluetoothSocket();
	this->bluetoothSocket.SetInit(env);
	this->bluetoothAdapter = BluetoothAdapter();
	this->bluetoothAdapter.SetInit(env);
}

string TsMeasure::ReadWait(int times, int waitMilliseconds, string error) {
	string mes = "";
	jint time = 0;
	while (time < times) {
		jbyteArray buffer = Env->NewByteArray(1024);
		this_thread::sleep_for(chrono::milliseconds(waitMilliseconds));
		int bytes = this->bluetoothSocket.InputRead(Env, Socket, buffer);
		if (Env->ExceptionCheck()) {
			Env->ExceptionOccurred();
			Env->ExceptionClear();
			return error;
		}
		if (bytes != 0) {
			char* src = (char*) Env->GetByteArrayElements(buffer, 0);
			mes += src;
			if (StringUtil::EndWith(mes.data(), TsCmd::Surffix.data()))
				break;
		} else {
			break;
		}
		time = time + 1;
	}
	return mes;
}

bool TsMeasure::Write(string cmd, string operation, string* const error) {
	this->bluetoothSocket.OutputWrite(Env, Socket,
			Convert::StringToByteArray(Env, cmd));
	if (Env->ExceptionCheck()) {
		Env->ExceptionOccurred();
		Env->ExceptionClear();
		*error = "error:OutputWrite " + operation;
		return false;
	}
	return true;
}

bool TsMeasure::CheckDeviceType(string src, string cmp[], int cmpsize) {
	for (int i = 0; i < cmpsize; i++) {
		string tmp = cmp[i];
		string::size_type index = src.find(tmp);
		if (index != string::npos) {
			return true;
		}
	}
	return false;
}

bool TsMeasure::CheckDoMeasure(const char* src) {
	vector<string> sp = StringUtil::Split(src, ",");
	if (sp.size() < 2
			|| (sp[2] != "0:0\r\n" && sp[2] != "0:0" && sp[2] != "0:0\n")) {
		return false;
	}
	return true;
}

string TsMeasure::CheckGetCoordData(const char* src) {
	vector<string> sp = StringUtil::Split(src, ",");
	if (sp.size() < 6 || sp[2] != "0:0") {
		return "error:CheckGetCoordData result";
	}
	string suffix = "\r\n";
	string prefixE = "E=";
	string prefixN = "N=";
	string prefixH = "H=";
	string data = prefixE + sp[3] + suffix + prefixN + sp[4] + suffix + prefixH
			+ sp[5] + suffix;
	return data;
}

string TsMeasure::CheckGetDeviceNo(const char* src) {
	vector<string> sp = StringUtil::Split(src, ",");
	if (sp.size() < 3 || sp[2] != "0:0") {
		return "error:CheckGetDeviceNo result";
	}
	string data = sp[3];
	size_t n = data.find_last_not_of("\r\n");
	if (n != string::npos) {
		data.erase(n + 1, data.size() - n);
	}
	return data;
}

bool TsMeasure::VerifyDeviceType(string* const error) {
	if (Write(TsCmd::GetDeviceType(), "GetDeviceType", error) == false) {
		return false;
	}
	string mes = ReadWait(10, 200, "error:InputRead GetDeviceType");
	string typelist[] = { "1201", "TS15", "06" };
	if (CheckDeviceType(mes.data(), typelist, 2) == false) {
		*error = "error:Unknown RPC, procedure ID invalid.";
		return false;
	}
	return true;
}

bool TsMeasure::DoMeasure(string* const error) {
	if (Write(TsCmd::DoMeasure(), "DoMeasure", error) == false) {
		return false;
	}
	string mes = ReadWait(10, 200, "error:InputRead DoMeasure");
	if (CheckDoMeasure(mes.data()) == false) {
		*error = "error:device CheckDoMeasure result";
		return false;
	}
	return true;
}

const string TsMeasure::GetCoordData(jint waitMilliseconds) {
	string mes = "";
	if (Write(TsCmd::GetCoordData(), "GetCoordData", &mes) == false) {
		return mes;
	}
	mes = ReadWait(1, waitMilliseconds, "error:InputRead GetCoordData");
	return CheckGetCoordData(mes.data());
}

string TsMeasure::GetDeviceNo() {
	string mes = "";
	if (Write(TsCmd::GetDeviceNo(), "GetDeviceNo", &mes) == false) {
		return 0;
	}
	mes = ReadWait(10, 200, "error:InputRead GetDeviceNo");
	return CheckGetDeviceNo(mes.c_str());
}

static const string src_d64 =
		"MSwxLDcsMiwxLDUsNCwwLDMsMSw2LDUsOSwxLDcsNiwwLDMsNSw0LDAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsLTg1ODk5MzQ2MCwtODU4OTkzNDYwLC04NTg5OTM0NjAsMjAs";
static const string src_n64 =
		"MywxLDAsNSwyLDUsNyw4LDMsNSwzLDIsMywzLDIsOSwyLDcsMSwwLDUsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMCwwLDAsMjEs";
bool TsMeasure::VerifyDeviceNo(JNIEnv * env, jstring src) {
	if (src == 0)
		return false;
	string devcode = GetDeviceNo();
	string src64 = env->GetStringUTFChars(src, 0);
	RSA rsa = RSA();
	string decd = base64_decode(src_d64);
	string decn = base64_decode(src_n64);
	int *d = RSA::ConvertKeyToIntArray(decd, MAX);
	int *n = RSA::ConvertKeyToIntArray(decn, MAX);
	string des64 = base64_decode(src64);
	string verify = rsa.tdecrypto(d, n, des64);
	if (devcode != verify) {
		return false;
	}
	return true;
}

bool TsMeasure::VerifyBlueToothMac(JNIEnv * env, jstring src, jobject adapter) {
	if (src == 0)
		return false;
	string devcode = this->bluetoothAdapter.getAddress(env, adapter);
	string src64 = env->GetStringUTFChars(src, 0);
	RSA rsa = RSA();
	string decd = base64_decode(src_d64);
	string decn = base64_decode(src_n64);
	int *d = RSA::ConvertKeyToIntArray(decd, MAX);
	int *n = RSA::ConvertKeyToIntArray(decn, MAX);
	string des64 = base64_decode(src64);
	string verify = rsa.tdecrypto(d, n, des64);
	if (devcode != verify) {
		return false;
	}
	return true;
}

