package com.example.neonbuild;

import java.io.InputStream;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.text.NoCopySpan.Concrete;
import android.text.Selection;
import android.text.Spannable;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ScrollView;
import android.widget.TextView;

public class MainActivity extends Activity {
	
	private static native String stringFromJNI();
	private static native String doAllTheThings();
	
	static {
		System.loadLibrary("lightItUpWithNEON");
	}
	
	public static String s;
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
			
		final Button benchmarkButton = (Button)findViewById(R.id.button1);
		final TextView textView = (TextView)findViewById(R.id.textView1);
		
		s = stringFromJNI();
		textView.setText(s);
		Log.d("Captain's Log", s);
		
		benchmarkButton.setOnClickListener(new OnClickListener() {
		@Override
		public void onClick(View v){
				s += '\n';
				s += doAllTheThings();
				textView.setText(s);
			}
		});
		
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	
}
