enum tipo_uber {
    UBER_PLANET,
    UBER_XL,
    UBER_BLACK
};

struct posicion {
    double x;
    double y;
};

struct info_auto {
    bool disponibilidad;
    posicion posXY;
    tipo_uber tipo;
    char placa[7];
};

struct info_servicio {
    int viajes;
    int autos_libres;
    double ganancia;
};

program UBER{
    version UBER_VERSION{
        info_auto solicitar_viaje(posicion) = 1;
        void terminar_viaje(posicion, double, string) = 2;
        info_servicio estado_servicio(void) = 3;
    } = 1;
} = 0x20000002;