//
//  main.cpp
//  dudu
//
//  Created by Juscelino Tanaka on 12/6/16.
//  Copyright © 2016 Juscelino Tanaka. All rights reserved.
//

#include <iostream>
#include <vector>
#include <list>
#include <algorithm> // função find
#include <stack> // pilha para usar na DFS

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#define GetCurrentDir getcwd

using namespace std;

typedef enum : int {
    NaoVisitado,
    Visitando,
    Concluido,
} TColor;

typedef struct {
    int value;
    int start, end;
    TColor color;
} TNode;

bool sim = true;

class Grafo
{
    int totalVertices;
    
    vector<TNode> vertice;
    
    vector<vector<int> > adj;
    
    vector<vector<TNode> > adjs;
    
public:
    Grafo();
    Grafo(int totalVertices);
    void addAresta (int v1, int v2);
    
    void BuscaProfundidade(int v);
    void DuduDFS(int v);
    void DuduDFS();
    
    void dfs(int v);
    
    void ListaVizinhos ();
    
    void DAG (int v);
};

Grafo::Grafo() {
    
}

int tempo = 0;

Grafo::Grafo(int totalVertices) {
    this->totalVertices = totalVertices;
    
    for (int i = 0; i < totalVertices; i++) {
        adj.push_back(vector<int>()); // Add an empty row
        adjs.push_back(vector<TNode>());
        
        TNode temp;
        temp.color = NaoVisitado;
        temp.value = i;
        temp.end = 0;
        vertice.push_back(temp);
    }
}

void Grafo::addAresta(int v1, int v2) {
    adj[v1].push_back(v2); // Add column to all rows
    
    adjs[v1].push_back(vertice[v2]);
}


//https://davidng94.wordpress.com/2015/11/03/uri-online-judge-1610-dudu-service-maker/
bool depthFirstBreadth(int vertex) {
    status[vertex] = VISITED;
    
    // cout << "Vertex: " << vertex << endl;
    // cout << "Adjacents Size: " << adjacentsTable[vertex].size() << endl;
    
    for(int index=0; index<adjacentsTable[vertex].size(); index++) {
        int adjacentVertex = adjacentsTable[vertex][index];
        
        // cout << "Adjacents Vertex: " << adjacentsTable[vertex][index] << endl;
        // cout << "Adjacents Vertex Status: " << status[adjacentVertex] << endl << endl;
        
        if(status[adjacentVertex] == NOT_VISITED) {
            if(!depthFirstBreadth(adjacentVertex)) {
                return false;
            }
        } else if(status[adjacentVertex] == VISITED) {
            return false;
        }
    }
    
    status[vertex] = FINISHED;
    return true;
}


bool Grafo::DAG (int v) {
    if (vertice[v].color == Concluido)
        return false;
    
    vertice[v].start = tempo++;
    vertice[v].color = Visitando;
    
    for (vector<TNode>::iterator neighbours = adjs[v].begin() ; neighbours != adjs[v].end(); neighbours++) {
        if (vertice[neighbours->value].color == NaoVisitado) {
            DAG(neighbours->value);
        }
        else if (vertice[neighbours->value].color == Visitando) {
            if (vertice[neighbours->value].end == 0) {
                //                cout << "loop de " << v << " para " << neighbours->value << endl;
                sim = false;
            }
        }
    }
    
    vertice[v].end = tempo++;
    vertice[v].color = Concluido;
    
}

void Grafo::dfs(int v)
{
    stack<int> pilha;
    bool visitados[totalVertices]; // vetor de visitados
    int tempo = 0;
    
    // marca todos como não visitados
    for(int i = 0; i < totalVertices; i++)
        visitados[i] = false;
    
    while(true)
    {
        vector<TNode>::iterator it;
        
        if(!visitados[v])
        {
            tempo++;
            cout << "Visitando vertice " << v << " ...\n";
            visitados[v] = true; // marca como visitado
            pilha.push(v); // insere "v" na pilha
        }
        
        bool achou = false;
        
        // busca por um vizinho não visitado
        for(it = adjs[v].begin(); it != adjs[v].end(); it++)
        {
            if(!visitados[it->value])
            {
                achou = true;
                break;
            }
        }
        
        if(achou) {
            v = it->value; // atualiza o "v"
        } else
        {
            // se todos os vizinhos estão visitados ou não existem vizinhos
            // remove da pilha
            pilha.pop();
            // se a pilha ficar vazia, então terminou a busca
            if(pilha.empty())
                break;
            // se chegou aqui, é porque pode pegar elemento do topo
            v = pilha.top();
        }
    }
}


void Grafo::DuduDFS (int v) {
    stack<int> pilha;
    bool visitados[totalVertices];
    
    for (int i = 0; i < totalVertices; i++) {
        visitados[i] = false;
    }
    
    do {
        if (!visitados[v]) {
            cout << "Visitando: " << v << endl;
            visitados[v] = true;
            pilha.push(v);
        }
        
        bool achou = false;
        vector<int>::iterator it;
        
        for(it = adj[v].begin(); it != adj[v].end(); it++)
        {
            if(!visitados[*it])
            {
                achou = true;
                break;
            }
        }
        
        if(achou) {
            v = *it; // atualiza o "v"
        }
        else
        {
            // se todos os vizinhos estão visitados ou não existem vizinhos
            // remove da pilha
            pilha.pop();
            // se a pilha ficar vazia, então terminou a busca
            if(pilha.empty())
                break;
            // se chegou aqui, é porque pode pegar elemento do topo
            v = pilha.top();
        }
        
    } while (!pilha.empty());
}


void Grafo::DuduDFS () {
    stack<int> pilha;
    bool visitados[totalVertices]; // vetor de visitados
    
    // marca todos como não visitados
    for(int i = 0; i < totalVertices; i++)
        visitados[i] = false;
    
    for (int i = 0; i < adj.size(); i++) {
        if (visitados[i])
            continue;
        
        int v = i;
        
        do {
            if(!visitados[v])
            {
                cout << "Visitando vertice " << v << " ...\n";
                visitados[v] = true; // marca como visitado
                pilha.push(v); // insere "v" na pilha
            } else {
                cout << "Ja visitado: " << v << endl;
            }
            
            bool achou = false;
            vector<int>::iterator it;
            
            // busca por um vizinho não visitado
            for(it = adj[v].begin(); it != adj[v].end(); it++)
            {
                // it - lista de vizinhos
                if(!visitados[*it])
                {
                    achou = true;
                    break;
                }
            }
            
            if(achou)
                v = *it; // atualiza o "v"
            else
            {
                cout << "nao achou para: " << v << endl;
                // se todos os vizinhos estão visitados ou não existem vizinhos
                // remove da pilha
                pilha.pop();
                // se a pilha ficar vazia, então terminou a busca
                if(pilha.empty())
                    break;
                // se chegou aqui, é porque pode pegar elemento do topo
                v = pilha.top();
            }
        } while (!pilha.empty());
        
        cout << endl;
    }
}

void Grafo::ListaVizinhos () {
    
    for (int i = 0; i < adj.size(); i++) {
        cout << "Parentes de " << i << ": ";
        for (vector<int>::iterator it = adj[i].begin(); it != adj[i].end(); it++ ) {
            cout << *it << ", ";
        }
        cout << endl;
    }
}

int InitializeInput (int argc, const char * argv[]) {
    if (argc > 1)
    {
        char cCurrentPath[FILENAME_MAX];
        
        if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
        {
            return errno;
        }
        
        cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
        
        string path(cCurrentPath);
        path.append("/");
        path.append(argv[1]);
        
        FILE * fp = freopen(path.c_str(), "r", stdin);
        if (fp == NULL)
        {
            perror(argv[1]);
            exit(1);
        }
    }
    
    return 0;
}


int main (int argc, const char * argv[]) {
    int t, n, m;
    int a, b; // a depende de b
    
    Grafo g;
    
    InitializeInput(argc, argv);
    
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        cin >> m;
        
        g = Grafo(n);
        
        for (int j = 0; j < m; j++) {
            cin >> a >> b;
            a--;
            b--;
            g.addAresta(a, b);
        }
        
        for (int i = 0; i < n; i++) {
            g.DAG(i);
        }
        
        cout << (sim  ? "NAO" : "SIM") << endl;
    }
    
    
    // Grafo g;
    return 0;
}
