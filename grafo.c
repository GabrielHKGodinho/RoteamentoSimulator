#include "grafo.h"

void preencher_lista(Grafo *G){
    char m[CIDADES][SIGLA]={{'P','O','A','\0'},{'F','L','O','\0'},{'C','W','B','\0'},{'S','P','O','\0'},{'C','G','R'},
    {'V','I','T'},{'B','H','O'},{'R','J','O'},{'C','U','B'},{'P','V','E'},{'R','B','R'},{'G','O','I'},{'B','R','A'},{'P','A','L'},
    {'S','A','L'},{'A','R','A'},{'M','A','C'},{'R','E','C'},{'C','A','G'},{'J','O','P'},{'N','A','T'},{'F','O','R'},{'T','E','R'},
    {'S','L','U'},{'B','E','L'},{'M','A','C'},{'M','A','N'},{'B','O','V'}};
    for(int i=0; i<G->V; i++)
        strcpy(G->lista[i],m[i]);
}

char** inicia_lista(){
    char** m;
    m=(char**)malloc(sizeof(char*));
    m[0]=(char*)malloc(SIGLA*sizeof(char));
    m[0][0]='C';
    m[0][1]='W';
    m[0][2]='B';
    m[0][3]='\0';
    return m;
}

void adiciona_cidade(Grafo*G, char cid[SIGLA]){
    G->V++;
    realloc(G->Adj,G->V*sizeof(Enlace*));
    G->Adj[G->V-1]=NULL;
    realloc(G->lista,G->V*sizeof(char*));
    G->lista[G->V-1]=(char*)malloc(SIGLA*sizeof(char));
    strcpy(G->lista[G->V-1],cid);
}

/*Função para criar um grafo com matriz de adjacências com 0 em todas as posições.*/
Grafo* criar_grafo () {
    Grafo *G = (Grafo *)malloc(sizeof(Grafo));
    G->E = 0;
    G->V = 1;
    G->Adj = (Enlace **)malloc(sizeof(Enlace *));
    G->Adj[0] = NULL;

    G->lista=inicia_lista();
    return G;
}

/*Função para destruir um grafo construído com matriz de adjacências.*/
void liberar_grafo (Grafo *G) {
   int v;
   for (v = 0; v < G->V; v++) {
      if (G->Adj[v] != NULL) {
         free(G->Adj[v]);
      }
   }
   free(G->Adj);
   free(G);
}

/*Função para imprimir o grafo com seus devidos pesos*/
void imprimir_grafo(Grafo *G){
    int i;
    Enlace* p;
    for (i = 0; i < G->V; i++){
        printf("%s->", G->lista[i]);
        for (p = G->Adj[i]; p != NULL; p = p->next)
            printf(" %s (Tipo: %c) ", p->cidade,p->tipoC);
        printf("\n");
  }
}

/*Realiza a conexao ordenada*/
void realiza_aconexao(Grafo *G, int v, int u, char tipo){
    Enlace* p=G->Adj[v];
    while(p!=NULL){
        if(strcmp(p->cidade,G->lista[u]))
            return;
        p=p->next;
    }
    p=(Enlace*)malloc(sizeof(Enlace));
    strcpy(p->cidade,G->lista[u]);
    p->tipoC=tipo;
    p->next=G->Adj[v];
    G->Adj[v]=p;
}

/*Função para inserir uma conexao na rede*/
void inserir_conexao(Grafo *G, int v, int u, char tipo){
  realiza_aconexao(G,v,u,tipo);
  realiza_aconexao(G,u,v,tipo);
  G->E++;
}

int main () {
    char state='a';
    char cidadenova[SIGLA];

    Grafo *G = criar_grafo();
    while(state){
        system("cls");
        printf("\t\t\tSIMULADOR DE NETWORK\n\n");
        printf("MENU: \nA. Adicionar conexao\nB. Remover conexao\nC. Procurar melhor rota\nD. Lista de Servidores\n");
        printf("E. Adicionar Cidade\nF. Sair\n");
        scanf("%c",&state);
        getchar();
        system("cls");

        switch (state) {
            case'a':
            case 'A':
                break;

            case'b':
            case 'B':
                break;

            case'c':
            case 'C':
                break;

            case'd':
            case 'D':
                imprimir_grafo(G);
                getchar();
                break;

            case'e':
            case 'E':
                printf("Digite a sigla da cidade a ser inserida (3 letras, todas maiusculas): ");
                scanf("%s",&cidadenova);
                adiciona_cidade(G,cidadenova);
                getchar();
                break;

            case'f':
            case 'F':
                return 0;
                break;
        }

    }

    return 0;
}
