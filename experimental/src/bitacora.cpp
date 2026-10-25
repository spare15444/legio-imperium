#include <iostream>
#include <string>
#include <list>
using namespace std;

struct EventoBatalla {
    int idTurno;
    string nombreLegionAfectada;
    string tipoTropa;
    int cantidadBajas;
    string descripcionEstrategica;
};

class BitacoraGuerra {
private:
    list<EventoBatalla> eventos;
public:
    void registrarEvento(EventoBatalla evento) {
        eventos.push_back(evento);
    }
    void mostrarHistorial(){
        cout << "\n===== HISTORIAL DE BATALLA (BITACORA) =====" << endl;
        for (auto it = eventos.begin(); it != eventos.end(); ++it) {
            cout << "Turno: " << it->idTurno 
                 << " | Legion: " << it->nombreLegionAfectada 
                 << " | Bajas: " << it->cantidadBajas 
                 << " | Detalle: " << it->descripcionEstrategica << endl;
        }
    }
};
