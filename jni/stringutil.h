/*
 * stringutil.h
 *
 *  Created on: 2016Äê5ÔÂ17ÈÕ
 *      Author: a
 */
#include <jni.h>
#include <string>
#include <vector>
#include <sstream>
#ifndef STRINGUTIL_H_
#define STRINGUTIL_H_
typedef unsigned char BYTE;
using std::string;
using std::vector;
using std::stringstream;
class StringUtil {
public:
	static string NullToParity(string src);
	static string NullToEven(string src);
	static BYTE* NullToParityByte(string src);
	static BYTE* NullToEvenByte(string src);
	static string ToNull(string src);
	static BYTE ToNullByte(BYTE src);
	static BYTE* ToNullByte(string src);
	static BYTE* ToNullByte(BYTE* src);
	static vector<string> Split(string str, string pattern);
	static bool EndWith(const char * src, const char * end);
	static string IntToString(int & i);
};
#endif /* STRINGUTIL_H_ */
