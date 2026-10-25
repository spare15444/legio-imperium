#include <string>
#include <list>
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
