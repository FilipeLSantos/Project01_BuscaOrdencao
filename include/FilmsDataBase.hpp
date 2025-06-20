#pragma once
#include <iostream>
#include <string>
#include "Films.hpp"
#include "Sorting.hpp"
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
        size_t tconst_to_index(string tcons){
            int default_value = -1;
            int index;
            
            if(tcons.empty()) return default_value;
            auto new_end = remove_if(tcons.begin(), tcons.end(), [](char c){!isdigit;});
            tcons.erase(new_end,tcons.end());

            index = stoi(tcons);
            index = (index - 7917518)/2;
            return index;
        }


        // funçoes auxiliares para armazenar as keys nas listas de bucketing
        // para armazenar os indices nas listas de string (title_type, genre_index)
        void add_to_string_vectors(vector<std::pair<string,std::vector<size_t>>>& index, const string& key, size_t filme_tconst){
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
                    key_found = true;
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
        void add_to_int_vectors(vector<std::pair<int,std::vector<size_t>>>& index, const int& key, size_t filme_tconst){
            if(key == -1) return;
            // essa função funciona similarmente a da string 
            bool key_found = false;
            // loop para iterar sobre cada pair no vetor de pairs
            for (auto& par_existente : index){   
                // verifica se a key int do pair é a mesma passada pelo param da função
                if(par_existente.first == key){
                    // empurra o tconst para o vetor mapeado nesse indice-key do vector index
                    par_existente.second.push_back(filme_tconst);
                    key_found = true;
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

        // função para ordenar os vetores de filtragem depois que todos os filme foram adicionados aos vetores de filtragem
        void finalize_setup(){
            
            // é possivel que a implementação dos vectores de string mudem para int usando um algoritmo de hash, como mapeamento direto

            // Ordena os pares de string, lexicograficamente, que permite uma busca ligeiramente mais rapida
            if(!title_typle_index.empty()){
                quickSort_to_String(title_typle_index,0,title_typle_index.size()-1);
            }
            if(!genre_index.empty()){
                quickSort_to_String(genre_index,0,genre_index.size()-1);
            }
            
            // Ordena os indexes de int pela chave do pair (index.first) para uso de busca binária
            if(!year_index.empty()){
                quickSort(year_index,0,year_index.size()-1);
            }
            if(!runtime_minutes_index.empty()){
                quickSort(runtime_minutes_index,0,runtime_minutes_index.size()-1);
            }
            

        }

        // função que retorna um filme baseado no tconst do mesmo
        const Filme* get_filme_by_tconst(string tconst_val) {
            size_t pos = tconst_to_index(tconst_val);
            if(pos >= 0){return &todos_filmes[pos];}
            else return nullptr;            
        }

    

    public: 
        // Filtro 1:
        // Filtra um ou mais titleTypes 
        // Efetivamente um OR de titleTypes
        vector<size_t> filter_by_titletyple(vector<string>& types){
            vector<size_t> result_indices;

            // retorna caso não haja filtragem em types
            if(types.empty()){
                return result_indices;
            }

            result_indices = binary_search_to_vector(title_typle_index, types[0]);
            
            // caso só haja um  filtro de types
            if(types.size() == 1){
                return result_indices;
            }

            for (size_t i = 1; i < types.size(); ++i){
                vector<size_t> current_type_indices = binary_search_to_vector(title_typle_index,types[i]);
                result_indices = merge_union_unique(result_indices, current_type_indices);
            }

            return result_indices;
        } // FIM do filtro 1

        // Filro 2:
        // Filtra um ou mais genres
        // Efetivamente um OR de genres
        vector<size_t> filter_by_genres_or(vector<string>& genres_list){
            vector<size_t> result_indices;

            // retorna caso não haja filtragem em genres
            if(genres_list.empty()){
                return result_indices;
            }

            result_indices = binary_search_to_vector(genre_index, genres_list[0]);
            
            // caso só haja um  filtro de genres
            if(genres_list.size() == 1){
                return result_indices;
            }

            for (size_t i = 1; i < genres_list.size(); ++i){
                vector<size_t> current_genre_indices = binary_search_to_vector(genre_index,genres_list[i]);
                result_indices = merge_union_unique(result_indices, current_genre_indices);
            }
            
            return result_indices;
        } // FIM de genres or
        
        // Filtra um e outros genres
        // Efetivamente um AND de genres
        vector<size_t> filter_by_genres_and(vector<string>& genres_list){
            vector<size_t> result_indices;
            if(genres_list.empty()) {
                for(size_t i=0;i< todos_filmes.size(); ++i){
                    result_indices.push_back(i);
                }
                return result_indices;
            }

            result_indices = binary_search_to_vector(genre_index, genres_list[0]);
            if(result_indices.empty()) return result_indices;

            for(size_t i = 0; i < genres_list.size(); i++){
                vector<size_t>current_genre_indices = binary_search_to_vector(genre_index,genres_list[0]);
                vector<size_t> intersection;
                for(size_t key_from_current : current_genre_indices){
                    if(binary_equal(result_indices, key_from_current)){
                        intersection.push_back(key_from_current);      
                    }
                }
                result_indices = intersection;
                if(result_indices.empty()) break;
            }
            return result_indices;
        }

        // Filtro 3:
        // filtragem por duração específica
        vector<size_t> filter_by_duration(int duration){
            return binary_search_to_vector(runtime_minutes_index,duration);
        }
        
        // filtragem por range (mix/max) limit the runtime
        vector<size_t> filter_by_duration_range(int min_duration, int max_duration)const{
            vector<size_t> result_indices;
            
            // encontra o primeiro pair a ser adicionado no vetor, acima de min
            int start = binary_search_for_pair(runtime_minutes_index,min_duration);

            // coleta todos os resultados a partir de start
            for (int i = start; i < runtime_minutes_index.size(); i++){
                const auto& pair = runtime_minutes_index[i];
            
                // verifica se o pair.first(duração) excede o max do intervalo
                // em caso positivo, quebra o loop e não adiciona ao vector
                if(pair.first > max_duration){
                    break;
                }

                result_indices = merge_union_unique(result_indices, pair.second);
                // Defunct: result_indices.insert(result_indices.end(),pair.second.begin(), pair.second.end());

            }

            /* Defunct:
            // após o loop deveremos ordenar o vector para manter as duplicatas adjacentes
            // preparação para a retirada das duplicatas com unico_e_redimensiona
            if(!result_indices.empty()){
                quickSort_size_t(result_indices,0,result_indices.size()-1);
                ordena_unico_e_redimensiona(result_indices);
            }
            */
            
            return result_indices;
        }

        // Filtro 4:
        // filtragem por ano especifico
        vector<size_t> filter_by_year(int year){
            return binary_search_to_vector(year_index,year);
        }
        
        // filtragem por range (mix/max) limit the year
        vector<size_t> filter_by_year_range(int min_year, int max_year)const{
            vector<size_t> result_indices;
            
            // encontra o primeiro pair a ser adicionado no vetor, acima de min
            int start = binary_search_for_pair(year_index,min_year);

            // coleta todos os resultados a partir de start
            for (int i = start; i < year_index.size(); i++){
                const auto& pair = year_index[i];
            
                // verifica se o pair.first(duração) excede o max do intervalo
                // em caso positivo, quebra o loop e não adiciona ao vector
                if(pair.first > max_year){
                    break;
                }
                result_indices = merge_union_unique(result_indices, pair.second);
                // Defunct: result_indices.insert(result_indices.end(),pair.second.begin(), pair.second.end());

            }

            /*Defunct:
            // após o loop deveremos ordenar o vector para manter as duplicatas adjacentes
            // preparação para a retirada das duplicatas com unico_e_redimensiona
            if(!result_indices.empty()){
                quickSort_size_t(result_indices,0,result_indices.size()-1);
                ordena_unico_e_redimensiona(result_indices);
            }
            */
            
            return result_indices;
        }

        // ###############################################################################################################
        // Agora, é a combinação de filtros e a query de filtragem
        // Para filtragem AND, recebe vetores de filtros especificos e realiza AND de filtragem
        vector<size_t> combine_filters_and(vector<vector<size_t>>& filter_results){
            // caso os filtros de AND sejam nulos ou nenhum
            // se a lista de filter_results é vazia, contudo, significa sem resultados
            if(filter_results.empty()) return {};

            // Caso o vetor de filtragem só possua um vetor filtrado, retorna ele mesmo
            if(filter_results.size() == 1){
                return filter_results[0];
            }

            vector<size_t> result_indices = filter_results[0];

            for(size_t i = 1; i < filter_results.size(); i++){
                vector<size_t>current_filter_indices = filter_results[i];
                vector<size_t> intersection;
                for(size_t key_from_current : current_filter_indices){
                    if(binary_equal(result_indices, key_from_current)){
                        intersection.push_back(key_from_current);      
                    }
                }
                result_indices = intersection;
                if(result_indices.empty()) break;
            }
            return result_indices;

        }

        // Para filtragem OR, recebe vetores de filtros especificos e realiza OR de filtragem
        vector<size_t> combine_filters_or(vector<vector<size_t>>& filter_results){
            //vetor de filtragem sem filtros
            vector<size_t> result_indices;
            if(filter_results.empty()) return result_indices;

            // caso o vetor de filtragem so possua um vetor filtrado, retorna ele mesmo
            if(filter_results.size()==1) return filter_results[0];

            // inicia o resultado com o primeiro vetor de filtragem
            result_indices = filter_results[0];

            // itera sobre o resto dos vetores de filtros
            for (size_t i = 1; i < filter_results.size(); i++){
                result_indices = merge_union_unique(result_indices, filter_results[i]); 
            }

            return result_indices;

        } // fim da funcçap


        // Para recever os objetos Filmes baseados nos indices
        vector<const Filme*> get_filmes_from_indices(const vector<size_t>& indices) const{
            vector<const Filme*> result_filmes;
            for(size_t indice : indices){
                if(indice < todos_filmes.size()){
                    result_filmes.push_back(&todos_filmes[indice]);
                }
            }

            return result_filmes;
        }
};