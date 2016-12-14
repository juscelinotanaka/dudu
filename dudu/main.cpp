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

using namespace std;

class Documento {
    int id;
    vector<int> dependentes;
public:
    Documento(int id);
    
    bool AdicionarDependetes (Documento d);
    bool ChecarDependentes(vector<Documento> v);
    bool VectorContem(vector<int> v, int i);
};

Documento::Documento(int id) {
    this->id = id;
}

class Questao {
    int totalDocumentos;
    
public:
    vector<Documento> docs;
    Questao (int totalDocs);
    bool CriarDependencia (int de, int para);
};

Questao::Questao (int totalDocs) {
    this->totalDocumentos = totalDocs;
    for (int i = 0; i < totalDocs; i++) {
        Documento temp(i);
        docs.push_back(temp);
    }
}


bool Questao::CriarDependencia (int de, int para) {
    return this->docs[para].AdicionarDependetes(this->docs[de]);
}

bool Documento::AdicionarDependetes(Documento d) {
    if ( d.dependentes.size() > 0) {
        for (vector<int>::iterator it = d.dependentes.begin(); it != d.dependentes.end(); it++) {
            int other = *it;
            if(other == id){
                return false;
            }else{
                dependentes.push_back(other);
            }
        }
    }
    dependentes.push_back(d.id);
    
    return true;
}
bool Documento::ChecarDependentes(vector<Documento> v) {
    if ( dependentes.size() > 0) {
        for (vector<int>::iterator it = dependentes.begin(); it != dependentes.end(); it++) {
            int other = *it;
            if(VectorContem(v[other].dependentes, id)){
                return false;
            }
        }
    }
    return true;
}
bool Documento::VectorContem(vector<int> v, int n){
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        int other = *it;
        if(other == n){
            return true;
        }
    }
    return false;
}

int main (int argc, const char * argv[]) {
    int t, n, m;
    int a, b; // a depende de b
    
//    InitializeInput(argc, argv);
    
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        cin >> m;
        
        bool sim = true;
        
        Questao q(n);
        
        for (int j = 0; j < m; j++) {
            cin >> a >> b;
            a--;
            b--;
            if (q.CriarDependencia(a, b) == false) {
                sim = false;
//                break;
            }
        }
        
        if(sim){
            for (vector<Documento>::iterator it = q.docs.begin(); it != q.docs.end(); it++) {
                Documento other = *it;
                if(!other.ChecarDependentes(q.docs)){
                    sim = false;
                    break;
                }
            }
        }
        cout << (sim  ? "NAO" : "SIM") << endl;
    }
    
    return 0;
}
