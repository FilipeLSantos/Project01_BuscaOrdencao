#pragma once
#include <vector>
#include <utility>
#include <cmath>
#include "Cinema.hpp"
#include "FilmsDataBase.hpp"

using namespace std;

class Cinema_DataBase{
    private: 
        vector <Cinema> allCinemas; // todos os cinemas

        // Filtros
        vector <pair <Coordinate, vector <size_t>>> locationFilter; // localização
        vector <pair <double, vector<size_t>>> priceFilter; // preço do ingressos

    public:

        //armazenar cinemas
        void insertCinema(const string& line){
            Cinema Cinema(line);
            allCinemas.push_back(Cinema);

            // indice do vetor base, para usa nas estruturas de filtros
            unsigned cinemaIndex = allCinemas.size() - 1;

            addFilter(locationFilter, Cinema.point, cinemaIndex);
            addFilter(priceFilter, Cinema.ticketPrice, cinemaIndex);
        }

        // adiconar em filtros
        template <typename T>
        void addFilter(vector <pair<T, vector<size_t>>>& filter, const T& key, size_t index){
            for(auto &par : filter){
                if(par.first == key){
                    par.second.push_back(index);
                    return;
                }
            }

            filter.push_back({key, {index}});
        }

        // filter: location
        vector <Cinema> localization(Coordinate location, double radius){
            vector <Cinema> resultDistance;
            double d;

            for(const auto& par : locationFilter){
                d = calculateDistance(location, par.first);

                if(d <= radius){
                    for( size_t i : par.second)
                        resultDistance.push_back(allCinemas[i]);
                }

            }

            return resultDistance;
        }

        double calculateDistance(Coordinate point0, Coordinate point1){
            return sqrt(pow(point0.x - point1.x, 2) + pow(point0.y - point1.y, 2));
        }

        // filter: price
        vector <Cinema> price(double priceLimit){
            vector <Cinema> resultPrice;

            for(const auto& par : priceFilter){
                if(par.first <= priceLimit){
                    for(size_t i : par.second)
                        resultPrice.push_back(allCinemas[i]);
                }
            }

            return resultPrice;
        }

        // Combinação de FILTROS AND específicos de cinema
        vector<Cinema> filter_cinema_and(const vector<Cinema>& vec1, const vector<Cinema>& vec2){
            vector<Cinema> result;
            result.reserve(vec1.size() + vec2.size());

            size_t i = 0;
            size_t j = 0;

            while(i < vec1.size() && j < vec2.size()){
                if(vec1[i].cinemaID < vec2[2].cinemaID){
                    // como o push_back só é feito caso tenha match, caminha na lista
                    i++;
                }
                else if(vec2[j].cinemaID < vec1[i].cinemaID){
                    // como o push_back só é feito caso tenha match, caminha na lista
                    j++;
                }
                else{
                    // as duas strings são iguais lexicograficamente
                    // adiciona no result
                    if(result.empty() || result.back().cinemaID != vec1[i].cinemaID){
                        result.push_back(vec1[i]);
                    }
                }
            }
            
            // não é necessário percorrer o restante das lista, já que o interesse é a intersecção

        }

        // Combinação de FILTROS OR específicos de cinema
        vector<Cinema> filter_cinema_or(const vector<Cinema>& vec1, const vector<Cinema>& vec2){
            vector<Cinema> result;
            result.reserve(vec1.size() + vec2.size());

            size_t i = 0;
            size_t j = 0;

            while(i < vec1.size() && j < vec2.size()){
                if(vec1[i].cinemaID < vec2[2].cinemaID){
                    // adicinamos se valor é unico, diferente do antecessor
                    if(result.empty() || result.back().cinemaID != vec1[i].cinemaID){
                        result.push_back(vec1[i]);
                    }
                    i++;
                }
                else if(vec2[j].cinemaID < vec1[i].cinemaID){
                    // adicionamos se o valor é unico, diferente do antecessor
                    if(result.empty() || result.back().cinemaID != vec2[j].cinemaID){
                        result.push_back(vec2[j]);
                    }
                    j++;
                }
                else{
                    // as duas strings são iguais lexicograficamente
                    // adiciona no result se unico
                    if(result.empty() || result.back().cinemaID != vec1[i].cinemaID){
                        result.push_back(vec1[i]);
                    }
                }
            }

            // percorre os restantes da lista
            while(i < vec1.size()){
                if(result.empty() || result.back().cinemaID != vec1[i].cinemaID){
                    result.push_back(vec1[i]);
                }
                i++;
            }
            while(j < vec2.size()){
                if(result.empty() || result.back().cinemaID != vec2[j].cinemaID){
                        result.push_back(vec2[j]);
                }
                j++;
            }

        }

        // para os filtros que envolvem a busca de filmes basta interar os filmes contidos em cada cinema...
        // ... com os filmes do vetor de filtragem resultante
        // filtra os cinemas que possuem filmes já filtrados, pela filtragem específica de filmes, e os armazena
        // essa função considera que ambos os vetores, filtragem de filmes e cinemas, possuem os filmes ordenados
        vector<Cinema> cinemas_by_filtered_movies(vector<size_t>& movies_filtered_vec, vector<Cinema>& cinemas_filtered_vec){
            vector<Cinema> cinemas_with_matches;
            
            // Pra cada cinema no vetor de cinemas já filtrados pelos filtros específicos de cinemas
            for(Cinema cinema : cinemas_filtered_vec){
                size_t ptr_filme_cinema = 0;
                size_t ptr_filtrado = 0;
                bool filme_encontrado = false;

                // enquanto ambos os ponteiros estiverem dentro dos limites dos vetores de filmes (tanto filmes do cinema quanto filmes filtrados)
                while(ptr_filme_cinema < cinema.exibitionFilms.size() && ptr_filtrado < movies_filtered_vec.size()){
                    size_t movie_in_cinema = tconst_index(cinema.exibitionFilms[ptr_filme_cinema]);
                    size_t filtered_movie = movies_filtered_vec[ptr_filtrado];

                    if(movie_in_cinema == filtered_movie){
                        // Um match, encontramos um filme do cinema na base de filmes filtrados
                        filme_encontrado = true; 
                        break; // para de verificar esse cinema e vai para o práximo, já temos um cinema com PELO MENOS um filme do tipo filtrado

                    }
                    else if(movie_in_cinema < filtered_movie){
                        // o filme do cinema é menor, então avance o ponteiro do filme de cinema
                        ptr_filme_cinema++;
                    }else{
                        // o filme dos filmes filtrados é menor, avance o ponteiro do filme filtrado
                        ptr_filtrado++;
                    }

                }
                
                // o filme foi encontrado, este cinema entra nos cinemas que possuem tipo de filme que procuramos
                if(filme_encontrado){
                    cinemas_with_matches.push_back(cinema);
                }
            }

            return cinemas_with_matches;
        }

        // função auxiliar para transformar o tconst em int pos, em caso de tcosnt valido (%2==0)
        size_t tconst_index(string tcons){
            int default_value = -1;
            int index;
            
            if(tcons.empty()) return default_value;
            auto new_end = remove_if(tcons.begin(), tcons.end(), [](char c){!isdigit;});
            tcons.erase(new_end,tcons.end());

            index = stoi(tcons);
            if(index % 2 == 0){
                index = (index - 7917518)/2;
                return index;
            }else{
                return -1;
            }
            
        }

        /*
        // função posicional de cinema no vetor total
        size_t cinema_to_pos(string cinema_ID){
            int default_value = -1;
            int index;
            
            if(cinema_ID.empty()) return default_value;
            auto new_end = remove_if(cinema_ID.begin(), cinema_ID.end(), [](char c){!isdigit;});
            cinema_ID.erase(new_end,cinema_ID.end());

            index = stoi(cinema_ID);
            index =- 1;
            return index;
        }
        */

};