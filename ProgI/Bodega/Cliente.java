class Cliente{
    String nomeCliente, cpfCliente;
    private boolean venderFiado;

    public Cliente(){
        this.venderFiado = false;
    }

    public Cliente(String nome, String cpf, boolean fiado){
        this.nomeCliente = nome;
        this.cpfCliente = cpf;
        this.venderFiado = fiado;
    }

    public void mudaConfianca(){
        this.venderFiado = (venderFiado) ? false : true;
    }

    public String toString(){
        return "Nome: " + nomeCliente + "\nCPF: " + cpfCliente + "\nCliente compra fiado? " + ((venderFiado)? "Sim":"Não");
    }
}
