package com.blog;

import java.util.ArrayList;

public class Blog {
	private ArrayList <Post> posts = new ArrayList <> ();
	
	public Blog() {}
	
	public void getData(Post p){
		posts.add(p);
	}
	
	public Post getPost(int i){
		if((i) > posts.size()) return null;
		return posts.get(i-1);
	}
	
	public void showAll(){
		int i = 1;
		for(Post p : posts){
			System.out.printf("Código %d:\n%s\n", i++, p.show());
		}
	}
	
}
