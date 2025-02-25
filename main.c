#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void CriaMatrizInt (int num_linhas, int num_colunas, char **matriz_char, int **matriz_int);
void PrintaChar (int num_linhas, int num_colunas, char **matriz_char, int **matriz_int);
int Explora (int num_linhas, int num_colunas, int l, int c, int dist, int **matriz_int, int cordcam[2]);
int SetaProximos (int num_linhas, int num_colunas, int dist, int **matriz_int, int proximos[10][2]);
void TracaCaminho (int num_linhas, int num_colunas, int **matriz_int, int dist, int cordcam[2]);
int FugaHumana(int num_linhas, int num_colunas, char **matriz_char);

int main () {
    //Leitura do Arquivo 
    int num_linhas, num_colunas;
    char **matriz_char;
    char c;
    FILE *fp;

    fp = fopen("Matriz.txt", "r");

    fscanf(fp, "%d %d", &num_linhas, &num_colunas);

    matriz_char = (char **)malloc(num_linhas * sizeof(char *));
    
    for (int i = 0; i < num_linhas; i++) {
        matriz_char[i] = (char *)malloc((num_colunas) * sizeof(char));
    }

    for (int i = 0; i < num_linhas; i++) {
        for (int j = 0; j < num_colunas; j++) {
            fscanf(fp, " %c", &c);
            matriz_char[i][j] = c;
        }
    }

    fclose(fp);

    if(FugaHumana(num_linhas, num_colunas, matriz_char)) {
        printf("\n Caminho encontrado! \n");
    } else {
        printf("\n Caminho não encontrado \n");
    };
}

int FugaHumana(int num_linhas, int num_colunas, char **matriz_char) {

    //Cria uma matriz int
    int **matriz_int;

    matriz_int = (int **)malloc(num_linhas * sizeof(int *));
    
    for (int i = 0; i < num_linhas; i++) {
        matriz_int[i] = (int *)malloc((num_colunas) * sizeof(int));
    }

    //Copia para uma matriz Int
    CriaMatrizInt(num_linhas, num_colunas, matriz_char, matriz_int);

    //Inicia Proximos
    int proximos[10][2];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 2; j++) {
            proximos[i][j] = -1;
        }
    }

    //Acha a posição inicial
    for (int i = 0; i < num_linhas; i++) {
        for (int j = 0; j < num_colunas; j++) {
            if(matriz_char[i][j] == 'H') {
                proximos[0][0] = i;
                proximos[0][1] = j;
            }
        }
    }

    //Lógica para busca no mapa
    int cont = 0, dist = 1, verif = 0;
    int cordcam[2] = {0};

    while (cont == 0) {
        for (int i = 0; i < 10; i++) {
            int LinhaNaoNulla = 0;

            for (int j = 0; j < 2; j++) {
                if(proximos[i][j] >= 0) {
                    LinhaNaoNulla = 1;
                }   
            }

            if(LinhaNaoNulla) {
                if(Explora(num_linhas, num_colunas, proximos[i][0], proximos[i][1], dist, matriz_int, cordcam)) {
                    TracaCaminho (num_linhas, num_colunas, matriz_int, dist - 1, cordcam);
                    PrintaChar(num_linhas, num_colunas, matriz_char, matriz_int);                
                    verif++;
                    cont++;
                    return 1;
                    break;
                };
                proximos[i][0] = -1;
                proximos[i][1] = -1;
            }
        }
        if(SetaProximos(num_linhas, num_colunas, dist, matriz_int, proximos) && (verif == 0)) {
            cont++;
            return 0;        
        }
        dist++;
    }

    free(matriz_char);
    free(matriz_int);
    return 0;
}

void CriaMatrizInt (int num_linhas, int num_colunas, char **matriz_char, int **matriz_int) {
    for (int i = 0; i < num_linhas; i++) {
        for (int j = 0; j < num_colunas; j++) {
            if(matriz_char[i][j] == 'o') {
                matriz_int[i][j] = 0;
            } else if (matriz_char[i][j] == 'R') {
                matriz_int[i][j] = -1;
            } else if (matriz_char[i][j] == 'H') {
                matriz_int[i][j] = -2;
            } else if (matriz_char[i][j] == 'Z') {
                matriz_int[i][j] = -3;
            }
        }
    }
}

void PrintaChar (int num_linhas, int num_colunas, char **matriz_char, int **matriz_int) {
    printf("\n");

    for (int i = 0; i < num_linhas; i++) {
        for (int j = 0; j < num_colunas; j++) {    
            if(matriz_int[i][j] == -4) {
                matriz_char[i][j] = '*';
            }     
        }
    }

    for (int i = 0; i < num_linhas; i++) {
        for (int j = 0; j < num_colunas; j++) {
            printf("%c ", matriz_char[i][j]);
        }
        printf("\n");
    }
}

int Explora (int num_linhas, int num_colunas, int l, int c, int dist, int **matriz_int, int cordcam[2]) {

    //cima
    if (l != 0) {
        if (matriz_int[l - 1][c] == 0) {
            matriz_int[l - 1][c] = dist;
        } else if (matriz_int[l - 1][c] == -3) {
            cordcam[0] = l;
            cordcam[1] = c;
            return 1;
        }
    }

    //direita
    if ((c + 1) < num_colunas) {
        if (matriz_int[l][c + 1] == 0) {
            matriz_int[l][c + 1] = dist;
        } else if (matriz_int[l][c + 1] == -3) {
            cordcam[0] = l;
            cordcam[1] = c;
            return 1;
        }
    }

    //baixo
    if ((l + 1) < num_linhas) {
        if (matriz_int[l + 1][c] == 0) {
            matriz_int[l + 1][c] = dist;   
        } else if (matriz_int[l + 1][c] == -3) {
            cordcam[0] = l;
            cordcam[1] = c;         
            return 1;
        }
    }

    //esquerda
    if (c != 0) {
        if (matriz_int[l][c - 1] == 0) {
            matriz_int[l][c - 1] = dist;
        } else if (matriz_int[l][c - 1] == -3) {
            cordcam[0] = l;
            cordcam[1] = c;        
            return 1;
        }
    }

    return 0;
}

int SetaProximos (int num_linhas, int num_colunas, int dist, int **matriz_int, int proximos[10][2]) {
    int indice_prox = 0;
    int control = 0;

    for (int i = 0; i < num_linhas; i++) {
        for (int j = 0; j < num_colunas; j++) {
            if(matriz_int[i][j] == dist) {
                proximos[indice_prox][0] = i;
                proximos[indice_prox][1] = j;
                
                indice_prox++;
            } else {
                control++;
            }
        }
    }

    if (control == (num_linhas * num_colunas)) {
        return 1;
    }
    
    return 0;
}

void TracaCaminho (int num_linhas,int num_colunas, int **matriz_int, int dist, int cordcam[2]) {
    int row = cordcam[0];
    int col = cordcam[1];

    while(dist > 0){
        matriz_int[row][col] = -4;
        dist--;

        if(dist == 0) {
            break;
        }

        if(row != 0) {
            if(matriz_int[row - 1][col] == (dist)) { //cima
                row = row - 1;          
            }
        } 
        
        if(col != (num_colunas - 1)) {
            if (matriz_int[row][col + 1] == (dist)) { //direita
                col = col + 1;   
            }
        }

        if(row != (num_linhas - 1)) {
            if (matriz_int[row + 1][col] == (dist)) { //baixo
                row = row + 1;
            }
        }

        if(col != 0) {
            if(matriz_int[row][col - 1] == (dist)) { //esquerda
                col = col - 1;
            }
        }

    }
    
}