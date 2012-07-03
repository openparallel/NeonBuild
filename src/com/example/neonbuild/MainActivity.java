package com.example.neonbuild;

import android.R.string;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.SharedPreferences;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.support.v4.app.NavUtils;

@SuppressLint("ParserError")
public class MainActivity extends Activity {

	private static native String stringFromJNI();
	
	static {
		System.loadLibrary("lightItUpWithNEON");
	}
	
    @Override
    public void onCreate(Bundle bundle) {
        super.onCreate(bundle);
        //setContentView(R.layout.activity_main);
        
        String s = stringFromJNI();
        Log.d("Captain's Log", s);
        
        LinearLayout layout = new LinearLayout(this);
        TextView statement = new TextView(this);

        layout.setLayoutParams(new ViewGroup.LayoutParams(-1,-1));
        layout.setBackgroundColor(0xff444444);

        statement.setLayoutParams(new ViewGroup.LayoutParams(-1,-2));
        statement.setTextColor(0xffffffff);
        statement.setTextSize(1,44);

        statement.setText(s);
        layout.addView(statement);

        setContentView(layout);
        
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }

    
}
