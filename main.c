#include <stdio.h>
#include <stdlib.h>
const int TAMANHO = 100;

int categ(int *opcao);
int valid();


struct tudo{
  int dia;
  int mes;
  int ano;
  double gasto;
  char s;
  int contador;
  
};

//Contar linhas
int countlines()
{
  FILE *fp;
  char ch;
  int linesCount=0;
  fp=fopen("carteira.txt","r");
  if(fp==NULL) {
    return -1;
  }
  while((ch=fgetc(fp))!=EOF) {
    if(ch=='\n')
        linesCount++;
  }
  fclose(fp);
  return linesCount;
}

//Criar HTML
void criar_html(){
  FILE* html = fopen("archive.html", "w");
  FILE* ler = fopen("leitura.txt", "r");
  char frase[100];
  fprintf(html, "<html><body>");
  // while(fgets(frase, 100, ler) != NULL){
  //   fprintf(html, "<li>%s</li>", frase);
  // }
  fprintf(html, "</body></html>");
  fclose(html);
  fclose(ler);
}



//Ler arquivo option 2
void read_archive(int *escolhido, int *func){
  char* categories[] = {"Moradia", "Estudos", "Transporte", "Alimentação", "Trabalho" };
  int i=0,j=0, count_lines = 0;
  double valor[100];
  FILE *arquivo;
  arquivo = fopen("carteira.txt", "r");

  count_lines = countlines() / 5;
  int M[5][count_lines];
  
  for(j=0; j<count_lines;++j){
    for(i=0; i<5; ++i){
      if(i==3){
        fscanf(arquivo, "%lf\n", &valor[j]);
      }
      else{
        fscanf(arquivo, "%d\n", &M[i][j]);
      }
    }
  }

  //     Data: %d/%d/%d-> M[0][j], M[1][j], M[2][j]
  //     Gasto: -> valor[j]
  //     Categoria: -> categories[M[4][j] - 1]
  FILE* html = fopen("archive.html", "w");
  double total = 0;

  if(*func == 2){
    fprintf(html, "<html><body>\n");
    fprintf(html, "\n");
    fprintf(html, "<p>");
    fprintf(html, "---------------------------------------------\n");
    fprintf(html, "</p>");
    fprintf(html, "\n");
    for(j=0; j<count_lines;++j){
      if(M[2][j] == *escolhido){
        fprintf(html, "<p>");
        fprintf(html, "Data: %d/%d/%d\n", M[0][j], M[1][j], M[2][j]);
        fprintf(html, "</p>");
        fprintf(html, "<p>");
        fprintf(html, "Gasto: R$ %.2lf\n", valor[j]);
        fprintf(html, "</p>");
        fprintf(html, "<p>");
        fprintf(html, "Categoria: %s\n", categories[M[4][j] - 1]);
        fprintf(html, "</p>");
        fprintf(html, "\n");
        fprintf(html, "<p>");
        fprintf(html, "---------------------------------------------\n");\
        fprintf(html, "</p>");
        fprintf(html, "\n");
        total += valor[j];
      }
    }
    fprintf(html, "Total de gastos do ano de %d: R$ %.2lf\n", *escolhido, total);
    fprintf(html, "</body></html>");
    fclose(html);
    fclose(arquivo);
    puts("");
    printf("Seu arquivo em HTML foi criado com sucesso! \n\n");
  }
  else{
    int cat = categ(&*func);
    fprintf(html, "<html><body>\n");
    fprintf(html, "\n");
    fprintf(html, "<p>");
    fprintf(html, "---------------------------------------------\n");
    fprintf(html, "</p>");
    fprintf(html, "\n");
    for(j=0; j<count_lines;++j){
      if(M[1][j] == *escolhido && (M[4][j]) == cat){
        fprintf(html, "<p>");
        fprintf(html, "Data: %d/%d/%d\n", M[0][j], M[1][j], M[2][j]);
        fprintf(html, "</p>");
        fprintf(html, "<p>");
        fprintf(html, "Gasto: R$ %.2lf\n", valor[j]);
        fprintf(html, "</p>");
        fprintf(html, "<p>");
        fprintf(html, "Categoria: %s\n", categories[M[4][j] - 1]);
        fprintf(html, "</p>");
        fprintf(html, "\n");
        fprintf(html, "<p>");
        fprintf(html, "---------------------------------------------\n");\
        fprintf(html, "</p>");
        fprintf(html, "\n");
        total += valor[j];
      }
    }
    fprintf(html, "Total de gastos do mês %d: R$ %.2lf\n",*escolhido, total);
    fprintf(html, "</body></html>");
    fclose(html);
    fclose(arquivo);
    puts("");
    printf("Seu arquivo em HTML foi criado com sucesso! \n\n");
  }
}

//opcao 3
void option_3(){
  struct tudo op3;
  int num_3 = 3;
  printf("Você escolheu a opção 3 (Relatório de movimentação para categoria!\n\n");

  //Escolher o mes
  printf("Escolha o mes que deseja receber o relatório dos 12 meses: ");
  scanf("%d", &op3.mes);
  puts("");
  read_archive(&op3.mes, &num_3);
}

//opcao 2
void option_2(){
  struct tudo op2;
  int num_2 = 2;
  printf("Você escolheu a opção 2 (Relatório dos últimos 12 meses)!\n\n");

  //Escolher o ano
  printf("Escolha o ano que deseja receber o relatório dos 12 meses: ");
  scanf("%d", &op2.ano);

  read_archive(&op2.ano, &num_2);
}

//Categorias
int categ(int *opcao){
    printf("Veja agora alguma opcoes de categorias: \n");
    printf("------------------------------\n");
    printf("1 - Moradia \n");
    printf("2 - Estudos \n");
    printf("3 - Transporte \n");
    printf("4 - Alimentação \n");
    printf("5 - Trabalho \n\n");
    printf("Escolha uma categoria: ");

    return (valid(& *opcao));
}

//Add no arquivo txt
void add_archive(double* gasto, int *dia, int *mes, int *ano){
    int x = 1;
    FILE* f = fopen("carteira.txt", "a+");
    fprintf(f,"%d\n", *dia);
    fprintf(f,"%d\n", *mes);
    fprintf(f,"%d\n", *ano);
    fprintf(f, "%lf\n", *gasto);
    fprintf(f, "%d\n", categ(&x));
    fclose(f);
}

//opção 1:
void option_1(){
    struct tudo uso;
    puts("");
    printf("Você escolheu a opção 1 (Cadastro)!\n\n\n");

    //Gastos em double
    printf("Quanto você gastou?");
    scanf("%lf", &uso.gasto);
    puts("");

    //Para separar o dia/mes/ano
    printf("Qual foi o dia:");
    scanf("%d", &uso.dia);
    puts("");
    printf("Qual foi o mês:");
    scanf("%d", &uso.mes);
    puts("");
    printf("Qual foi o ano:");
    scanf("%d", &uso.ano);
    puts("");
    add_archive(&uso.gasto, &uso.dia, &uso.mes, &uso.ano);
    puts("");
    printf("O cadastro de receita foi bem sucedido!\n\n");
}


//Valida se o usuário escreveu certo
int valid(int *verifica){
    do{
        scanf("%d", & *verifica);
        if(*verifica < 0 || *verifica > 5){
            printf("Opcao invalida.\n");
            printf("Escolha uma opcao valida.\n");
        }

    }
    while(*verifica < 0 || *verifica > 5);
    return *verifica;
}

//Introdução para o cliente
int intro(int *opcao){
    printf("----------------------------------\n");
    printf("A seguir veja as opções:\n");
    printf("----------------------------------\n");
    printf("1 - Cadastrar nova receita/gastos;\n");
    printf("2 - Relatório de movimentação (últimos 12 meses);\n");
    printf("3 - Relatório de movimentação para categoria (último mês);\n");
    printf("4 - Econômizar no mês.\n");
    printf("0 - Sair\n\n");
    printf("Escolha uma das opções acima: (número).\n");

    return valid(& *opcao);
}

//funcao principal
int main()
{
    int opcao=0, start = 1, chamada=0;
    while(start == 1){
      chamada = intro(&opcao);

      //opção 1:
      if(chamada == 1){
          option_1();
      }
      //opção 2:
      else if(chamada == 2){
          option_2();
      }
      //opção 3:
      else if(chamada == 3){
        option_3();
      }
      //opção 4:
      else if(chamada == 4){

      }
      //opção 5:
      else if(chamada == 5){

      }
      //Saida:
      else if(chamada == 0){
        printf("Você escolheu a opção saida.\n");

        printf("Até a próxima ;)\n");

        start = 0;
      }
    }
    //    printf("%d", print_intro(&opcao));
    return 0;
}