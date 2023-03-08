#include<iostream>
#include<queue>
#include <string>

using namespace std;

struct TipoProduto{
    char tipo;
    float percent;
};

struct Produto{
    int cod_produto;
    char tipo;
    float preco;
};

queue<TipoProduto> fila_tipo;

//função cadastra tipo
void cadastro_tipo(){
    TipoProduto novo_tipo; //criando uma variável do tipo que criamos lá em cima

    cout << "Cadastre o tipo do produto \n A, B ou C:" << endl;
    cin >> novo_tipo.tipo; //usando o novo tipo de dados criado, adicionamos o novo tipo na variável da nossa estrutura

    cout << "Digite o percentual do imposto:" << endl;
    cin >> novo_tipo.percent;   //fazendo o mesmo com o nosso percentual

    fila_tipo.push(novo_tipo);  //colocamos na nossa fila para o tipo esses dados que estão na nossa variável que recebe a nossa estrutura

    cout << "Tipo cadastrado com sucesso";
}

queue<Produto> fila_produto;

//função cadastro produto
void cadastro_produto(){
    Produto novo_produto; //criando uma variável do tipo que criamos lá em cima

    cout << "Digite um tipo para o produto: " << endl;
    cin >> novo_produto.tipo;  //usando o novo tipo de dados criado, adicionamos o novo tipo na variável da nossa estrutura

    //fazendo a verificação se o produto já está cadastrado
    bool tipo_encontrado = false;
    queue<TipoProduto> tipoTemp;    //criamos essa fila do tipo de dados criados lá em cima

    while(!fila_tipo.empty()){
        TipoProduto tipo_armazenado = fila_tipo.front(); //armazenamos a frente da nossa fila em uma variável do tipo 'TipoProduto'
        fila_tipo.pop();    //andando na fila

        //verificando se o tipo existente no sistema é igual ao tipo que você digitou para armazenar um novo produto
        if(tipo_armazenado.tipo == novo_produto.tipo){

            tipo_encontrado = true;
            novo_produto.preco = -tipo_armazenado.percent;  //adicionamos ao novo produto um preco usando o armazenamento do tipo que armazenamos antes
            break;
        }
        tipoTemp.push(tipo_armazenado); //colocamos na frente de nossa nova fila auxiliadora para o tipo do produto o nosso novo tipo armazenado
    }

    //E enquanto essa nova fila estiver cheia
    while(!tipoTemp.empty()){
        fila_tipo.push(tipoTemp.front());   //adicionamos na nossa fila de tipos a frente do tipo digitado pelo usuário para verificarmos
        tipoTemp.pop(); //e andamos com a fila
    }

    //Se não encontrarmos o tipo que o usuário digitou
    if(!tipo_encontrado){
        cout << "O tipo nao foi encontrado" << endl;
        return;
    }

    //dando um novo código ao novo produto que será cadastrado
    static int codigo = 1;
    novo_produto.cod_produto = codigo++;

    cout << "Digite o preco do produto: ";
    cin >> novo_produto.preco;  //armazenando o preço
    fila_produto.push(novo_produto); //esqueci de colocar o novo produto com o preço já armazenado na fila original OMG

    cout << "Produto cadastrado com sucesso!" << endl;
}

//função tras o preço
void preco_prod(){
    //verificando se a fila de produtos está vazia
    if(fila_produto.empty()){
        cout << "Fila esta vazia, adicione produtos nela" << endl;
        return;
    }


    int codigo;
    cout << "Digite o codigo do produto: " << endl;
    cin >> codigo;

    bool prod_encontrado = false;
    queue<Produto> prodTemp; //nova fila auxiliadora

    while(!fila_produto.empty()){
            //criamos uma variável que guarda o elemento da frente de nossa fila
        Produto produto_cadastro = fila_produto.front();
        fila_produto.pop();

        if(produto_cadastro.cod_produto == codigo){ //se o que a nossa variável recebe do tipo cod_produto da nossa estrutura for igual ao código digitado
            prod_encontrado = true;                 //nosso booleano se torna true

            //usando o percentual lá de cima para calcular o imposto no preco para depois mostrar o preço
            queue<TipoProduto> tiposTemp;
            bool tipo_encontrado = false;

            while(!fila_tipo.empty()){
                TipoProduto tipo_cadastro = fila_tipo.front();
                fila_tipo.pop();

                //verificando se o tipo já cadastrado anteriormente é igual ao tipo digitado para cadastrar o novo produto
                if(tipo_cadastro.tipo == produto_cadastro.tipo){
                    tipo_encontrado = true;
                    produto_cadastro.preco += tipo_cadastro.percent;    //calculo do preço com o percent incluso
                    break;
                }
                tiposTemp.push(tipo_cadastro);
            }
            while(!tiposTemp.empty()){
                    //adicionando a fila auxiliar à fila tipo original
                fila_tipo.push(tiposTemp.front());
                tiposTemp.pop();
            }

            cout << "Preco do produto = " << produto_cadastro.preco << endl;
            break;
        }
        prodTemp.push(produto_cadastro);
        }

            while(!prodTemp.empty()){
                fila_produto.push(prodTemp.front());
                prodTemp.pop();
            }

            if(!prod_encontrado){
                cout << "Produto não encontrado." << endl;
            }
        }

//função para excluir tipo
void excluir_tipo(){
    char tipo_excluir;

    cout << "Digite o tipo que deseja excluir: " << endl;
    cin >> tipo_excluir;

    queue<TipoProduto> tiposTemp; //criando uma fila auxiliadora

    while(!fila_tipo.empty()){
        if(fila_tipo.front().tipo == tipo_excluir){ //se o tipo que você deseja excluir for igual a um dos tipos já existentes na fila
                while(!fila_produto.empty()){
                    if(fila_produto.front().tipo == tipo_excluir){ //verifica se o tipo que você quer excluir já está com um produto
                        cout << "Nao sera possivel excluir um tipo que ja esta atribuido a um produto" << endl;
                        return;
                    }
                    fila_produto.pop();
                }
            }else{
                tiposTemp.push(fila_tipo.front());
            }
            fila_tipo.pop();
        }

        fila_tipo = tiposTemp;
        cout << "Tipo excluido com sucesso!" << endl;
}

int main()
{
     int op, prod;

    cout << "MENU" << endl;
    cout << "1- Cadastrar tipo do produto." << endl;
    cout << "2- Cadastrar produto." << endl;
    cout << "3- Consultar preco de um produto." << endl;
    cout << "4- Excluir tipo." << endl;
    cout << "5- Sair." << endl;

     do{
        cout << "\nEscolha uma opcao do menu: " << endl;
        cin >> op;

        switch(op){
            case 1:
                cadastro_tipo();
            break;

            case 2:
                cadastro_produto();
            break;

            case 3:
                preco_prod();

            break;

            case 4:
                excluir_tipo();
            break;

            case 5:
                cout << "Saindo...";
                return 0;
            break;

            default:
                cout << "Opcao invalida, tente novamente" << endl;
            }

    }while(op > 0 && op <= 5);

    return 0;
}

