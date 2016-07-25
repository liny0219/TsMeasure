package com.example.tsmeasure;

import java.io.IOException;
import java.util.ArrayList;
import com.example.jnits.TsUtil;
import com.example.jnits.Tslib;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

public class MainActivity extends Activity {
	private Button mButtonScan;
	private Button mButtonRead;
	private Button mButtonSend;
	private TextView mTextViewMsg;
	private ListView mListView;
	private BluetoothAdapter mBlueToothAdapter = null;
	private BluetoothReceiver mBlueToothReceiver = null;
	private ArrayList<BluetoothDevice> mDevices = new ArrayList<BluetoothDevice>();
	private DevicesListAdapter mAdapter;
	private BluetoothDevice mSelectDevice;
	private static final int MESSAGE_UI = 1;
	private MyHandler transHandler = null;
	private BluetoothSocket mSocket;
	// ʹ�ô�Demo���޸�Ϊ�����ע����
	private final static String VERIFYCODE = "MTIxNDAyODQ0MDU3OTczNzAxMzY1NDgzMTIxNDAyODQ0MDU3OTczNzAxMzY1NDgzMTIxNzgxMzA5MTgzMDAwMDY0NTg5MTYyMTIxNDAyODQ0MDU3OTczNzAxMzY1NDgzMTIxNDAyODQ0MDU3OTczNzAxMzY1NDgzMTIxNzgxMzA5MTgzMDAwMDY0NTg5MTYyMTIxNzYyNjA3NjA4Mzg2MTAxODgyMDA0MTIxOTYwMTk1MjkzNTAzNTQ5ODAyNTY0MTIxNzgxMzA5MTgzMDAwMDY0NTg5MTYyMTIwNzc3NjQ2Mjg5NzMzNDY5NjIwODIxMjA5MDA3MDA2MzAyNDE1MzU0MjAwMjEyMTc4MTMwOTE4MzAwMDA2NDU4OTE2MjEyMTk2MDE5NTI5MzUwMzU0OTgwMjU2NDEyMDkwMDcwMDYzMDI0MTUzNTQyMDAyMTIxNzgxMzA5MTgzMDAwMDY0NTg5MTYyMTIxNTI4MjgyNDU3ODcyMzI4Mjk4ODIxMTIxNTg3NDEyNjYyODYwODUzNDY3NTE0";

	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		if (mSocket != null)
			try {
				mSocket.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		super.onPause();
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		Tslib.Init();
		mAdapter = new DevicesListAdapter();
		mBlueToothAdapter = BluetoothAdapter.getDefaultAdapter();
		transHandler = new MyHandler(MainActivity.this.getMainLooper());
		mButtonScan = (Button)

		findViewById(R.id.button_Scan);
		mButtonSend = (Button) findViewById(R.id.button_Send);
		mButtonRead = (Button) findViewById(R.id.button_Read);
		mTextViewMsg = (TextView) findViewById(R.id.textView_Msg);
		mButtonRead.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				// if (mSocket == null || mSelectDevice == null) {
				// UpdateUI("���Ƚ�������");
				// return;
				// }
				// if (!mSocket.isConnected()) {
				// try {
				// mSocket = BlueToothUtil.Connect(mSelectDevice);
				// } catch (IOException e) {
				// // TODO Auto-generated catch block
				// e.printStackTrace();
				// }
				// }
				// TsUtil ts = new TsUtil(mSocket);
				// String data = ts.GetDeviceNo(2000);
				if (mBlueToothAdapter == null)
					return;
				UpdateUI(mBlueToothAdapter.getAddress());
			}
		});
		mButtonSend.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				if (mSocket == null || mSelectDevice == null) {
					UpdateUI("���Ƚ�������");
					return;
				}
				if (!mSocket.isConnected()) {
					try {
						mSocket = BlueToothUtil.Connect(mSelectDevice);
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				if (mBlueToothAdapter == null)
					return;
				TsUtil ts = new TsUtil(mBlueToothAdapter, mSocket);
				String data = ts.DoMeasure(3000, 6000, VERIFYCODE);
				UpdateUI(data);
			}
		});

		mListView = (ListView) findViewById(R.id.listView);
		mListView.setAdapter(mAdapter);
		mListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
				mSelectDevice = mDevices.get(position);
				if (mSelectDevice != null)
					mTextViewMsg.setText("��ѡ���豸��" + mSelectDevice.getName() + "  ��ַ��" + mSelectDevice.getAddress());
				try {
					if (mSocket != null) {
						mSocket.close();
						mSocket = null;
					}
					mSocket = BlueToothUtil.Connect(mSelectDevice);
					if (mSocket != null) {
						// ���ӳɹ�
						UpdateUI("�������ӳɹ�");
					} else {
						UpdateUI("��������ʧ��");
					}

				} catch (IOException e) {
					UpdateUI("��������ʧ��");
				}
			}
		});

		IntentFilter intentFilter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
		mBlueToothReceiver = new BluetoothReceiver();
		registerReceiver(mBlueToothReceiver, intentFilter);
		mButtonScan.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				mDevices.clear();
				mAdapter.notifyDataSetChanged();
				StringBuilder sbMessage = new StringBuilder();
				if (mBlueToothAdapter == null) {
					sbMessage.append("�����Ҳ��������豸��\n");
					mTextViewMsg.setText(sbMessage.toString());
					return;
				}
				sbMessage.append("����ӵ�������豸��\n");
				if (mBlueToothAdapter.isEnabled() == false) {
					sbMessage.append("�����豸������\n");
					Intent intent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
					startActivity(intent);
					mTextViewMsg.setText(sbMessage.toString());
					return;
				}
				mBlueToothAdapter.startDiscovery();

			}
		});
	}

	private void UpdateUI(String content) {
		Message msg = transHandler.obtainMessage(MESSAGE_UI);
		msg.obj = content;
		transHandler.sendMessage(msg);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

	class MyHandler extends Handler {
		public MyHandler() {
		}

		public MyHandler(Looper L) {
			super(L);
		}

		// ���������д�˷���,��������
		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			super.handleMessage(msg);
			// �˴����Ը���UI
			switch (msg.what) {
			case MESSAGE_UI:
				String content = (String) msg.obj;
				if (content == null || content.isEmpty())
					return;
				mTextViewMsg.setText(content);
			}
		}
	}

	private class BluetoothReceiver extends BroadcastReceiver {
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			if (BluetoothDevice.ACTION_FOUND.equals(action)) {
				BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
				mDevices.add(device);
				mAdapter.notifyDataSetChanged();
			}
		}
	}

	@Override
	public void finish() {
		unregisterReceiver(mBlueToothReceiver);
		super.finish();
	}

	private class DevicesListAdapter extends ArrayAdapter<BluetoothDevice> {

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			if (convertView == null)
				convertView = MainActivity.this.getLayoutInflater().inflate(android.R.layout.simple_list_item_1, null);
			BluetoothDevice device = mDevices.get(position);
			TextView textView = (TextView) convertView.findViewById(android.R.id.text1);
			textView.setText("�豸�� " + device.getName() + "  ��ַ��" + device.getAddress());
			return convertView;
		}

		public DevicesListAdapter() {
			super(MainActivity.this, android.R.layout.simple_list_item_1, android.R.id.text1, mDevices);
		}
	}
}