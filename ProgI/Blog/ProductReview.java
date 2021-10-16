package com.blog;

public class ProductReview extends Post implements Evaluable{
	private String brand;
	private int stars;
	
	public ProductReview(){
		super();
	}
	
	public ProductReview(String title, String content, String brand, int stars){
		super(title, content);
		this.setBrand(brand);
		this.evaluate(stars);
	}
	
	public void evaluate(int value){
		this.setStars(value);
	}
	
	public String getBrand() {
		return this.brand;
	}
	public int getStars() {
		return this.stars;
	}
	public void setBrand(String brand) {
		this.brand = brand;
	}
	public void setStars(int stars) {
		this.stars = stars;
	}
	
	@Override
	public String show() {
		return super.show() + "Avaliação do produto de 1 a 10: " + this.getStars() + "\nMarca do produto: " + this.getBrand() + "\n";
	}
	
}
