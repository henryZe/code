package com.example.dcmotor;

public class NativeOperate {

	public native int openDCmotorDev();

	public native void operateDCmotor(int turn, int direct);

	public native void closeDCmotorDev();

	private static NativeOperate NativeObject = new NativeOperate();

	private NativeOperate() {

	}

	public static NativeOperate createObject() {
		return NativeObject;
	}

	static {
		System.loadLibrary("DCmotor");
	}
}
