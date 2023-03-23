#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***********************************************************

--PROJETO EM C--
Autor do trabalho:
Thiago Mafort

projeto que recebe registros, os ordena pela data e salva em 
um arquivo.txt

*************************************************************
Exemplo de amostragem dos dados no arquivo.txt:
Codigo: F20 -> tipo: string
Nome: Flavia -> tipo: string
Valor: 677.00 -> tipo: float
Mes: 08 -> tipo: int
Ano: 2020 -> tipo: int
*************************************************************/



struct vendedor {
    char codigo_vendedor[25];
    char nome_vendedor[25];
    float valor_venda;
    int mes;
    int ano;
};

int leArquivo(int registros, struct vendedor *vendedor) {
    int i;
    char texto[25];
    FILE *f;
    f = fopen("arquivo.txt", "r");

    for (i = 0; i < registros; i++) {
    fscanf(f, "%s %s", texto, vendedor[i].codigo_vendedor);
    fscanf(f, "%s %s", texto, vendedor[i].nome_vendedor);
    fscanf(f, "%s %f", texto, &vendedor[i].valor_venda);
    fscanf(f, "%s %d", texto, &vendedor[i].mes);
    fscanf(f, "%s %d", texto, &vendedor[i].ano);
    }
    fclose(f);
    return 0;
}

int criaArquivo() {
    FILE *f;
    FILE *var;

    f = fopen("arquivo.txt", "w");
    fclose(f);
    var = fopen("tamanhoArray.txt", "w");
    fclose(var);
    return 0;
}
// ************ Funcao que registra dados (2) ************
int incluiRegistro() {
    int j, registros;
    char texto[25],cod[25];
    FILE *f;
    FILE *var;
    int i = 0;

    struct vendedor vendedor[100];
    struct vendedor vendedor1[100];
    struct vendedor aux[100];

    var = fopen("tamanhoArray.txt", "r");

    fscanf(var, "%s %d", texto, &registros);

    registros = 1 + registros;
    fclose(var);

    f = fopen("arquivo.txt", "r");
    leArquivo(registros, vendedor1);
    fclose(f);

    f = fopen("arquivo.txt", "a+");

    printf("\n****Insira dados no arquivo ****\n");
    printf("Digite o codigo de vendedor: \n");
        scanf("%s", vendedor[i].codigo_vendedor);
    strcpy(cod, vendedor[i].codigo_vendedor);

    for (j = 0; j < registros; j++) {
        while (strcmp(cod, vendedor1[j].codigo_vendedor) == 0) {
            printf("\n----ESTE CODIGO JA EXISTE----\nDigite outro codigo:\n");
                scanf("%s", vendedor1[j].codigo_vendedor);
            strcpy(vendedor[i].codigo_vendedor, vendedor1[j].codigo_vendedor);
        }
    }
    printf("Digite o nome de vendedor: \n");
        getchar();
        fgets(vendedor[i].nome_vendedor, sizeof(vendedor[i].nome_vendedor), stdin);
    printf("Digite o valor da venda: \n");
        scanf("%f", &vendedor[i].valor_venda);
    printf("Digite o mes das vendas(numerico): \n");
        scanf("%d", &vendedor[i].mes);
    printf("Digite o ano das vendas: \n");
        scanf("%d", &vendedor[i].ano);
    i++;

    var = fopen("tamanhoArray.txt", "w");
    fprintf(var, "\nRegistros: %d", registros);
    fclose(var);

    for (i = 0; i < registros; i++) {
    fprintf(f, "\nCodigo: %s\nNome: %s\nValor: %f\nMes: %d\nAno: %d ",
            vendedor[i].codigo_vendedor, vendedor[i].nome_vendedor,
            vendedor[i].valor_venda, vendedor[i].mes, vendedor[i].ano);
    }
    fclose(f);

    f = fopen("arquivo.txt", "r");
    leArquivo(registros, vendedor);

    for (j = 1; j < registros; j++) {
        for (i = 0; i < registros - 1; i++) {
            if ((vendedor[i].ano * 10 + vendedor[i].mes) >
          (vendedor[i + 1].ano * 10 + vendedor[i + 1].mes)) {
                aux[i] = vendedor[i];
                vendedor[i] = vendedor[i + 1];
                vendedor[i + 1] = aux[i];
            }
        }
    }
    fclose(f);

    fopen("arquivo.txt", "w");
    for (i = 0; i < registros; i++) {
        if(strcmp(vendedor[i].codigo_vendedor, " ") != 0){
            fprintf(f, "\nCodigo: %s\nNome: %s\nValor: %.2f\nMes: %d\nAno: %d ",
            vendedor[i].codigo_vendedor, vendedor[i].nome_vendedor,
            vendedor[i].valor_venda, vendedor[i].mes, vendedor[i].ano);
        }
    }
    fclose(f);
    return 0;
}
// ************ Funcao que remove determinado vendedor (3) ************
int removeVendedor() {
    FILE *f;
    FILE *var;
    int i, registros;
    char texto[25], codigo[25];

    var = fopen("tamanhoArray.txt", "r");
    fscanf(var, "%s %d", texto, &registros);
    fclose(var);

    f = fopen("arquivo.txt", "r+");

    struct vendedor vendedor[registros];
    struct vendedor vazio;

    strcpy(vazio.codigo_vendedor, "");
    strcpy(vazio.nome_vendedor, "");
    vazio.valor_venda = 0;
    vazio.mes = 0;
    vazio.ano = 0;

    for (i = 0; i < registros; i++) {
        fscanf(f, "%s %s", texto, vendedor[i].codigo_vendedor);
        printf("\n%s %s\n", texto, vendedor[i].codigo_vendedor);

        fscanf(f, "%s %s", texto, vendedor[i].nome_vendedor);
        printf("%s %s\n", texto, vendedor[i].nome_vendedor);

        fscanf(f, "%s %f", texto, &vendedor[i].valor_venda);
        printf("%s %f\n", texto, vendedor[i].valor_venda);

        fscanf(f, "%s %d", texto, &vendedor[i].mes);
        printf("%s %d\n", texto, vendedor[i].mes);

        fscanf(f, "%s %d", texto, &vendedor[i].ano);
        printf("%s %d\n", texto, vendedor[i].ano);

    }
    printf("Digite o codigo do vendedor que deseja excluir: ");
        scanf("%s",codigo);
    fclose(f);

    f = fopen("arquivo.txt", "w");

    for (i = 0; i < registros; i++) {
        if (strcmp(codigo, vendedor[i].codigo_vendedor ) == 0) {
            vendedor[i] = vazio;
            for (i = 0; i < registros; i++) {
                if ((strcmp(vendedor[i].codigo_vendedor, "") != 0)) {
                fprintf(f, "\nCodigo: %s\nNome: %s\nValor: %f\nMes: %d\nAno: %d",
                         vendedor[i].codigo_vendedor, vendedor[i].nome_vendedor,
                          vendedor[i].valor_venda, vendedor[i].mes, vendedor[i].ano);
                }
            }
        }
    }
    fclose(f);

    var = fopen("tamanhoArray.txt", "w");
    fprintf(var, "Registros: %d",registros - 1);
    fclose(var);

    return 0;
}
// ************ Funcao que altera valor de venda (4) ************
int alterarvalor() {
    FILE *f;
    FILE *var;
    int i, registros;
    char texto[25], codigo[25];
    char novoV[15] = " ";

    var = fopen("tamanhoArray.txt", "r");
    fscanf(var, "%s %d", texto, &registros);
    fclose(var);

    f = fopen("arquivo.txt", "r");
    struct vendedor vendedor[registros];

    for (i = 0; i < registros; i++) {
        fscanf(f, "%s %s", texto, vendedor[i].codigo_vendedor);
            if(strcmp(vendedor[i].codigo_vendedor,novoV) != 0){
                printf("%s %s\n", texto, vendedor[i].codigo_vendedor);

                fscanf(f, "%s %s", texto, vendedor[i].nome_vendedor);
                printf("%s %s\n", texto, vendedor[i].nome_vendedor);

                fscanf(f, "%s %f", texto, &vendedor[i].valor_venda);
                printf("%s %f\n", texto, vendedor[i].valor_venda);

                fscanf(f, "%s %d", texto, &vendedor[i].mes);
                printf("%s %d\n", texto, vendedor[i].mes);

                fscanf(f, "%s %d", texto, &vendedor[i].ano);
                printf("%s %d\n", texto, vendedor[i].ano);
            }else{
                i--;
            }
    }
    printf("\nDigite o codigo do vendedor que deseja modificar o valor de venda: ");
        scanf("%s", codigo);
    for (i = 0; i < registros; i++) {
        if (strcmp(codigo, vendedor[i].codigo_vendedor) == 0) {
            printf("\nO valor eh: %f\n", vendedor[i].valor_venda);
            printf("\nDigite o novo valor: ");
                scanf("%f", &vendedor[i].valor_venda);
        }
    }
    fclose(f);

    f = fopen("arquivo.txt", "w");

    for (i = 0; i < registros; i++) {
        fprintf(f, "\nCodigo: %s\nNome: %s\nValor: %f\nMes: %d\nAno: %d\n ",
            vendedor[i].codigo_vendedor, vendedor[i].nome_vendedor,
            vendedor[i].valor_venda, vendedor[i].mes, vendedor[i].ano);
    }

    fclose(f);
    return 0;
}
// ************ Funcao que determina o maior valor de venda (5) ************
int maiorValor() {
    FILE *f, *var;
    char texto[25], nome[25];
    int i, ano, mes, registros;
    int verificar = 0;

    var = fopen("tamanhoArray.txt", "r");
    fscanf(var, "%s %d", texto, &registros);
    fclose(var);

    f = fopen("arquivo.txt", "r");
    struct vendedor vendedor[registros];
    leArquivo(registros, vendedor);

    float maior = vendedor[0].valor_venda;

    for (i = 0; i < registros; i++) {
        if (vendedor[i].valor_venda > maior) {
            maior = vendedor[i].valor_venda;
            verificar = i;
        }
    }
    ano = vendedor[verificar].ano;
    strcpy(nome, vendedor[verificar].nome_vendedor);
    mes = vendedor[verificar].mes;

    printf("\nO maior valor de venda eh: %.2f \nEssa venda foi feita por %s, na data %d/%d\n", maior, nome, mes, ano);
    fclose(f);
    return 0;
}
// ******* Funcao que determina o maior valor de venda pela data (6) ************
int vendaData() {
    int registros, mes, ano;
    int j = 0;
    int i = 0;
    FILE *f, *var;
    char texto[25];
    float vendas[10];
    float maior;

    var = fopen("tamanhoArray.txt", "r");
    fscanf(var, "%s %d", texto, &registros);
    fclose(var);

    f = fopen("arquivo.txt", "r");
    struct vendedor vendedor[registros];
    leArquivo(registros, vendedor);

    printf("Digite o mes desejado:\n");
        scanf("%d", &mes);
    printf("Digite o ano desejado:\n");
        scanf("%d", &ano);
    maior = vendas[0];

    for (i = 0; i < registros; i++) {
        if ((mes == vendedor[i].mes) && (ano == vendedor[i].ano)) {
            vendas[j] = vendedor[i].valor_venda;
            j++;
        }
    }
    for (i = 0; i < registros; i++) {
        if (vendas[i] > maior) {
            maior = vendas[i];
        }
    }
    printf("A maior venda da data %d/%d eh: R$%.2f\n", mes, ano, maior);
    fclose(f);
    return 0;
}
// ************ Funcao do total de vendas de um mes/ano (7) ************
int totalData() {
    int i, registros, mes, ano;
    FILE *f;
    FILE *var;
    char texto[25];
    float soma = 0;

    var = fopen("tamanhoArray.txt", "r");
    fscanf(var, "%s %d", texto, &registros);
    fclose(var);

    f = fopen("arquivo.txt", "r");
    struct vendedor vendedor[registros];

    leArquivo(registros, vendedor);

    printf("Digite o mes desejado:\n");
        scanf("%d", &mes);
    printf("Digite o ano desejado:\n");
        scanf("%d", &ano);

    for (i = 0; i < registros; i++) {
        if ((mes == vendedor[i].mes) && (ano == vendedor[i].ano)) {
            soma =  soma + vendedor[i].valor_venda;
        }
    }
    printf("\nTotal de vendas do mes %d/%d eh: R$ %.2f\n", mes, ano, soma);
    fclose(f);
    return 0;
}
// ************ Funcao do total de vendas de um ano (8) ************
int totalAno() {
    FILE *f, *var;
    int i, registros, ano;
    char texto[25];

    float soma = 0;

    var = fopen("tamanhoArray.txt", "r");
    fscanf(var, "%s %d", texto, &registros);
    fclose(var);

    f = fopen("arquivo.txt", "r");
    struct vendedor vendedor[registros];

    leArquivo(registros, vendedor);

    printf("Digite o ano desejado:\n");
        scanf("%d", &ano);
    for (i = 0; i < registros; i++) {
        if (ano == vendedor[i].ano) {
            soma = soma + vendedor[i].valor_venda;

        }
    }
    printf("Total de vendas do ano %d eh: %.2f\n", ano, soma);
    fclose(f);
    return 0;
}
// ************ Registro de saida padrao (9) ************
int saida() {
    int i, registros;
    FILE *f;
    FILE *var;
    char texto[25];

    var = fopen("tamanhoArray.txt", "r");
    fscanf(var, "%s %d", texto, &registros);
    fclose(var);

    f = fopen("arquivo.txt", "r");
    struct vendedor vendedor[registros];

    printf("\n___________ VENDAS COMPUTADAS __________\n");

    leArquivo(registros, vendedor);
    strcpy(texto, "");

    for (i = 0; i < registros ; i++) {
        if ((strcmp(vendedor[i].codigo_vendedor, texto) != 0)) {
            printf("\nCodigo do vendedor: %s\n", vendedor[i].codigo_vendedor);
            printf("Nome: %s\n", vendedor[i].nome_vendedor);
            printf("Valor: %.2f\n", vendedor[i].valor_venda);
            printf("Data: %d/%d\n", vendedor[i].mes, vendedor[i].ano);
            printf("\n----------------------------------------\n");
        }
    }
    fclose(f);
    return 0;
}
// ************ Excluir o arquivo de dados (10) ************
int excluiArquivo() {
    int retorno, retorno2;
    char sim;


    printf("\n------- ATENCAO! --------\n\nVoce realmente quer excluir todo o "
         "arquivo? \n(Digite 'S' maiusculo para continuar ou qualquer tecla "
         "para nao excluir o arquivo):\n");
        getchar();
        scanf("%c", &sim);
    if (sim == 'S') {
        retorno = remove("arquivo.txt");
        retorno2 = remove("tamanhoArray.txt");
            if (retorno == 0 && retorno2 == 0) {
                printf("\n---- Arquivo deletado!----\n");
            } else {
                printf("Nao deletado");
            }
    } else {
        printf("Voce decidiu nao exluir o arquivo.\n");
    }
    return 0;
}
// ************ Execucao do menu de opcoes ************
int menu() {
    int choice = 0;

    while (true) {
        printf("\nESCOLHA UMA FUNCIONALIDADE ABAIXO: \n");
        printf("1)  Criar Arquivo\n");
        printf("2)  Incluir determinado registro\n");
        printf("3)  Excluir determinado vendedor\n");
        printf("4)  Alterar valor de uma venda\n");
        printf("5)  Consultar maior valor de venda registrado\n");
        printf("6)  Consultar maior valor de venda pela data\n");
        printf("7)  Total de vendas de um determinado mes/ano\n");
        printf("8)  Total de vendas de um determinado ano \n");
        printf("9)  Imprimir os registros na saida padrao\n");
        printf("10) Excluir o arquivo de dados\n");
        printf("11) Finalizar o programa\n");
        scanf("%d", &choice);

    switch (choice) {
        case 1:
            criaArquivo();
            break;
        case 2:
            incluiRegistro();
            break;
        case 3:
            removeVendedor();
            break;
        case 4:
            alterarvalor();
            break;
        case 5:
            maiorValor();
            break;
        case 6:
            vendaData();
            break;
        case 7:
            totalData();
            break;
        case 8:
            totalAno();
            break;
        case 9:
            saida();
            break;
        case 10:
            excluiArquivo();
            break;
        case 11:
            printf("\n ------ Programa finalizado. ------\n");
            exit(0);
    }
    }
    return 0;
}
int main(void) {
    menu();
    return 0;
}
