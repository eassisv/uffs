CREATE DATABASE galinha;
USE galinha;
CREATE TABLE usuarios(
    id_usuario int not null AUTO_INCREMENT PRIMARY KEY,
    nome varchar(30) not null,
    email varchar(128) not null,
    login varchar(20) not null,
    senha varchar(255) not null,
    admin tinyint not null
);

CREATE TABLE posts(
    id_post int PRIMARY KEY AUTO_INCREMENT not null,
    id_usuario int not null,
    texto text not null,
    titulo varchar(40) not null,
    categoria varchar(30) not null,
    data_post date not null,
    FOREIGN KEY (id_usuario) REFERENCES usuarios(id_usuario)
);

CREATE TABLE comentarios(
    id_comentario int not null PRIMARY KEY AUTO_INCREMENT,
    id_usuario int not null,
    id_post int not null,
    data_postagem date not null,
    comentario varchar(255) not null,
    FOREIGN KEY (id_usuario) REFERENCES usuarios(id_usuario) ON DELETE CASCADE,
    FOREIGN KEY (id_post) REFERENCES posts(id_post) ON DELETE CASCADE
);

CREATE TABLE avaliacoes(
    id_usuario int not null,
    id_post int not null,
    avaliacao tinyint not null,
    PRIMARY KEY (id_usuario, id_post),
    FOREIGN KEY (id_usuario) REFERENCES usuarios(id_usuario),
    FOREIGN KEY (id_post) REFERENCES posts(id_post)
);

CREATE TABLE imagens(
    id_imagem int not null PRIMARY KEY AUTO_INCREMENT,
    id_post int not null,
    endereco varchar(255) not null,
    descricao varchar(255) not null,
    FOREIGN KEY (id_post) REFERENCES posts(id_post) ON DELETE CASCADE
);
