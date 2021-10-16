<body>
<?php
	include('cabecalho.php');
	include('nav_menu.php');
	if(isset($_GET['erro'])){
		$erro = $_GET['erro'];
		$mensagem;
		$color;
		if($erro == '0'){
			$mensagem = 'Cadastro realizado';
			$color = 'success';
		}else{
			$mensagem = str_replace(' ', '_', $erro);
			$color = 'danger';
		}
?>

	<div class="alert alert-<?php echo $color ?>" role="alert">
		<?php echo $mensagem; ?>
	</div>

<?php
	}else{
		include('form_cadastro.php');
	}
?>

</body>
</html>
