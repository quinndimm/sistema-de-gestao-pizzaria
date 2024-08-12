/*Incluindo as bibliotecas que seram usadas para esse programa*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char op; /*Variavel global para capturar em qual gerencia o usuario quer entrar  */

void getch(){
    system("read b");
}

/*Estrutura do tipo de endereço*/
typedef struct{
    char logradouro[10];
    char complemento[20];
    char cep[10];
    char bairro[20];
    char cidade[20];
    char estado[3];
}end;

/*Estrutura do tipo cliente junto com a estrutura endereço */
typedef struct{
    int codigo;
    char nome[30];
    char cnpj[20], cpfj[20];
    char telefone[10];
    end endereço;
}Cli;

/*Estrutura do tipo produto */
typedef struct{
    int codigo;
    char nome[30];
    char fornecedor[30];
    char categoria[30];
    int quantidade[30];
    float valorUnit;
}Prod;

/*Estrutura do tipo pedido junto com as estruturas 'cliente' e 'produto' */
typedef struct{
    int codigo;
    int dia;
    int mes;
    int ano;
    Cli clienteQuePediu;
    Prod *produtoPedido;
    int *qntProdutoPedido;
    int qnt;
}Ped;

/*Declaração da função menu, que irá gerenciar o funcionamento do programa*/
void menu();

/*Declaração das funções que gerenciam a ações relacionadas com o cliente  */
void gerenciaDeClientes(Cli*, int*, FILE*);
     Cli cadastrarCliente(Cli*, int);
     void listarCliente(Cli*, int);
          void ordenarClientePorOrdemAlfabetica(Cli*, int);
    void buscarCliente(Cli*, int);
    void atualizarCliente (Cli*, int);
    void excluirCliente(Cli*, int*);
    void imprimirCliente(Cli);

/*Declaração das funções que gerenciam as ações relacionadas aos produtos */
void gerenciaDeProdutos(Prod*, int*, FILE*);
     Prod cadastrarProduto(Prod, int);
     void listarProdutosCadastrados(Prod, int);
          void ordenarProdutoPorNomme(Prod, int);
          void filtrarCategoria();
     void buscarProdutoCadastrados(Prod, int);
     void atualizarProdutoCadastrado(Prod, int);
     void atualizarEstoqueProduto(Prod, int);
     void imprimirProduto(Prod);

/*Declaração das funções que que gerenciam as ações relacionadas aos pedidos */
void gerenciaDePedidos(Ped*, Cli*, Prod*, int*, int, int);
     void cadastrarPedido(Ped*, Cli*, Prod*, int*, int, int);
        void obterData(Ped*);
     void listarPedidosDeUmCliente(Ped*, int);
        void ordenarPedidosPorData(Ped*, int);
     void listarPedidosDeUmDia(Ped*, int);
        void ordenarPorNomeCliente(Ped*, int);
     void imprimirPedido(Ped);

/*Função principal*/
int main(){
    FILE *arquivo; /*Declaração de um arquivo*/
    Prod *produto; /*Declarando um ponteiro para a estrutura produto*/
    Cli *cliente; /*declarando um ponteiro para a estrutura cliente*/
    Ped *pedido; /*declarando um ponteiro para a estrutura pedido*/
    int contCliente=0, contProduto=0, contPedido=0; /*Inicializando os contadores em '0'*/

    /*Alocando memoria para os ponteiros*/
    produto = calloc(10, sizeof(Prod));
    cliente = calloc(10, sizeof(Cli));
    pedido = calloc(10, sizeof(Ped));

    /*Chamada da função menu*/
    menu();

    do{ /*Ciclo que ira controlar o funcionamento do programa*/
        switch(op){
             case 'C':
             case 'c':
                  gerenciaDeClientes(cliente, &contCliente, arquivo);
                  break;

             case 'P':
             case 'p':
                 gerenciaDeProdutos(produto, &contProduto, arquivo);
                 break;

             case 'E':
             case 'e':
                  gerenciaDePedidos(pedido, cliente, produto, &contPedido, &contCliente, &contProduto);
                  break;

             case 'S':
             case 's':
                  exit(1);

             default:
                  printf(" COMANDO INVALIDO!! \n Entre com o comando novamente.\n");
                  sleep(2);
                  system("clear");
                  menu();
        }

    }while (1);
     
     return 0;
    
} /*Fim da função principal*/

/*Código da função menu*/
void menu(){
     printf("Menu de Gerenciamento\n");
     printf("C - Gerenciar Clientes\n");
     printf("P - Gerenciar Produtos\n");
     printf("E - Gerenciar Pedidos\n");
     printf("S - Sair\n");
     printf("Digite um comando para proceguir: ");
     scanf("%c", &op);
     system("clear");
}

/*Código da função que gerencia os clientes*/
void gerenciaDeClientes(Cli *cliente, int *contCliente, FILE *arquivo){
     char opção;

     do{
          printf("Gerenciar Clientes\n");
          printf("C -Cadastrar Cliente\n");
          printf("L - Listar clientes cadastrados\n");
          printf("B - Buscar cliente cadastrado\n");
          printf("A - Atualizar cliente cadastrado\n");
          printf("E - Excluir cliente cadatrado\n");
          printf("\n Digite uma opção para prosseguir: ");
          scanf("%c",&opção);
          system("clear");

          switch (opção)
          {
          case 'C':
          case 'c':
                arquivo = fopen("Força de Vendas.txt", "a+");
                if(arquivo == NULL) {
                    printf("Não foi possivel abrir o arquivo.");
                    return;
               }

               printf("Cadastro de Cliente\n");
               fprintf(arquivo, "%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;\n", cliente[*contCliente].codigo, cliente[*contCliente].nome, cliente[*contCliente].cnpj, cliente[*contCliente].cpf, cliente[*contCliente].telefone, cliente[*contCliente].endereço.logradouro,cliente[*contCliente].endereço.complemento,cliente[*contCliente].endereço.cep, cliente[*contCliente].endereço.bairro,cliente[*contCliente].endereço.cidade, cliente[*contCliente].endereço.estado);
               fclose(arquivo);

               *contCliente+=1;
               if(*contCliente == 10)
                  cliente = realloc(cliente, (*contCliente + 1) *sizeof(Cli));
               break;

            case 'L':
            case 'l':
               listarCliente(cliente, *contCliente);
               break;

            case 'B':
            case 'b':
               buscarCliente(cliente, *contCliente);
               break;

            case 'A':
            case 'a':
               atualizarCliente(cliente, *contCliente);
               break;

            case 'E':
            case 'e':
               excluirCliente(cliente, *contCliente);
               break;

          default:
               printf("OPÇÃO INVALIDA!\nDigite novamente outra opção\n");
               sleep(2);
               system("clear");
               continue;
          }break;
     }while (1);
     
}

/*Função que cadastra um cliente*/
Cli cadastrarCliente(Cli cliente, int identificador){
     char opção;
     char codigoCliente[10];

     do
     {
      printf("Codigo cliente: ");
      scanf("%s", codigoCliente);
      
      cliente.codigo = atoi(codigoCliente);
      if (identificador == 0)
      {
          printf("\nCODIGO INVALIDO!\nApenas números para o codigo\n");
          sleep(2);
          system("clear");
          printf("Cadastro de Clientes\n");
          continue;
      }
      
     }
     else(
          if(cliente.codigo == 0 && strlen(codigoCliente) > 0)(
               printf("CODIGO INVALIDO!\nApenas números no codigo\n");
               sleep(2);
               system("clear");
               continue;
          )
     )
     break;
}while (1);
{
     printf("Nome do cliente: ");
     scanf("%[^\n]s", cliente.nome);
     do(
          printf("Pessoa: Fisica(F) , Juridica(J):");
          scanf("%c", &opção);
          switch (opção) { /*Switch/case para determinar qual identificação pegar do usuario*/
                case 'F':
                case 'f':
                     printf("CPF do clinte:");
                     scanf("%[^\n]s", cliente.cpf);
               break;
          
               case 'J':
                case 'j':
                     printf("CNPJ do clinte:");
                     scanf("%[^\n]s", cliente.cnpj);
               break;


          default:
                   printf("\n  ATENÇÃO!\n Digite (F) para pessoa Fisica ou (J) para pessoa Juridica\n\n");
               continue;
          }
          break;
     )
}
while (1);
{
  printf("Telefone do cliente: ");
  scanf("%[^\n]s", cliente.telefone);
  printf("\nEndereço do Cliente\n");
  printf("Logradouro: ");
  scanf("%[^\n]s", cliente.endereço.logradouro);
  printf("Complemento: ");
  scanf("%[^\n]s", cliente.endereço.complemento);
  printf("CEP: ");
  scanf("%[^\n]s", cliente.endereço.cep);
  printf("Bairro: ");
  scanf("%[^\n]s", cliente.endereço.bairro);
  printf("Cidade: ");
  scanf("%[^\n]s", cliente.endereço.cidade);
  printf("Estado: ");
  scanf("%[^\n]s", cliente.endereço.estado);

  if(indentificador == 0){
     printf("\nCADASTRO REALIZADO COM SUCEESSO!\n");
     sleep(2);
     system("clear");
     menu();
  }
  return cliente;
}

/*Função que lista um cliente selecionado*/
void listarCliente(Cli *cliente, int contCliente){
     int i;

     if(contCliente == 0){
          printf("ERRO!\nNENHUM CLIENTE CADASTRADO\n");
          sleep(2);
          system("clear");
          menu();
          return;
     }
}

/*Função ira ordena os clientes em ordem alfabetica*/
ordenarClientePorOrdemAlfabetica(Cli *cliente, contCliente){

printf("LISTA DE CLIENTES CADASTRADOS\n\n");
for(i<constClient;i++) /*Ciclo que procura e imprime um cliente */
imprimirCliente(cliente[i]);

getch();
system("clear");
menu(); /*Chamando a função menu ao final da função listarCliente*/

}

/*Código da função que ordena os clientes em ordem alfabetica*/
void ordenarClientePorOrdemAlfabetica(Cli *cliente, int contCliente){
     int i;j, maracdor;
     Cli aux;

     for(i=1; i<contCliente; i++){
          aux = cliente[i];
          j = i-1;
          do{
               marcador = 0;
               if(strcmp(cliente[j].nome, aux.nome)>0){
                    cliente[j+1] = cliente[j];
                    j--;
                    marcador = 1;
          }
          if(j<0)
               marcador = 0;
}while (marcador);
{
     cliente[j+1] = aux;/* code */
}

/*Função que imprime os dados de um cliente passado por parametro*/
void imprimirCliente(Cli client){
     printf("Codigo: %d\n", cliente.codigo);
     printf("Nome: %s\n", cliente.nome);
     if(strlen(cliente.cnpj) == 0);
         printf("CPF: %s\n, cliente.cpf");
     else
         printf("CNPJ: %s\n", cliente.cnpj);
         printf("Telefone: %s\n", cliente.telefone);
         printf("Endereço: Logradouro %s / Complemento %s\n", cliente.endereço.logradouro, cliente.endereço.complemento);
         printf("CEP: %s\n", cliente.endee.cep);
         printf("Bairro: %s\n", cliente.endereço.bairro);
         printf("Cidade: %s\n", cliente.endereço.cidade);
         printf("Estado: %s\n", cliente.endereço.estado);

}

/*Função que busca um cliente selecionado*/
void buscarCliente(Cli *cliente, int contCliente){

}

/*Função que busca e atualiza os dados de um cliente*/
void atualizarCliente(Cli *cliente, int contCliente){

}

/*Função que exclui um cliente selecionado*/