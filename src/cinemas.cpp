#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <list>

using namespace std;

class Cinema{
    private:
        string cinemaID;
        string nameCinema;
        double coordinateX, coordinateY;
        double ticketPrice;
        vector <string> exhibitionFilms;

    public: 

    // Construtor
    Cinema(const string& line){
        stringstream ss(line);
        string field;

        // CinemaID e nameCinema
        getline(ss, cinemaID, ',');
        getline(ss, nameCinema, ',');
        
        // coordinateX e coordinateY
        getline(ss, field, ',');
        coordinateX = stod(field);
        getline(ss, field, ',');
        coordinateY = stod(field);

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

    // Impressão de cada line
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

    // function 4
    list <Cinema> location(const list <Cinema>& cinema ,double radius, double coordinateX, double coordinateY){
        list <Cinema> result;
        double distance;

        for(const Cinema& c : cinema){
            distance = calculateDistance(coordinateX, coordinateY, c.coordinateX, c.coordinateY);

            if(distance <= radius)
                result.push_back(c);
        }

        return result;
    }

    double calculateDistance(double x0, double y0, double x1, double y1){
        return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
    }

    // function 5
    list <Cinema> price(const list <Cinema>& cinema, double price){
        list <Cinema> prices;

        for(const Cinema& c : cinema){
            if(c.ticketPrice <= price)
                prices.push_back(c);
        }

        return prices;
    }

    // function 6
    list <Cinema> year(const list <string>);

};
