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
}

/*Código da função que gerencia os clientes*/
void gerenciaDeClientes(Cli *cliente, int *contCliente, FILE *arquivo){
}

/*Função que cadastra um cliente*/
Cli cadastrarCliente(Cli cliente, int identificador){
}

/*Função que lista um cliente selecionado*/
void listarCliente(Cli *cliente, int contCliente){
}

/*Código da função que ordena os clientes em ordem alfabetica*/
void ordenarClientePorOrdemAlfabetica(Cli *cliente, int contCliente){
}

