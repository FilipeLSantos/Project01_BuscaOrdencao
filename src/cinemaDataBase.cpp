#include <vector>
#include <utility>
#include "Cinema.cpp"

using namespace std;

class Cinema_DataBase{
    private: 
        vector <Cinema> allCinemas; // todos os cinemas

        // Filtros
        vector <pair <Coordinate, vector <size_t>>> location; // localização
        vector <pair <double, vector<size_t>>> price; // preço do ingressos

    public:


};