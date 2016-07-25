package com.example.jnits;

import java.io.IOException;
import java.util.Calendar;

import com.example.jnits.TsThread.TsThreadType;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothSocket;

public class TsUtil {
	private TsThread thread;

	public TsUtil(BluetoothAdapter adapter, BluetoothSocket socket) {
		thread = new TsThread(adapter, socket);
	}

	public String DoMeasure(int waitMilliseconds, int timeoutMilliseconds, String code) {
		thread.setWaitMilliseconds(waitMilliseconds);
		thread.setThreadType(TsThreadType.DoMeasure);
		thread.setCode(code);
		thread.start();
		waitTimeout(timeoutMilliseconds);
		return thread.getData();
	}

	public String GetDeviceNo(int timeoutMilliseconds) {
		thread.setThreadType(TsThreadType.GetDeviceNo);
		thread.start();
		waitTimeout(timeoutMilliseconds);
		return thread.getData();
	}

	private void waitTimeout(int milliseconds) {
		Calendar sCalendar = Calendar.getInstance();
		while (true) {
			Calendar eCalendar = Calendar.getInstance();
			long l = eCalendar.getTimeInMillis() - sCalendar.getTimeInMillis();
			if (Math.abs(l) > milliseconds) {
				break;
			}
		}
		thread.close();
	}

}

class TsThread extends Thread {
	private String message = "";
	private BluetoothSocket socket;
	private int waitMilliseconds;
	private TsThreadType type;
	private String code = "";
	private BluetoothAdapter adapter;

	public TsThread(BluetoothAdapter adapter, BluetoothSocket socket) {
		this.adapter = adapter;
		this.socket = socket;
	}

	@Override
	public void run() {
		switch (type) {
		case DoMeasure:
			message = Tslib.getInstance().Measure(adapter, socket, waitMilliseconds, 0, code);
			break;
		case GetDeviceNo:
			message = Tslib.getInstance().GetDeviceNo(socket, 0);
			break;
		}

	}

	public String getData() {
		return message;
	}

	public void setWaitMilliseconds(int waitMilliseconds) {
		this.waitMilliseconds = waitMilliseconds;
	}

	public void setThreadType(TsThreadType type) {
		this.type = type;
	}

	public void setCode(String code) {
		this.code = code;
	}

	enum TsThreadType {
		DoMeasure, GetDeviceNo
	}

	public void close() {
		try {
			this.socket.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
