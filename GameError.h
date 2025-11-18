#pragma once
#include <string>
#include <stdexcept>
#include <SDL3/SDL.h>

//superclase de todas las excepciones del juego
class GameError : public std::logic_error {
public:
    GameError(const std::string& msg) : std::logic_error(msg) {}
};

//error relacionado con SDL
class SDLError : public GameError {
public:
    SDLError() : 
        GameError(std::string("SDL Error: ") + SDL_GetError()) {
    }
};

//error de archivo no encontrado
class FileNotFoundError : public GameError {
public:
    FileNotFoundError(const std::string& filename) : 
        GameError("Error: El siguiente archivo no ha sido encontrado: " + filename) {
    }
};

//error de formato de archivo (archivo corrupto o mal formado)
class FileFormatError : public GameError {
public:
    FileFormatError(const std::string& filename, int line, const std::string& msg) :
        GameError("Error: Archivo corrupto o mal formado: " + filename + " en la linea " + std::to_string(line) + ": " + msg) {
    }
};
