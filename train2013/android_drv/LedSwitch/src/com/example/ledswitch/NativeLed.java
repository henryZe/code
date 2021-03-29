package com.example.ledswitch;

public class NativeLed {

	public native int openLedDev();

	public native void operateLed(int ledPos, String operate);

	public native void closeLedDev();

	private static NativeLed NativeObject = new NativeLed();

	private NativeLed() {

	}

	public static NativeLed createObject() {
		return NativeObject;
	}

	static {
		System.loadLibrary("ledoperate");
	}
}
