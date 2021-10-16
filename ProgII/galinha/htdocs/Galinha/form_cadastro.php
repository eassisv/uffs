<form method="post" action="cadastrar.php" class="container mt-4 col-lg-6 col-md-8 col-sm-12">
	<div class="form-group">
		<label for="nome">Nome:</label>
		<input type="text" class="form-control" minlength="2" maxlength="20" autocomplete="off" name="nome" onfocus>
	</div>
	<div class="form-group">
		<label for="email">E-mail:</label>
		<input type="email" class="form-control" autocomplete="off" name="email">
	</div>
	<div class="form-group">
		<label for="usuario">Nome de usuário:</label>
		<input type="text" class="form-control" minlength="5" maxlength="16" autocomplete="off" name="usuario">
	</div>
	<div class="form-row">
		<div class="form-group col-lg-6 col-md-12">
			<label for="senha">Senha:</label>
			<input type="password" class="form-control" autocomplete="off"  minlength="5" maxlength="20" name="senha">
		</div>
		<div class="form-group col-lg-6 col-md-12">
			<label for="senhac">Confirmar senha:</label>
			<input type="password" class="form-control" autocomplete="off" minlength="5" maxlength="20" name="senhac">
		</div>
	</div>
	<button type="submit" class="btn btn-primary">Cadastrar</button>
</form>
