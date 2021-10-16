<?php

function validar_usuario($usuario){
	if(!ctype_alnum($usuario->getLogin()))
		return false;
	if(!ctype_alpha($usuario->getNome()))
		return false;
	return true;
}

?>