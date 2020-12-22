#include<iostream> 

class UserData { 

private: 

    string name; 

    string last_name; 

    string email; 

    string phone_number; 

    /*Methods*/ 

public: 

    void set_name(string name_temp); 

    string get_name(); 
}; 

UserData* new_node()
{   
    
     UserData *ptr = new UserData();
     return ptr;
    }  

void UserData::set_name(string name_temp) 

{ 

    name = name_temp; 

} 

string UserData::get_name() 

{ 

    return name; 

} 

void UserData::set_last_name(string name_temp) 

{ 

    last_name = name_temp; 

} 

string UserData::get_name() 
{
    return name; 
} 

int main(void) 

{ 

    int option=0; 

    UserData *ptr_node;
    string name; 

    do { 

        std::cout << "Directorio Telefonico\n"; 
        std::cout << "Seleccione una opcion:\n\n";
        std::cout << "1. Agregar Nuevo\n\n"; 
        std::cout << "Seleccione:"; 
        std::cin >> option; 

  
        switch (option) 
        { 

        case 1:  
            ptr_node = new_node();
            system("cls"); 
            UserData user_new;
            cout << "Nombre:"; 
            cin >> name; 
            User_New.set_name(name); 
            cout << User_New.get_name(); 
            system("pause"); 

        } 

    } while (option != 4); 

} 