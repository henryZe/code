package com.example.ledswitch;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;

public class MainActivity extends Activity implements OnCheckedChangeListener {

	private RadioGroup rgObj;

	private NativeLed operation = NativeLed.createObject();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		operation.openLedDev();

		rgObj = (RadioGroup) findViewById(R.id.rg);

		// 在事件源中设置监听器
		rgObj.setOnCheckedChangeListener(this);
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();

		operation.closeLedDev();
	}

	public void onCheckedChanged(RadioGroup arg0, int Id) {
		// TODO Auto-generated method stub

		for (int i = 1; i < 5; i++) {
			operation.operateLed(i, "off");
		}
		
		switch (Id) {
		case R.id.rb1:
			operation.operateLed(1, "on");
			break;

		case R.id.rb2:
			operation.operateLed(2, "on");
			break;

		case R.id.rb3:
			operation.operateLed(3, "on");
			break;

		case R.id.rb4:
			operation.operateLed(4, "on");
			break;

		default:
			break;
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
