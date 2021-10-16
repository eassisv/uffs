#define MAX_DIR 170
#define MAX_INF 35
//constantes para a matriz

//lista das funcoes que o jogo possui
typedef struct _domino TpPeca;

TpPeca* gera_lista();

void libera_lista(TpPeca *lista);

TpPeca* insere_elemento(TpPeca *peca, int e, int d);

void insere_mesa(TpPeca **Mesa, int i, int esq, int dir);

void remove_peca(TpPeca **lista, int x, int *esq, int *dir);

void imprime_lista(TpPeca *peca);

TpPeca* gera_pecas();

int conta_pecas(TpPeca *lista);

TpPeca* pesca_peca(TpPeca **pesca, TpPeca *Jog);

int percorre_lista(TpPeca *lista, int esq, int dir);

void busca_peca(TpPeca *lista, int i, int *esq, int *dir);

int inicio_jogo(TpPeca **J1, TpPeca **JM, TpPeca **Mesa);

int tem_peca(TpPeca *lista, int esq, int dir);

int jogada_maquina(TpPeca *JM, int esq_mesa, int dir_mesa, int *esq, int *dir);

int conta_pontos(TpPeca *lista);

void atualiza_mesa(TpPeca *Mesa, int *esq_mesa, int *dir_mesa);

void imprime_mesa(char m[][171]);

void insere_matriz(char m[][171], TpPeca *Mesa);

void gera_mesa(char m[][171]);
