#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
using namespace std;

// quicksort para vetores inteiros tradicionais
// serão usados para retirar duplicatas no vector result dos filtros
int partition_size_t(vector<size_t>& vec, int low, int high){
    size_t pivot = vec[high];
    int i = (low - 1);
    for(int j = low; j <high; j++){
        if(vec[j]<pivot){
            i++;
            swap(vec[i],vec[j]);
        }

    }
    swap(vec[i+1], vec[high]);
    return i + 1;

}

void quickSort_size_t(vector<size_t>& vec, int low,int high){
    if(low < high){
        int randomIndex = low + rand() % (high - low +1);
        swap(vec[randomIndex],vec[high]);
        int pi = partition_size_t(vec, low, high);

        quickSort_size_t(vec,low,pi -1);
        quickSort_size_t(vec,pi+1,high);
    }
}

// quick sort para o vector de pairs inteiros
int partition(vector<pair<int,vector<size_t>>>& vec, int low, int high){
    int pivot = vec[high].first; // pivo sendo a maior key do vetor de pairs
    int i = (low-1); // index do menor elemento, centro

    for (int j = low; j < high; j ++){
        // se o primeiro elemento é menor que o pivot
        if(vec[j].first < pivot){
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return i+1; 
}

void quickSort(vector<pair<int,vector<size_t>>>& vec, int low, int high){
    if(low < high){
    
        int randomIndex = low + rand() % (high - low + 1);
        swap(vec[randomIndex], vec[high]);

        int pi = partition(vec,low,high);
        quickSort(vec,low,pi-1);
        quickSort(vec,pi+1,high);
    }
}

// não se esqueça de dar seed no random number generator no main()
// srand(time(NULL))

//função de hashing para as listas de string 
unsigned hash(const string& key, const int& size){
    unsigned hash = 5281;
    for(char c : key){
        hash = ((hash<<5)+hash) + c;
    }        
    return hash % size;
}

//##############################################################################################
// funcões de sorting para os pairs de string
// SIM, sorting de string. Como? C++ lexicograicamente compara os valores de string, então "<" funciona para strings
int partition_to_String(vector<pair<string,vector<size_t>>>& vec, int low, int high){
    string pivot = vec[high].first; // pivo sendo a maior key do vetor de pairs
    int i = (low-1); // index do menor elemento, centro

    for (int j = low; j < high; j ++){
        // se o primeiro elemento é menor que o pivot
        if(vec[j].first < pivot){
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return (i+1); 
}

void quickSort_to_String(vector<pair<string,vector<size_t>>>& vec, int low, int high){
    if(low < high){
    
        int randomIndex = low + rand() % (high - low + 1);
        swap(vec[randomIndex], vec[high]);

        int pi = partition_to_String(vec,low,high);
        quickSort_to_String(vec,low,pi-1);
        quickSort_to_String(vec,pi+1,high);
    }
}


// binary search para encontrar os vetores dado uma chave string e inseri-los em um vector
vector<size_t> binary_search_to_vector(const vector<pair<string,vector<size_t>>>& index, string& key_to_find){
    int low = 0;
    int high = index.empty() ? -1: static_cast<int>(index.size()-1); 
    vector<size_t> result;

    while(low <= high){
        // calcula o ponto médio do vetor
        int mid = low + (high - low)/2;
        string mid_key = index[mid].first;
        

        if (mid_key == key_to_find){
            // a chave foi achada
            cout <<"[Debug] Found key" << key_to_find << " at" << mid << endl;
        
            // guarda o vetor da chave num vetor source
            vector<size_t> source_vec = index[mid].second;
            
            // insere os elementos do source num outro vetor, o resultado de fato
            // é importante fazermos isso pois pode ser necessário mudar o tipo do result para evitar duplicatas
            result.insert(result.end(),source_vec.begin(),source_vec.end());
            return result;

        }
        else if(mid_key < key_to_find){
            // a chave pode estar o percentil superior
            low = mid + 1;
        }else{
            // a chave pode estar no percentil inferior
            high = mid - 1;
        }

    }// fim do while

    // if o while finalizou, a chave nao foi achada!
    cout << "[DEBUG] key " << key_to_find << " not found" << endl;
    return result;

}

//############################################################################
// PARA UNIÃO
// função para buscar o primeiro elemento menor que o value, caso não encontre a ultima pos é devolvido
int primeiro_menor(const vector<size_t>&vec, size_t value){
    int low = 0;
    int high = vec.size(); // permite retornar a última pos, inserção pois maior
    while(low < high){
        int mid = low + (high - low)/2;
        if(vec[mid]<value){
            low = mid + 1;
        }else{
            high = mid;
        }
    }
    return low;
}

// função de adicão para cada valor de um vector para outro, sem duplicata, usado nos filtros
bool add_if_unique(vector<size_t>& vec, size_t value){
    // encontra a pos onde o valor deve estar
    int pos = primeiro_menor(vec,value);

    // checa as duplicatas. Se a pos é válida e o valor é o "value" passado, é duplicata
    if(pos < vec.size() && vec[pos]==value){
        return false;
    }

    // manualmente adiciona o elemento na pos correta
    // 1. adiciona uma pos extra para deslocar o vector
    vec.push_back(0); // dummy

    // 2. desloca os elementos em 1+ pos a partir da pos achada
    for(int i = vec.size() - 1; i > pos; i--){
        vec[i] = vec[i-1];
    }  
    vec[pos] = value;
    return true;
}

//##############################################################################
// PARA INTERSECÇÃO
// funções para a intersecção de filtros, usando os vectors de posições
// função para verificar se value equal qualquer key
bool binary_equal(const vector<size_t>&vec, size_t value){
    int low = 0;
    int high = vec.size();
    while(low < high){
        int mid = low + (high - low) /2;
        if(vec[mid] == value) return true;
        else if (vec[mid] < value) low = mid + 1;
        else high = mid;
    }
    return false;
}

vector<size_t> add_if_duplicate(vector<size_t>& vec, size_t value){
    vector<size_t> result;
    if(binary_equal(vec, value)){
        result.push_back(value);
    }
    return result;
}

// #####################################################################################################
// binary search para encotrar os vetores dado uma chave int e inseri-los em outro vetor
// mesma função, assinaturas distintas
vector<size_t> binary_search_to_vector(const vector<pair<int,vector<size_t>>>& index, int& key_to_find){
    int low = 0;
    int high = index.empty() ? -1: static_cast<int>(index.size()-1); 
    vector<size_t> result;

    while(low <= high){
        // calcula o ponto médio do vetor
        int mid = low + (high - low)/2;
        int mid_key = index[mid].first;
        

        if (mid_key == key_to_find){
            // a chave foi achada
            cout <<"[Debug] Found key" << key_to_find << " at" << mid << endl;
        
            // guarda o vetor da chave num vetor source
            vector<size_t> source_vec = index[mid].second;
            
            // insere os elementos do source num outro vetor, o resultado de fato
            // é importante fazermos isso pois pode ser necessário mudar o tipo do result para evitar duplicatas
            result.insert(result.end(),source_vec.begin(),source_vec.end());
            return result;

        }
        else if(mid_key < key_to_find){
            // a chave pode estar o percentil superior
            low = mid + 1;
        }else{
            // a chave pode estar no percentil inferior
            high = mid - 1;
        }

    }// fim do while

    // if o while finalizou, a chave nao foi achada!
    cout << "[DEBUG] key " << key_to_find << " not found" << endl;
    return result;

}

// #################################################################################
// função para buscar binariamente nos pairs dos filtros que usam inteiros
// const e referencia (&) foram adicionados nesta função <-------------- ATTENTION
int binary_search_for_pair(const vector<std::pair<int, std::vector<size_t>>>& index, int value){
    int low = 0;
    int high = index.size();
    while(low<high){
        int mid = low + (high - low) / 2;
        if(index[mid].first < value){
            low = mid + 1;
        }else{
            high = mid;
        }
    }
    return low;
}

// lembre-se, a função só é efetiva se o vetor estiver ordenado
// pois a ordenação me garante que as duplicatas estarão adjacentes
void ordena_unico_e_redimensiona(vector<size_t>& vec){
    if(vec.size() == 2){return;} // já é unico

    // posicao onde o próximo elemento unico deve ser inserido no vector
    int write_index = 1;

    // read_index escaneia o vector
    for(int read_index = 1; read_index < vec.size(); read_index++){
        // se o elemento é distinto do anterior...
        if(vec[read_index] != vec[read_index - 1]){
            // então escreve na pos daquele que não era distinto
            vec[write_index] = vec[read_index]; 
            write_index++;
        }
    }

    // depois do loop todos os elementos distintos estarão no inicio
    // redimensiona para tam correspondente a pos do ultimo elem unico
    vec.resize(write_index);   

}

/*
 * uma função merge mais eficiente que a add_if_unique
 * performa em O(M+N) pois percorre os dois vetores simultâneamente
 * o add_if_unique performava em O(k * n * log(n))
 * vec1 é o primeiro vetor ordenado
 * vec2 é o segundo vetor ordenado
 * o return devolve um novo vetor ordenado, a união dos dois vetores sem duplicatas
*/
vector<size_t> merge_union_unique(const vector<size_t>& vec1, const vector<size_t>& vec2){
    vector<size_t> result;
    // reservar memória para evitar realocações
    result.reserve(vec1.size() + vec2.size());
    
    size_t i = 0; // ponteiro da primeira lista
    size_t j = 0; // ponteiro da segunda lista

    // percorre as duas listas simultêneamente
    while(i < vec1.size() && j < vec2.size()){
        if(vec1[i] < vec2[j]){
            // caso o elemento do primeiro vetor seja menor, adicionamos se único
            // a lista pode estar vazia ou, como é ordenada, já possuir o elemento vindo da igualdade
            if(result.empty() || result.back() != vec1[i]){
                result.push_back(vec1[i]);
            }
            i++;
        }
        else if(vec2[j] < vec1[i]){
            // caso o elemento do segundo vetor seja menor, adicionamos se único
            // a lista pode estar vazia ou, como é ordenada, já possuir o elemento vindo da igualdade
            if(result.empty() || result.back() != vec2[j]){
                result.push_back(vec2[j]);
            }
            j++;
        }
        else{ 
            // os dois elementos são iguais
            // adiciona um deles se não é duplicado
            if(result.empty() || result.back()!= vec1[i]){
                result.push_back(vec1[i]);
            }
            i++;
            j++;
        }
    }

    // depois de percorrer as duas listas simultâneamente, teremos que percorrer os restantes da lista 1 ou lista 2
    // adiciona os restantes da lista 1
    while(i < vec1.size()){
        if(result.empty() || result.back() != vec1[i]){
            result.push_back(vec1[i]);
        }
        i++;
    }
    // adiciona os restantes da lista 2
    while(j < vec1.size()){
        if(result.empty() || result.back() != vec2[j]){
            result.push_back(vec2[j]);
        }
        j++;
    }

    return result;

}