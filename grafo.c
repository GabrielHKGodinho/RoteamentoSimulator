#include "grafo.h"

void preencher_lista(Grafo *G){
    adiciona_cidade(G,"FLO\0");//1
    adiciona_cidade(G,"CWB\0");//2
    adiciona_cidade(G,"SPO\0");//3
    adiciona_cidade(G,"CGR\0");//4
    adiciona_cidade(G,"VIT\0");//5
    adiciona_cidade(G,"BHO\0");//6
    adiciona_cidade(G,"RJO\0");//7
    adiciona_cidade(G,"CUB\0");//8
    adiciona_cidade(G,"PVE\0");//9
    adiciona_cidade(G,"RBR\0");//10
    adiciona_cidade(G,"GOI\0");//11
    adiciona_cidade(G,"BRA\0");//12
    adiciona_cidade(G,"PAL\0");//13
    adiciona_cidade(G,"SAL\0");//14
    adiciona_cidade(G,"ARA\0");//15
    adiciona_cidade(G,"MCE\0");//16
    adiciona_cidade(G,"REC\0");//17
    adiciona_cidade(G,"CAG\0");//18
    adiciona_cidade(G,"JOP\0");//19
    adiciona_cidade(G,"NAT\0");//20
    adiciona_cidade(G,"FOR\0");//21
    adiciona_cidade(G,"TER\0");//22
    adiciona_cidade(G,"SLU\0");//23
    adiciona_cidade(G,"BEL\0");//24
    adiciona_cidade(G,"MAC\0");//25
    adiciona_cidade(G,"MAN\0");//26
    adiciona_cidade(G,"BOV\0");//27

    inserir_conexao(G,0,1,'f');
    inserir_conexao(G,0,2,'f');
    inserir_conexao(G,1,3,'c');
    inserir_conexao(G,2,3,'c');
    inserir_conexao(G,2,4,'f');
    inserir_conexao(G,3,7,'f');
    inserir_conexao(G,3,6,'f');
    inserir_conexao(G,3,12,'f');
    inserir_conexao(G,3,21,'c');
    inserir_conexao(G,4,8,'f');
    inserir_conexao(G,5,7,'f');
    inserir_conexao(G,5,14,'c');
    inserir_conexao(G,6,7,'f');
    inserir_conexao(G,6,12,'f');
    inserir_conexao(G,6,15,'f');
    inserir_conexao(G,7,12,'f');
    inserir_conexao(G,8,11,'f');
    inserir_conexao(G,8,9,'c');
    inserir_conexao(G,9,10,'c');
    inserir_conexao(G,11,12,'c');
    inserir_conexao(G,11,13,'f');
    inserir_conexao(G,12,26,'c');
    inserir_conexao(G,12,25,'c');
    inserir_conexao(G,12,21,'f');
    inserir_conexao(G,13,24,'f');
    inserir_conexao(G,14,17,'f');
    inserir_conexao(G,15,25,'f');
    inserir_conexao(G,16,17,'f');
    inserir_conexao(G,17,18,'c');
    inserir_conexao(G,17,21,'f');
    inserir_conexao(G,17,22,'c');
    inserir_conexao(G,18,20,'c');
    inserir_conexao(G,18,19,'f');
    inserir_conexao(G,19,23,'f');
    inserir_conexao(G,19,20,'f');
    inserir_conexao(G,20,21,'f');
    inserir_conexao(G,21,23,'f');
    inserir_conexao(G,21,27,'c');
    inserir_conexao(G,22,24,'c');
    inserir_conexao(G,23,24,'f');
    inserir_conexao(G,24,25,'c');
    inserir_conexao(G,24,26,'c');
    inserir_conexao(G,26,27,'c');

}

char** inicia_lista(){
    char** m;
    m=(char**)malloc(sizeof(char*));
    m[0]=(char*)malloc(SIGLA*sizeof(char));
    m[0][0]='P';
    m[0][1]='O';
    m[0][2]='A';
    m[0][3]='\0';
    return m;
}

void adiciona_cidade(Grafo*G, char cid[SIGLA]){
    G->V++;
    G->Adj=(Enlace**)realloc(G->Adj,G->V*sizeof(Enlace*));
    G->Adj[G->V-1]=NULL;
    G->lista=(char**)realloc(G->lista,G->V*sizeof(char*));
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
        if(strcmp(p->cidade,G->lista[u])==0)
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
    char state='a',tipo;
    char cidadenova[100];
    int i,cid1,cid2;

    Grafo *G = criar_grafo();

    preencher_lista(G);

    while(state){
        system("cls");
        printf("\t\t\tSIMULADOR DE NETWORK\n\n");
        printf("MENU: \nA. Adicionar conexao\nB. Remover conexao\nC. Procurar melhor rota\nD. Lista de Servidores\n");
        printf("E. Adicionar Cidade\nF. Remover Cidade\nG. Sair\n");
        scanf("%c",&state);
        getchar();
        system("cls");

        switch (state) {
            case'a':
            case 'A':
                while(tipo!='z'){
                    printf("Digite 'X X z' para cancelar\nDigite o codigo das duas cidades a serem conectadas e o tipo de conexao");
                    printf("('f' para fibra optica e 'c' para cabo ethernet: \n\n");
                    scanf("%d %d %c",&cid1,&cid2,&tipo);
                    getchar();
                    printf("%d %d %c",cid1,cid2,tipo);

                    if(tipo>=65 && tipo<=90)
                        tipo+=32;

                    if (cid1<G->V && cid2<G->V && (tipo=='c' || tipo=='f')){
                        inserir_conexao(G,cid1,cid2,tipo);
                        break;
                    }
                    system("cls");
                }
                tipo='a';
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
                while(strcmp(cidadenova,"z")!=0&&strcmp(cidadenova,"Z")!=0){
                    printf("Digite 'z' para cancelar\nDigite a sigla da cidade a ser inserida (3 letras, todas maiusculas): ");
                    scanf("%s",&cidadenova);
                    getchar();
                    system("cls");
                    if(strlen(cidadenova)==3){
                        for(i=0; i<SIGLA-1; i++)
                            if(cidadenova[i]>=97 && cidadenova[i]<=122)
                                cidadenova[i]-=32;

                        adiciona_cidade(G,cidadenova);
                        break;
                    }
                }


                strcpy(cidadenova,"n");
                break;

            case'f':
            case 'F':
                break;

            case'g':
            case 'G':
                return 0;
                break;
        }

    }

    return 0;
}
