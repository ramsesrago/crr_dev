#include<iostream> 
#include<map>

class ContactData { 

private: 

    std::string _name;
    std::string _last_name;
    std::string _email;
    std::string _phone_number;
   
public: 

    ContactData(std::string name, std::string last_name, std::string email, std::string phone_number){
        _name = name;
        _phone_number = phone_number;
        _email = email;
        _last_name = last_name;
    }
    
    std::string get_name(void){
        return _name;
    }
}; 

class Organizer {
    private:
        std::map<int, ContactData*> map;
        int _id=0;

    public: 
       void create_contact(std::string name, std::string last_name, std::string email, std::string phone_number) {
            ContactData* contact = new ContactData(name,last_name,email,phone_number);  
            map[_id] = contact;
            ++_id;
       }

       bool delete_contact(int id) {
        bool found=false;
        for (auto& it : map) {
               if(id==it.first)
                {
                    map.erase(id);
                    delete(it.second);
                    found=true;
                }
                    
            }   
            return found;
       }

       void display_contacts(void) {
           for (auto& it : map) {
               std::cout << "The name of the contact for id: " << it.first << " is: " << it.second->get_name() << std::endl;
            }
       }
    };


int main(void) 
{ 

    int option=0,id=0;
    bool found;
    Organizer org;
    std::string name, last_name, email, phone_number;
 
    do { 

        std::cout << "Directorio Telefonico\n"; 
        std::cout << "Seleccione una opcion:\n\n";
        std::cout << "1. Agregar Nuevo\n\n"; 
        std::cout << "2. Imprimir contactos\n\n"; 
        std::cout << "3. Eliminar Contacto\n\n"; 
        std::cout << "4. Salir\n\n"; 
        std::cout << "Seleccione:"; 
        std::cin >> option; 

  
        switch (option) 
        { 

        case 1:
            system("clear");
            std::cout << "Nombre:"; 
            std::cin >> name; 
            std::cout << "Apellido:"; 
            std::cin >> last_name; 
            std::cout << "Email:"; 
            std::cin >> email; 
            std::cout << "Telefono:"; 
            std::cin >> phone_number; 
            org.create_contact(name,last_name,email,phone_number);
            std::cout << "Contacto nuevo guardado con exito";
            system("clear");
            break;
            
        case 2:
            system("clear");
            org.display_contacts();
            system("clear");
            break;
        
        case 3:
            system("clear");
            std::cout << "Introduce ID a eliminar:"; 
            std::cin >> id; 
            found=org.delete_contact(id);
            if(found)
                std::cout << "Elemento encontrado y eliminado"; 
            else
                std::cout << "Elemento no encontrado"; 
            system("clear");
            break;
        }

    } while (option != 4); 

} 