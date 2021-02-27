package com.example.dcmotor;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;
import android.widget.Toast;

public class MainActivity extends Activity {

	private static final String TAG = "MainActivity";
	private RadioGroup rgObj;
	private NativeOperate operation = NativeOperate.createObject();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		operation.openDCmotorDev();

		rgObj = (RadioGroup) findViewById(R.id.rg);
		rgObj.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			@Override
			public void onCheckedChanged(RadioGroup group, int checkedId) {
				// TODO Auto-generated method stub
				Log.i(TAG, "change choice id:" + checkedId);
				switch (checkedId) {
				case R.id.stopRb:
					Toast.makeText(MainActivity.this, "stop",
							Toast.LENGTH_SHORT).show();
					operation.operateDCmotor(0, 2);
					break;

				case R.id.forRb:
					Toast.makeText(MainActivity.this, "forward",
							Toast.LENGTH_SHORT).show();
					operation.operateDCmotor(1, 0);
					break;

				case R.id.bckRb:
					Toast.makeText(MainActivity.this, "backward",
							Toast.LENGTH_SHORT).show();
					operation.operateDCmotor(1, 1);
					break;

				default:
					break;
				}
			}
		});
	}

	
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		
		operation.closeDCmotorDev();
	}

	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
