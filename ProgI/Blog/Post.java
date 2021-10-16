package com.blog;

import java.util.Date;
import java.util.Locale;
import java.util.Properties;
import java.text.DateFormat;

public class Post {
	private String title, content;
	private int like, deslike;
	private Date date;
	
	public Post(){
		this.date = new Date();
		this.like = this.deslike = 0;
	}
	
	public Post(String title, String content) {
		this.setTitle(title);
		this.setContent(content);
		this.date = new Date();
		this.like = this.deslike = 0;
	}

	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}
	
	public void likeIncrease(){
		this.like++;
	}
	
	public void deslikeIncrease(){
		this.deslike++;
	}

	public int getLike() {
		return this.like;
	}

	public int getDeslike() {
		return this.deslike;
	}

	public String getDate() {
		Properties ps = System.getProperties();
		Locale local = new Locale((String)ps.get("user.language"), (String)ps.get("user.country"));
		DateFormat df = DateFormat.getDateInstance(DateFormat.MEDIUM, local);
		return df.format(this.date);
	}
	
	public String show(){
		return "\nTítulo do Post: " + this.getTitle() + "\nPost: " + this.getContent() + "\nData do Post: " +
			   this.getDate() + "\nLikes: " + this.getLike() + "\nDeslikes: " +this.getDeslike() + "\n";
	}

}
