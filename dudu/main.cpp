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


class Grafo
{
    int vertices;
    vector<vector<int> > adj;
    vector<int> * ad;
    
public:
    Grafo();
    Grafo(int totalVertices);
    void addAresta (int v1, int v2);
    
    void BuscaProfundidade(int v);
    void DuduDFS(int v);
    void DuduDFS();
    
    void dfs(int v);
    
    void ListaVizinhos ();
};

Grafo::Grafo() {
    
}

Grafo::Grafo(int totalVertices) {
    cout << "Inicializando com: " << totalVertices << endl;
    this->vertices = totalVertices;
    
    ad = new vector<int>[totalVertices];
    
    for (int i = 0; i < totalVertices; i++) {
        adj.push_back(vector<int>()); // Add an empty row
    }
    
    vector< vector<int> > vec;
    for (int i = 0; i < 4; i++) {
        vec.push_back(vector<int>()); // Add an empty row
        for (int i = 0; i < vec.size(); i++) {
            vec[i].push_back(i); // Add column to all rows
        }
    }
}

void Grafo::addAresta(int v1, int v2) {
    cout << "linked " << v1 << " to " << v2 << endl;
    adj[v1].push_back(v2); // Add column to all rows
    ad[v1].push_back(v2);
}

void Grafo::dfs(int v)
{
    stack<int> pilha;
    bool visitados[vertices]; // vetor de visitados
    
    // marca todos como não visitados
    for(int i = 0; i < vertices; i++)
        visitados[i] = false;
    
    while(true)
    {
        if(!visitados[v])
        {
            cout << "Visitando vertice " << v << " ...\n";
            visitados[v] = true; // marca como visitado
            pilha.push(v); // insere "v" na pilha
        }
        
        bool achou = false;
        vector<int>::iterator it;
        
        // busca por um vizinho não visitado
        for(it = adj[v].begin(); it != adj[v].end(); it++)
        {
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
    bool visitados[vertices];
    
    for (int i = 0; i < vertices; i++) {
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
//            cout << "\t: " << *it << endl;
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
    bool visitados[vertices]; // vetor de visitados
    
    // marca todos como não visitados
    for(int i = 0; i < vertices; i++)
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
        path.append("/dudu/");
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
        
//        g.ListaVizinhos();
        g.DuduDFS();
        
        cout << endl;
    }
    
    
    
    // Grafo g;
    return 0;
}
