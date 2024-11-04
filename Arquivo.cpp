#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio2.h>

struct tpProd 
{
    int codProd;
    char nomeProd[30];
    int quantProd;
    float precoProd;
};

int buscaCod(FILE *PtrProd, int cod)
{
    tpProd R;
    rewind(PtrProd);

    fread(&R, sizeof(tpProd), 1, PtrProd);

    while(!feof(PtrProd) && cod != R.codProd)
         fread(&R, sizeof(tpProd), 1, PtrProd);
    
    if(cod == R.codProd)
        return ftell(PtrProd) - sizeof(tpProd);
    else
        return -1;
}

void cadProduto(void)
{
    tpProd prodR;
    FILE *PtrProd = fopen("produtos.dat", "ab+");

    printf("Cadastro de produtos: \n");
    printf("Digite o codigo do produto: \n");
    scanf("%d", &prodR.codProd);
    while(prodR.codProd != 0)
    {
        if(buscaCod(PtrProd,prodR.codProd) == -1 || ftell(PtrProd) == 0)
        {
            printf("Nome do Produto: \n");
            fflush(stdin);
            gets(prodR.nomeProd);
            printf("Quantidade do Produto no estoque: \n");
            scanf("%d", &prodR.quantProd);
            printf("Preco do Produto: \n");
            scanf("%f", &prodR.precoProd);

            fwrite(&prodR, sizeof(tpProd), 1, PtrProd);
        } else {
            printf("Este registro ja existe!\n");
        }
        printf("Digite o codigo do produto: \n");
        scanf("%d", &prodR.codProd);
    }

    fclose(PtrProd);
}

void exibirProd(void){
    tpProd R;
    FILE *PtrProd = fopen("produtos.dat", "rb");

    if(PtrProd == NULL)
        printf("\nErro de Abertura\n");
    else 
    {
        fread(&R, sizeof(tpProd), 1, PtrProd);
        while(!feof(PtrProd))
        {
            printf("\nCod. do produto: %d", R.codProd);
            printf("\nNome do produto: %s", R.nomeProd);
            printf("\nQtd. do produto: %d", R.quantProd);
            printf("\nPreco do produto: %.2f", R.precoProd);
            fread(&R, sizeof(tpProd), 1, PtrProd);
        }

         fclose(PtrProd);
    }
    getch();
}

void exibirProdE(void)
{
	int pos;
	tpProd R;
	FILE *PtrProd = fopen("produtos.dat", "rb");
	
	printf("Digite o codigo do produto que deseja buscar: ");
	scanf("%d", &R.codProd);
	
	while(R.codProd != 0)
	{
		if(PtrProd == NULL)
			printf("Erro de Abertura\n");
		else
		{
			pos = buscaCod(PtrProd , R.codProd);
			if(pos == -1)
				printf("Não foi encontrado produto ou nao ha registros!");
			else
			{
				fseek(PtrProd,pos,0);
				fread(&R, sizeof(tpProd), 1, PtrProd);
				printf("\nEncontrado!\n\n");
				printf("Codigo do produto: %d\n", R.codProd);
				printf("Nome do produto: %s\n", R.nomeProd);
				printf("Quantidade no estoque: %d\n", R.quantProd);
				printf("Preco do produto: %.2f", R.precoProd);
			}
			printf("\n\nDigite o codigo do produto que deseja buscar: ");
			scanf("%d", &R.codProd);
		}		
	}
	
	fclose(PtrProd);
}

void deletarRegistros(void)
{
	FILE *PtrProd = fopen("produtos.dat", "wb");
	fclose(PtrProd);
}

void Menu(void){
	char op;
	do
	{
		system("cls");
		printf("\n### GERENCIAMENTO DE PRODUTOS ###\n");
		printf("[A] Cadastrar Produtos\n");
		printf("[B] Exibir Produtos\n");
		printf("[C] Exibir Produtos Especificos\n");
		printf("[D] Deletar Registros\n");
		printf("[ESC] Finalizar\n");
		op = toupper(getch());
		switch(op)
		{
			case 'A': 
					cadProduto();
					break;
			
			case 'B': 
					exibirProd();
					break;
			
			case 'C': 
					exibirProdE();  
					break;
		
			case 'D':
					deletarRegistros();
					break;					
		}
		
	}while (op!=27);
}

int main(void){
    Menu();
    return 0;
}



