#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;
// reduction para pintar solo una figura de las seis
uniform vec2 reduction = vec2(1./6., 1.0);
// reduccion para pintar en un tablero con 15x15
uniform vec2 secondReduction = vec2(15., 15.);
uniform float wide = 1./6.;

void main()
{
    // offset inicial (redundante)
    vec2 offset = vec2(0, 0);

    // calculamos coordinates para todas aquellas veces que no hemos de girar la
    // orientacion de nada, asi luego solo necesitamos sumar el offset que toque
    vec2 coordinates = (reduction * secondReduction * vtexCoord);

    // calculamos la (col, row) para que sea mas facil
    int col = int(vtexCoord.x/(1./15.));
    int row = int(vtexCoord.y/(1./15.));
    
    
    /*
     * IMPORTANTE
     * para poder pintar el mismo elemento varias veces, por ejemplo multiples bolitas
     * o una pared en toda una columna, hemos de limitar las coordinates entre la
     * wide de un elemento. Es decir, si tenemos 6 figuras diferentes (fantasma, pacman, bolita...)
     * wide = 1/6. Por tanto, si queremos pintar pacman, hemos de limitar coordinates
     * entre 1/6 y 2/6.
     * para conseguir eso, utilizamos la funcion:
     *
     * coordinates.x = mod(coordinates.x - offset.x, wide) + offset.x;
     *
     * donde mod(a, b) es equivalente a a%b, pero con decimales, despues sumamos offset.x
     * y de esta forma limitaremos a coordinates tal que [coordinates.x, coordinates.x + wide]
     * asi podemos pintar fantasma ... fantasma ... fantasma
     * en vez de          fantasma ... pacman   ... bolita 
    */
    
    if (row == 0 || row == 14) {        // pintar bordes cuadrados sin giro
        offset = vec2(3./6., 0.0);
        coordinates += offset;
        coordinates.x = mod(coordinates.x - offset.x, wide) + offset.x;
    } else {                            // pintar todo el interior con bolitas
        offset = vec2(5./6., 0.0);
        coordinates += offset;
        coordinates.x = mod(coordinates.x - offset.x, wide) + offset.x;
    }
    
    // ahora reemplazaremos todo lo anterior con lo que queramos, como si trabajaramos por capas
    
    // pintamos mas muros azules horizontales
    if (row != 0 && row != 14 && row % 2 == 0 && 
        col != 1 && col != 7 && col != 13) {
        offset = vec2(3./6., 0.0);
        coordinates += offset;
        coordinates.x = mod(coordinates.x - offset.x, wide) + offset.x;
    }
    
    // pintamos pacman
    if (row == 1 && col == 4) {
        offset = vec2(1./6., 0.0);
        coordinates += offset;
        coordinates.x = mod(coordinates.x - offset.x, wide) + offset.x;
    }
    
    // pintamos fantasma
    if (row == 1 && col == 5) {
        offset = vec2(0./6., 0.0);
        coordinates += offset;
        coordinates.x = mod(coordinates.x - offset.x, wide) + offset.x;
    }
    
    // pintamos correctamente los bordes horizontales (que han de girarse)
    // por ello recalculamos coordinates, pero con vtexCoord.yx en vez de vtexCoord.xy
    if (col == 0 || col == 14) {
        offset = vec2(3./6., 0.0);
        coordinates = (reduction * secondReduction * vtexCoord.yx);
        coordinates += offset;
        coordinates.x = mod(coordinates.x - offset.x, wide) + offset.x;
    }
    
    // pintamos cada una de las esquinas orientandolas correctamente, que se consigue
    // cambiando el signo y el orden de las variables xy segun convenga
    if (col == row && col == 0) {
        offset = vec2(4./6., 0.0);
        coordinates = (reduction * secondReduction * -vtexCoord.yx);
        coordinates += offset;
        coordinates.x = mod(coordinates.x - offset.x, wide) + offset.x;
    } else if (col == 0 && row == 14) {
        offset = vec2(4./6., 0.0);
        coordinates = (reduction * secondReduction * vec2(-vtexCoord.x,vtexCoord.y));
        coordinates += offset;
        coordinates.x = mod(coordinates.x - offset.x, wide) + offset.x;
    } else if (col == 14 && row == 14) {
        offset = vec2(4./6., 0.0);
        coordinates = (reduction * secondReduction * vec2(vtexCoord.x,vtexCoord.y));
        coordinates += offset;
        coordinates.x = mod(coordinates.x - offset.x, wide) + offset.x;
    } else if (col == 14 && row == 0) {
        offset = vec2(4./6., 0.0);
        coordinates = (reduction * secondReduction * vec2(vtexCoord.x,-vtexCoord.y));
        coordinates += offset;
        coordinates.x = mod(coordinates.x - offset.x, wide) + offset.x;
    }

    fragColor = texture(colorMap, coordinates);
}
