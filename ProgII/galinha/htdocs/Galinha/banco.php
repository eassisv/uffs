<?php

class Banco{
	private $conexao;

	public function __construct($servidor, $usuario, $senha, $banco){
		return $this->setConexao($servidor, $usuario, $senha, $banco);
	}

	public function setConexao($servidor, $usuario, $senha, $banco){
		return $this->conexao = new mysqli($servidor, $usuario, $senha, $banco);
	}

	public function getConexao(){
		return $this->conexao;
	}

	public function inserir_usuario($usuario){
		$erro = $this->conexao->connect_errno;
		if($erro !== 0) return $erro . ' ' . $conexao->connect_error;
		$query = "INSERT INTO usuarios(nome, email, login, senha, admin) VALUES(
				  '{$usuario->getNome()}',
				  '{$usuario->getEmail()}',
				  '{$usuario->getLogin()}',
				  '{$usuario->getSenha()}', 0);";

		return $this->conexao->query($query);
	}

	public function buscar_usuario_login($login){
		$erro = $this->conexao->connect_errno;
		if($erro !== 0) return $erro . ' ' . $this->conexao->connect_error;
		$query = "SELECT * FROM usuarios WHERE login = '$login';";
		$resultado = $this->conexao->query($query);
		return $resultado;
	}

}

?>
