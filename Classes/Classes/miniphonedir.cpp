#include<iostream> 

using namespace std; 

  

class UserData { 

private: 

    string name; 

    string last_name; 

    string email; 

    string phone_number; 

    /*Method*/ 

public: 

    void set_name(string name_temp); 

    string get_name(); 

    

     

}; 

  

void UserData::set_name(string name_temp) 

{ 

    name = name_temp; 

} 

  

string UserData::get_name() 

{ 

    return name; 

} 

  

int main(void) 

{ 

    int option; 

    string name; 

    do { 

        cout << "Directorio Telefonico\n"; 

        cout << "Seleccione una opcion:\n\n"; 

        cout << "1. Agregar Nuevo\n\n"; 

        cout << "Seleccione:"; 

        cin >> option; 

  

        switch (option) 

        { 

        case 1:  

            system("cls"); 

            UserData User_New; 

            cout << "Nombre:"; 

            cin >> name; 

            User_New.set_name(name); 

            cout << User_New.get_name(); 

            system("pause"); 

        } 

    } while (option != 4); 

} 