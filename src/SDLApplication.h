#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include "gameStateMachine.h"

//Declaraciones anticipadas
class GameError;
class Texture;

/**
 * Clase principal del juego.
 */
class SDLApplication : private GameStateMachine
{
public:
	//Métodos privados del GameStateMachine
	using GameStateMachine::pushState;
	using GameStateMachine::popState;
	using GameStateMachine::empty;
	using GameStateMachine::replaceState;

	// Se actualiza el juego cada tantos milisegundos
	static constexpr int FRAME_RATE = 30;

	enum TextureName
	{
		FROG = 0,
		BACKGROUND,
		CAR1, CAR2, CAR3, CAR4, CAR5,
		LOG1, LOG2,
		TURTLE,
		WASP,
		MENUBACKGROUND,
		CONTINUAR,
		ELIGEUNMAPA,
		GAMEOVER,
		HASGANADO,
		LEFT,
		RIGHT,
		AVISPADO,
		ORIGINAL,
		PRACTICA1,
		TRIVIAL,
		VELOZ,
		REINICIAR,
		SALIR,
		VOLVERALMENU,
		NUM_TEXTURES
	};


	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 448;
	static constexpr int WINDOW_HEIGHT = 484;

private:
	std::array<Texture*, NUM_TEXTURES> textures;
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool exit;

public:
	SDLApplication();
	~SDLApplication();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	// Ejecuta el bucle principal del juego
	void run();

	//Crea una ventana de error
	static void mostrarError(const GameError& e);

	//obtiene ventana de SDL para render 
	SDL_Renderer* getRenderer() const { return renderer; }

	//Cambia el estado de salida del juego
	void setExit(bool e) { exit = e; }
};


inline Texture*
SDLApplication::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
