package com.example.tsmeasure;

import java.io.IOException;
import java.util.UUID;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;

public class BlueToothUtil {
	static BluetoothAdapter mAdapter = null;

	public static boolean IsEnable() {
		try {
			mAdapter = BluetoothAdapter.getDefaultAdapter();
		} catch (Exception e) {
			return false;
		}
		return true;
	}


	public static boolean BlueIsOpen() {
		if (mAdapter == null) {
			return false;
		}
		return mAdapter.isEnabled();

	}

	public static boolean OpenBlue() {
		if (mAdapter == null) {
			return false;
		}
		return mAdapter.enable();
	}


	public static BluetoothDevice GetDevice(String MAC) throws Exception {
		BluetoothDevice device = null;
		device = mAdapter.getRemoteDevice(MAC);
		return device;
	}


	public static BluetoothSocket Connect(BluetoothDevice device)
			throws IOException {
		// ¹Ì¶¨µÄUUID
		final String SPP_UUID = "00001101-0000-1000-8000-00805F9B34FB";
		UUID uuid = UUID.fromString(SPP_UUID);
		BluetoothSocket socket = null;
		socket = device.createRfcommSocketToServiceRecord(uuid);
		socket.connect();
		return socket;
	}
}
