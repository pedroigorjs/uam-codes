#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stddef.h>

typedef struct {
  char nome[30];
  unsigned int ano_nascimento;
  float montante_gastos_mes;
} Cliente;

typedef struct {
  Cliente *clientes;
  unsigned int qtde_clientes;
  unsigned int limite_pessoas;
} Clientes;

void criarLista(Clientes *pLista) {
  pLista->clientes = (Cliente *) malloc(10 * sizeof(Cliente));
  pLista->qtde_clientes = 0;
  pLista->limite_pessoas = 10;
}

Cliente criarCliente() {
  Cliente novo_cliente;

  fflush(stdin);
  printf("Nome do cliente: ");
  fflush(stdin);
  scanf("%s", novo_cliente.nome);
  printf("Ano de nascimento: ");
  fflush(stdin);
  scanf("%d", &novo_cliente.ano_nascimento);
  printf("Montante gasto no mês: ");
  fflush(stdin);
  scanf("%f", &novo_cliente.montante_gastos_mes);
  fflush(stdin);

  return novo_cliente;
}

void incluirCliente(Clientes *lista) {
  int i;
  
  printf("\nCadastrando Cliente Nº%d:\n", lista->qtde_clientes + 1);
  if(lista->qtde_clientes == lista->limite_pessoas) {
    lista->clientes = realloc(lista->clientes, (lista->limite_pessoas+10)*sizeof(Cliente));
    lista->limite_pessoas += 10;
    
    for(i = lista->qtde_clientes; i <= lista->qtde_clientes; i++) {
      Cliente novo_cliente = criarCliente();
      memcpy((lista->clientes+i), &novo_cliente, sizeof(Cliente));
      (lista->qtde_clientes)++;
    }
  }

  if(lista ->qtde_clientes == 0) {
    i = 0;
    Cliente novo_cliente = criarCliente();
    memcpy((lista->clientes+i), &novo_cliente, sizeof(Cliente));
    (lista->qtde_clientes)++;
  } else {
    i = lista->qtde_clientes;
    Cliente novo_cliente = criarCliente();
    memcpy((lista->clientes+i), &novo_cliente, sizeof(Cliente));
    (lista->qtde_clientes)++;
  }
}

void removerCliente(Clientes *lista) {
  int i;
  int posicao;

  printf("Nº do Cliente: ");
  fflush(stdin);
  scanf("%d", &posicao);
  posicao -= 1;

  if(lista->qtde_clientes == 0) {
    printf("Não há clientes cadastrados.");
  } else if(posicao >= lista ->qtde_clientes) {
    printf("Este cliente não existe.");
  } else {
    for(i = posicao; i < lista->qtde_clientes; i++) {
      memcpy((lista->clientes+i), (lista->clientes+i+1), sizeof(Cliente));
      (lista->qtde_clientes)--;
    }
  }
}

void listarCliente(Clientes *lista, int i) {
  printf("\n\nCliente Nº%d:\n", i + 1);
  printf("\nNome: %s", lista->clientes[i].nome);
  printf("\nNome: %d", lista->clientes[i].ano_nascimento);
  printf("\nNome: %.2f", lista->clientes[i].montante_gastos_mes);
}

void listarClientes(Clientes *lista) {
  for(int i = 0; i < lista->qtde_clientes; i++) {
    listarCliente(lista, i);
  }

  printf("\n\nClientes cadastrados: %d", lista->qtde_clientes);
}

void zerarMontantes(Clientes *lista) {
  for(int i = 0; i < lista->qtde_clientes; i++) {
    lista->clientes[i].montante_gastos_mes = 0;
  }
  printf("Todos os montantes foram zerados.");
}

void atualizarMontante(Clientes *lista) {
  int posicao;
  float montanteAtual;

  printf("\nNº do Cliente: ");
  fflush(stdin);
  scanf("%d", &posicao);

  if(posicao > lista->qtde_clientes || lista->qtde_clientes == 0) {
    printf("Cliente não cadastrado.");
  } else {
    printf("\nValor do montante a atualizar: ");
    fflush(stdin);
    scanf("%f", &montanteAtual);

    lista->clientes[posicao - 1].montante_gastos_mes = montanteAtual;
  }
}

void exibirMontante(Clientes *lista) {
  int posicao;

  printf("\nNº do Cliente: ");
  fflush(stdin);
  scanf("%d", &posicao);

  if(posicao > lista->qtde_clientes || lista->qtde_clientes == 0) {
    printf("Cliente não cadastrado.");
  } else {
    printf("Montante do Cliente Nº%d: %f", posicao, lista->clientes[posicao - 1].montante_gastos_mes);
  }
}

void menu(Clientes *lista) {
  int opcao;

  printf("\n\nMenu:\n[0] - Incluir Cliente\n[1] - Remover Cliente\n[2] - Atualizar montante do Cliente\n[3] - Zerar todos os montantes\n[4] - Cliente melhor comprador\n[5] - Exibir montante de um Cliente\n[6] - Listar Clientes\n\nEscolha uma Opção: ");

  fflush(stdin);
  scanf("%d", &opcao);

  if(opcao == 0) {
    incluirCliente(lista);
    menu(lista);
  } else if(opcao == 1) {
    removerCliente(lista);
    menu(lista);
  } else if(opcao == 2) {
    atualizarMontante(lista);
    menu(lista);
  } else if(opcao == 3) {
    zerarMontantes(lista);
    menu(lista);
  } else if(opcao == 5) {
    exibirMontante(lista);
    menu(lista);
  } else if(opcao == 6) {
    listarClientes(lista);
    menu(lista);
  }
}

int main() {
  setlocale(LC_ALL, "Portuguese");

  Clientes *lista_clientes;
  criarLista(lista_clientes);

  menu(lista_clientes);

  return 0;
}
  
