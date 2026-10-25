#include <iostream>
#include "../include/motor_combate.hpp"

using namespace std;

// ================================== MAIN ==================================
int main() {
    cout << "===== LEGIO IMPERIUM =====" << endl << endl;

    Consul consul("Julio Cesar", "Consul");
    cout << "CONSUL: " << consul.getNombre() << " | Cargo: " << consul.getCargo() << endl;

    Legatus legatus("Marco Antonio", "Legion XIII Gemina");
    cout << "LEGATUS: " << legatus.getNombre() << " | Asignado a: " << legatus.getLegioAsignada() << endl << endl;

    // Crear Bitácora
    BitacoraGuerra bitacora;

    // Crear Legiones con sus tropas dinámicas (gestión manual de memoria)
    Legion legion1("Legio XIII Gemina", "Marco Antonio");
    legion1.agregarUnidad(new Legionario(120));
    legion1.agregarUnidad(new Caballeria(30));
    legion1.agregarUnidad(new Ballesta(20));

    Legion legion2("Legio I Italica", "Tito Labieno");
    legion2.agregarUnidad(new Legionario(100));
    legion2.agregarUnidad(new Caballeria(25));
    legion2.agregarUnidad(new Ingeniero(10));

    // Simular batalla entre Legion 1 (TriplexAcies) y Legion 2 (Cuneus)
    simularBatalla(legion1, "TriplexAcies", legion2, "Cuneus", bitacora);

    // Mostrar historial registrado en la bitácora
    bitacora.mostrarHistorial();

    return 0;
}