#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

struct Coordinate{
    double x, y;
};

class Cinema{
    private:
        string cinemaID;
        string nameCinema;
        Coordinate point;
        double ticketPrice;
        vector <string> exibitionFilms;

    public:
        // leitura do arquivo
        Cinema(const string& line){
            stringstream ss(line);
            string field;

            // CinemaID e nameCinema
            getline(ss, cinemaID, ',');
            getline(ss, nameCinema, ',');

            // Coordinate point
            getline(ss, field, ',');
            point.x = stod(field);
            getline(ss, field, ',');
            point.y = stod(field);

            // ticketPrice
            getline(ss, field, ',');
            ticketPrice = stod(field);

            // exibitionFilms
            while(getline(ss, field, ',')){
                if(!field.empty())
                    exibitionFilms.push_back(field);
            }
        }

        // Impressão
        void print() const{
            cout << "Cinema ID: " << cinemaID
                << "Nome: " << nameCinema
                << "Cordenadas [" << point.x  << ", " << point.y << "]"
                << "Preço do Ingresso: R$ " << ticketPrice
                << "Filmes em exibição: { ";

            if(exibitionFilms.empty())
                cout << "Nenhum fileme em cartaz !";
            else{
                for(int i = 0; i < exibitionFilms.size(); i++){
                    cout << exibitionFilms[i];

                    if(i < exibitionFilms.size()-1)
                        cout << ", ";
                }
            }
            cout << " }";
        }
        
};