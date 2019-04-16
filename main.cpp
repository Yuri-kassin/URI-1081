#include <cstdlib>
#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>


#define INF -1 // Não descoberto (desconexo).
#define NUL -2 // Orfão (raiz).
#define PRETO 0 // Descendentes já estão pretos ou não tem descendentes.
#define CINZA 1 // Descoberto.
#define BRANCO 2 // Não descoberto.


int *cor;
int *predescessor;
int *descoberta; // Tempo de descoberta
int *termino; // Tempo de término
int tempo; // "Relógio"
int *imprimido;

using namespace std;

vector<int> *g;
int aux = 0;
int ba = 0;


void DFS_visit(int vA)
{
    ba =1;
 //   cout<<vA<<" entrou"<<endl;
    aux++;
    int vB;
    vector<int>::iterator it;
    cor[vA] = CINZA; // Pinta de cinza o vértice que está sendo avaliado no momento, o que significa que ele acaba de ser descoberto.
    tempo++; // O tempo passa, uma vez que a chamada desta função representa o percorrimento de uma aresta (afastando-se da raiz).
    descoberta[vA] = tempo; // Guarda o tempo em que o vértice foi descoberto. Em outras palavras, guarda o tempo em que a busca em profundidade passa pelo vértice pela primeira vez.
//    if(!g[vA].empty()) {
//        for(int i=0;i<aux*2;i++){
//                cout<<" ";
//        }
//            cout<<vA<<"-"<<g[vA]<<endl;
//            g[vA].erase(g[vA].begin());
//
//    }

//        cout<<"caso do "<<vA<<": "<<endl;
//        for (it = g[vA].begin(); it != g[vA].end(); it++) {
//            cout<<*it<<endl;
//        }

//    cout<<"vA e"<<vA<<endl;
//        vector<int>::iterator a;
    for(it = g[vA].begin(); it!=g[vA].end(); it++) {

        vB = *it; // Recebe o valor para que o iterador está apontando
 //       cout<<"vb e "<<*it<<endl;
        for(int i=0;i<aux*2;i++){
            cout<<" ";
        }
        cout<<vA<<"-"<<vB;
        if(descoberta[vB]==INF && imprimido[vB] ==0)cout<<" pathR(G,"<<vB<<")";
        imprimido[vB] = 1;
        cout<<endl;
//        a = g[vA].begin();
//        cout<<"talvea seja deletado "<<*a<<endl;
        g[vA].erase(g[vA].begin());
        it--;

//        if(cor[vB] == BRANCO) {
//            for(int i=0;i<aux*2;i++){
//                cout<<" ";
//            }
//            if(*(it)==*(it-1)) cout
//            cout<<vA<<" tem tamanho "<<g[vA].size()<<endl;
//            cout<<vA<<"-"<<vB<<" pathR(G,"<<vB<<")"<<endl;

        predescessor[vB] = vA; // O predecessor do vértice adjacente se torna o vértice que está sendo avaliado pela função(vA).
          if(!g[vB].empty())DFS_visit(vB); // A função é chamada, recursivamente, para avaliar o vértice adjacente.
//        }
    }
    aux--;
    cor[vA] = PRETO; // Pinta de preto o vértice que está sendo avaliado pela função, já que todos os vértices descendentes dele já foram completamente avaliados (e também pintados de preto).
    termino[vA] = tempo; // Guarda o tempo em que todos os vértices descendentes daquele que está sendo avaliado (vA) são completamente avaliados (e também pintados de preto). Em outras palavras, guarda o tempo em que a busca em profundidade passa pelo vértice pela segunda vez.
    tempo++; // O tempo passa, uma vez que o fim desta função representa o percorrimento de uma aresta (aproximando-se da raiz).
}


void DFS(int numeroDeVertices, int raiz)
{
    // Alocação dinâmica
    cor = new int[numeroDeVertices];
    predescessor = new int[numeroDeVertices];
    descoberta = new int[numeroDeVertices];
    termino = new int[numeroDeVertices];
    imprimido = new int[numeroDeVertices];

    int vA;

    for(vA=0; vA < numeroDeVertices; vA++)
    { // Coloca os valores iniciais em todas as posições dos vetores cor, descoberta e predecessor.

        cor[vA] = BRANCO;
        descoberta[vA] = INF;
        predescessor[vA] = NUL;
        imprimido[vA] = 0;

    }

    tempo = -1;

    for(int i=0; i < numeroDeVertices-1; i++)
    {
        if(cor[i]==BRANCO) {
            if(ba == 1 && !g[i].empty())cout<</*"banana "<<i<<*/endl;
            DFS_visit(i);
        }

    }
}


int main()
{
    int T;
    cin>>T;
    for(int j=0; j<T; j++) {
        int N, M;
        vector<int>::iterator it;
        cin >> N >> M;
        g = new vector<int>[N + 1];
        int x, y;

        for (int i = 0; i < M; i++) {
            cin >> x >> y;
            g[x].push_back(y);
//            g[y].push_back(x);
        }
        for(int i = 0; i<N; i++) {
            if(!g[i].empty())sort(g[i].begin(),g[i].end());
//            cout<<"caso do "<<i<<": "<<endl;
//            for (it = g[i].begin(); it != g[i].end(); it++) {
//                cout<<*it<<endl;
//            }
        }

        cout<<"Caso "<<j+1<<":"<<endl;
        ba = 0;
        DFS(N + 1, 0); //primerio parâmetro = tamanho do grafo; lsegundo parâmetro = vértice inicial
        cout<<endl;

    }

    return 0;
}
