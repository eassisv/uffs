<?php

class Usuario{
	private $nome, $senha, $email, $login, $admin;

	public function __construct($nome, $email, $login, $senha){
		$this->setNome($nome);
		$this->setSenha($senha);
		$this->setEmail($email);
		$this->setLogin($login);
	}

	public function setNome($nome){
		$this->nome = $nome;
	}

	public function setSenha($senha){
		$this->senha = $senha;
	}

	public function setLogin($login){
		$this->login = $login;
	}

	public function setEmail($email){
		$this->email = $email;
	}

	public function getNome(){
		return $this->nome;
	}

	public function getSenha(){
		return $this->senha;
	}

	public function getEmail(){
		return $this->email;
	}

	public function getLogin(){
		return $this->login;
	}


}

?>
