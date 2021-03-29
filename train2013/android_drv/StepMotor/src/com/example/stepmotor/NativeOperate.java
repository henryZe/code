package com.example.stepmotor;

public class NativeOperate {

	public native int openStepDev();

	public native int operateStep(int operate);

	public native void closeStepDev();

	private static NativeOperate NativeObject = new NativeOperate();

	private NativeOperate() {

	}

	public static NativeOperate createObject() {
		return NativeObject;
	}

	static {
		System.loadLibrary("stepmotor");
	}
	
}
