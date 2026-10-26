#include <iostream>
#include <string>
#include <list>
//hola
using namespace std;

// CLASE PERSONA ----------------------------------------------------------------
class Persona {
private:
    string nombre;

public:
    Persona() { nombre = ""; }
    Persona(string nombre) { this->nombre = nombre; }
    string getNombre() { return nombre; }
    void setNombre(string nombre) { this->nombre = nombre; }
};

// CLASE CONSUL ----------------------------------------------------------------
class Consul : public Persona {
private:
    string cargo;
public:
    Consul() : Persona() { cargo = ""; }
    Consul(string nombre, string cargo) : Persona(nombre) { this->cargo = cargo; }
    string getCargo() { return cargo; }
    void setCargo(string cargo) { this->cargo = cargo; }
};

// CLASE LEGATUS ---------------------------------------------------------------
class Legatus : public Persona {
private:
    string legioAsignada;
public:
    Legatus() : Persona() { legioAsignada = ""; }
    Legatus(string nombre, string legioAsignada) : Persona(nombre) { this->legioAsignada = legioAsignada; }
    string getLegioAsignada() { return legioAsignada; }
    void setLegioAsignada(string legioAsignada) { this->legioAsignada = legioAsignada; }
};

// CLASE UNIDAD MILITAR ----------------------------------------------------------
class UnidadMilitar {
protected:
    int cantidad;
    int ataque;
    int defensa;
    int costo;

public:
    UnidadMilitar() { cantidad = 0; ataque = 0; defensa = 0; costo = 0; }
    UnidadMilitar(int cantidad, int ataque, int defensa, int costo) {
        this->cantidad = cantidad;
        this->ataque = ataque;
        this->defensa = defensa;
        this->costo = costo;
    }

    int getCantidad() { return cantidad; }
    void setCantidad(int cantidad) { this->cantidad = cantidad; }
    int getAtaque() { return ataque; }
    int getDefensa() { return defensa; }
    int getCosto() { return costo; }

    virtual int calcularAtaque() { return cantidad * ataque; }
    virtual int calcularDefensa() { return cantidad * defensa; }
};

// TIPOS DE UNIDAD 
class Legionario : public UnidadMilitar{
public:
    Legionario() : UnidadMilitar(0, 25, 35, 5) {}
    Legionario(int cantidad) : UnidadMilitar(cantidad, 25, 35, 5) {}
    int calcularAtaque() override { return cantidad * ataque; }
    int calcularDefensa() override { return cantidad * defensa; }
};

class Caballeria : public UnidadMilitar {
public:
    Caballeria() : UnidadMilitar(0, 45, 15, 12) {}
    Caballeria(int cantidad) : UnidadMilitar(cantidad, 45, 15, 12) {}
    int calcularAtaque() override { return cantidad * ataque; }
    int calcularDefensa() override { return cantidad * defensa; }
};

class Ballesta : public UnidadMilitar {
public:
    Ballesta() : UnidadMilitar(0, 60, 5, 20) {}
    Ballesta(int cantidad) : UnidadMilitar(cantidad, 60, 5, 20) {}
    int calcularAtaque() override { return cantidad * ataque; }
    int calcularDefensa() override { return cantidad * defensa; }
};

class Ingeniero : public UnidadMilitar {
public:
    Ingeniero() : UnidadMilitar(0, 5, 20, 10) {}
    Ingeniero(int cantidad) : UnidadMilitar(cantidad, 5, 20, 10) {}
    int calcularAtaque() override { return cantidad * ataque; }
    int calcularDefensa() override { return cantidad * defensa; }
};

class Esclavo : public UnidadMilitar{
public:
    Esclavo() : UnidadMilitar(0, 2, 5, 1) {}
    Esclavo(int cantidad) : UnidadMilitar(cantidad, 2, 5, 1) {}
    int calcularAtaque() override { return cantidad * ataque; }
    int calcularDefensa() override { return cantidad * defensa; }
};

// ================================== BITÁCORA DE GUERRA ==================================
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

// ================================== ESTRATEGIAS TÁCTICAS ===================================
struct EstadisticasCombate{
    double ataque;
    double defensa;
    bool caballeriaInmovilizada = false;
};

EstadisticasCombate triplexAcies(
    double ataqueBase,
    double defensaBase,
    double porcentajeLegionarios,
    double ataqueBallestas
) {
    EstadisticasCombate resultado;
    resultado.ataque = ataqueBase * 1.10 + ataqueBallestas * 0.15;
    resultado.defensa = defensaBase * 1.25;

    if (porcentajeLegionarios >= 50.0) {
        resultado.defensa *= 1.35;
    }
    return resultado;
}

EstadisticasCombate cuneus(
    double ataqueBase,
    double defensaBase,
    double ataqueCaballeria
) {
    EstadisticasCombate resultado;
    resultado.ataque = ataqueBase * 1.45 + ataqueCaballeria * 0.50;
    resultado.defensa = defensaBase * 0.75;
    return resultado;
}

EstadisticasCombate orbis(
    double ataqueBase,
    double defensaBase
) {
    EstadisticasCombate resultado;
    resultado.ataque = ataqueBase * 0.65;
    resultado.defensa = defensaBase * 1.60;
    resultado.caballeriaInmovilizada = true;
    return resultado;
}

// CLASE LEGION --------------------------------------------------------------------
class Legion {
private:
    string nombre;
    string legatusAsignado;    
    list<UnidadMilitar*> unidades;

public:
    Legion(string nombre, string legatus) {
        this->nombre = nombre;
        this->legatusAsignado = legatus;
    }

    void agregarUnidad(UnidadMilitar* unidad) {
        unidades.push_back(unidad);
    }

    int obtenerHPtotal() {
        int totalHP = 0;
        for (auto it = unidades.begin(); it != unidades.end(); ++it) {
            totalHP += (*it)->getCantidad();
        }
        return totalHP;
    }

    double obtenerAtaqueBase() {
        double atkBase = 0;
        for (auto it = unidades.begin(); it != unidades.end(); ++it) {
            atkBase += (*it)->calcularAtaque();
        }
        return atkBase;
    }

    double obtenerDefensaBase() {
        double defBase = 0;
        for (auto it = unidades.begin(); it != unidades.end(); ++it) {
            defBase += (*it)->calcularDefensa();
        }
        return defBase;
    }

    double obtenerPorcentajeLegionarios() {
        int totalSoldados = 0;
        int soldadosLegionarios = 0;
        for (auto it = unidades.begin(); it != unidades.end(); ++it) {
            totalSoldados += (*it)->getCantidad();
            if (dynamic_cast<Legionario*>(*it) != nullptr) {
                soldadosLegionarios += (*it)->getCantidad();
            }
        }
        if (totalSoldados == 0) return 0.0;
        return (static_cast<double>(soldadosLegionarios) / totalSoldados) * 100.0;
    }

    double obtenerAtaqueBallestas(){
        double atkBallestas = 0;
        for (auto it = unidades.begin(); it != unidades.end(); ++it) {
            if (dynamic_cast<Ballesta*>(*it) != nullptr) {
                atkBallestas += (*it)->calcularAtaque();
            }
        }
        return atkBallestas;
    }

    double obtenerAtaqueCaballeria() {
        double atkCaballeria = 0;
        for (auto it = unidades.begin(); it != unidades.end(); ++it) {
            if (dynamic_cast<Caballeria*>(*it) != nullptr) {
                atkCaballeria += (*it)->calcularAtaque();
            }
        }
        return atkCaballeria;
    }

    string getNombre() { return nombre; }

    void aplicarBajas(int bajas) {
        for (auto it = unidades.begin(); it != unidades.end(); ++it) {
            if (bajas <= 0) break;
            int cant = (*it)->getCantidad();
            if (cant <= bajas) {
                bajas -= cant;
                (*it)->setCantidad(0);
            } else {
                (*it)->setCantidad(cant - bajas);
                bajas = 0;
            }
        }
    }

    ~Legion() {
        for (auto it = unidades.begin(); it != unidades.end(); ++it) {
            delete *it;
        }
        unidades.clear();
    }   
};

// ================================== MOTOR DE COMBATE =====================================
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
