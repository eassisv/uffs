<?php

require_once('usuario.php');
require_once('banco.php');

if(isset($_POST['nome']) && $_POST['nome'] != '' && $_POST['email'] != '' && $_POST['usuario'] != '' && $_POST['senha'] != ''){

	$banco = new Banco('localhost', 'user', 'sistema', 'galinha');

	$nome = ucwords(strtolower($_POST['nome']));
	$mascara = '/^[a-zA-Z\']{2,20}$/';

	if(!preg_match($mascara, $nome)){
		header('Location: cadastro.php?erro=nome_invalido');
		die();
	}

	$nome = addslashes($nome);
	$mascara = '([a-zA-Z0-9\\.\-_]{1,})([@])([a-zA-Z0-9]{1,})([.])([a-z]{2,3})';

	if(!preg_match('/^'.$mascara.'$/' , $_POST['email']) && !preg_match('/^'.$mascara.'([.])([a-z]{1,2})$/', $_POST['email'])){
		header('Location: cadastro.php?erro=email_invalido');
		die();
	}

	$email = htmlentities($_POST['email']);
	$login = $_POST['usuario'];
	$mascara = '/^[a-zA-Z0-9_.-]{5,16}$/';

	if(!preg_match($mascara, $login)){
		header('Location: cadastro.php?erro=usuario_invalido');
		die();
	}

	if((integer)$banco->buscar_usuario_login($login) != 0){
		header('Location: cadastro.php?erro=usuario_existente');
		die();
	}

	$senha = $_POST['senha'];
	$senhac = $_POST['senhac'];

	if($senha !== $senhac){
		header('Location: cadastro.php?erro=senhas_diferentes');
		die();
	}
	if(strlen($senha) < 5){
		header('Location: cadastro.php?erro=senha_invalida');
		die();
	}
	$senha = password_hash($senha, PASSWORD_DEFAULT);
	$usuario = new Usuario($nome, $email, $login, $senha);
	if($banco->inserir_usuario($usuario)){
		header('Location: cadastro.php?erro=0');
	}else{
		header('Location: cadastro.php?erro=erro_banco');
	}
}else{
	header('Location: cadastro.php?erro=incompleto');
}

?>
