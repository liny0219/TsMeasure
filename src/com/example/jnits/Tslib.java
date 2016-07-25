package com.example.jnits;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothSocket;

public class Tslib {

	// 全站仪测量接口，本接口为同步调用，读取时为阻塞状态，一旦出现全站仪无数据返回，需要开辟线程做超时调用
	public native String Measure(BluetoothAdapter adapter, BluetoothSocket socket, int waitMilliseconds,
			int validateType, String code);

	public native String GetDeviceNo(BluetoothSocket socket, int validateType);

	public static void Init() {
		System.loadLibrary("Tslib");
	}

	// 私有的默认构造子
	private Tslib() {
	}

	// 注意，这里没有final
	private static Tslib single = null;

	// 静态工厂方法
	public synchronized static Tslib getInstance() {
		if (single == null) {
			single = new Tslib();
		}
		return single;
	}

	public enum ValidateType {
		/** 无校验 */
		NULL(0),
		/** 奇校验 */
		PARITY(1),
		/** 偶校验 */
		EVEN(2);
		private int value = 0;

		private ValidateType(int value) { // 必须是private的，否则编译错误
			this.value = value;
		}
	}
}
