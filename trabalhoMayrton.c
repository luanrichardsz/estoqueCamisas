#include <stdio.h>
#include <string.h>

//define tamanho do estoque da camisa
#define MAX_CAMISAS 1200

//dados que a camisa tem que ter
typedef struct {
    char tamanho[5];
    char marca[50];
    char cor[20];
    float preco;
    int quantidade;
} Camisa;

// fun��es para salvar e carregar estoque
void salvarEstoque(Camisa estoque[], int numCamisas);
void carregarEstoque(Camisa estoque[], int *numCamisas);

// declarando as fun��es
void iniciar(Camisa estoque[], int *numCamisas);
void inserir(Camisa estoque[], int *numCamisas);
void listar(Camisa estoque[], int numCamisas);
void remover(Camisa estoque[], int *numCamisas);
void buscar(Camisa estoque[], int numCamisas);

void salvarEstoque(Camisa estoque[], int numCamisas) {
    FILE *arquivo = fopen("estoque.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar.\n");
        return;
    }

    // Grava o n�mero de camisas na primeira linha
    fprintf(arquivo, "%d\n", numCamisas);

    // Grava os dados de cada camisa
    int i;
    for ( i = 0; i < numCamisas; i++) {
        fprintf(arquivo, "%s\n", estoque[i].tamanho);
        fprintf(arquivo, "%s\n", estoque[i].marca);
        fprintf(arquivo, "%s\n", estoque[i].cor);
        fprintf(arquivo, "%.2f\n", estoque[i].preco);
        fprintf(arquivo, "%d\n", estoque[i].quantidade);
    }

    fclose(arquivo);
    printf("Estoque salvo com sucesso!\n");
}

void carregarEstoque(Camisa estoque[], int *numCamisas) {
    FILE *arquivo = fopen("estoque.txt", "r");
    if (arquivo == NULL) {
        printf("Nenhum estoque encontrado. Come�ando com estoque vazio.\n");
        *numCamisas = 0;
        return;
    }

    // L� o n�mero de camisas
    fscanf(arquivo, "%d\n", numCamisas);

    // L� as camisas do arquivo
    int i;
    for ( i = 0; i < *numCamisas; i++) {
        fscanf(arquivo, "%s\n", estoque[i].tamanho);
        fscanf(arquivo, "%[^\n]\n", estoque[i].marca);
        fscanf(arquivo, "%[^\n]\n", estoque[i].cor);
        fscanf(arquivo, "%f\n", &estoque[i].preco);
        fscanf(arquivo, "%d\n", &estoque[i].quantidade);
    }

    fclose(arquivo);
    printf("Estoque carregado com sucesso!\n");
}

//inserir as camisas no estoque
void inserir(Camisa estoque[], int *numCamisas) {
    if (*numCamisas >= MAX_CAMISAS) {
        printf("Estoque cheio! N�o � poss�vel adicionar mais camisas.\n");
        return;
    }

    Camisa novaCamisa;
    printf("Digite o tamanho da camisa (PP, P, M, G, GG): ");
    scanf("%s", novaCamisa.tamanho);

    printf("Digite a marca da camisa: ");
    scanf(" %[^\n]s", novaCamisa.marca);

    printf("Digite a cor da camisa: ");
    scanf(" %[^\n]s", novaCamisa.cor);

    printf("Digite o preco da camisa: ");
    scanf("%f", &novaCamisa.preco);

    printf("Digite a quantidade de camisas: ");
    scanf("%d", &novaCamisa.quantidade);

    estoque[*numCamisas] = novaCamisa;
    (*numCamisas)++;
    salvarEstoque(estoque, *numCamisas); // Salva o estoque ap�s inserir
    printf("Camisa adicionada com sucesso!\n");
}

//listar todas as camisas
void listar(Camisa estoque[], int numCamisas) {
    if (numCamisas == 0) {
        printf("Nao existem camisas no estoque.\n");
        return;
    }
	int i;
    for (i = 0; i < numCamisas; i++) {
        printf("\nCamisa %d:\n", i + 1);
        printf("  Tamanho: %s\n", estoque[i].tamanho);
        printf("  Marca: %s\n", estoque[i].marca);
        printf("  Cor: %s\n", estoque[i].cor);
        printf("  Preco: %.2f\n", estoque[i].preco);
        printf("  Quantidade: %d\n", estoque[i].quantidade);
    }
}

//remover camisa do estoque
void remover(Camisa estoque[], int *numCamisas) {
    if (*numCamisas == 0) {
        printf("Nao existem camisas no estoque.\n");
        return;
    }

    int camisaNum;
    printf("Digite o numero da camisa que deseja remover: ");
    scanf("%d", &camisaNum);

    if (camisaNum < 1 || camisaNum > *numCamisas) {
        printf("Numero invalido!\n");
        return;
    }
	int i;
    for ( i = camisaNum - 1; i < *numCamisas - 1; i++) {
        estoque[i] = estoque[i + 1];
    }
    (*numCamisas)--;
    
    salvarEstoque(estoque, *numCamisas); // Salva o estoque ap�s remover
    printf("Camisa removida com sucesso!\n");
}

//buscar camisa com modelo, cor ou tamanho
void buscar(Camisa estoque[], int numCamisas) {
    char busca[10];
    printf("Digite a MARCA, COR ou TAMANHO da camisa para buscar: ");
    scanf(" %9[^\n]", busca);

    int encontrou = 0;
    int i;
    for ( i = 0; i < numCamisas; i++) {
        if (strstr(estoque[i].marca, busca) || strstr(estoque[i].cor, busca) || strstr(estoque[i].tamanho, busca)) {
            printf("\nCamisa encontrada:\n");
            printf("  Tamanho: %s\n", estoque[i].tamanho);
            printf("  Marca: %s\n", estoque[i].marca);
            printf("  Cor: %s\n", estoque[i].cor);
            printf("  Preco: %.2f\n", estoque[i].preco);
            printf("  Quantidade: %d\n", estoque[i].quantidade);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("\nNenhuma camisa encontrada.\n");
    }
}

//atualizar certa coisa da camisa
void atualizar(Camisa estoque[], int numCamisas) {
    if (numCamisas == 0) {
        printf("Estoque vazio! \n");
        return;
    }
    
    int indiceCamisa;
    
    printf("Digite o indice que se encontra a camisa para ela ser atualizada (1 a %d): ", numCamisas);
    scanf("%d", &indiceCamisa); // Corrigido: passamos o endere�o de 'indiceCamisa'
    
    if (indiceCamisa < 1 || indiceCamisa > numCamisas) {
        printf("Indice invalido! \n");
        return;
    }
    
    Camisa *camisa = &estoque[indiceCamisa - 1];
    
    printf("Digite o novo tamanho (PP, P, M, G, GG): ");
    scanf("%s", camisa->tamanho);  // Corrigido: leitura do tamanho
    
    printf("Digite a nova marca: ");
    scanf("%s", camisa->marca);  // Corrigido: leitura da marca
    
    printf("Digite a nova cor: ");
    scanf("%s", camisa->cor);    // Corrigido: leitura da cor
    
    printf("Digite o novo preco: ");
    scanf("%f", &camisa->preco); // Corrigido: leitura do pre�o
    
    printf("Digite a nova quantidade: ");
    scanf("%d", &camisa->quantidade); // Corrigido: leitura da quantidade
    
    printf("Camisa atualizada com sucesso! \n");
}

// Fun��o para aplicar desconto a camisas com base em marca, cor ou tamanho
void desconto(Camisa estoque[], int numCamisas) {
    if (numCamisas == 0) {
        printf("Estoque vazio! \n");
        return;
    }

    // Solicitar o crit�rio de busca (marca, cor ou tamanho)
    char criterio[50];
    printf("Digite o criterio para aplicar o desconto (marca, cor ou tamanho): ");
    scanf(" %[^\n]s", criterio);

    // Solicitar o percentual de desconto
    float percentualDesconto;
    printf("Digite o percentual de desconto (ex: 10 para 10%%): ");
    scanf("%f", &percentualDesconto);

    if (percentualDesconto < 0 || percentualDesconto > 100) {
        printf("Percentual de desconto invalido! Deve ser entre 0 e 100.\n");
        return;
    }

    // Calcular o valor do desconto
    float valorDesconto = percentualDesconto / 100.0;

    int camisasDescontadas = 0;

    // Iterar sobre o estoque e aplicar o desconto nas camisas que correspondem ao crit�rio
    int i;
    for ( i = 0; i < numCamisas; i++) {
        if (strstr(estoque[i].marca, criterio) || strstr(estoque[i].cor, criterio) || strstr(estoque[i].tamanho, criterio)) {
            // Mostrar o pre�o original
            printf("\nCamisa %d (Marca: %s, Cor: %s, Tamanho: %s):\n", i + 1, estoque[i].marca, estoque[i].cor, estoque[i].tamanho);
            printf("  Preco original: %.2f\n", estoque[i].preco);

            // Aplicar o desconto
            float precoOriginal = estoque[i].preco;
            estoque[i].preco -= precoOriginal * valorDesconto;

            // Mostrar o pre�o com desconto
            printf("  Preco com desconto: %.2f\n", estoque[i].preco);
            camisasDescontadas++;
        }
    }

    // Verificar se o desconto foi aplicado em pelo menos uma camisa
    if (camisasDescontadas == 0) {
        printf("Nenhuma camisa foi encontrada com o crit�rio '%s'.\n", criterio);
    } else {
        printf("Desconto de %.2f%% aplicado com sucesso!\n", percentualDesconto);
        salvarEstoque(estoque, numCamisas);
    }
}

// Fun��o para validar o tamanho da camisa
int validarTamanho(char *tamanho) {
    if (strcmp(tamanho, "PP") == 0 || strcmp(tamanho, "P") == 0 ||
        strcmp(tamanho, "M") == 0 || strcmp(tamanho, "G") == 0 || strcmp(tamanho, "GG") == 0) {
        return 1;  // Tamanho v�lido
    }
    return 0;  // Tamanho inv�lido
}

// Fun��o para registrar a venda de camisas
void venderCamisa(Camisa estoque[], int *numCamisas) {
    if (*numCamisas == 0) {
        printf("Estoque vazio! N�o � poss�vel realizar vendas.\n");
        return;
    }

    char tamanho[5];
    int quantidadeVenda;
    int i, camisaIndex = -1;
    float valorVenda = 0.0;

    // Solicitar o tamanho da camisa e a quantidade a ser vendida
    printf("Digite o tamanho da camisa para venda (ex: PP, P, M, G, GG): ");
    scanf("%s", tamanho);

    // Valida��o do tamanho
    if (!validarTamanho(tamanho)) {
        printf("Tamanho inv�lido! Os tamanhos v�lidos s�o: PP, P, M, G, GG.\n");
        return;
    }

    printf("Digite a quantidade de camisas a ser vendida: ");
    scanf("%d", &quantidadeVenda);

    // Verificar se a quantidade de venda � v�lida
    if (quantidadeVenda <= 0) {
        printf("Quantidade inv�lida! A quantidade deve ser maior que zero.\n");
        return;
    }

    // Procurar no estoque o tamanho da camisa
    for (i = 0; i < *numCamisas; i++) {
        if (strcmp(estoque[i].tamanho, tamanho) == 0) {
            camisaIndex = i;
            break;
        }
    }

    if (camisaIndex == -1) {
        printf("Camisa do tamanho '%s' n�o encontrada no estoque.\n", tamanho);
        return;
    }

    // Verificar se h� camisas suficientes no estoque
    if (estoque[camisaIndex].quantidade < quantidadeVenda) {
        printf("Estoque insuficiente! Temos apenas %d camisas do tamanho '%s'.\n", estoque[camisaIndex].quantidade, tamanho);
        return;
    }

    // Calcular o valor da venda
    valorVenda = estoque[camisaIndex].preco * quantidadeVenda;

    // Registrar a venda: diminuir a quantidade do estoque
    estoque[camisaIndex].quantidade -= quantidadeVenda;
    
    // Exibir detalhes da venda
    printf("\nVenda realizada com sucesso!\n");
    printf("Voc� vendeu %d camisas do tamanho '%s'.\n", quantidadeVenda, tamanho);
    printf("Valor total da venda: R$ %.2f\n", valorVenda);
    printf("Estoque restante do tamanho '%s': %d camisas\n", tamanho, estoque[camisaIndex].quantidade);

    // Salvar o estoque ap�s a venda
    salvarEstoque(estoque, *numCamisas);
}


//iniciar o sistema
void iniciar(Camisa estoque[], int *numCamisas) {
    carregarEstoque(estoque, numCamisas);

    int opcao;
    do {
        printf("\nGerenciamento da Loja de Camisas - Crazy Shirt\n");
        printf("1. Inserir\n2. Listar\n3. Remover\n4. Buscar\n5. Atualizar\n6. Desconto\n7. Vender\n0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserir(estoque, numCamisas);
                break;
            case 2:
                listar(estoque, *numCamisas);
                break;
            case 3:
                remover(estoque, numCamisas);
                break;
            case 4:
                buscar(estoque, *numCamisas);
                break;
            case 5:
                atualizar(estoque, *numCamisas);
                break;
            case 6:
                desconto(estoque, *numCamisas);
                break;
            case 7:
            	venderCamisa(estoque, *numCamisas);
            	break;
            case 0:
                printf("Saindo...\n");
                salvarEstoque(estoque, numCamisas);
                break;
            default:
                printf("Op��o inv�lida.\n");
        }
    } while (opcao != 0);
}

int main() {
    Camisa estoque[MAX_CAMISAS];
    int numCamisas = 0;

    iniciar(estoque, &numCamisas);
    return 0;
}