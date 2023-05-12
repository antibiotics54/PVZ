
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class registarPlayer
{
private:
    int contador =0;
public:
    //investigar vectores
    vector<string> player;
    string jugador;
    registarPlayer(string player);
    ~registarPlayer();
    int search(string txt_user);
    bool insert(string txt_user);
    bool eliminate(string txt_user);
    string obtener(string txt_user);
};

registarPlayer::registarPlayer(string player)
{
    this->jugador = player;
}

registarPlayer::~registarPlayer()
{
}

//funcion para buscar
int registarPlayer::search(string txt_user) {
    int p = -1;
    //se recorre todo el vector para validar si existe
    for (int l = 0; l < player.size(); l++) {
        //valida si en la posicion que esta, es igual al usuario dado en parametro
        if (this->player.at(l) == txt_user) {
            p = l;
            //si es retorna el numero en donde esta
            break;
        }
    }
    return p;
}

//insertar en arreglo
bool registarPlayer::insert(string username) {
    //se llama la funcion buscar y si es igual a -1 entonces significa que ese user no existe
    if (this->search(username) == -1) {
        //se añade username al final del vector una vez validado
        player.push_back(username);
        //sumamos al contador que ayuda a saber cuantos usernames se han creado
        this->contador++;
        return true;
    } else {
        return false;
    }
}

//eliminar de arreglo
bool registarPlayer::eliminate(string username){
    //se llama funcion de search para validar que el username esta en el vector
    if(search(username)!=-1){
        //se borra el elemento en ese espacio
        //begin() empieza a recorrer hasta que llegue al numero que le dio el search
        player.erase(player.begin()+search(username));
        return true;
    }else{
        return false;
    }
}

//buscar en el arreglo si existe
string registarPlayer::obtener(string txt_user){
    if(search(txt_user)!=-1){
        //si el usernam existe en el vector regresa el username en string
        return player[search(txt_user)];
    }else{
        return NULL;
    }
}



//FUNCIONES PARA CONTRASEÑA
//int registarPlayer::busqueda(string contra) {
//    int o = -1;
//    for (int l = 0; l < this->contra.length; l++) {
//        if (this->contra[l] == contra) {
//            o = l;
//            break;
//        }
//    }
//    return o;
//}

//bool registarPlayer::add(string pass) {
//    if (this->busqueda(pass) == -1) {
//        this->contra->push(pass);
//        return true;
//    } else {
//        return false;
//    }
//}
//
//bool registarPlayer::modify(string contra) {
//    if (this->busqueda(contra->getPassword()) != 1) {
//        contra->setPassword(contra->getPassword());
//        return true;
//    } else {
//        return false;
//    }
//}

