#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

//Variáveis globais
int i;
int qtd=0; //Contador de clientes

//Estrutura para armazenar informações do cliente
typedef struct{
    char nome[50];   //variável onde será armazenado nome do usuário
    int cpf, cep;   //variáveis onde serão armazenados CPF e CEP do usuário
    int id_pedido; //Novo campo para armazenar o ID do pedido associado ao cliente
}info;

//Estrutrura para armazenar informações do pedido
typedef struct Pedido{
    info cliente;
    int tipo;            //0. Bebida, 1. Pizza 25, 2. Pizza 30, 3. Pizza 45
    int sabor1, sabor2; //Índices dos sabores escolhidos
    int status;        //0: Pendente, 1: Concluído
    struct Pedido* prox;
}pedido;

pedido* frente = NULL;
pedido* atras = NULL;
int proximo_id_pedido = 1; //Variável para controlar a próxima identificação de pedido

//Opções de bebidas
char* bebidas[5] = {"Coca Cola", "Pepsi", "Guaraná Antarctica", "Coca Cola zero", "Kuat"};
//Opções de sabores de pizzas
char* sbr1_25[8] = {"3 Queijos\n       (molho, mussarela, requeijão, cheddar e orégano)\n", "Batata palha\n       (molho, mussarela, batata palha e orégano)\n", "Calabresa\n       (molho, mussarela, calabresa e orégano)\n", "Milho\n       (molho, mussarela, milho e orégano)\n", "Mista\n       (molho, mussarela, presunto e orégano)\n", "Marguerita\n       (molho, mussarela, tomate, manjericão e orégano)\n", "Mussarela\n       (molho, mussarela e orégano)\n", "Romeu e Julieta\n       (molho, mussarela e goiabada)\n"};
char* sbr2_25[8] = {"3 Queijos\n       (molho, mussarela, requeijão, cheddar e orégano)\n", "Batata palha\n       (molho, mussarela, batata palha e orégano)\n", "Calabresa\n       (molho, mussarela, calabresa e orégano)\n", "Milho\n       (molho, mussarela, milho e orégano)\n", "Mista\n       (molho, mussarela, presunto e orégano)\n", "Marguerita\n       (molho, mussarela, tomate, manjericão e orégano)\n", "Mussarela\n       (molho, mussarela e orégano)\n", "Romeu e Julieta\n       (molho, mussarela e goiabada)\n"};
char* sbr1_30[8] = {"5 Queijos\n       (molho, mussarela, requeijão, cheddar, provolone, gorgonzola e orégano)\n", "Bacon\n       (molho, mussarela, requeijão, bacon e orégano)\n", "Frango com Cheddar\n       (molho, mussarela, frango, cheddar e orégano)\n", "Portuguesa\n       (molho, mussarela, presunto, ovo, azeitona, cebola, pimentão e orégano)\n", "Vegetariana\n       (molho, mussarela, palmito, azeitona, manjericão e orégano)\n", "Prestígio(doce)\n       (chocolate e coco ralado)\n", "Brigadeiro(doce)\n       (chocolate e granulado)\n", "Banana com canela(doce)\n       (molho, mussarela, banana, leite condensado e canela)\n"};
char* sbr2_30[8] = {"5 Queijos\n       (molho, mussarela, requeijão, cheddar, provolone, gorgonzola e orégano)\n", "Bacon\n       (molho, mussarela, requeijão, bacon e orégano)\n", "Frango com Cheddar\n       (molho, mussarela, frango, cheddar e orégano)\n", "Portuguesa\n       (molho, mussarela, presunto, ovo, azeitona, cebola, pimentão e orégano)\n", "Vegetariana\n       (molho, mussarela, palmito, azeitona, manjericão e orégano)\n", "Prestígio(doce)\n       (chocolate e coco ralado)\n", "Brigadeiro(doce)\n       (chocolate e granulado)\n", "Banana com canela(doce)\n       (molho, mussarela, banana, leite condensado e canela)\n"};
char* sbr1_45[8] = {"Alteza\n       (molho, mussarela, atum, requeijão, cebola e orégano)\n", "Sertaneja\n       (molho, mussarela, carne seca, banana da terra, cebola e orégano)\n", "Super Caipira\n       (molho, mussarela, frango, milho, cheddar, requeijão, cebola e orégano)\n", "Calabresa Especial\n       (molho, mussarela, cebola, calabresa, requeijão, cheddar e orégano)\n", "Brasil\n       (molho, mussarela, bacon, cebola, requeijão, cheddar e orégano)\n", "Camarão com Gorgonzola\n       (molho, mussarela, camarão, gorgonzola e orégano)\n", "Crocante\n       (molho, mussarela, bacon, batata palha, cheddar e orégano)\n", "Clássica\n       (molho, mussarela, peito de peru, alho, champingnon, cebola e orégano)\n"};
char* sbr2_45[8] = {"Alteza\n       (molho, mussarela, atum, requeijão, cebola e orégano)\n", "Sertaneja\n       (molho, mussarela, carne seca, banana da terra, cebola e orégano)\n", "Super Caipira\n       (molho, mussarela, frango, milho, cheddar, requeijão, cebola e orégano)\n", "Calabresa Especial\n       (molho, mussarela, cebola, calabresa, requeijão, cheddar e orégano)\n", "Brasil\n       (molho, mussarela, bacon, cebola, requeijão, cheddar e orégano)\n", "Camarão com Gorgonzola\n       (molho, mussarela, camarão, gorgonzola e orégano)\n", "Crocante\n       (molho, mussarela, bacon, batata palha, cheddar e orégano)\n", "Clássica\n       (molho, mussarela, peito de peru, alho, champingnon, cebola e orégano)\n"};

//Função de inicializar fila de pedidos
void inicializarPizza(){
    frente = NULL;
    atras = NULL;
}

//Função para cadastrar e adicionar cliente a fila
void novoCadastro(){
	if(qtd==0){ //Condicional para que haja o primeiro cadastro
		system("cls");
		printf("=======================================================================================================================\n");
		printf("=================================> PRIMEIRO CADASTRO AINDA DISPONÍVEL - ESCOLHA A OPÇÃO 1 <============================\n");
		printf("=======================================================================================================================\n");
		sleep(3);
		system("cls");
	}
	else{ //Limpar fila para realizar novo cadastro
		while (filaVazia()!=1){
			desenfileirarPedido();
		}
	
    system("cls");
    printf("=======================================================================================================================\n");
    printf("===================================================> NOVO CADASTRO <===================================================\n");
    printf("=======================================================================================================================\n\n");
    cadastrar();    // Adiciona um novo cliente à fila
    fazerPedido(); // Permite que o cliente faça um pedido imediatamente após o cadastro
	}
}

//Função que verifica se há itens na fila
int filaVazia(){
    return frente == NULL; //Quando a fila estiver vazia o valor da 'frente' da fila será nulo
}

//Função que enfileira novo pedido assim que feito
void enfileirarPedido(info cliente, int tipo, int sabor1, int sabor2){
    pedido* novoPedido = (pedido*)malloc(sizeof(pedido));
    	if (novoPedido == NULL){ //Mensagem caso não consiga fazer alocação do novo pedido na memória
    		printf("=======================================================================================================================\n");
        	printf("========================================> ERRO AO ALOCAR MEMÓRIA PARA O PEDIDO <========================================\n");
        	printf("=======================================================================================================================\n");
        	exit(1);
    	}

    	novoPedido->cliente = cliente;
    	novoPedido->tipo = tipo;
    	novoPedido->sabor1 = sabor1;
    	novoPedido->sabor2 = sabor2;
    	novoPedido->status = 0; //Pedido inicialmente pendente
    	novoPedido->prox = NULL;

   		//Atribuir o ID do pedido associado ao cliente
    	novoPedido->cliente.id_pedido = proximo_id_pedido;

    if(filaVazia()){
        frente = novoPedido; //O novo pedido deve assumir a frente da fila, assim 'frente' deixará de ser nulo
    }
	else{
    	atras->prox = novoPedido; //Cria uma ligaçção do último elemento('atras') da fila ao novo elemento('novoPedido')
    }

    atras = novoPedido;
	
	sleep(1);
	system("cls");
	printf("=======================================================================================================================\n");
    printf("======================================> PEDIDO #%d ADICIONADO À FILA COM SUCESSO <======================================\n", proximo_id_pedido);
    printf("=======================================================================================================================\n");
    proximo_id_pedido++;
    sleep(3);
    system("cls");
}

//Função para retirar o primeiro pedido
void desenfileirarPedido(){
    if (filaVazia()){
    	printf("=======================================================================================================================\n");
        printf("============================================> A FILA DE PEDIDOS ESTÁ VAZIA <===========================================\n");
        printf("=======================================================================================================================\n");
		Sleep(2000);
        system("cls");
        return;
    }

    pedido* pedidoRemovido = frente;

    //Exibir informações do pedido antes de remover
    printf("=======================================================================================================================\n");
    printf("===================================================> REMOVENDO... <====================================================\n");
    printf("=======================================================================================================================\n");
    printf("======> PEDIDO #%d \n\n======> #DETALHES\n", pedidoRemovido->cliente.id_pedido);
	
    if(pedidoRemovido->tipo == 0){
        printf("======> Bebida: %s\n", bebidas[pedidoRemovido->sabor1]);
    }
	else{
        printf("======> Tipo de pizza (%d)\n", pedidoRemovido->tipo);
        printf("======> 1° Sabor: %s\n", 
            (pedidoRemovido->tipo == 1) ? sbr1_25[pedidoRemovido->sabor1] : 
            ((pedidoRemovido->tipo == 2) ? sbr1_30[pedidoRemovido->sabor1] : sbr1_45[pedidoRemovido->sabor1]));
        printf("======> 2° Sabor: %s\n", 
            (pedidoRemovido->tipo == 1) ? sbr2_25[pedidoRemovido->sabor2] : 
            ((pedidoRemovido->tipo == 2) ? sbr2_30[pedidoRemovido->sabor2] : sbr2_45[pedidoRemovido->sabor2]));
    }

    printf("======> Status: %s\n", (pedidoRemovido->status == 0) ? "Pendente" : "Concluído");
    printf("=======================================================================================================================\n");
    sleep(7);
    system("cls");

    frente = frente->prox;

    free(pedidoRemovido);
    printf("\n");
}
//Função para cadastrar novo cliente
void cadastrar(){
    info novoCliente;
    printf("======> NOME: ");
    fgets(novoCliente.nome, 50, stdin);
    fflush(stdin);
    printf("======> CPF: ");
    scanf("%d", &novoCliente.cpf);
    fflush(stdin);
    printf("======> CEP: ");
    scanf("%d", &novoCliente.cep);
    fflush(stdin);

    system("cls");

    enfileirarPedido(novoCliente, 0, 0, 0); //Adicionar pedido de bebida à fila automaticamente
    qtd++;
}

//Função para exibir cardápio com opções de bebidas
void cardapioBebidas(){
	printf("=======================================================================================================================\n");
    printf("=================================================> CARDÁPIO DE BEBIDAS <===============================================\n");
    printf("=======================================================================================================================\n\n");
    	for ( i = 0; i < 5; i++) {
        	printf("======>(%d) %s\n", i + 1, bebidas[i]);
    	}

    int escolhaBebida;
    
    printf("\n======> Escolha a bebida: ");
    scanf("%d", &escolhaBebida);
    fflush(stdin);

    enfileirarPedido(frente->cliente, 0, escolhaBebida - 1, 0);
}
//Função para exibir cardápio com opções de pizzas
void cardapioPizza(int tipo){
    char** sabor1;
    char** sabor2;
    int qtdSabores;

    switch(tipo){ //Definindo os cardápios e a quantidade de sabores com base no tipo de pizza
        case 1:
            sabor1 = sbr1_25;
            sabor2 = sbr2_25;
            qtdSabores = 8;
            break;
        case 2:
            sabor1 = sbr1_30;
            sabor2 = sbr2_30;
            qtdSabores = 8;
            break;
        case 3:
            sabor1 = sbr1_45;
            sabor2 = sbr2_45;
            qtdSabores = 8;
            break;
        default:
            return;
    }
    
    //Mostrando o cardápio com os 1° sabores
	printf("=======================================================================================================================\n");
    printf("===============================================> CARDÁPIO %d - SABOR 1 <================================================\n", tipo);
    printf("=======================================================================================================================\n\n");
    
    for(i = 0; i < qtdSabores; i++){
        printf("======>(%d) %s\n", i + 1, sabor1[i]);
    }

    int escolhaSabor1;
    printf("\n======> OPÇÃO: ");
    scanf("%d", &escolhaSabor1);
    fflush(stdin);

    system("cls"); //Limpar tela pra melhorar visualização dos sabores do cardápio com o 2° sabor
    
    //Cardápio com o 2° sabor da pizza
    printf("=======================================================================================================================\n");
    printf("===============================================> CARDÁPIO %d - SABOR 2 <================================================\n", tipo);
    printf("=======================================================================================================================\n\n");
    	for(i = 0; i < qtdSabores; i++){
        	printf("======>(%d) %s\n", i + 1, sabor2[i]);
    	}

    int escolhaSabor2;
    
    printf("\n======> OPÇÃO: ");
    scanf("%d", &escolhaSabor2);
    fflush(stdin); //Limpar buffer
    enfileirarPedido(frente->cliente, tipo, escolhaSabor1 - 1, escolhaSabor2 - 1);
}

//Função para realizar pedido seja ele de pizzas ou bebidas
void fazerPedido(){
    system("cls");
    
    	if(qtd > 0){ //Mensagem de boas-vindas para clientes que já fizeram cadastro
    		printf("=======================================================================================================================\n");
        	printf("====================================================> FAZER PEDIDO <===================================================\n");
        	printf("=======================================================================================================================\n\n");
        	printf("======>(0) Bebida\n");
        	printf("======>(1) Pizzas Comum (R$ 25,00 - 8 fatias, 2 sabores)\n");
        	printf("======>(2) Pizzas da Casa (R$ 30,00 - 8 fatias, 2 sabores)\n");
        	printf("======>(3) Pizzas Especiais (R$ 45,00 - 8 fatias, 2 sabores)\n");
        
        	int escolhaTipoPedido;
        
        	printf("\n======> Escolha o tipo de pedido: ");
        	scanf("%d", &escolhaTipoPedido);
        	fflush(stdin);

        		switch(escolhaTipoPedido){
            		case 0:
                		system("cls");
                		cardapioBebidas(); //Chama a função do cardápio de bebidas
                	break;
            		case 1:
            		case 2:
            		case 3:
                		system("cls");
                		cardapioPizza(escolhaTipoPedido); //Chama a função do cardápio das pizzas que contem os cardápios das pizzas de R$ 25,00, R$ 30,00 E R$ 45,00
                	break;
            		default:
            			system("cls");
            			printf("=======================================================================================================================\n");
                		printf("==================================================> OPÇÃO INVÁLIDA! <==================================================\n");
                		printf("=======================================================================================================================\n");
                		sleep(4);
                		system("cls");
					break;
        		}
    	}
		else{
			printf("=======================================================================================================================\n");
    	    printf("====================================================> CADASTRO <=======================================================\n");
    	    printf("=======================================================================================================================\n\n");
    	    cadastrar(); //Adiciona um novo cliente à fila
    	    fazerPedido(); //Permite que o cliente faça um pedido imediatamente após o cadastro
    	}
}

//Função que chama a função de desenfileirar para realizar a retirada do pedido
void retirarPedidos(){
        desenfileirarPedido();
}

//Função para exibir pedidos realizados anteriormente
void meusPedidos(){
	system("cls");
		if(filaVazia()){
			printf("=======================================================================================================================\n");
			printf("==============================================> VOCÊ NÃO POSSUI PEDIDOS <==============================================\n");
			printf("=======================================================================================================================\n");
    		sleep(5);
    		system("cls");
			return;
		}
		pedido* temp = frente; //Inicializa temp com o endereço do primeiro pedido
		printf("====================================================> MEUS PEDIDOS <====================================================\n");
			while (temp != NULL){ //Enquanto temp não atingir o final da fila
        	//Exibe informações do pedido
    			printf("======> PEDIDO #%d:\n", temp->cliente.id_pedido);
    				if(temp->tipo == 0){
        printf("\n======> Bebida: %s\n", bebidas[temp->sabor1]);
    				}
					else{
        				printf("\n======> Tipo de Pizza (%d)\n", temp->tipo);
        				printf("======> 1° Sabor: %s\n", (temp->tipo == 1) ? sbr1_25[temp->sabor1] : ((temp->tipo == 2) ? sbr1_30[temp->sabor1] : sbr1_45[temp->sabor1]));
        				printf("======> 2° Sabor: %s\n", (temp->tipo == 1) ? sbr2_25[temp->sabor2] : ((temp->tipo == 2) ? sbr2_30[temp->sabor2] : sbr2_45[temp->sabor2]));
    				}

    				printf("======> Status: %s\n", (temp->status == 0) ? "Pendente" : "Concluído");
    				printf("========================================================================================================================");

    				temp = temp->prox; //Avança temp para o próximo pedido na fila
  					printf("\n");
			}
			sleep(7);
			system("cls");

}

//Função principal que apresentação do menu 
void menu(){
	int escolha;
	
		while(1){
			printf("=======================================================================================================================");
			printf("\n==============================================> SEJA BEM-VINDO A PIZZARIA <============================================");
			printf("\n=======================================================================================================================");

			
				if(qtd==0){ //Cao nenhum pedido tenha sido feito, ele dará uma Coca Cola gratis para o primeiro usuário cadastrado
					printf("\n\n===================> PROMOÇÃO COCA 10%% DE DESCONTO, CASO NÃO QUEIRA BASTA RETIRAR DA FILA NA OPÇÃO <===================");
					printf("\n=============================>'RETIRAR O PRIMEIRO PEDIDO DA FILA ÁPOS O CADASTRO <=====================================");	
				}
				printf("\n\n======>(1) Fazer cadastro\n======>(2) Cardápio\n======>(3) Meus pedidos\n======>(4) Novo cadastro (Adicionar uma nova fila de pedidos)\n");
				printf("======>(5) Retirar o primeiro pedido da fila\n======>(6) Sair\n\n======> Digite a opção: ");
				scanf("%d", &escolha);
				fflush(stdin);
				system("cls");
				
    				switch (escolha){ //Chamando a variável escolha que vai chamar a função escolhida pelo usuário
        				case 1:
           					fazerPedido();
            				qtd++;
            			break;
        				case 2:
            				fazerPedido();
            			break;
        				case 3:
            				meusPedidos();
            			break;
        				case 4:
        					novoCadastro(); 
        				break;
        				case 5:
            				retirarPedidos();
            			break;
         				case 6: //Caso o usuário tenha escolhido sair do programa
         					printf("=======================================================================================================================\n");
		  					printf("==============================================> ATÉ MAIS! VOLTE SEMPRE <=============================================\n");
		  					printf("=======================================================================================================================\n");
		  					sleep(1);
            				exit(0);  
		  				break;
        				default: //Caso o usuário tenha tentado realizar uma função que não esteja entre as opções
        					printf("=======================================================================================================================\n");
            				printf("==========================================> OPÇÃO INVÁLIDA! TENTE NOVAMENTE <==========================================\n");
            				printf("=======================================================================================================================\n");
            				sleep(4);
            				system("cls");
    				}
		}
}

//Função principal do programa que chama as funções de inicialização dos pedidos de pizzas, o 'setlocale' permitindo o uso da norma padrão do português brasileiro e chamando o menu
int main(){
	inicializarPizza();
	setlocale(LC_ALL, "portuguese");
	menu();
}
