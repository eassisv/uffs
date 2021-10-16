class Animal{
    private String nome, cor, ambiente;
    private int patas, comprimento;
    private double velocidade;

    public Animal(){}

	public Animal(String nome, String cor, String ambiente, int patas, int comprimento, double velocidade){
		this.setNome(nome);
		this.setCor(cor);
		this.setAmbiente(ambiente);
		this.setPatas(patas);
		this.setComprimento(comprimento);
		this.setVelocidade(velocidade);
	}

	public String getCor(){
		return cor;
	}

	public void setCor(String cor){
		this.cor = cor;
	}

	public String getNome(){
		return nome;
	}

	public void setNome(String nome){
		this.nome = nome;
	}

	public String getAmbiente(){
		return ambiente;
	}

	public void setAmbiente(String ambiente){
		this.ambiente = ambiente;
	}

	public int getPatas(){
		return patas;
	}

	public void setPatas(int patas){
		this.patas = patas;
	}

	public int getComprimento(){
		return comprimento;
	}

	public void setComprimento(int comprimento){
		this.comprimento = comprimento;
	}

	public double getVelocidade(){
		return velocidade;
	}

	public void setVelocidade(double velocidade){
		this.velocidade = velocidade;
	}

	public String toString(){
		return "Nome: " + this.getNome() + "\nComprimento: " + this.getComprimento() + "\nPatas: "
			   + this.getPatas() + "\nCor: " + this.getCor() + "\nAmbiente: " + this.getAmbiente() + 
			   "\nVelocidade : " + this.getVelocidade() + "m/s";
	}
}