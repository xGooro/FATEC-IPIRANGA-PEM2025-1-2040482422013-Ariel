/*-------------------------------------------------------*
*                      FATEC Ipiranga                    *
* Disciplina: Programaçao Estruturada e Modular          *
*          Prof. Veríssimo                               *
*--------------------------------------------------------*
* Objetivo do Programa: Calcular notas e classificar candidatos               *
* Data - 27/02/2025                                      * 
* Autor: ARIEL PEREIRA DA SILVA;2040482422013            *
*--------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#define MAX_CANDIDATOS 50
#define MAX_NOME 100

typedef struct {
    char nome[MAX_NOME];
    float notas_PE[4];
    float notas_AC[5];
    float notas_PP[10];
    float notas_EB[3];
    float nota_final;
} Candidato;
float calcularMediaCentral(float notas[], int tamanho) {
    float soma = 0, maior = notas[0], menor = notas[0];
    
    for(int i = 0; i < tamanho; i++) {
        soma += notas[i];
        if(notas[i] > maior) maior = notas[i];
        if(notas[i] < menor) menor = notas[i];
    }
    
    return (soma - maior - menor) / (tamanho - 2);
}
float calcularNotaFinal(Candidato c) {
    float pe = calcularMediaCentral(c.notas_PE, 4);
    float ac = calcularMediaCentral(c.notas_AC, 5);
    float pp = calcularMediaCentral(c.notas_PP, 10);
    float eb = calcularMediaCentral(c.notas_EB, 3);
    
    return (pe * 0.3) + (ac * 0.1) + (pp * 0.4) + (eb * 0.2);
}
void ordenarCandidatos(Candidato cand[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(cand[j].nota_final < cand[j+1].nota_final) {
                Candidato temp = cand[j];
                cand[j] = cand[j+1];
                cand[j+1] = temp;
            }
        }
    }
}

int main() {
    Candidato candidatos[MAX_CANDIDATOS];
    int num_candidatos;
    
    do {
        printf("Digite o numero de candidatos (maximo 50): ");
        scanf("%d", &num_candidatos);
    } while(num_candidatos < 1 || num_candidatos > MAX_CANDIDATOS);
    
    for(int i = 0; i < num_candidatos; i++) {
        printf("\nCandidato %d\n", i+1);
        
        printf("Nome do candidato: ");
        scanf(" %[^\n]s", candidatos[i].nome);
        
        printf("Digite as 4 notas da Prova Escrita (0 a 10):\n");
        for(int j = 0; j < 4; j++) {
            do {
                scanf("%f", &candidatos[i].notas_PE[j]);
            } while(candidatos[i].notas_PE[j] < 0 || candidatos[i].notas_PE[j] > 10);
        }
        
        printf("Digite as 5 notas da Analise Curricular (0 a 10):\n");
        for(int j = 0; j < 5; j++) {
            do {
                scanf("%f", &candidatos[i].notas_AC[j]);
            } while(candidatos[i].notas_AC[j] < 0 || candidatos[i].notas_AC[j] > 10);
        }
        
        printf("Digite as 10 notas da Prova Pratica (0 a 10):\n");
        for(int j = 0; j < 10; j++) {
            do {
                scanf("%f", &candidatos[i].notas_PP[j]);
            } while(candidatos[i].notas_PP[j] < 0 || candidatos[i].notas_PP[j] > 10);
        }
        
        printf("Digite as 3 notas da Entrevista (0 a 10):\n");
        for(int j = 0; j < 3; j++) {
            do {
                scanf("%f", &candidatos[i].notas_EB[j]);
            } while(candidatos[i].notas_EB[j] < 0 || candidatos[i].notas_EB[j] > 10);
        }
        
        candidatos[i].nota_final = calcularNotaFinal(candidatos[i]);
    }
    
    ordenarCandidatos(candidatos, num_candidatos);
    
    int limite = (num_candidatos < 15) ? num_candidatos : 15;
    printf("\nCLASSIFICACAO FINAL 15 MELHORES\n");
    printf("Posicao  Nome                            Nota Final\n");
    for(int i = 0; i < limite; i++) {
        printf("%2d       %-30s  %.2f\n", i+1, candidatos[i].nome, candidatos[i].nota_final);
    }
    
    return 0;
}