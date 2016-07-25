/*
 * Convert.h
 *
 *  Created on: 2016Äê5ÔÂ16ÈÕ
 *      Author: a
 */
#include <jni.h>
#include <string>
#ifndef CONVERT_H_
#define CONVERT_H_
using std::string;
class Convert {
public:
	static const jbyteArray StringToByteArray(JNIEnv* env, string str) ;
};
#endif /* CONVERT_H_ */
