package com.blog;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		Blog blog = new Blog();
		Post post;
		int stars;
		String title, content, brand, source;
		int opcao;
		do{
			System.out.println("1 - Novo post de notícia");
			System.out.println("2 - Nova resenha de produto");
			System.out.println("3 - Novo post de outros assuntos");
			System.out.println("4 - Listar todas as postagens");
			System.out.println("5 - Curtir uma postagem");
			System.out.println("6 - Não curtir uma postagem");
			System.out.println("0 - Sair");
			System.out.print("Escolha a opção: ");
			opcao = in.nextInt();
			in.nextLine();
			switch(opcao){
			case 1:
				System.out.println("\nTítulo da notícia:");
				title = in.nextLine();
				System.out.println("Notícia:");
				content = in.nextLine();
				System.out.println("Fonte da notícia:");
				source = in.nextLine();
				post = new News(title, content, source);
				blog.getData((Post)post);
				System.out.println();
				break;
			case 2:
				System.out.println("\nTítulo do review:");
				title = in.nextLine();
				System.out.println("Review do produto:");
				content = in.nextLine();
				System.out.println("Marca do produto:");
				brand = in.nextLine();
				System.out.println("Avaliação do produto com valor de 1 a 10:");
				stars = in.nextInt();
				while(stars > 10 || stars < 1){
					System.out.println("Digite um valor entre 1 e 10");
					stars = in.nextInt();
				}
				in.hasNextLine();
				post = new ProductReview(title, content, brand, stars);
				blog.getData((Post)post);
				System.out.println();
				break;
			case 3:
				System.out.println("\nTítulo do post: ");
				title = in.nextLine();
				System.out.println("Post:");
				content = in.nextLine();
				post = new Post(title, content);
				blog.getData((Post)post);
				System.out.println();
				break;
			case 4:
				System.out.println();
				blog.showAll();
				break;
			case 5:
				System.out.print("\nCódigo do post: ");
				post = blog.getPost(in.nextInt());
				if(post == null)
					System.out.println("\nCódigo inválido\n");
				else{
					post.likeIncrease();
					System.out.println("\nFeito :D\nLikes da postagem: " + post.getLike() + "\n");
				}break;
			case 6:
				System.out.print("\nCódigo do post: ");
				post = blog.getPost(in.nextInt());
				if(post == null)
					System.out.println("\nCódigo inválido\n");
				else{
					post.deslikeIncrease();
					System.out.println("\nFeito :(\nDeslikes da postagem: " + post.getDeslike() + "\n");
				}
				break;
			case 0:
				break;
			default:
				System.out.println("Opcão inválida\n");
			}
		}while(opcao != 0);
		
		in.close();
	}

}
