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

        getline(ss, cinemaID, ',');
        getline(ss, nameCinema, ',');
        
        getline(ss, field,',');
        coordinateX = stoi(field);

        getline(ss, field,',');
        coordinateY = stoi(field);

        getline(ss, field,',');
        ticketPrice = stod(field);

        


    }


};
