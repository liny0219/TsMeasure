package com.example.jnits;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothSocket;

public class Tslib {

	// ȫվ�ǲ����ӿڣ����ӿ�Ϊͬ�����ã���ȡʱΪ����״̬��һ������ȫվ�������ݷ��أ���Ҫ�����߳�����ʱ����
	public native String Measure(BluetoothAdapter adapter, BluetoothSocket socket, int waitMilliseconds,
			int validateType, String code);

	public native String GetDeviceNo(BluetoothSocket socket, int validateType);

	public static void Init() {
		System.loadLibrary("Tslib");
	}

	// ˽�е�Ĭ�Ϲ�����
	private Tslib() {
	}

	// ע�⣬����û��final
	private static Tslib single = null;

	// ��̬��������
	public synchronized static Tslib getInstance() {
		if (single == null) {
			single = new Tslib();
		}
		return single;
	}

	public enum ValidateType {
		/** ��У�� */
		NULL(0),
		/** ��У�� */
		PARITY(1),
		/** żУ�� */
		EVEN(2);
		private int value = 0;

		private ValidateType(int value) { // ������private�ģ�����������
			this.value = value;
		}
	}
}
