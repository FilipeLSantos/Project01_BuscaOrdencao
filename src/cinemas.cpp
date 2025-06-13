#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

class Cinema{
    private:
        string cinemaID;
        string nameCinema;
        int coordinateX, coordinateY;
        double ticketPrice;
        vector <string> exhibitionFilms;

    public: 

    Cinema(const string& line){
        stringstream ss(line);
        string field;

        // CinemaID e nameCinema
        getline(ss, cinemaID, ',');
        getline(ss, nameCinema, ',');
        
        // coordinateX e coordinateY
        getline(ss, field, ',');
        coordinateX = stoi(field);
        getline(ss, field, ',');
        coordinateY = stoi(field);

        // ticketPrice
        getline(ss, field, ',');
        ticketPrice = stod(field);

        // exhibitionFilms
        while(getline(ss, field, ',')){
            if(!field.empty()){
                exhibitionFilms.push_back(field);
            }
        }
    }

    void imprimir() const {
        cout << "CinemaID: " << cinemaID
             << ", Nome: " << nameCinema
             << ", Coordenadas: (" << coordinateX << "," << coordinateY << ")"
             << ", Preço do Ingresso: R$" << ticketPrice
             << ", Filmes em Exibição: ";
        if(exhibitionFilms.empty()){
            cout << "Nenhum";
        }else{
            for(size_t i = 0; i < exhibitionFilms.size(); ++i) {
                cout << exhibitionFilms[i];

                if (i < exhibitionFilms.size() - 1)
                    cout << ", ";
            }
        }
        cout << endl;
    }

};
