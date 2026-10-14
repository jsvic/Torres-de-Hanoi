#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n;
    
char ***arr_torres; // array das torres

void criar_torre(int index_torre, int qtd_discos) {
    int count = (n - qtd_discos)+2, tamanho_disco = 1, j=0;
    // count é o tamanho da torre
    for(int i = 0; i < n+2; i++) {
        if(count == 0){
            // adicionar o disco
            for(j; j < tamanho_disco; j++) {
                arr_torres[i][index_torre][j] = '_';
            }
            // adiciona o espaço vazio ao lado do disco
            for(j=tamanho_disco; j<n+2; j++) {
                arr_torres[i][index_torre][j] = ' ';
            }
            j=0;
            tamanho_disco++;
        } else {
            // adiciona a torre
            arr_torres[i][index_torre][0] = '|';
            for(j=1; j<n+2; j++) {
                arr_torres[i][index_torre][j] = ' ';
            }
            j=0;
            count--;
        }
        
    }
}

void mostrar_torres() {
     printf("\n");
        for(int i = 0; i<n+2; i++){
        for(int u = 0; u<3; u++) {
            for(int j = 0; j<n+2; j++) {
                printf("%c", arr_torres[i][u][j]); // i: linha; u: torre; j: coluna
            }
        }
        printf("\n");
    }
    printf("0%*s1%*s2%*s\n", n + 1, "", n + 1, "", n + 1, ""); // enumeração de cada torre
}

void adicionar_disco(int index_torre, int tamanho_disco, int index_disco) {
     for(int i = 0; i<tamanho_disco; i++) {
            arr_torres[index_disco][index_torre][i] = '_';  
    }
}

void remover_disco(int index_torre, int tamanho_disco, int index_disco) {
    arr_torres[index_disco][index_torre][0] = '|';  
    for(int i = 1; i<5; i++) {
            arr_torres[index_disco][index_torre][i] = ' ';       
    }
}

void mover_disco(int torre_original, int torre_destino) {
    int qtd_discos_original=0, tamanho_disco=0, qtd_disco_destino=0, tamanho_disco_destino=0, u, j, index_disco_original, index_disco_destino=n+1;
    
    for(int i = 0; i < n+2; i++) {
        if(arr_torres[i][torre_original][0] == '_' && tamanho_disco == 0){
            // encontra o primeiro disco
            index_disco_original = i;
            for(u = 0; u < n+2; u++) {
                //encontre o tamanho do disco
                if(arr_torres[i][torre_original][u] == '_'){
                    tamanho_disco++;
                }else {break;}
            }
        }
        if(arr_torres[i][torre_destino][0] == '_' && tamanho_disco_destino == 0){
            // econtra, se existe um disco na torre, o primeiro disco
            index_disco_destino = i-1;
            for(j = 0; j < n+2; j++) {
                // econtra o tamanho do disco
                if(arr_torres[i][torre_destino][j] == '_'){
                    tamanho_disco_destino++;
                }else {break;}
            }

        }
    }
    
    // validação: discos menores não podem está por cima de maiores
    if(tamanho_disco == 0) {
        printf("A torre não possui discos");
    } else if (tamanho_disco_destino != 0 && tamanho_disco>tamanho_disco_destino) {
        printf("Movimento não permitido");
    } else {
        // trocando os discos
        remover_disco(torre_original, tamanho_disco,index_disco_original);
        adicionar_disco(torre_destino, tamanho_disco,index_disco_destino);
    }
}
void solucao(int num, int orig, int aux, int dest) {
    if (num == 1){
        // realiza a solução trivial
        mover_disco(orig,dest);
        mostrar_torres();
    } else if (num>1) {
        // reduz o problema até n=1
        solucao(num-1, orig, dest, aux);
        mover_disco(orig, dest);
        mostrar_torres();
        solucao(num-1, aux, orig, dest);
    }
 }
 
void mostrar_solucao() {
    char resp;
    printf("Deseja ver a solução com os movimentos minimos?(y/n) ");
    scanf(" %c", &resp);
    if(resp == 'y') {
        printf("===Mostrando a Solução===");
        solucao(n, 0, 1, 2);
        printf("===Terminando a Solução===");
    }
}

int main()
{
    printf("Objetivo do jogo: Levar todos os discos à torre desejada (o da direita)\nRegras:\n-> Todo movimento leva o disco do topo da torre para o topo da pilha da outra torre\n-> Nenhhum disco pode ficar por cima de um disco menor que ele\n");
    printf("\nQuantidade de discos: ");
    if (scanf("%d", &n) != 1 || n <= 0) { // valida o input
        printf("Quantidade inválida!\n");
        return 1;
    }
    
    int linhas = n+2;

  arr_torres = malloc(linhas * sizeof(char **)); // cria o array das linhas
    if (arr_torres == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }
    
   for (int i = 0; i < linhas; i++) {
        arr_torres[i] = malloc(3 * sizeof(char *)); // cria o array das torres
        if (arr_torres[i] == NULL) {
            printf("Erro ao alocar memória para a linha %d!\n", i);
            for (int j = 0; j < i; j++) {
                free(arr_torres[j]);
            }
            free(arr_torres);
            return 1;
        }
        
        for(int j = 0; j < linhas; j++) {
            arr_torres[i][j] = malloc(linhas * sizeof(char)); // cria o array das colunas
             if (arr_torres[i][j] == NULL) {
            printf("Erro ao alocar memória para a linha %d!\n", i);
            for (int j = 0; j < i; j++) {
                free(arr_torres[j]);
            }
            free(arr_torres);
            return 1;
            }
        }
    }
    
    // cria as 3 torres
    for(int i = 0; i<3; i++) {
        if(i == 0) {
            criar_torre(i, n);
        } else {
            criar_torre(i, 0);
        }
    }
    
    mostrar_torres();
    
    int terminar=0, torre_original, torre_destino, movimentos= 0, minimos;
    float precisao;
    char c;
    while(1) {
        torre_original = -1;
        torre_destino = -1;
        
        printf("\nPara desistir, digite -1 em qualquer um dos inputs\n");
        
        printf("\nEscolha o disco para mover: ");
        if(scanf("%d", &torre_original) !=1) {
            printf("Torre inválida, digite novamente");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        
        if(torre_original == -1) {
            break;
        }
        
        printf("\nEscolha a torre que esse disco vai: ");
        if(scanf("%d", &torre_destino) !=1) {
            printf("Torre inválida, digite novamente");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
    
        if(torre_destino == -1) {
            break;
        }
        
        movimentos++;
        
        mover_disco(torre_original, torre_destino);
        
        mostrar_torres();
        
        terminar = 1;
        for(int i = 2; i < linhas; i++) {
            // caso todos os discos estejam na torre objetivo, encerra o while
            if(arr_torres[i][2][0] != '_') {
                terminar = 0;
            }
        }
        
        if(terminar == 1) {
            break;
        }
    }
    
    if(movimentos == 0) {
        mostrar_solucao();
    } else {
        minimos = pow(2,n)-1;
        precisao = ((float)minimos/movimentos) * 100;
        
        printf("\nParabéns você ganhou!!!\n\nMovimentos realizados: %d\nMovimentos mínimos: %d\nPecisão: %.2f%%\n", movimentos, minimos, precisao);
        
        if(minimos != movimentos) {
            mostrar_solucao();
        }
    }
    free(arr_torres);
    
    return 0;
}