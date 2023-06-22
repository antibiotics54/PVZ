#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>



using namespace std;

SDL_Texture* Texture, * Fondo, * inicio, * solContador, * dimP, * dimS, * dimW, * PeaIcon, * WalIcon, * SunIcon, * Txt, * mostrarSol;
SDL_Rect space, Image, cuadro, zWalk, guisante, Espacio, movePea, dibujoPea, dibujoSun, dibujoWalnut, danger, moveWalnut, moveSunflower, pos, solPos, txtPos;
int walkWidth, txtWidth;
bool cambio1 = false, cambio2 = false, cambio3 = false;

#define zombie "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\ZombieWalkingSprites1.png"
#define pelota "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\pea.png"
#define sunny "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\sun.png"
#define patio "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\Patio.png"
#define flor "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\sunflower.png"
#define pea "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\peashooters_copy.png"
#define iconP "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\icon_peashooter_100.png"
#define dimIconP "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\icon_peashooter_100_dim.png"
#define iconS "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\icon_sunflower.png"
#define dimIconS "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\icon_sunflower_dim.png"
#define iconW "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\icon_walnut.png"
#define dimIconW "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\icon_walnut_dim.png"
#define pegar "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\impacto.png"
#define walNut "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\roca_copy.png"
#define login "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\fondo_login.png"
#define danger1 "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\danger1.png"
#define comiendo "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\comiendo.png"
#define field "\\Users\\lenovo\\source\\repos\\SDL_Projects\\foticos\\text_field.png"

//defini aqui arriba mis dirrectorios porque en mac es distinto

//structs que son como clases
enum Button {
    ICON_CHOOSE,
    FRONTYARD,
    CREAR,
};

struct Icon {
    bool is_sunflower_chosen=false;
    bool is_peashooter_chosen=false;
    bool is_walnut_chosen=false;
};
struct Block {
    int x1, x2;
    int y1, y2;
};

struct Sun {
    int final_col;
    int final_row;
    int MoveOnY;
    int wait_seconds;
};

struct Sunflower {
    int row, col;
    int byte, vida;
};

struct Walnut {
    int row, col;
    int byte, vida;
    string directory;
};

struct Peashooter {
    int row, col;
    int byte, vida;
};

struct Pea {
    int row;
    int x_location;
    int col;
};

struct Jugador {
    int sol_total;
    string name;
    bool firstclick;
    bool mouse;
};

struct Zombie {
    int row;
    int y_location;
    int x_location;
    int health;
    bool moving;
    string directory;
};

struct Objetos {
    vector<Zombie> zombies;
    vector<Peashooter> peashooter;
    vector<Sunflower> sunflower;
    vector<Walnut> walnut;
    vector<Sun> suns;
    vector<Pea> peas;
};


vector<vector<Block> > Screen;



/*
void crearWalnuts(Objetos &obj) {
    Walnut temp;
    temp.col = 540;
    temp.row = 84;
    obj.walnut.push_back(temp);
    Walnut temp1;
    temp1.col = 540;
    temp1.row = 178;
    obj.walnut.push_back(temp1);
    Walnut temp2;
    temp2.col = 540;
    temp2.row = 278;
    obj.walnut.push_back(temp2);
    Walnut temp3;
    temp3.col = 540;
    temp3.row = 381;
    obj.walnut.push_back(temp3);
    Walnut temp4;
    temp4.col = 540;
    temp4.row = 473;
    obj.walnut.push_back(temp4);
    std::cout << "Creado";

}
*/

//crear el board desde la imagen
vector<vector<Block> > Create_Board() {
    vector<vector<Block> > result;
    vector<Block> temps;
    Block temp;
    for (int y = 0; y < 5; y++) {
        temps.clear();
        for (int x = 0; x < 9; x++) {
            temp.x1 = 250 + (x * 81);
            temp.x2 = 250 + ((x + 1) * 81);
            temp.y1 = 70 + (y * 101);
            temp.y2 = 70 + ((y + 1) * 101);
            //cout << "row: " << y << ", col: " << x << "   X1: " << temp.x1<< ", Y1:"<< temp.y1<< endl;
            temps.push_back(temp);
        }
        result.push_back(temps);
    }
    return result;
}

//verificacion si se puede mover el zombie
bool ZombiePuedeMoverse(Zombie zomb, int row, int col, vector<vector<Block> >& map) {
    int right_limit = map[row][col].x2 - 35;
    int left_limit = map[row][col].x1;
    int zombie_new_location = zomb.x_location - 1;
    if (zomb.row == row && zombie_new_location < right_limit && zombie_new_location > left_limit)
        return true;
    return false;
}

//verificar si el zombie choco con la planta
bool ZombieChocadoConPlantas(Objetos& elements, Zombie& zomb, vector<vector<Block> >& map) {
    for (int i = 0; i < elements.walnut.size(); i++) {
        if (ZombiePuedeMoverse(zomb, elements.walnut[i].row, elements.walnut[i].col, map)) {
            zomb.moving = false;
            return true;
        }
    }
    for (int i = 0; i < elements.peashooter.size(); i++) {
        if (ZombiePuedeMoverse(zomb, elements.peashooter[i].row, elements.peashooter[i].col, map)) {
            zomb.moving = false;
            return true;
        }
    }
    for (int i = 0; i < elements.sunflower.size(); i++) {
        if (ZombiePuedeMoverse(zomb, elements.sunflower[i].row, elements.sunflower[i].col, map)) {
            zomb.moving = false;
            return true;
        }
    }
    zomb.moving = true;
    return false;
}

//verificar si el zombie se creo en la misma fila que el peashooter
bool IsZombieInPeashooterRow(Peashooter peashooter, Zombie zomb) {
    if (zomb.row == peashooter.row) {
        return true;
    }
    return false;
}

//verificar si el zombie esta en la posicion de la pea
bool IsZombieInPeaRow(Pea peas, Zombie zomb) {
    if (zomb.row == peas.row) {
        return true;
    }
    return false;
}

//verificacion de zombie golpeado
bool PeaGolpeadoZombie(Pea peas, Zombie zomb) {
    if (zomb.x_location <= peas.x_location)
        return true;
    return false;
}

//
void apply_pea_hitting_zombie(Objetos& elements, int p_ind, int z_ind) {
    if (PeaGolpeadoZombie(elements.peas[p_ind], elements.zombies[z_ind])) {
        elements.zombies[z_ind].health--;
        elements.peas.erase(elements.peas.begin() + p_ind);
        if (elements.zombies[z_ind].health == 0)
            elements.zombies.erase(elements.zombies.begin() + z_ind);
    }
}

//funcion para crear pea
void crear_Pea(int row, int col, Objetos& obj, vector<vector<Block> > sc) {
    Pea temp;
    temp.row = row;
    temp.col = col;
    temp.x_location = sc[row][col].x2;
    obj.peas.push_back(temp);
}

//funcion para crear pea dependiendo de la posicion
void mostrarPea(Objetos& obj, SDL_Renderer* ren, vector<vector<Block> > sc) {
    for (int gus = 0; gus < obj.peas.size(); gus++) {
        SDL_Surface* temp = IMG_Load(pelota);
        Texture = SDL_CreateTextureFromSurface(ren, temp);
        guisante.x = obj.peas[gus].x_location;
        int row = obj.peas[gus].row;
        int col = obj.peas[gus].col;
        guisante.y = sc[row][col].y1 + 20;
        SDL_RenderCopy(ren, Texture, NULL, &guisante);
    }
}

//funcion para que la pea se mueva desde un punto hasta el zombie
void MoverPea(Objetos& obj) {
    for (int gus = 0; gus < obj.peas.size(); gus++) {
        obj.peas[gus].x_location += 5;
    }
}

//funcion para crear soles randomly
//cada sol cuesta 50
void Create_Suns(Objetos& obj) {
    srand(time(NULL));
    Sun temp;
    temp.MoveOnY = 5;
    temp.wait_seconds = 30;
    temp.final_row = rand() % 5;
    temp.final_col = rand() % 9;
    obj.suns.push_back(temp);
    std::cout << "\n nuevo sol Y:" << temp.final_col << "\n";
}

//funcion para crear zombies random
void RandZombies(Objetos& obj) {
    srand(time(NULL));
    Zombie temp;
    temp.x_location = 999;
    temp.health = 10;
    temp.moving = true;
    temp.directory = zombie;
    int row = rand() % 5;
    temp.row = row;
    switch (row) {
    case 0:
        temp.y_location = 84;
        break;
    case 1:
        temp.y_location = 178;
        break;
    case 2:
        temp.y_location = 278;
        break;
    case 3:
        temp.y_location = 381;
        break;
    case 4:
        temp.y_location = 473;
        break;
    }
    std::cout << temp.y_location << "\n";
    obj.zombies.push_back(temp);
}


//funcion para mover el zombie desde derecha a izquierda
void move_zombies(vector<Zombie>& zombies) {
    for (int i = 0; i < zombies.size(); i++) {
        if (zombies[i].moving) {
            zombies[i].x_location -= 2;
        }
        if (zombies[i].x_location == 0) {
            zombies[i].health--;
        }
    }
}

bool has_zombie_reached_element(Zombie zom, int row, int col, vector<vector<Block> > sc) {

    int right_limit = sc[row][col].x2 - 35;
    int left_limit = sc[row][col].x1;
    int zombie_new_location = zom.x_location - 5;
    if (zom.row == row &&
        zombie_new_location < right_limit &&
        zombie_new_location > left_limit)
        return true;
    return false;
}


void CrearPeashooters(Objetos& obj) {
    Peashooter temp;
    temp.col = 7;
    temp.row = 0;
    temp.vida = 30;
    obj.peashooter.push_back(temp);
    Peashooter temp2;
    temp2.col = 7;
    temp2.row = 1;
    temp2.vida = 30;
    obj.peashooter.push_back(temp2);
    Peashooter temp3;
    temp3.col = 7;
    temp3.row = 2;
    temp3.vida = 30;
    obj.peashooter.push_back(temp3);
    Peashooter temp4;
    temp4.col = 7;
    temp4.row = 3;
    temp4.vida = 30;
    obj.peashooter.push_back(temp4);
    Peashooter temp5;
    temp5.col = 7;
    temp5.row = 4;
    temp5.vida = 30;
    obj.peashooter.push_back(temp5);
}

//funcion para imprimir los peashooters
void PrintPeashooters(SDL_Renderer* ren, Objetos& obj, vector<vector<Block> > sc) {
    SDL_Surface* temp = IMG_Load(pea);
    Texture = SDL_CreateTextureFromSurface(ren, temp);
    if (temp == NULL) {
        cout << "Error loading image: " << SDL_GetBasePath();
        return;
    }
    //cout << "size: " << obj.peashooter.size() << "\n";
    int col, row;
    for (int gustavo = 0; gustavo < obj.peashooter.size(); gustavo++) {
        //cout << "Peashooter No. " << gustavo<< endl;
        //cout << "Row: " << obj.peashooter[gustavo].row << ", Col: " << obj.peashooter[gustavo].col << endl;
        cout << "Vida Peashooter No." << gustavo <<" : " << obj.peashooter[gustavo].vida << endl;
        col = obj.peashooter[gustavo].col;
        row = obj.peashooter[gustavo].row;
        Espacio.x = sc[row][col].x1+30;
        Espacio.y = sc[row][col].y1 + 20;
    
        //cout << "coords peashooter:" << Espacio.x << " , " << Espacio.y << "\n";
        //std::cout << gustavo << ". Aqui?\n";
        SDL_RenderCopy(ren, Texture, &movePea, &Espacio);
        
    }
}

void apply_zombie_byte_on_peashooter(Objetos& obj, int z_ind, int p_ind, vector<vector<Block> > sc) {
    if (has_zombie_reached_element(obj.zombies[z_ind], obj.peashooter[p_ind].row, obj.peashooter[p_ind].col, sc)) {
        obj.zombies[z_ind].moving = false;
        obj.peashooter[p_ind].vida--;
        if (obj.peashooter[p_ind].vida == 0 ) {
            //cout << "?" << endl;
            obj.zombies[z_ind].moving = true;
            obj.peashooter.erase(obj.peashooter.begin() + p_ind);
        }
    }
}

void handle_zombie_peashooter_encounter(Objetos& obj, vector<vector<Block> > sc) {
    for (int i = 0; i < obj.peashooter.size(); i++)
        for (int j = 0; j < obj.zombies.size(); j++)
            apply_zombie_byte_on_peashooter(obj, j, i, sc);
}

//funcion para mostrar walnuts
void mostrarWalnuts(SDL_Renderer* ren, Objetos& obj) {
    for (int gus = 0; gus < obj.walnut.size(); gus++) {
        SDL_Surface* temp = IMG_Load(walNut);
        Texture = SDL_CreateTextureFromSurface(ren, temp);
        if (temp == NULL) {
            std::cout << "Error loading image: " << SDL_GetBasePath();
            return;
        }
        pos.x = obj.walnut[gus].col;
        pos.y = obj.walnut[gus].row;
        SDL_RenderCopy(ren, Texture, &moveWalnut, &pos);
    }
}

//funcion para imprimir los zombies
//funcion para imprimir los zombies
void MostrarZombies(SDL_Renderer* ren, vector<Zombie>& zombies, Objetos& obj, vector<vector< Block> >& sc) {
    Zombie z;

    for (int i = 0; i < zombies.size(); i++) {
        int row = zombies[i].row;
        int col = zombies[i].y_location;
        //cambiar sprites dependiendo de la health
        if (zombies[i].health == 10) {
            SDL_Surface* temp = IMG_Load(zombie);
            Texture = SDL_CreateTextureFromSurface(ren, temp);
            zWalk.h = 49;
            zWalk.w = 41;
            cambio1 = true;
            cambio2 = false;
            cambio3 = false;
        }
        else if (zombies[i].health < 5) {
            SDL_Surface* temp = IMG_Load(zombie);
            Texture = SDL_CreateTextureFromSurface(ren, temp);
            zWalk.w = 25;
            zWalk.h = 46;
            cambio1 = false;
            cambio2 = true;
            cambio3 = false;
        }
        else if (!ZombieChocadoConPlantas(obj, z, sc)) {
            SDL_Surface* temp = IMG_Load(comiendo);
            zWalk.w = 29;
            zWalk.h = 45;
            cambio1 = false;
            cambio2 = false;
            cambio3 = true;
            Texture = SDL_CreateTextureFromSurface(ren, temp);
        }

        space.x = zombies[i].x_location;
        space.y = sc[row][8].y1 - 10;
        if (space.x > 256 && zombies[i].health > 0) {
            SDL_RenderCopy(ren, Texture, &zWalk, &space);
        }
        else {
            zombies.erase(zombies.begin() + i);
        }
    }
}


//funcion para que los soles cambien de posicion randomly
void MoverSoles(vector<Sun>& sol, vector<vector<Block> > sc) {
    for (int i = 0; i < sol.size(); i++) {
        int row = sol[i].final_row;
        int col = sol[i].final_col;
        int limite = sc[row][col].y1 + 30;
        if (sol[i].MoveOnY <= limite) {
            sol[i].MoveOnY += 5;
        }
        else if (sol[i].wait_seconds > 0) {
            sol[i].wait_seconds--;
        }
        else {
            sol.erase(sol.begin() + i);
        }

    }
}

//funcion para imprimir los peashooters
void PrintSunflowers(SDL_Renderer* ren, Objetos& obj, vector<vector<Block> > sc) {
    SDL_Surface* temp = IMG_Load(flor);
    Texture = SDL_CreateTextureFromSurface(ren, temp);
    if (temp == NULL) {
        cout << "Error loading image: " << SDL_GetBasePath();
        return;
    }
    //cout << "size: " << obj.peashooter.size() << "\n";
    int col, row;
    for (int gustavo = 0; gustavo < obj.sunflower.size(); gustavo++) {
        //   cout << "Peashooter No. " << gustavo<< endl;
        //   cout << "Row: " << obj.peashooter[gustavo].row << ", Col: " << obj.peashooter[gustavo].col << endl;
        col = obj.sunflower[gustavo].col;
        row = obj.sunflower[gustavo].row;
        Espacio.x = sc[row][col].x1 + 50;
        Espacio.y = sc[row][col].y1 + 20;

        //cout << "coords peashooter:" << Espacio.x << " , " << Espacio.y << "\n";
        //std::cout << gustavo << ". Aqui?\n";
        SDL_RenderCopy(ren, Texture, &moveSunflower, &Espacio);

    }
}

void apply_zombie_byte_on_sunflower(Objetos& obj, int z_ind, int s_ind, vector<vector<Block> > sc) {
    if (has_zombie_reached_element(obj.zombies[z_ind], obj.sunflower[s_ind].row, obj.sunflower[s_ind].col, sc)) {
        obj.sunflower[s_ind].vida--;
        obj.zombies[z_ind].moving = false;
        if (obj.sunflower[s_ind].byte < 0) {
            obj.zombies[z_ind].moving = true;
            obj.sunflower.erase(obj.sunflower.begin() + s_ind);
        }
    }
}

void handle_zombie_sunflower_encounter(Objetos& obj, vector<vector<Block> > sc) {
    for (int i = 0; i < obj.sunflower.size(); i++)
        for (int j = 0; j < obj.zombies.size(); j++)
            apply_zombie_byte_on_sunflower(obj, j, i, sc);
}



//funcion para imprimir los walnuts
void PrintWalnuts(SDL_Renderer* ren, Objetos& obj, vector<vector<Block> > sc) {
    SDL_Surface* temp = IMG_Load(walNut);
    Texture = SDL_CreateTextureFromSurface(ren, temp);
    if (temp == NULL) {
        cout << "Error loading image: " << SDL_GetBasePath();
        return;
    }
    //cout << "size: " << obj.peashooter.size() << "\n";
    int col, row;
    for (int gustavo = 0; gustavo < obj.walnut.size(); gustavo++) {
        //   cout << "Peashooter No. " << gustavo<< endl;
        //   cout << "Row: " << obj.peashooter[gustavo].row << ", Col: " << obj.peashooter[gustavo].col << endl;
        col = obj.walnut[gustavo].col;
        row = obj.walnut[gustavo].row;
        Espacio.x = sc[row][col].x1 + 50;
        Espacio.y = sc[row][col].y1 + 20;

        //cout << "coords peashooter:" << Espacio.x << " , " << Espacio.y << "\n";
        //std::cout << gustavo << ". Aqui?\n";
        SDL_RenderCopy(ren, Texture, &moveWalnut, &Espacio);

    }
}

void apply_zombie_byte_on_walnut(Objetos& obj, int z_ind, int w_ind, vector<vector<Block> > sc) {
    if (has_zombie_reached_element(obj.zombies[z_ind], obj.walnut[w_ind].row, obj.walnut[w_ind].col, sc)) {
        obj.zombies[z_ind].moving = false;
        obj.walnut[w_ind].vida--;
        if (obj.walnut[w_ind].vida < 0) {
            obj.zombies[z_ind].moving = true;
            obj.walnut.erase(obj.walnut.begin() + w_ind);
        }
    }
}

void handle_zombie_walnut_encounter(Objetos& obj, vector<vector<Block> > sc) {
    for (int i = 0; i < obj.walnut.size(); i++)
        for (int j = 0; j < obj.zombies.size(); j++)
            apply_zombie_byte_on_walnut(obj, j, i, sc);
}

//funcion para imprimir soles
void MostrarSoles(SDL_Renderer* ren, vector<Sun>& sol, vector<vector<Block> > sc) {
    for (int i = 0; i < sol.size(); i++) {
        SDL_Surface* temp = IMG_Load(sunny);
        Texture = SDL_CreateTextureFromSurface(ren, temp);
        cuadro.x = sc[0][sol[i].final_col].x1;
        cuadro.y = sol[i].MoveOnY;
        SDL_RenderCopy(ren, Texture, NULL, &cuadro);
    }
}


void sumarSoles(Objetos& obj, vector<vector<Block> >& sc, int mouse_x, int mouse_y, bool& sun_picked, Jugador& player) {
    for (int i = 0; i < obj.suns.size(); i++) {
        int row = obj.suns[i].final_row;
        int col = obj.suns[i].final_col;
        int right = sc[row][col].x2;
        int left = sc[row][col].x1;
        int up = obj.suns[i].MoveOnY;
        int down = obj.suns[i].MoveOnY + 80;
        if (mouse_x > left && mouse_x < right &&
            mouse_y>up && mouse_y < down) {
            obj.suns.erase(obj.suns.begin() + i);
            sun_picked = true;
            player.sol_total += 50;
            std::cout << "Cant soles: " << player.sol_total << "\n";
            break;
        }
    }
}

void gen_random_sun_from_sunflower(Objetos& obj, Sunflower sunflower, vector<vector<Block> >& sc) {
    Sun temp;
    temp.final_col = sunflower.col;
    temp.final_row = sunflower.row;
    temp.MoveOnY = sc[sunflower.row][sunflower.col].y1 - 20;
    temp.wait_seconds = 30;
    obj.suns.push_back(temp);
}

//funcion para quitarle vida a los zombies
void QuitarVidas(vector<Peashooter>& peas, vector<Zombie>& zomb) {
    for (int i = 0; i < zomb.size(); i++) {
        if (zomb[i].x_location == peas[i].row) {
            zomb[i].health--;
        }
    }
}

//boolean para saber que icon fue seleccionado
void iconSelected(Icon& icon, int x, int y) {
    if ((y > 106) && (y < 195) && (x > 50) && (x < 110)) {
        icon.is_sunflower_chosen = true;
        cout << "SUNFLOWER SELECTED";
    }
    else if ((y > 234) && (y < 323) && (x > 50) && (x < 110)) {
        icon.is_walnut_chosen = true;
        cout << "WALNUT SELECTED";
    }
    else if ((y > 170) && (y < 259) && (x > 50) && (x < 110)) {
        icon.is_peashooter_chosen = true;
        cout << "PEASHOOTER SELECTED";
    }
}

bool click_is_in_frontyard(vector<vector< Block> >& sc, int mouse_x, int mouse_y) {
    int right_bound = sc[0][8].x2;
    int left_bound = sc[0][0].x1;
    int upper_bound = sc[0][0].y1;
    int lower_bound = sc[4][0].y2;
    if (mouse_x > left_bound && mouse_x < right_bound &&
        mouse_y > upper_bound && mouse_y < lower_bound)
        return true;
    return false;
}

void determine_row_and_col_chosen_by_second_click(vector<vector< Block> > &sc, int mouse_x, int mouse_y, int& row, int& col) {
    for (int y = 0; y < 5; y++)
        for (int x = 0; x < 9; x++)
            if (mouse_x > sc[y][x].x1 && mouse_x < sc[y][x].x2 &&
                mouse_y > sc[y][x].y1 && mouse_y < sc[y][x].y2) {
                row = y; col = x;
                break;
            }
}

//boolean para crear plantas dependiendo del icon choosen
void crearPlantas(Objetos& obj, Icon& icon, int& sol_total, int& x, int& y, vector<vector< Block> >& sc) {
    int row, col;
    determine_row_and_col_chosen_by_second_click(sc, x, y, row, col);
    if ((icon.is_peashooter_chosen) && (sol_total >= 100)) {
        Peashooter ptemp;
        ptemp.row = row;
        ptemp.col = col;
        ptemp.vida = 10;
        obj.peashooter.push_back(ptemp);
        sol_total -= 100;
        icon.is_peashooter_chosen = false;
        cout << "Peashooter creado";
    }
    else if ((icon.is_sunflower_chosen) && (sol_total >= 50)) {
        Sunflower stemp;
        stemp.row = row;
        stemp.col = col;
        stemp.vida = 10;
        obj.sunflower.push_back(stemp);
        sol_total -= 50;
        cout << "Sunflower creada";
    }
    else if ((icon.is_walnut_chosen) && (sol_total >= 50)) {
        Walnut wtemp;
        wtemp.row = row;
        wtemp.col = col;
        wtemp.vida = 30;
        obj.walnut.push_back(wtemp);
        sol_total -= 50;
        cout << "Walnt creada";
    }
}

bool ganar(Objetos& obj) {
    if (obj.zombies.size() == 0) {
        return true;
    }
    return false;
}


//funcion para display los icons de las plantas
void display_icon(SDL_Renderer* renderer) {
    //crear las imagenes de los icons
    SDL_Surface* pDim = IMG_Load(dimIconP);
    SDL_Surface* p = IMG_Load(iconP);
    SDL_Surface* sDim = IMG_Load(dimIconS);
    SDL_Surface* s = IMG_Load(iconS);
    SDL_Surface* wDim = IMG_Load(dimIconW);
    SDL_Surface* w = IMG_Load(iconW);
    dimP = SDL_CreateTextureFromSurface(renderer, pDim);
    PeaIcon = SDL_CreateTextureFromSurface(renderer, p);
    dimS = SDL_CreateTextureFromSurface(renderer, sDim);
    SunIcon = SDL_CreateTextureFromSurface(renderer, s);
    dimW = SDL_CreateTextureFromSurface(renderer, wDim);
    WalIcon = SDL_CreateTextureFromSurface(renderer, w);
    int width = 89, height = 60, iconX = 50, peaY = 167, walnutY = 231, sunY = 103;

    dibujoPea.x = iconX;
    dibujoPea.y = peaY;
    dibujoPea.w = width;
    dibujoPea.h = height;
    dibujoSun.x = iconX;
    dibujoSun.y = sunY;
    dibujoSun.w = width;
    dibujoSun.h = height;
    dibujoWalnut.x = iconX;
    dibujoWalnut.y = walnutY;
    dibujoWalnut.w = width;
    dibujoWalnut.h = height;
}

//funcion para mostrar txt
void texto(SDL_Renderer* sprite, TTF_Font* font, int& soles) {
    SDL_Color color = { 255, 255, 255 };
    string texto = to_string(soles);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, texto.c_str(), color);
    SDL_Texture* muestra = SDL_CreateTextureFromSurface(sprite, textSurface);
    SDL_Rect textRect;
    textRect.x = 100;
    textRect.y = 35;
    SDL_QueryTexture(muestra, nullptr, nullptr, &textRect.w, &textRect.h);
    SDL_RenderCopy(sprite, muestra, nullptr, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(muestra);
}


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    if (TTF_Init() < 0) {
        cout << "Error intializing SDL_ttf: " << TTF_GetError() << endl;
        return 2;
    }
    SDL_StartTextInput();
    vector<vector< Block> > sc = Create_Board();
    bool run = true;
    Jugador player;
    player.mouse = false;
    Objetos Object;
    Icon icon{};
    cuadro.h = 44;
    cuadro.w = 44;
    space.h = 90;
    space.w = 90;
    pos.w = 58;
    pos.h = 60;
    Espacio.w = 58;
    Espacio.h = 60;
    guisante.w = 20;
    guisante.h = 20;
    cout << Object.zombies.size() << "\n";

    SDL_Window* window = SDL_CreateWindow("YIPEEEE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 600, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        cout << "No carga ventana";
        return 4;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface* temple = IMG_Load(patio);
    SDL_Surface* sun_icon = IMG_Load(sunny);
    SDL_Surface* mostrar = IMG_Load(field);

    //para chequear que pasaba con las imagenes
    if (temple == NULL && sun_icon == NULL && mostrar == NULL) {
        cout << "Error loading image: " << SDL_GetBasePath();
        return 5;
    }
    solContador = SDL_CreateTextureFromSurface(renderer, sun_icon);
    Fondo = SDL_CreateTextureFromSurface(renderer, temple);
    mostrarSol = SDL_CreateTextureFromSurface(renderer, mostrar);

    SDL_FreeSurface(temple);
    SDL_FreeSurface(sun_icon);
    SDL_FreeSurface(mostrar);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    //=============================================================
    //VALERIA PROBANDO SPRITES
    const int moving = 60;
    int y = 0, x = 0;
    int timeZombie = 0, timeWalnut = 0, timePea = 0, timeSunflower = 0;
    int txtWidth = 0, txtHeight = 0;
    SDL_QueryTexture(Texture, NULL, NULL, &txtWidth, &txtHeight);

    zWalk.x = zWalk.y = 0;
    movePea.x = movePea.y = 0;
    moveWalnut.x = moveWalnut.y = 0;
    moveWalnut.h = 32;
    moveWalnut.w = 27;
    movePea.h = 31;
    movePea.w = 27;
    zWalk.h = 49;
    zWalk.w = 41;
    solPos.x = solPos.y = 5;
    solPos.h = solPos.w = 100;
    txtPos.x = 95;
    txtPos.y = 35;
    txtPos.w = 60;
    txtPos.h = 40;
    player.sol_total = 50;
    //===========================================================

    int gus = 0;
    CrearPeashooters(Object);
    if (ganar(Object)) {
        run = true;
    }
    else {
        run = false;
    }

    while (run) {

        //==========================AQUI LO CAMBIAS ==========================
        TTF_Font* font = TTF_OpenFont("/Users/valeriaalfaro/Library/Fonts/35021733747.ttf", 33);
        if (!font) {
            cout << "Failed to load font: " << TTF_GetError() << endl;
        }
        SDL_GetMouseState(&x, &y);

        bool solClick;
        sumarSoles(Object, sc, x, y, solClick, player);
        bool mousePressed = false;

        SDL_Event event;
        SDL_PollEvent(&event);


        switch (event.type) {
        case SDL_QUIT:
            run = false;
            IMG_Quit();
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                x = event.button.x;
                y = event.button.y;
                if (!mousePressed && player.mouse == false) {
                    cout << "click" << "   MOUSE X:" << x;
                    if (x > 20 && x < 113 && y>102 && y < 292) {
                        iconSelected(icon, x, y);
                        mousePressed = true;
                        player.mouse = true;
                    }
                }
                else if (player.mouse == true) {
                    if (click_is_in_frontyard(sc, x, y)) {
                        crearPlantas(Object, icon, player.sol_total, x, y, sc);
                        player.mouse = false;
                    }
                    cout << "RIGHT";
                }
            }
            break;
        }

        texto(renderer, font, player.sol_total);
        SDL_RenderPresent(renderer);


        SDL_RenderCopy(renderer, Fondo, NULL, NULL);
        SDL_RenderCopy(renderer, solContador, NULL, &solPos);
        SDL_RenderCopy(renderer, mostrarSol, NULL, &txtPos);
        display_icon(renderer);

        //verificacion de como aparecen los icons
        if (player.sol_total < 50) {
            //display todo en dim
            SDL_RenderCopy(renderer, dimP, NULL, &dibujoPea);
            SDL_RenderCopy(renderer, dimS, NULL, &dibujoSun);
            SDL_RenderCopy(renderer, dimW, NULL, &dibujoWalnut);
        }
        else if (player.sol_total >= 50) {
            //display solo las plantas sunflower y roca
            SDL_RenderCopy(renderer, SunIcon, NULL, &dibujoSun);
            SDL_RenderCopy(renderer, WalIcon, NULL, &dibujoWalnut);
            if (player.sol_total >= 100) {
                //mostrar peashooter
                SDL_RenderCopy(renderer, PeaIcon, NULL, &dibujoPea);
            }
            else {
                //poner el peashooter en dim
                SDL_RenderCopy(renderer, dimP, NULL, &dibujoPea);
            }
        }


        //==================================================================
        //zombies
        if (gus % 1200 == 0) {
            RandZombies(Object);
        }

        handle_zombie_peashooter_encounter(Object, sc);
        handle_zombie_sunflower_encounter(Object, sc);
        handle_zombie_walnut_encounter(Object, sc);

        move_zombies(Object.zombies);
        MostrarZombies(renderer, Object.zombies, Object, sc);
        //cout << "?" << endl;
        PrintPeashooters(renderer, Object, sc);
        PrintWalnuts(renderer, Object, sc);
        PrintSunflowers(renderer, Object, sc);
        // mostrarWalnuts(renderer, Object);


         //esto crea los sprites
         //contador para frame del sprite actual
        timeZombie++;
        timePea++;
        timeWalnut++;
        timeSunflower++;

        if (moving / timeZombie == 4) {
            //set el contador a 0
            timeZombie = 0;
            if (cambio1) {
                zWalk.x += 41;
                if (zWalk.x >= 369) {
                    zWalk.x = 0;

                }
            }
            else if (cambio2) {
                zWalk.x += 25;
                if (zWalk.x >= 183) {
                    zWalk.x = 0;

                }
            }
            else if (cambio3) {
                zWalk.x += 31;
                if (zWalk.x >= 218) {
                    zWalk.x = 0;

                }
            }

        }


        if (moving / timePea == 6) {
            timePea = 0;
            movePea.x += 27;
            if (movePea.x >= 217) {
                movePea.x = 0;
            }
        }
        



        if (gus % 1200 == 0) {
            Create_Suns(Object);
            for (int gus = 0; gus < Object.sunflower.size(); gus++) {
                gen_random_sun_from_sunflower(Object,Object.sunflower[gus], sc);
            
            }
        }

        for (int P = 0; P < Object.zombies.size(); P++) {
            for (int G = 0; G < Object.peashooter.size(); G++) {
                if (IsZombieInPeashooterRow(Object.peashooter[G], Object.zombies[P]) && gus % 250 == 0) {
                    crear_Pea(Object.peashooter[G].row, Object.peashooter[G].col, Object, sc);

                }
            }
        }
        MoverPea(Object);
        mostrarPea(Object, renderer, sc);

        for (int A = 0; A < Object.zombies.size(); A++) {
            for (int L = 0; L < Object.peas.size(); L++) {
                if (IsZombieInPeaRow(Object.peas[L], Object.zombies[A])) {
                    apply_pea_hitting_zombie(Object, L, A);
                }
                else if (Object.peas[L].x_location == 1050) {
                    Object.peas.erase(Object.peas.begin() + L);
                }
            }
        }


        //soles
        MoverSoles(Object.suns, sc);
        MostrarSoles(renderer, Object.suns, sc);


        gus += 10;
        SDL_Delay(30);


    }
    cout << "Zombie Pos x: " << gus << "\n Zombie Pos Y: " << space.y;

    cout << "\n\n" << Object.zombies.size() << "\n";
    cout << Object.suns.size();

    SDL_DestroyWindow(window);
    SDL_RenderClear(renderer);
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    return 0;
}
