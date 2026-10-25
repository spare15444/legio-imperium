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

