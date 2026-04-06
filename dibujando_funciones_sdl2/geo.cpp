/*

dibujar con sdl2 usando geometría primitiva

comando sugerido: g++ -Wall -Wextra geo.cpp $(pkg-config --libs --cflags sdl2) -o geito

*/

#include <iostream>
#include <SDL2/SDL.h>
#include <array>

#define NUMELEMARRAY(a) (sizeof(a) / sizeof(a[0]))

// Rectángulo que ocupa el dibujo
#define ANCHOPERSONA 50
#define ALTOPERSONA 70

#define VANCHO 650
#define VALTO 480

SDL_Texture *crearPersona(SDL_Renderer *render)
{
    SDL_Surface *superficie = SDL_CreateRGBSurface(0, ANCHOPERSONA, ALTOPERSONA, 32, 0, 0, 0, 0);

    // Creamos la superficie de la persona, el cual es un rectángulo de 50x70
    if (!superficie)
        return nullptr;

    // Pintamos la superficie de blanco
    SDL_FillRect(superficie, nullptr, SDL_MapRGB(superficie->format, 0xFF, 0xFF, 0xFF));

    // Creamos la estructura de la persona
    SDL_Rect esqueleto[] = {
        {20, 0, 10, 10},  // Cabeza
        {0, 10, 10, 40},  // Brazo derecho
        {40, 10, 10, 40}, // Brazo izquierdo
        {10, 10, 30, 30}, // Cuerpo
        {10, 40, 10, 30}, // Pierna derecha
        {30, 40, 10, 30}, // Pierna izquierda
    };

    std::array<unsigned, 3> color = {0x3F, 0x5A, 0x55}; // Color azul

    for (unsigned i = 0; i < NUMELEMARRAY(esqueleto); i++)
    {
        SDL_FillRect(superficie, &esqueleto[i], SDL_MapRGB(superficie->format, color.at(0), color.at(1), color.at(2)));
        // Cambiamos de color de acuerdo a las partes del dibujo
        for (unsigned j = 0; j < color.size(); j++)
        {
            color.at(j) = color.at(j) << 1;
        }
    }

    SDL_Texture *textura = SDL_CreateTextureFromSurface(render, superficie);
    SDL_FreeSurface(superficie);

    return textura;
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO != 0))
        return -1;

    SDL_Window *ventana = SDL_CreateWindow("Geometria con SDL2", 100, 100, VANCHO, VALTO, SDL_WINDOW_SHOWN);
    if (!ventana)
        return -1;
    SDL_Renderer *render = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!render)
        return -1;
    SDL_Texture *persona = crearPersona(render);
    if (!persona)
        return -1;

    // funciones lambda

    // esta función determina la posición del siguiente dibujo en el eje x
    auto sigx = [](SDL_Rect &r) -> SDL_Rect
    {
        SDL_Rect resultado = r;
        resultado.x = r.x + ANCHOPERSONA + 10; // Espacio entre dibujos
        return resultado;
    };

    // esta función determina la posición del siguiente dibujo en el eje y
    auto sigy = [](SDL_Rect &r) -> SDL_Rect
    {
        SDL_Rect resultado = r;
        resultado.y = r.y + ALTOPERSONA + 10; // Espacio entre dibujos
        return resultado;
    };

    bool salir = false;
    SDL_Event evento;

    while (!salir)
    {
        while (SDL_PollEvent(&evento))
        {
            if (evento.type == SDL_QUIT)
            {
                salir = true;
            }
        }
        SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF); // fondo ventana blanco
        SDL_RenderClear(render);

        SDL_Rect e = {0, 0, ANCHOPERSONA, ALTOPERSONA};
        // hasta no llenar la ventana seguir dibujando
        do
        {
            SDL_RenderCopy(render, persona, nullptr, &e);
            SDL_Rect temp = sigx(e);
            // Si el siguiente dibujo en x sale del ancho de la ventnaa ir hacia abajo
            if (temp.x + ANCHOPERSONA > VANCHO)
            {
                e.x = 0;
                temp = sigy(e);
                // Si el sig. dibujo sale del alto de la ventna ... salir del ciclo
                if (temp.y + ALTOPERSONA > VALTO)
                    break;
            }
            e = temp;
        } while (true);

        SDL_RenderCopy(render, persona, nullptr, &e);
        SDL_RenderPresent(render);
    }
    SDL_DestroyTexture(persona);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(ventana);

    SDL_Quit();

    return 0;
}