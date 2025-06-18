#include <string>
#include <vector>
#include <cmath>
#include "Cinema.cpp"


using namespace std;

class CinemaDataBase{
    private:
        vector <Cinema> allCinemas;

        vector <pair <string, vector <size_t>>> titleType; // tipos
        vector <pair <string, vector <size_t>>> genres; // generos
        vector <pair <int, vector <size_t>>> runtimeMinutes; // duração do filme
        vector <pair <double, vector <size_t>>> location; // localização
        vector <pair <double, vector <size_t>>> price; // preços
        vector <pair <string, vector <size_t>>> year; // anos

    public:

        long cinemaID_index(string cinemaID){
            int default_value = -1;
            int index;

            if(cinemaID.empty())
                return default_value;
        }

        void insertCinema(const string& line){
            Cinema cinema(line);
            allCinemas.push_back(cinema);
            unsigned indexVetBase = allCinemas.size()-1;
        }

        // function 4 
        vector <Cinema> distance(double x, double y, double radius){
            vector <Cinema> resultDistance;
            double d;

            for(const Cinema& c : allCinemas){
                d = calculateDistance(x,y, c.coordinateX, c.coordinateY);

                if(d <= radius)
                    resultDistance.push_back(c);
            }

            return resultDistance;
        }

        double calculateDistance(double x0, double y0, double x1, double y1){
            return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
        }

        // function 5
        vector <size_t> price(double price){
            vector <size_t> resultPrice;

            for(size_t i = 0; i < allCinemas.size(); i++){
                if(allCinemas[i].ticketPrice <= price)
                    resultPrice.push_back(i);
            }

            return resultPrice;
        }

};