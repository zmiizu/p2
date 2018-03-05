
#include <iostream>
#include <vector>
#include <cmath>
#include <cfloat>
#include <string>

using namespace std;

struct Base {
   string name;
   int people;
   int equipment;
   double x,y;
};

struct Ship {
   string name;
   int maxPeople;
   int maxEquipment;
   int curPeople;
   int curEquipment;
   vector<Base> bases;
};

struct Planet {
  string name;
  vector<Base> bases;
  vector<Ship> ships;
};


// ---------------- error -------------------------

enum Error {
  ERR_UNKNOWN_OPTION,
  ERR_WRONG_NUMBER,
  ERR_LOW_PEOPLE,
  ERR_WRONG_BASE_NAME,
  ERR_WRONG_SHIP_NAME,
  ERR_NO_BASES,
  ERR_NO_SHIPS
};

void error(Error n)
{
  switch (n) {

    case ERR_UNKNOWN_OPTION:
      cout << "Error, unknown option" << endl;
      break;

    case ERR_WRONG_NUMBER:
      cout << "Error, wrong number, must be positive" << endl;
      break;

    case ERR_LOW_PEOPLE:
      cout << "Error, low people number" << endl;
      break;

    case ERR_WRONG_BASE_NAME:
      cout << "Error, base name not found" << endl;
      break;

    case ERR_WRONG_SHIP_NAME:
      cout << "Error, wrong ship name" << endl;
      break;

    case ERR_NO_BASES:
      cout << "Error, there are no bases in the planet" << endl;
      break;

    case ERR_NO_SHIPS:
      cout << "Error, there are no ships in the planet" << endl;
      break;
  }
}

//[(main base) 1251 12345 (12.34,-7.89)]
// ------------------------------------------------------------------
void printBase(const Base &base) // prints base info
{
    cout << "[(" << base.name << ") " << base.people << " "
         << base.equipment << "(" << base.x << ", " << base.y << ")]" << endl;
}

//[(Corellian cruiser Princess Leia) 300{0} 45000{0}]
void printShip(const Ship &ship) // prints ship info
{
    cout << "[(" << ship.name << ") " << ship.maxPeople << "{" << ship.curPeople
         << "} " << ship.maxEquipment << "{" << ship.curEquipment << "}]" << endl;
}

void printPlanet(const Planet &planet) // prints planet info
{
    cout << "Planet: " << planet.name << endl;
    cout << "Ships:" << endl;

    for (unsigned i = 0; i < planet.ships.size(); i++) {
        printShip(planet.ships[i]);
    }

    cout << "Bases:" << endl;

    for (unsigned i = 0; i < planet.bases.size(); i++) {
        printBase(planet.bases[i]);
    }

    cout << endl;
}

// Creates/modifies a base
void createBase(Planet &planet)
{
    bool exists = false;
    string name;
    cout << "Enter base name:";
    getline(cin, name);

    for (unsigned i = 0; i < planet.bases.size(); i++) {
        if (planet.bases[i].name == name) {
            exists = true;
        }
    }

    if (!exists) {
        int people;
        cout << "Enter base people:";
        cin >> people;
        cin.get();

        if (people < 0) {
            error(ERR_WRONG_NUMBER);
        }
        else {
            if (people < 50) {
                error(ERR_LOW_PEOPLE);
            }
            else {
                int equipment;
                cout << "Enter base equipment (Kg):";
                cin >> equipment;
                cin.get();

                if (equipment < 0) {
                    error(ERR_WRONG_NUMBER);
                }
                else {
                    int x, y;
                    cout << "Enter base coordinate x:";
                    cin >> x;
                    cout << "Enter base coordinate y:";
                    cin >> y;
                    cin.get();

                    Base b;
                    b.name = name;
                    b.people = people;
                    b.equipment = equipment;
                    b.x = x;
                    b.y = y;

                    planet.bases.push_back(b);
                }
            }
        }
    }
}

// Creates a ship
void createShip(Planet &planet)
{
    bool exist = false;
    string name;
    cout << "Enter ship name: ";
    getline(cin, name);


    if(!exist){
        int people;
        int equipment;

        cout << "Enter ship maximum people: ";
        cin >> people;
        cin.get();

        if(people < 0){
            error(ERR_WRONG_NUMBER);
        }
        else if(people < 100) {

            error(ERR_LOW_PEOPLE);
        }
        else {
            cout << "Enter ship maximum equipment: ";
            cin >> equipment;

            cin.get();

            if(equipment < 0){
                error(ERR_WRONG_NUMBER);
            }
            else{
                Ship s;

                s.curEquipment = 0;
                s.curPeople = 0;
                s.maxPeople = people;
                s.maxEquipment = equipment;

                planet.ships.push_back(s);
            }
        }
    }
    else {
        error(ERR_WRONG_SHIP_NAME);
    }

}


void deleteBase(Planet &planet)
{
    string name;
    string yn;

    if(planet.bases.size() == 0){
        error(ERR_NO_BASES);
    }

    cout << "Enter base name: ";
    getline(cin,name);

    for(unsigned i = 0; i < planet.bases.size(); i++){
        if(name != planet.bases[i].name){
            error(ERR_WRONG_BASE_NAME);
        }
    }

    for(unsigned i = 0; i < planet.bases.size(); i++){
        if(name == planet.bases[i].name){
            cout << printBase << endl;
            cout << "Delete (Y/N)?";
            getline(cin,yn);

            if(yn == "Y"){
                planet.bases.erase(planet.bases.begin()+i);
            }
        }
    }
}

void deleteShip(Planet &planet)
{
    string name;
    string yn;

    if(planet.ships.size() == 0){
        error(ERR_NO_SHIPS);
    }

    cout << "Enter ship name: ";
    getline(cin,name);

    for(unsigned i = 0; i < planet.ships.size(); i++){
        if(name != planet.ships[i].name) {
            error(ERR_WRONG_SHIP_NAME);
        }
    }

    for(unsigned i = 0; i < planet.ships.size(); i++){
        if(name == planet.ships[i].name){
            cout << printShip << endl;
            cout << "Delete (Y/N)?";
            getline(cin, yn);

            if(yn == "Y"){
                planet.ships.erase(planet.ships.begin()+i);
            }
        }
    }

}

void evacuationPlan(Planet &planet)
{
}

// ------------------------------------------------------
void menu()
{
  cout << "-----========== Evacuation ==========-----" << endl
       << "1- List info" << endl
       << "2- Add/modify base" << endl
       << "3- Add ship" << endl
       << "4- Delete base" << endl
       << "5- Delete ship" << endl
       << "6- Evacuation plan" << endl
       << "q- Quit" << endl
       << "Option: " ;
}


int main()
{
   Planet planet;
   planet.name = "Hoth";
   char option;

   do {
        menu();
        cin >> option; cin.get();

        switch (option) {
          case '1': {
            printPlanet(planet);
            break;
          }
          case '2': {
            createBase(planet);
            break;
          }
          case '3': {
            createShip(planet);
            break;
          }
          case '4': {
            deleteBase(planet);
            break;
          }
          case '5': {
            deleteShip(planet);
            break;
          }
          case '6': {
            evacuationPlan(planet);
            break;
          }
          case 'q': {
            break;
          }
          default:  {
            error(ERR_UNKNOWN_OPTION);
            break;
          }
        }
   } while (option != 'q');

   return 0;
}
