#include "grafo.h"

/* Essa funcao preenche o grafo com as cidades e conexoes padroes */
void preencher_grafo(Grafo *G){
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
    inserir_conexao(G,6,14,'f');
    inserir_conexao(G,6,21,'f');
    inserir_conexao(G,7,12,'f');
    inserir_conexao(G,8,11,'f');
    inserir_conexao(G,8,9,'c');
    inserir_conexao(G,9,10,'c');
    inserir_conexao(G,11,12,'c');
    inserir_conexao(G,11,13,'f');
    inserir_conexao(G,12,26,'c');
    inserir_conexao(G,12,24,'c');
    inserir_conexao(G,12,21,'f');
    inserir_conexao(G,13,24,'f');
    inserir_conexao(G,14,17,'f');
    inserir_conexao(G,14,15,'f');
    inserir_conexao(G,15,16,'f');
    inserir_conexao(G,16,17,'f');
    inserir_conexao(G,17,18,'c');
    inserir_conexao(G,17,21,'f');
    inserir_conexao(G,17,22,'c');
    inserir_conexao(G,18,20,'c');
    inserir_conexao(G,18,19,'f');
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

/* Funcao para alocar a lista */
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

/*Funcao para adicionar uma cidade(vertice) ao grafo*/
void adiciona_cidade(Grafo*G, char cid[SIGLA]){
    G->V++;
    G->Adj=(Enlace**)realloc(G->Adj,G->V*sizeof(Enlace*));
    G->Adj[G->V-1]=NULL;
    G->lista=(char**)realloc(G->lista,G->V*sizeof(char*));
    G->lista[G->V-1]=(char*)malloc(SIGLA*sizeof(char));
    strcpy(G->lista[G->V-1],cid);
}

/*Funcao para remover uma cidade(vertice) do grafo*/
void remove_cidade(Grafo *G, int c){
    int i,j;
    Enlace* p;

    for(p=G->Adj[c];p!=NULL;p=p->next){
        j=0;
        while(strcmp(G->lista[j],p->cidade)!=0){
            j++;
        }
        desconectar(G,c,j);
    }

    G->V--;
    for(i=c; i<G->V; i++){
        G->Adj[i]=G->Adj[i+1];
        G->lista[i]=G->lista[i+1];
    }
    G->Adj=(Enlace**)realloc(G->Adj,G->V*sizeof(Enlace*));
    G->lista=(char**)realloc(G->lista,G->V*sizeof(char*));

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

/*Função para destruir um grafo construído com lista de adjacências.*/
void liberar_grafo (Grafo *G) {
   int v;
   for (v = 0; v < G->V; v++) {
      if (G->Adj[v] != NULL) {
         free(G->Adj[v]);
      }
   }
   free(G->Adj);
   free(G->lista);
   free(G);
}

/*Função para imprimir o grafo com seus devidos tipos de conexao*/
void imprimir_grafo(Grafo *G){
    int i;
    Enlace* p;
    for (i = 0; i < G->V; i++){
        printf("[%.2d] %s->",i, G->lista[i]);
        for (p = G->Adj[i]; p != NULL; p = p->next)
            printf(" %s (Tipo: %c) ", p->cidade,p->tipoC);
        printf("\n");
  }
}

/*Realiza a conexao ordenada*/
void realiza_conexao(Grafo *G, int v, int u, char tipo){
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
  realiza_conexao(G,v,u,tipo);
  realiza_conexao(G,u,v,tipo);
  G->E++;
}

/*Função calcula o menor custo de distancia entre dois vértices do grafo*/ //Incompleta
void dijkstra(Grafo *G, int v, int u){
    int custo[G->V][G->V], distancia[G->V], pred[G->V];
    int visitado[G->V], cont, distanciamin, proxno;

    //Criar e preencher a matriz de pesos
    int k = 0;
    int Gi [G->V][G->V];
    for(int i = 0; i < G->V; i++){
        for(int j = 0; j < G->V; j++){
            Gi[i][j] = -1;
        }
    }
    Enlace* p;
    for (int i = 0; i < G->V; i++){
        for (p = G->Adj[i]; p != NULL; p = p->next){
            if(p->tipoC == 'f'){
                while(strcmp(G->lista[k], p->cidade) != 0)
                    k++;
                Gi[i][k] = 2;
            }
            else if(p->tipoC == 'c'){
                while(strcmp(G->lista[k], p->cidade) != 0)
                    k++;
                Gi[i][k] = 5;
            }
        k = 0;
        }
    }
    //Fim preenchimento
    /*
    for(int i = 0; i < G->V; i++){
        for(int j = 0; j < G->V; j++){
            printf("%d ", Gi[i][j]);
        }
        printf("\n");
    }*/

    for(int i = 0; i < G->V; i++){
        for(int j = 0; j < G->V; j++){
            if(Gi[i][j] == -1)
                custo[i][j] = 99999;
            else
                custo[i][j] = Gi[i][j];
        }
    }

    for(int i = 0; i < G->V; i++){
        distancia[i] = custo[v][i];  //v é o indice da posição de saida q foi passada como parametro para achar o menor caminho
        pred[i] = v;
        visitado[i] = 0;
    }

    distancia[v] = 0;
    visitado[v] = 1;
    cont = 1;

    while(cont < (G->V)-1){
        distanciamin = 99999;

        for(int i = 0; i < G->V; i++){
            if(distancia[i] < distanciamin && !visitado[i]){
                    distanciamin = distancia[i];
                    proxno = i;
            }
        }

        //verifica se existe melhor caminho atraves do proximo node
        visitado[proxno] = 1;
        for(int i = 0; i < G->V; i++){
            if(!visitado[i]){
                if(distanciamin + custo[proxno][i] < distancia[i]){
                    distancia[i] = distanciamin + custo[proxno][i];
                    pred[i] = proxno;
                }
            }
        }

        cont++;
    }

    /*
    printf("\nDistancia entre o no %d e o no %d = %d", v, u, distancia[u]);
    printf("\nCaminho = %d", u);
    int j = u;
    do{
        j = pred[j];
        printf(" <- %d", j);
    }while(j != v);
    */
    //imprime o caminho e a distancia de cada node
    for(int i = 0; i < G->V; i++){
        if(i != v){
            printf("\nDistancia do no %d = %d", i, distancia[i]);
            printf("\nCaminho = %d", i);
            int j = i;

            do{
                j = pred[j];
                printf(" <- %d", j);
            }while(j != v);
        }
    }

}

/*Funcao para remover conexao ordenada*/
void remover_conexao(Grafo *G, int v, int u){
    Enlace* p=G->Adj[v];
    Enlace* aux=G->Adj[v];
    while(strcmp(p->cidade,G->lista[u])!=0){
        if(p==NULL)
            return;
        aux=p;
        p=p->next;
    }
    if (aux==p){
        G->Adj[v]=p->next;
        free(p);
    }
    else{
        aux->next=p->next;
        free(p);
    }
}

/*Funcao para remover a conexao(aresta) entre duas cidades*/
void desconectar( Grafo*G, int v, int u){
    remover_conexao(G, v, u);
    remover_conexao(G, u, v);
    G->E--;
}

/*Salva o grafo em um arquivo .txt*/
FILE* salvar(Grafo *G){
    FILE*arq=fopen(BACKUP,"w+");
    Enlace *p;
    int i,j;
    for(i=0;i<G->V;i++)
        fprintf(arq,"%s\n",G->lista[i]);

    fprintf(arq,"FIM\n");

    for(i=0;i<G->V;i++)
        for(p=G->Adj[i];p!=NULL;p=p->next){
            j=0;
            while(strcmp(G->lista[j],p->cidade)!=0){
                j++;
            }
            fprintf(arq,"%d %d %c\n",i,j,p->tipoC);
        }
    fprintf(arq,"0 0 z");

    fclose(arq);

    return arq;
}

/*Carrega o grafo salvo*/
Grafo* carregar(Grafo *G){
    liberar_grafo(G);

    Grafo* Gn=criar_grafo();
    remove_cidade(Gn,0);

    FILE* arq=fopen(BACKUP,"r");

    int cid1,cid2;
    char read[SIGLA],tipo='c';

    while(strcmp(read,"FIM")!=0){
        fscanf(arq,"%s",read);
        adiciona_cidade(Gn,read);
    }
    remove_cidade(Gn,Gn->V-1);

    while(tipo!='z'){
        fscanf(arq,"%d %d %c",&cid1,&cid2,&tipo);
        inserir_conexao(Gn,cid1,cid2,tipo);
    }
    remover_conexao(Gn,0,0);

    fclose(arq);
    return Gn;
}

int main () {
    char state='a';         /*Representa a escolha no menu*/
    char tipo;              /*'f' ou 'c' para adicionar conexoes*/
    char resp='t';          /*Resposta do usuario*/
    char cidadenova[100];   /*Sigla da cidade a ser adicionada*/
    int i;                  /*Para iteracoes*/
    int cid1;               /*Indice da cidade 1*/
    int cid2;               /*Indice da cidade 2*/
    FILE *parq;             /*Ponteiro pro arquivo*/

    Grafo *G = criar_grafo();

    preencher_grafo(G);

    /*Menu do simulador*/
    while(state){
        system("cls");
        printf("\t\t\tSIMULADOR DE NETWORK\n\n");
        printf("MENU: \nA. Adicionar conexao\nB. Remover conexao\nC. Alterar Conexao\nD. Procurar melhor rota\n");
        printf("E. Lista de Servidores\nF. Adicionar Cidade\nG. Remover Cidade\nH. Limpar Simulacao\nI. Salvar\nJ. Carregar\nK. Sair\n");
        scanf("%c",&state);
        getchar();
        system("cls");

        switch (state) {
            /*ADICIONAR CONEXAO*/
            case'a':
            case 'A':
                while(tipo!='z'){
                    printf("-Digite 'X X z' para cancelar\n\n-Digite o codigo das duas cidades a serem conectadas e o tipo de conexao\n");
                    printf("\t('f' para fibra optica e 'c' para cabo ethernet): \n\n");
                    scanf("%d %d %c",&cid1,&cid2,&tipo);
                    getchar();

                    if(tipo>=65 && tipo<=90)
                        tipo+=32;

                    if (cid1<G->V && cid2<G->V && (tipo=='c' || tipo=='f')&&(cid1>=0 && cid2>=0)){
                        inserir_conexao(G,cid1,cid2,tipo);
                        break;
                    }
                    system("cls");
                }
                tipo='a';
                break;

            /*REMOVER CONEXAO*/
            case'b':
            case 'B':
                while(cid1!=-1){
                    printf("-Digite '-1 X' para cancelar\n\n-Digite o codigo das duas cidades a serem desconectadas:\n\n");
                    scanf("%d %d",&cid1,&cid2);
                    getchar();

                    if ((cid1<G->V && cid2<G->V)&&(cid1>=0 && cid2>=0)){
                        desconectar(G,cid1,cid2);
                        break;
                    }
                    system("cls");
                }
                cid1=0;
                break;

            /*ALTERAR TIPO DA ROTA*/
            case'c':
            case 'C':
                break;

            /*PROCURAR MELHOR ROTA*/
            case'd':
            case 'D':
                break;

            /*LISTAR CIDADES*/
            case'e':
            case 'E':
                imprimir_grafo(G);
                getchar();
                break;

            /*ADICIONAR CIDADE*/
            case'f':
            case 'F':
                while(strcmp(cidadenova,"z")!=0&&strcmp(cidadenova,"Z")!=0){
                    printf("-Digite 'z' para cancelar\n\n-Digite a sigla da cidade a ser inserida (3 letras, todas maiusculas): ");
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

            /*REMOVER CIDADE*/
            case'g':
            case 'G':
                while(cid1!=-1){
                    printf("-Digite '-1' para cancelar\n\n-Digite o codigo da cidade a ser removida:\n\n");
                    scanf("%d",&cid1);
                    getchar();

                    if ((cid1<G->V)&&(cid1>=0)){
                        remove_cidade(G,cid1);
                        break;
                    }
                }
                cid1=0;
                break;

            /*LIMPAR GRAFO*/
            case'h':
            case 'H':
                while(resp!='y'&&resp!='n'){
                    printf("Tem certeza que deseja excluir a simulacao atual?(y/n)\n");
                    scanf("%c",&resp);
                    getchar();
                    system("cls");
                    if(resp>=65&&resp<=90)
                        resp+=32;
                }
                if(resp=='y'){
                    liberar_grafo(G);
                    G=criar_grafo();
                    remove_cidade(G,0);
                    printf("Simulacao excluida com sucesso!\n");
                    getchar();
                }
                resp='t';
                break;

            /*SALVAR GRAFO*/
            case'i':
            case 'I':
                parq=salvar(G);
                printf("Simulacao salva com sucesso!\n");
                getchar();
                break;

            /*CARREGAR GRAFO*/
            case'j':
            case 'J':
                G=carregar(G);
                printf("Dados carregados com sucesso!\n");
                getchar();
                break;

            /*SAIR DO SIMULADOR*/
            case'k':
            case 'K':
                return 0;
                break;
        }

    }

    liberar_grafo(G);
    return 0;
}
