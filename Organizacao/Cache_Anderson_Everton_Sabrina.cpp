/*
    Implementação de memória cache para disciplina de Organização de computadores - UFFS - 2017.2
    Grupo: Anderson Tomkelski, Éverton Assis e Sabrina Moczulski
*/

#include <bits/stdc++.h>
using namespace std;

void geraPrincipal(map <string, string[4]> &m){
	string key, vlr;
	for(int i = 0; i < 256; i++){		
		key.clear();
		for(int j = 7; j >= 0; j-- ){
		key.push_back('0' + ((i >> j) & 1));
		}
		for(int k = 0; k < 4; k++){
			vlr.clear();			
			for(int l = 0; l < 8; l++)
				vlr.push_back('0' + (rand() % 2));
			m[key][k] = vlr;
		}
	}
}

void imprimePrincipal(map <string, string[4]> principal){
	system("clear");
	cout << "   X    " << "    00   " << "    01   " << "   10    " << "    11" << endl;
	cout << "--------------------------------------------" << endl;
	for(auto a : principal){
		cout << a.first << ' ' << a.second[0];
		cout << ' ' << a.second[1];
		cout << ' ' << a.second[2];
		cout << ' ' << a.second[3] << endl;
	}
	cout << "Aperte ENTER para voltar ao Menu";
	getchar();
}

void imprimeCache(map <string, string[7]> cache){
	system("clear");
	cout << " x " << "  tag   " << "val  ";
	cout << "   C0   " << "    C1   " << "    C2   ";
	cout << "    C3   " << "  Db" << endl;
	cout << "------------------------------------------------------------" << endl;
	for(auto a : cache){
		cout << a.first << ' ' << a.second[0];
		cout << "   " << a.second[1];
		cout << "   " << a.second[2];
		cout << ' ' << a.second[3];
		cout << ' ' << a.second[4];
		cout << ' ' << a.second[5];
		cout << "   " << a.second[6] << endl;
	}
	cout << "\n\nAperte ENTER para voltar ao Menu";
	getchar();
}

void geraCache(map <string, string[7]> &m){
	string key, vlr;
	for(int i = 0; i < 16; i++){		
		key.clear();
		for(int j = 3; j >= 0; j-- ){
			key.push_back('0' + ((i >> j) & 1));
		}
		vlr.clear();			
		for(int l = 0; l < 4; l++)
				vlr.push_back('0' + (rand() % 2));
			m[key][0] = vlr;
		m[key][1].push_back('1');
		for(int k = 2; k < 6; k++){
			vlr.clear();
			for(int l = 0; l < 8; l++)
				vlr.push_back('0' + (rand() % 2));
			m[key][k] = vlr;
		vlr.clear();
		vlr.push_back('0');
		m[key][6] = vlr;		
		}
	}
}

void mostraMenu(){
	system("clear");
	cout << "\tMenu" << endl;
	cout << "1. Ler Valor" << endl;
	cout << "2. Escrever Valor" << endl;
	cout << "3. Imprimir Cache" << endl;
	cout << "4. Imprimir Principal" << endl;
	cout << "5. Imprimir Estatisticas" << endl;
	cout << "0. Sair" << endl;
	cout << "Escolha opcao: ";
}

void iniciaEstatisticas(map <string, unsigned> &m){
	m["nAcessos"] = 0;
	m["nAcertos"] = 0;
	m["nFaltas"] = 0;
	m["nLeituras"] = 0;
	m["nEscritas"] = 0;
	m["nAcLei"] = 0;
	m["nAcEsc"] = 0;
	m["nFaLei"] = 0;
	m["nFaEsc"] = 0;
}

void leDaMemoria(map <string, string[4]> &p, map <string, string[7]> &c, string keyF, string keyP){
	c[keyP][1].clear();
	c[keyP][1].push_back('0');
	c[keyP][0].clear();
	c[keyP][0].append(keyF, 0, 4);
	c[keyP][6].clear();
	c[keyP][6].push_back('0');
	c[keyP][2] = p[keyF][0]; 
	c[keyP][3] = p[keyF][1];
	c[keyP][4] = p[keyF][2];
	c[keyP][5] = p[keyF][3];	
}

void escreveNaMemoria(map <string, string[4]> &p, map <string, string[7]> &c, string keyF, string keyP){
	c[keyP][6].clear();
	c[keyP][6].push_back('0');
	p[keyF][0] = c[keyP][2]; 
	p[keyF][1] = c[keyP][3]; 
	p[keyF][2] = c[keyP][4]; 
	p[keyF][3] = c[keyP][5];
}

void lerValor(map <string, string[4]> &p, map <string, string[7]> &c, map <string, unsigned> &e){
	e["nAcessos"]++;
	e["nLeituras"]++;
	string keyP, keyS, keyF;
	cout << "Digite o endereço para ser lido:\n>>>>>> ";
	cin >> keyF;
	keyP.clear();
	keyP.append(keyF, 4, 4);
	keyS.clear();
	keyS.append(keyF, 0, 4);	

	if(c[keyP][1][0] == '1'){
		leDaMemoria(p, c, keyF, keyP);
		e["nFaltas"]++;
		e["nFaLei"]++;
	}
	else if(c[keyP][0].compare(keyS)){
		if(c[keyP][6][0] == '1'){
			string endereco;
			endereco.clear();
			endereco = c[keyP][0] + keyP;
			escreveNaMemoria(p, c, endereco, keyP);
			e["nEscritas"]++;
		}
		leDaMemoria(p, c, keyF, keyP);
		e["nFaltas"]++;
		e["nFaLei"]++;
	}else{
		e["nAcLei"]++;
		e["nAcertos"]++;
	}
	cout << c[keyP][2] << c[keyP][3] << c[keyP][4] << c[keyP][5] << endl;
	cout << "\n\nAperte ENTER para voltar ao Menu";
	getchar(); getchar();
} 

void escreveValor(map <string, string[4]> &p, map <string, string[7]> &c, map <string, unsigned> &e){
	e["nEscritas"]++;	
	string keyP, keyS, keyF, keyD;
	cout << "Digite o endereço onde o dado sera escrito:\n>>>>>> ";
	cin >> keyF;
	keyP.clear();
	keyP.append(keyF, 4, 4);
	keyS.clear();
	keyS.append(keyF, 0, 4);
	keyD.clear();
	keyD.append(keyF, 8, 2);

	if(c[keyP][0].compare(keyS) && c[keyP][6][0] == '1'){
		string keycache;
		keycache.clear();
		keycache = c[keyP][0] + keyP;
		cout << keycache;		
		escreveNaMemoria(p, c, keyF, keyP);
		e["nFaEsc"]++;	
	}else{
		e["nAcertos"]++;
		e["nAcEsc"]++;	
	}

	c[keyP][0] = keyS;
	cout << "Digite o dado a ser gravado\n>>>>>> ";
	string dado;
	dado.clear();
	cin >> dado;
	if(!keyD.compare("00")){
		c[keyP][2] = dado;
	}else	if(!keyD.compare("01")){
		c[keyP][3] = dado;
	}else if(!keyD.compare("10")){
		c[keyP][4] = dado;
	}else if(!keyD.compare("11")){
		c[keyP][5] = dado;
	}
	c[keyP][6][0] = '1';
	c[keyP][1][0] = '0';
}

void mostraEstatisticas(map <string, unsigned> e){
	for(auto m : e){
		cout << m.first << ": " << m.second << endl;
	}
	cout << "\n\nAperte ENTER para voltar ao Menu";
	getchar();
}

int main(void){
	map <string, unsigned> estatisticas;
	map <string, string[4]> principal;
	map <string, string[7]> cache;
	geraPrincipal(principal);
	geraCache(cache);
	iniciaEstatisticas(estatisticas);		
	while(1){
		mostraMenu();
		int opcao;
		cin >> opcao;
		getchar();		
		switch(opcao){
		case 0:
			return 0;		
		case 1:
			lerValor(principal, cache, estatisticas);
			break;
		case 2:
			escreveValor(principal, cache, estatisticas);
			break;
		case 3:
			imprimeCache(cache);	
			break;
		case 4:
			imprimePrincipal(principal);
			break;
		case 5:
			mostraEstatisticas(estatisticas);
		default:
			cout << "Opcao invalida\n";		
		}	
	}
return 0;
}
