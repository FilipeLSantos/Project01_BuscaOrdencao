#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set> // para resultados de filtros combinados
using namespace std;

int string_to_int(const string& s){
    int default_val = -1;
    if( s == "\N" || s.empty()){
        return default_val;
    }
    try {
        return stoi(s); // converte string para int
    } catch(const invalid_argument& a){
        return default_val; // argumento invalido retorna -1
    } catch(const out_of_range& b){
        return default_val; // argumento grande demais para os bits de int, retorna -1
    }
    
}

class Filme{
    public:
        string tconst;
        string titleType;
        string primaryTitle;
        string originalTitle;
        bool isAdult; 
        int startYear;
        int endYear;
        int runtimeMinutes;
        vector<string> genres;

    // construtor de parsing da linha
    Filme(const string& linha){
        stringstream ss(linha);
        string campo;

        getline(ss,tconst,'\t');
        getline(ss,titleType,'\t');
        getline(ss,primaryTitle,'\t');
        getline(ss,originalTitle,'\t');

        getline(ss, campo, '\t');
        (string_to_int(campo)) ? isAdult = 1 : isAdult = 0;

        getline(ss,campo,'\t');
        startYear = string_to_int(campo);

        getline(ss,campo,'\t');
        endYear = string_to_int(campo);
        
        getline(ss,campo,'\t');
        runtimeMinutes = string_to_int(campo);
        
        getline(ss,campo,'\t');
        if(campo != "\\N" && !campo.empty()){
            stringstream genres_ss(campo);
            string genre_item;
            while(getline(genres_ss,genre_item,',')){
                if(!genre_item.empty()){
                    genres.push_back(genre_item);
                }
            }
        }
        
    }

    void imprimir() const{
        cout << "tconst" << tconst << ",Title: " << titleType
        << ",PrimaryTitle: " << primaryTitle << ",OriginalTitle: " << originalTitle
        << ", isAdult: " << isAdult << ",StartYear: " << ((startYear == -1) ? "N/A" : to_string(startYear))
        << ",endYear: " << ((endYear == -1)  ? "N/A" : to_string(endYear)) 
        << ",runtimeMinutes: " << ((runtimeMinutes == -1 ) ? "N/A" : to_string(runtimeMinutes));
        if(genres.empty()){
            cout << "N/A";
        }
        for(unsigned i=0;i<genres.size(); i++){
            cout << genres[i] << (i == genres.size() ? "" : ",");
        }
        
        cout << endl;
    }


};