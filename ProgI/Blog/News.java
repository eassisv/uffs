package com.blog;

public class News extends Post{
	private String source;
	
	public News() {
		super();
	}
	
	public News(String title, String content, String source) {
		super(title, content);
		this.setSource(source);
	}

	public String getSource() {
		return source;
	}

	public void setSource(String source) {
		this.source = source;
	}
	
	@Override
	public String show(){
		return super.show() + "Fonte: " + this.getSource() + "\n";
	}
	
}
