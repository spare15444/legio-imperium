// #include <string>
// #include <iostream>

#include "estrategias.cpp"
#include "../include/motor_combate.hpp"
using namespace std;

void simularBatalla(Legion& l1, string strat1, Legion& l2, string strat2, BitacoraGuerra& bitacora) {
    int turno = 1;
    cout << "=== INICIO DE SIMULACION DE BATALLA ===" << endl;
    cout << l1.getNombre() << " VS " << l2.getNombre() << endl << endl;
    while (l1.obtenerHPtotal() > 0 && l2.obtenerHPtotal() > 0) {
        // 1. Resolver estadísticas de Legión 1 según su estrategia
        EstadisticasCombate stats1;
        if (strat1 == "TriplexAcies") {
            stats1 = triplexAcies(l1.obtenerAtaqueBase(), l1.obtenerDefensaBase(), l1.obtenerPorcentajeLegionarios(), l1.obtenerAtaqueBallestas());
        } else if (strat1 == "Cuneus") {
            stats1 = cuneus(l1.obtenerAtaqueBase(), l1.obtenerDefensaBase(), l1.obtenerAtaqueCaballeria());
        } else {
            stats1 = orbis(l1.obtenerAtaqueBase(), l1.obtenerDefensaBase());
        }

        // 2. Resolver estadísticas de Legión 2 según su estrategia
        EstadisticasCombate stats2;
        if (strat2 == "TriplexAcies") {
            stats2 = triplexAcies(l2.obtenerAtaqueBase(), l2.obtenerDefensaBase(), l2.obtenerPorcentajeLegionarios(), l2.obtenerAtaqueBallestas());
        } else if (strat2 == "Cuneus") {
            stats2 = cuneus(l2.obtenerAtaqueBase(), l2.obtenerDefensaBase(), l2.obtenerAtaqueCaballeria());
        } else {
            stats2 = orbis(l2.obtenerAtaqueBase(), l2.obtenerDefensaBase());
        }

        // --- Ataca Legion 1 a Legion 2 ---
        double dano1 = stats1.ataque - stats2.defensa;
        int bajas2 = (dano1 > 0) ? static_cast<int>(dano1 / 25.0) : 2;
        if (bajas2 > l2.obtenerHPtotal()) bajas2 = l2.obtenerHPtotal();
        
        l2.aplicarBajas(bajas2);
        bitacora.registrarEvento({turno, l2.getNombre(), "General", bajas2, l1.getNombre() + " ataca con " + strat1});

        if (l2.obtenerHPtotal() <= 0) break;

        // --- Ataca Legion 2 a Legion 1 ---
        double dano2 = stats2.ataque - stats1.defensa;
        int bajas1 = (dano2 > 0) ? static_cast<int>(dano2 / 25.0) : 2;
        if (bajas1 > l1.obtenerHPtotal()) bajas1 = l1.obtenerHPtotal();

        l1.aplicarBajas(bajas1);
        bitacora.registrarEvento({turno, l1.getNombre(), "General", bajas1, l2.getNombre() + " ataca con " + strat2});

        cout << "Turno " << turno << " -> " << l1.getNombre() << " HP: " << l1.obtenerHPtotal() 
             << " | " << l2.getNombre() << " HP: " << l2.obtenerHPtotal() << endl;

        turno++;
    }

    if (l1.obtenerHPtotal() > 0) {
        cout << "\n¡VICTORIA! La legion " << l1.getNombre() << " ha triunfado en el campo de batalla." << endl;
    } else {
        cout << "\n¡VICTORIA! La legion " << l2.getNombre() << " ha triunfado en el campo de batalla." << endl;
    }
}
