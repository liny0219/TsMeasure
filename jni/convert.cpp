/*
 * convert.cpp
 *
 *  Created on: 2016��5��16��
 *      Author: a
 */


#include <convert.h>

const jbyteArray Convert::StringToByteArray(JNIEnv* env, string str) {
	const char* cstr = str.data();
	int len = strlen(cstr);
	jbyteArray jbarr = env->NewByteArray(len);
	env->SetByteArrayRegion(jbarr, 0, len, (jbyte*) cstr);
	return jbarr;
}
