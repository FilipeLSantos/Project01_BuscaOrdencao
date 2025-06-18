#pragma once
#include <iostream>
#include <string>
#include "Filme.hpp"
using namespace std;

class FilmeDatabase{
    public:

        // armazenamento primário de todos os filmes
        std::vector<Filme> todos_filmes;

        // para filtragem podemos utilizar com listas
        // em que cada index da lista armazena outra lista, já filtrada pela chave de interesse

        // para filtro de ano
        // bucketing cria uma forma de consultar um filme sem iterar sobre toda a lista de filmes
        std::vector<std::pair<int, std::vector<size_t>>> year_index;
        // int é o ano e vector<size_t> é a lista de indices de tconst(os filmes)
        
        // para filtro de runtime minutes
        // bucketing com binary search para filtragem, nos permite acessar o primeiro index...
        // ... dentro do intervalo que queremos (runtime>= min), e dai até o runtime <= max [O(logN)]
        std::vector<std::pair<int, std::vector<size_t>>> runtime_minutes_index;
        // int para o valor de runtime, vector<size_t> é a lista de tconst

        // para filtro de ano
        // bucketing também, porém haverá redundância com pesquisa de mais de um gênero
        // ** é preciso retirar a redundância no union set gerado do filtro
        std::vector<std::pair<string,std::vector<size_t>>> genre_index;
        // string é o genero e vector<size_t> é a lista de indices de tconst que possuem o gênero

        // para filtro de titulo
        // title type pode ser usado como chave para filtrar os elementos 
        std::vector<std::pair<string,std::vector<size_t>>> title_typle_index;
        // string é o titletype e vector<size_t> é a lista de indices the tconst

    public:
        
        // função de indexação do tcosnt no mapeamento direto
        long tconst_to_index(string tcons){
            int default_value = -1;
            int index;
            
            if(tcons.empty()) return default_value;
            auto new_end = remove_if(tcons.begin(), tcons.end(), [](char c){!isdigit;});
            tcons.erase(new_end,tcons.end());

            index = stoi(tcons);
            index = (index - 7917518)/2;
        }


        // funçoes auxiliares para armazenar as keys nas listas de bucketing
        // para armazenar os indices nas listas de string (title_type, genre_index)
        void add_to_string_vectors(vector<std::pair<string,std::vector<size_t>>> index, const string& key, size_t filme_tconst){
            if(key.empty() || key == "\\N") return;
            // auto = declaração de variável que permite que o compilador decifre qutomaticamente que tipo é a variavel
            // flag se acharmos uma key identica já no index de string 
            bool key_found = false;
            // loop para iterar sobre cada pair no vetor de pairs
            for (auto& par_existente : index){   
                // verifica se a key string do pair é a mesma passada pelo param da função
                if(par_existente.first == key){
                    // empurra o tconst para o vetor mapeado nesse indice key do vector index
                    par_existente.second.push_back(filme_tconst);
                    key_found = false;
                    break;
                }
            }
            // caso o loop finalize sem achar a key, inserimos o pair key/tconst no vector para mapear essa key
            if(!key_found){
                vector<size_t> new_vector; // cria novo vetor
                new_vector.push_back(filme_tconst); // empurra o tconst para o novo vetor
                pair<string,vector<size_t>> new_pair(key,new_vector); // cria o para string/vetor para mapear essa key(string)
                index.push_back(new_pair); // aqui empurramos o par key/tconst para o vetor que mapeia as chaves
            }
        }

        //para armazenar os indices nas listas de inteiros(year_index,runtime)
        void add_to_int_vectors(vector<std::pair<int,std::vector<size_t>>> index, const int& key, size_t filme_tconst){
            if(key == -1) return;
            // essa função funciona similarmente a da string 
            bool key_found = false;
            // loop para iterar sobre cada pair no vetor de pairs
            for (auto& par_existente : index){   
                // verifica se a key int do pair é a mesma passada pelo param da função
                if(par_existente.first == key){
                    // empurra o tconst para o vetor mapeado nesse indice-key do vector index
                    par_existente.second.push_back(filme_tconst);
                    key_found = false;
                    break;
                }
            }
            // caso o loop finalize sem achar a key, inserimos o pair key/tconst no vector para mapear essa key
            if(!key_found){
                vector<size_t> new_vector; // cria novo vetor
                new_vector.push_back(filme_tconst); // empurra o tconst para o novo vetor
                pair<int,vector<size_t>> new_pair(key,new_vector); // cria o pair int/vetor para mapear essa key(int)
                index.push_back(new_pair); // aqui empurramos o par key/tconst para o vetor que mapeia as chaves
            }
        }

    // funcões para inserir um filmes nas listas de filtro
    public:
    
        // funcão que recebe a linha, constroi o objeto filme e popula os indices
        void add_movie_from_line(const string& linha){
            
            // invoca o construtor de Filme
            Filme filme(linha);
            todos_filmes.push_back(filme);
            unsigned index_vetorbase = todos_filmes.size() - 1;
            
            // popula os indices de filtragem
            add_to_string_vectors(title_typle_index, filme.titleType, tconst_to_index(filme.tconst));
            for (const string& genre : filme.genres){
                add_to_string_vectors(genre_index, genre,tconst_to_index(filme.tconst));
            }
            add_to_int_vectors(year_index,filme.startYear,tconst_to_index(filme.tconst));
            add_to_int_vectors(runtime_minutes_index, filme.runtimeMinutes, tconst_to_index(filme.tconst));
            
        }

        // função para ordenar os vetores de filtragem
        



        // funções auxiliares de carregamentos dos indices tconst das listas de bucketing
        // para receber indices das listas de string
        std::set<size_t> get_indices_string_(const std::vector<std::pair<string,std::vector<size_t>>> index, const string& key){}

        // para receber indices das listas de int
        std::set<size_t> get_indices_int_(const vector<std::pair<int, std::vector<size_t>>> index, const string& key){}


        

};