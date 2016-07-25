LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := Tslib
LOCAL_SRC_FILES := Tslib.cpp tscmd.cpp convert.cpp bluetoothsocket.cpp stringutil.cpp tsclass.cpp RSA.cpp base64.cpp bluetoothadapter.cpp
LOCAL_CPPFLAGS := -std=c++11 -D__cplusplus=201103L -fexceptions -frtti
include $(BUILD_SHARED_LIBRARY)