/*
 * tscmd.h
 *
 *  Created on: 2016Äê5ÔÂ13ÈÕ
 *      Author: a
 */
#include <string>
#ifndef TSCMD_H_
#define TSCMD_H_
using std::string;
class TsCmd {
public:
	static const string Surffix;

	static string DoMeasure();

	static string GetCoordData();

	static string Laser(bool isOpen);

	static string GetDeviceType();

	static string GetDeviceNo();
};

#endif /* TSCMD_H_ */
