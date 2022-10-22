#include <iostream>
#include <string>

using namespace std;

// 1 -  Fa�a uma fun��o que recebe uma certa medida e ajusta ela percentualmente
// entre dois valores m�nimo e m�ximo e retorna esse valor

int converteSensor(int medida, int minimo, int maximo)
{
    int ajuste;
    ajuste = ((medida - minimo) * 100)/(maximo - minimo);
    cout << ajuste << "\n";
    return ajuste;
}
// 2 - Fa�a uma fun��o que simule a leitura de um sensor lendo o
// valor do teclado ao final a fun��o retorna este valor
int leituraSensor()
{
    int valor;
    cout << "Sensor: " << "\n";
    cin >> valor;
    return valor;
}
// 3 - Fa�a uma fun��o que armazena uma medida inteira qualquer
// em um vetor fornecido. Note que como C n�o possui vetores
// nativos da linguagem, lembre-se que voc� precisa passar o
// valor m�ximo do vetor assim como a �ltima posi��o preenchida
// Evite tamb�m que, por acidente, um valor seja escrito em
// uma �rea de mem�ria fora do vetor

int armazenaVetor(int *ptr, int tamanhoVetor, int posicao, int medida) {

    *(ptr + posicao) = medida;
    if (posicao == tamanhoVetor-1) {
        return posicao;
    }
    return posicao + 1;

}

// 4 - Fa�a uma fun��o que recebe um vetor com 4 posi��es que cont�m
// o valor da dist�ncia de um pequeno rob� at� cada um dos seus 4 lados.
// A fun��o deve retornar duas informa��es: A primeira � a dire��o
// de maior dist�ncia ("Direita", "Esquerda", "Frente", "Tras") e a
// segunda � esta maior dist�ncia.
char* direcaoMenorCaminho(int posicao[])
{
    char* direcao[4] = {"Direita","Esquerda", "Frente", "Tras"};
    int index = 0;
    int maior_v = 0;
    for (int i=0; i < 4; i++){
        if (posicao[i] > maior_v){
            maior_v = posicao[i];
            index = i;
        }
    }

    return direcao[index];
}

// 5 - Fa�a uma fun��o que pergunta ao usu�rio se ele deseja continuar o mapeamento e
// retorna verdadeiro ou falso
bool leComando()
{
    char res;
    cout << "Deseja continuar?: (sim/nao) \n";
    cin >> res;
    if(tolower(res) == 'nao'){
        return 0;
    }
    else {
        return 1;
    }
}
// 6 - A fun��o abaixo (que est� incompleta) vai "dirigindo" virtualmente um rob�
// e atrav�s de 4 sensores em cada um dos 4 pontos do robo ("Direita", "Esquerda",
// "Frente", "Tras").
//      A cada passo, ele verifica as dist�ncias aos objetos e vai mapeando o terreno
// para uma movimenta��o futura.
//      Ele vai armazenando estas distancias em um vetor fornecido como par�metro
// e retorna a ultima posicao preenchida do vetor.
//      Esta fun��o deve ir lendo os 4 sensores at� que um comando de pare seja enviado
//
//      Para simular os sensores e os comandos de pare, use as fun��es j� constru�das
// nos �tens anteriores e em um looping cont�nuo at� que um pedido de parada seja
// enviado pelo usu�rio.
//
    //  Complete a fun��o com a chamada das fun��es j� criadas

int dirige(int *v,int maxv){
    int maxVetor = maxv;
    int *vetorMov = v;
    int posAtualVetor = 0;
    int dirigindo = 1;
    while(dirigindo){
        int medida = leituraSensor();
        medida = converteSensor(medida,0,830);
        posAtualVetor = armazenaVetor(medida, posAtualVetor, vetorMov);
        dirigindo = leComando();
    }
    return posAtualVetor;
}
// O trecho abaixo ir� utilizar as fun��es acima para ler os sensores e o movimento
// do rob� e no final percorrer o vetor e mostrar o movimento a cada dire��o baseado
// na maior dist�ncia a cada movimento
void percorre(int *v,int tamPercorrido){
    int *vetorMov = v;
    int maiorDir = 0;
    for(int i = 0; i< tamPercorrido; i+=4){
        // char *direcao = direcaoMenorCaminho(&(vetorMov[i]),&maiorDir);
        char *direcao = direcaoMenorCaminho(&(vetorMov[i], &maiorDir));
        cout << "Movimentando para %s distancia = %i\n" << direcao,maiorDir <<"\n";
    }
}
int main(int argc, char** argv) {
    int maxVetor = 100;
    int vetorMov[maxVetor*4];
    int posAtualVet = 0;
    posAtualVet = dirige(vetorMov,maxVetor);
    percorre(vetorMov,posAtualVet);
    return 0;
}
