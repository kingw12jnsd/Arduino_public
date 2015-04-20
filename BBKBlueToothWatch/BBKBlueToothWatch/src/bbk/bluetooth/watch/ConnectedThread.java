package bbk.bluetooth.watch;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.bluetooth.BluetoothSocket;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
/*
�ѽ������Ӻ��������̣߳���Ҫ��������������
socket������ȡ����������ȡԶ���������͹�������Ϣ
handler�������յ�����ʱ������Ϣ
*/
public class ConnectedThread extends Thread {
	
	private static final int RECEIVE_MSG = 7;
	private static final int SEND_MSG=8;
	private boolean isStop;
	private BluetoothSocket socket;
	private Handler handler;
	private InputStream is;
	private OutputStream os;
	
	public ConnectedThread(BluetoothSocket s,Handler h){
		socket=s;
		handler=h;
		isStop=false;
	}
	public void run(){
		System.out.println("connectedThread.run()");
		byte[] buf;
		int size;
		while(!isStop){
			size=0;
			buf=new byte[1024];
			try {
				is=socket.getInputStream();
				System.out.println("�ȴ�����");
				size=is.read(buf);
				System.out.println("��ȡ��һ������");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				isStop=true;
			}
			if(size>0){
				//�Ѷ�ȡ�������ݷŽ�Bundle�ٷŽ�Message��Ȼ���ͳ�ȥ
				sendMessageToHandler(buf, RECEIVE_MSG);
			}
		}
	}
	
	public void write(byte[] buf){
		try {
			os=socket.getOutputStream();
			os.write(buf);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println(buf.length+"---");
		sendMessageToHandler(buf, SEND_MSG);
	}
	
	private void sendMessageToHandler(byte[] buf,int mode){
		String msgStr=new String(buf);
		Bundle bundle=new Bundle();
		bundle.putString("str", msgStr);
		Message msg=new Message();
		msg.setData(bundle);
		msg.what=mode;
		handler.sendMessage(msg);
	}
}
