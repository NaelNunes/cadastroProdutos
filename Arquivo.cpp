#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	
}

int main(void){
    cadProduto();
    exibirProd();
}
