#include <bits/stdc++.h>
using namespace std;

map <double , int> m;
vector <double> v;

#define MAX 11234

double DPadrao(double media, int qnt, int op){
  double S2 = 0;

  if(op == 1)
    for(auto i : v)
      S2 += (i - media)*(i - media);
  if(op == 2)
    for(auto i : m)
      S2 += (i.second *(i.first - media)*(i.first - media));
  
  S2 /= qnt;
  
  return sqrt(S2);
}

int main(void){
  double dado, media = 0, S = 0, CV = 0;
  int vlr, qnt, i, op, ttl = 0;
  system("clear");
  cout << fixed << setprecision(2);
  while(1){
    printf("|---------------------------------------|\n");
    printf("|     Calculo de Medidas de dispersão   |\n");
    printf("|---------------------------------------|\n");
    printf("|    Digite algumas das opções abaixo:  |\n");
    printf("| 1 - Dados Isolados                    |\n");
    printf("| 2 - D.F. sem intervalo de classe      |\n");
    printf("| 3 - D.F. com intervalo de classe      |\n");
    printf("| 4 - Sair                              |\n");
    printf("|---------------------------------------|\n");
    printf("Opção: ");
    cin >> op;
    switch(op){
    case 1:
      printf("Número de entradas: ");
      cin >> qnt;
      for(i = 1; i <= qnt; i++){
	cout << i << "º dado: ";
	cin >> vlr;
	v.push_back(vlr);
	media += vlr;
      }
      media /= qnt;
      S = DPadrao(media, qnt, op);
      CV = (S/media)*100;
      system("clear");
      v.clear();
      printf("|---------------------------------------|\n");
      printf("| Medida de dispersão      | Resultado  |\n");
      printf("|--------------------------|------------|\n");
      printf("| Media                    | %9.2lf  |\n", media);
      printf("| Desvio Padrão            | %9.2lf  |\n", S);
      printf("| Coeficiente de Variaçao  | %9.2lf  |\n",CV);
      printf("|---------------------------------------|\n");
      printf("\n");
      break;
    case 2:
      cout << "Número de entradas: ";
      cin >> qnt;
      for(i = 1; i <= qnt; i++){
	cout << i << "º dado: ";
	cin >> dado;
	cout << "Frequência: ";
	cin >> vlr;
	m[dado] = vlr;
	media += (double)(dado * vlr);
	ttl += vlr;
      }
      media /= ttl;
      S = DPadrao(media, ttl, op);
      CV = (S/media)*100;
      system("clear");
      printf("|---------------------------------------|\n");
      printf("| Medida de dispersão      | Resultado  |\n");
      printf("|--------------------------|------------|\n");
      printf("| Media                    | %9.2lf  |\n", media);
      printf("| Desvio Padrão            | %9.2lf  |\n", S);
      printf("| Coeficiente de Variaçao  | %9.2lf  |\n",CV);
      printf("|---------------------------------------|\n");
      printf("\n");
      m.clear();      
      break;
    case 3:
      int v_i, v_f;
      double h;
      cout << "Digite o valor inicial: ";
      cin >> v_i;
      cout << "Digite o valor final: ";
      cin >> v_f;
      cout << "Numero de entradas: ";
      cin >> qnt;
      h = (double)(v_f - v_i) / qnt;
      printf("h = %.lf\n", h);
      for(i = 1; i <= qnt; i++){
	cout << "Frequência do "<< i <<"º intervalo: ";
	cin >> vlr;
	m[v_i+=h/2.0] = vlr;
	printf("vi = %d\n", v_i);
	media += (double)(v_i * vlr);
	ttl += vlr;
	v_i+=h/2.0;
      }
      media /= ttl;
      S = DPadrao(media, ttl, 2);
      CV = (S/media)*100;
      system("clear");
      printf("|---------------------------------------|\n");
      printf("| Medida de dispersão      | Resultado  |\n");
      printf("|--------------------------|------------|\n");
      printf("| Media                    | %9.2lf  |\n", media);
      printf("| Desvio Padrão            | %9.2lf  |\n", S);
      printf("| Coeficiente de Variaçao  | %9.2lf  |\n",CV);
      printf("|---------------------------------------|\n");
      printf("\n");
      m.clear(); 
      break;
    case 4:
      return 0;
    default:
      system("clear");
      printf("Opção Inválida\n\n");
      break;
    }
    media = 0.0;
    ttl = 0;
  }

  return 0;
}
