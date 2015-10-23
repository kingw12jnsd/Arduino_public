package bbk.sys.bluetooth;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import bbk.bbk.main.R;
import bbk.sys.math.DigitalTrans;
import bbk.sys.ui.BBKLayView;

import android.app.AlertDialog;
import android.app.Dialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.os.Handler;
import android.os.Message;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.ScrollView;
import android.widget.TextView;

public class BBKBlueTooth extends BBKLayView {

	// ========================================================================
	// ��Ϣ������ʹ�õĳ���
	private static final int FOUND_DEVICE = 1; // �����豸
	private static final int START_DISCOVERY = 2; // ��ʼ�����豸
	private static final int FINISH_DISCOVERY = 3; // ���������豸
	private static final int CONNECT_FAIL = 4; // ����ʧ��
	private static final int CONNECT_SUCCEED_P = 5; // �������ӳɹ�
	private static final int CONNECT_SUCCEED_N = 6; // �յ����ӳɹ�
	private static final int RECEIVE_MSG = 7; // �յ���Ϣ
	private static final int SEND_MSG = 8; // ������Ϣ

	// ========================================================================
	ConnectedThread connectedThread; // ��Զ���������ӳɹ�ʱ����
	ConnectThread connectThread; // �û�����б���ĳһ�Ҫ��Զ����������ʱ����
	// ========================================================================
	BluetoothSocket socket;
	BluetoothAdapter bluetoothAdapter = null;
	// ========================================================================
	// ���ֿؼ�
	Button bLink, bSend, bShow, bExit;
	TextView stateText;
	EditText sendText;
	ScrollView scrollView;
	LinearLayout chatContent;

	// �����豸�Ի�����ؿؼ�
	Dialog dialog;
	ProgressBar discoveryPro;
	ListView foundList;
	List<BluetoothDevice> foundDevices;

	// ========================================================================

	public void BBKBlueToothInt(Context context) {
		// ================================================================
		LayoutInt(context, R.layout.mainbluttooth);
		// ================================================================
		BBKBlueToothSoftInt();
		BBKBlueToothHasDevices();
		BroadcastInt();
		// ================================================================
		layshow(false);
		// ================================================================
	}

	public void BBKBlueToothSoftInt() {
		// -----------------------------------------------------------------
		bLink = (Button) BBKLay.findViewById(R.id.bLink);
		bSend = (Button) BBKLay.findViewById(R.id.bSend);
		bShow = (Button) BBKLay.findViewById(R.id.bShow);
		bExit = (Button) BBKLay.findViewById(R.id.bExit);
		stateText = (TextView) BBKLay.findViewById(R.id.stateText);
		sendText = (EditText) BBKLay.findViewById(R.id.sendText);
		scrollView = (ScrollView) BBKLay.findViewById(R.id.scrollView);
		chatContent = (LinearLayout) BBKLay.findViewById(R.id.chatContent);
		// -----------------------------------------------------------------

		// �����豸��ť������
		bLink.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				BBKBlueToothLink();
			}
		});

		// ������Ϣ��ť������
		bSend.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				BBKBlueToothSend(sendText.getText().toString());
			}
		});

		// ʹ�����ɱ�����
		bShow.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				BBKBlueToothCanFind();
			}
		});

		bExit.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				layshow(false);
			}
		});

	}

	// ====================================================================================
	// ����Link
	public void BBKBlueToothLink() {
		// -----------------------------------------------------------------
		bluetoothAdapter.cancelDiscovery();
		bluetoothAdapter.startDiscovery();
		// -----------------------------------------------------------------
		/*
		 * ͨ��LayoutInflater�õ��Ի����е������ؼ�
		 * ��һ��ListViewΪ�ֲ���������Ϊ����ʾ��������Ե������豸��������ʱ�ı�
		 * �ڶ���ListView��ProgressBarΪȫ�ֱ���
		 */
		LayoutInflater inflater = bbkAct.getLayoutInflater();
		View view = inflater.inflate(R.layout.dialog, null);
		discoveryPro = (ProgressBar) view
				.findViewById(R.id.discoveryPro);
		ListView bondedList = (ListView) view
				.findViewById(R.id.bondedList);
		foundList = (ListView) view.findViewById(R.id.foundList);

		// ������Ե������豸��ʾ����һ��ListView��
		Set<BluetoothDevice> deviceSet = bluetoothAdapter
				.getBondedDevices();
		final List<BluetoothDevice> bondedDevices = new ArrayList<BluetoothDevice>();
		if (deviceSet.size() > 0) {
			for (Iterator<BluetoothDevice> it = deviceSet.iterator(); it
					.hasNext();) {
				BluetoothDevice device = (BluetoothDevice) it.next();
				bondedDevices.add(device);
			}
		}
		bondedList.setAdapter(new MyAdapter(bbkAct, bondedDevices));

		// ���ҵ��������豸��ʾ���ڶ���ListView��
		foundDevices = new ArrayList<BluetoothDevice>();
		foundList.setAdapter(new MyAdapter(bbkAct, foundDevices));

		// ����ListView�󶨼�����
		bondedList.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1,
					int arg2, long arg3) {
				BluetoothDevice device = bondedDevices.get(arg2);
				BBKBlueToothConnect(device);
			}
		});
		foundList.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1,
					int arg2, long arg3) {
				BluetoothDevice device = foundDevices.get(arg2);
				BBKBlueToothConnect(device);
			}
		});

		AlertDialog.Builder builder = new AlertDialog.Builder(bbkAct);
		builder.setMessage("��ѡ��Ҫ���ӵ������豸").setPositiveButton("ȡ��",
				new DialogInterface.OnClickListener() {

					@Override
					public void onClick(DialogInterface dialog,
							int which) {
						bluetoothAdapter.cancelDiscovery();
					}
				});
		builder.setView(view);
		builder.create();
		dialog = builder.show();
	}
	// �жϱ����Ƿ����������Ƿ��ڿ���״̬
	public void BBKBlueToothHasDevices() {
		// �жϱ����Ƿ����������Ƿ��ڿ���״̬
		bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		if (bluetoothAdapter == null) {
			toastShow("����û�������豸��");
		}
		if (!bluetoothAdapter.isEnabled()) {
			Intent enableIntent = new Intent(
					BluetoothAdapter.ACTION_REQUEST_ENABLE);
			bbkAct.startActivityForResult(enableIntent, 1);
		} else {
			// chooseMode();
		}

	}

	// ʹ�����ɱ�����
	public void BBKBlueToothCanFind() {
		Intent intent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
		bbkAct.startActivity(intent);
	}

	// ��������
	public void BBKBlueToothSend(String sendStr) {
		if (socket == null) {
			toastShow("�������������豸");
		} else if (sendStr.equals("")) {
			toastShow("�������ݲ���Ϊ��");
		} else {
			byte[] z = DigitalTrans.hex2byte(sendStr);
			connectedThread.write(z);
		}
	}

	// ע��㲥������
	public void BroadcastInt() {
		// ע��㲥������
		mReceiver = new BroadcastReceiver() {

			@Override
			public void onReceive(Context arg0, Intent arg1) {
				// TODO Auto-generated method stub
				String actionStr = arg1.getAction();
				if (actionStr.equals(BluetoothDevice.ACTION_FOUND)) {
					BluetoothDevice device = arg1
							.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
					foundDevices.add(device);
					toastShow("�ҵ������豸��" + device.getName());
					mHandler.sendEmptyMessage(FOUND_DEVICE);
				} else if (actionStr
						.equals(BluetoothAdapter.ACTION_DISCOVERY_STARTED)) {
					mHandler.sendEmptyMessage(START_DISCOVERY);
				} else if (actionStr
						.equals(BluetoothAdapter.ACTION_DISCOVERY_FINISHED)) {
					mHandler.sendEmptyMessage(FINISH_DISCOVERY);
				}
			}

		};
		IntentFilter filter1 = new IntentFilter(BluetoothDevice.ACTION_FOUND);
		IntentFilter filter2 = new IntentFilter(
				BluetoothAdapter.ACTION_DISCOVERY_STARTED);
		IntentFilter filter3 = new IntentFilter(
				BluetoothAdapter.ACTION_DISCOVERY_FINISHED);

		bbkAct.registerReceiver(mReceiver, filter1);
		bbkAct.registerReceiver(mReceiver, filter2);
		bbkAct.registerReceiver(mReceiver, filter3);
	}

	// �㲥����������Ҫ�ǽ�������״̬�ı�ʱ�����Ĺ㲥
	private BroadcastReceiver mReceiver;

	// ��Ϣ������..�����򼦵ĸϽ�...
	private Handler mHandler = new Handler() {

		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			switch (msg.what) {
			case FOUND_DEVICE:
				foundList.setAdapter(new MyAdapter(bbkAct, foundDevices));
				break;
			case START_DISCOVERY:
				discoveryPro.setVisibility(View.VISIBLE);
				break;
			case FINISH_DISCOVERY:
				discoveryPro.setVisibility(View.GONE);
				break;
			case CONNECT_FAIL:
				toastShow("����ʧ��");
				break;
			case CONNECT_SUCCEED_P:
			case CONNECT_SUCCEED_N:
				toastShow("���ӳɹ�-----");
				if (msg.what == CONNECT_SUCCEED_P) {
					socket = connectThread.getSocket();
					connectedThread = new ConnectedThread(socket, mHandler);
					connectedThread.start();
				} else {
					if (connectThread != null) {
						connectThread.interrupt();
					}
					connectedThread = new ConnectedThread(socket, mHandler);
					connectedThread.start();
				}

				String stateStr = msg.getData().getString("name");
				stateStr = "���ڹ��ߣ�" + "��" + stateStr + "������";
				stateText.setText(stateStr);
				toastShow("���ӳɹ�");
				break;
			case RECEIVE_MSG:
			case SEND_MSG:
				String chatStr = msg.getData().getString("str");
				TextView text = new TextView(bbkAct);
				text.setText(chatStr);
				if (msg.what == SEND_MSG) {
					text.setBackgroundResource(R.drawable.chat_i);
					text.setPadding(40, 10, 30, 10);
				} else {
					text.setBackgroundResource(R.drawable.chat_u);
					text.setPadding(80, 10, 30, 10);
				}
				text.setTextSize(20);
				text.setTextColor(Color.BLACK);
				chatContent.addView(text);
				scrollView.scrollTo(0, chatContent.getHeight());
				break;
			}
		}

	};

	// /*
	// * ��ʾ�Ի���ѡ��ʹ���������컹�Ǵ��ڹ��� ������������������ʱʹ�õ�UUID��ͬ
	// ������Ϊ���ڹ���ʱ������������Զ�����ӵ�acceptThread
	// */
	// public void chooseMode() {
	// AlertDialog.Builder builder = new AlertDialog.Builder(this);
	// builder.setNegativeButton("���ڹ���",
	// new DialogInterface.OnClickListener() {
	// @Override
	// public void onClick(DialogInterface dialog, int which) {
	// // TODO Auto-generated method stub
	// Toast.makeText(bbkAct, "��ѡ����ʹ�ô��ڹ���",
	// Toast.LENGTH_SHORT).show();
	// }
	// });
	// builder.create().show();
	// }

	/*
	 * �˳�����ʱ����һ�º��£�ȡ��ע��㲥����������ֹ�̣߳��ر�socket
	 */
	public void BBKBlueToothDestroy() {		
		bbkAct.unregisterReceiver(mReceiver);
		if (socket != null) {
			try {
				socket.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		if (connectThread != null) {
			connectThread.interrupt();
		}
		if (connectedThread != null) {
			connectedThread.interrupt();
		}
		if (bluetoothAdapter.isEnabled()) {
			toastShow("���ֶ��ر�����");
		}

	}

	public void BBKBlueToothConnect(BluetoothDevice device) {
		bluetoothAdapter.cancelDiscovery();
		dialog.dismiss();
		toastShow("������ " + device.getName() + " ���� .... ");
		connectThread = new ConnectThread(device, mHandler, false);
		connectThread.start();
	}

}
