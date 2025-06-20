#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Filter{
    string field, value, operators;
};

vector <string> split(const string& s, char delimiter){
    vector <string> tokens;
    string token;
    istringstream tokenStream(s);

    while(getline(tokenStream, token, delimiter))
        tokens.push_back(token);
    
    return tokens;
}

void parseLine(const string& line, vector<Filter>& filters, vector <string>& logics){
    istringstream iss(line);
    string token;

    while(iss >> token){
        if(token == "E" || token == "OU"){
            logics.push_back(token);
        }else{
            string field, operators, value;

            size_t posOp = token.find("<=");
            if(posOp != string::npos){
                field = token.substr(0, posOp);
                operators =  "<=";
                value = token.substr(posOp+2);
            }else if((posOp = token.find("=")) != string::npos){
                field = token.substr(0, posOp);
                operators = "=";
                value = token.substr(posOp+1);
            }

            filters.push_back({field, value, operators});
        }

    }
}

int main (){
    string line;
    cout << "Digite os filtros (ex: genero=Comedy OU preco<=15 E localizacao=20019,510301,1000):\n";
    getline(cin, line);

    vector<Filter> filters;
    vector<string> logics;

    parseLine(line, filters, logics);

    for (size_t i = 0; i < filters.size(); ++i) {
        cout << "Filtro: " << filters[i].field << " " << filters[i].operators << " " << filters[i].value << endl;
        if (i < logics.size())
            cout << "Operador logico: " << logics[i] << endl;
    }

    return 0;
}

