#include <stdlib.h>

typedef char tipo_cadena[50];

union tipo_valor{
    int valor_entero;//0
    float valor_real;//1
    bool valor_logico;//2
    tipo_cadena valor_cad;//3
};

struct tipo_datoTS{
    tipo_cadena nombre;

    /**
     * 0 = entero
     * 1 = real
     * 2 = logico (bool)
     * 3 = cadena de caracteres
     * 4 = procedimiento
     * 5 = clase
     **/
    int tipo;
    tipo_valor valor;
    bool init;
};

struct nodo{
    tipo_datoTS dato;
    struct nodo *sig;
};

class Tabla{
    public:
        nodo *primero;
        bool insertar(tipo_datoTS *identificador);
        bool buscar(tipo_cadena nombre, tipo_datoTS *identificador);
        nodo * getFirst();
};