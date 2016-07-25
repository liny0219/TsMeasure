/*
 * stringutil.cpp
 *
 *  Created on: 2016年5月17日
 *      Author: a
 */

#include <stringutil.h>
string StringUtil::NullToParity(string src) {
	return 0;
}
string StringUtil::NullToEven(string src) {
	return 0;
}
BYTE* StringUtil::NullToParityByte(string src) {
	return 0;
}
BYTE* StringUtil::NullToEvenByte(string src) {
	return 0;
}
string StringUtil::ToNull(string src) {
	return 0;
}
BYTE StringUtil::ToNullByte(BYTE src) {
	return 0;
}
BYTE* StringUtil::ToNullByte(string src) {
	return 0;
}
BYTE* StringUtil::ToNullByte(BYTE* src) {
	return 0;
}

vector<string> StringUtil::Split(string src, string pattern) {
	string::size_type pos;
	vector<string> result;
	src += pattern; //扩展字符串以方便操作
	int size = src.size();
	for (int i = 0; i < size; i++) {
		pos = src.find(pattern, i);
		if (pos < size) {
			string s = src.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

bool StringUtil::EndWith(const char * src, const char * end) {
    bool result = false;
    if (src != NULL && end != NULL) {
        int l1 = strlen(src);
        int l2 = strlen(end);
        if (l1 >= l2) {
            if (strcmp(src + l1 - l2, end) == 0) {
                result = true;
            }
        }
    }
    return result;
}

string StringUtil::IntToString(int & i)
{
	string s;
	stringstream ss;
	ss << i;
	return ss.str();
}

