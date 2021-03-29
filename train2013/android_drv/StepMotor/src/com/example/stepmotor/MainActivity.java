package com.example.stepmotor;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends Activity {

	private Button btn;
	private Button antibtn;
	private Button speed;
	private Button slow;
	
	private EditText et;
	
	private NativeOperate operation = NativeOperate.createObject();
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		btn = (Button) findViewById(R.id.btnId);
		antibtn = (Button) findViewById(R.id.antibtnId);
		speed = (Button) findViewById(R.id.speedId);
		slow = (Button) findViewById(R.id.slowId);

		et = (EditText) findViewById(R.id.etId);
		et.setText("600");
		
		operation.openStepDev();
		
		btn.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub

				operation.operateStep(1);
			}
		});
		
		antibtn.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub

				operation.operateStep(2);
			}
		});
		
		speed.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub

				int num = operation.operateStep(3);
				et.setText(String.valueOf(num));
			}
		});
		
		slow.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub

				int num = operation.operateStep(4);
				et.setText(String.valueOf(num));
			}
		});
	}
	
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		
		operation.closeStepDev();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
