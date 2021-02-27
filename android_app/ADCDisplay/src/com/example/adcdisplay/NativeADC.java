package com.example.adcdisplay;

import android.os.Handler;
import android.os.Message;


public class NativeADC {
	
	private Handler handler;
	
	public native int openADCDev();

	public native void startThread();

	public native void closeADCDev();

	private static NativeADC nativeObject;

	private NativeADC(Handler handler) {
		
		this.handler = handler;
		
	}

	public static NativeADC createObject(Handler handler) {
		
		if(nativeObject == null)
		{
			nativeObject = new NativeADC(handler);
		}
		
		return nativeObject;
	}

	static {
		System.loadLibrary("adc");
	}
	
	void getAdcDataListener(int adcData)
	{
		Message msg = new Message();
		msg.arg1 = adcData;
		handler.sendMessage(msg);
	}
}
