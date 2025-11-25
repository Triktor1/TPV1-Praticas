#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <list>
#include "gameStateMachine.h"

#include "Vector2D.h"

//Declaraciones anticipadas
class HomedFrog;
class Frog;
class SceneObject;
class Texture;
class GameError;

struct Collision;

/**
 * Clase principal del juego.
 */
class Game : private GameStateMachine
{
public:
	using Anchor = std::list<SceneObject*>::iterator;
	// Se actualiza el juego cada tantos milisegundos
	static constexpr int FRAME_RATE = 30;
	// Tamaño real de la ventana
	static constexpr int WINDOW_WIDTH = 448;
	static constexpr int WINDOW_HEIGHT = 484;
	// Extremo inferior del río
	static constexpr int RIVER_LOW = 210;


	enum TextureName
	{
		FROG = 0,
		BACKGROUND,
		CAR1, CAR2, CAR3, CAR4, CAR5,
		LOG1, LOG2,
		TURTLE,
		WASP,
		NUM_TEXTURES
	};

private:
	//Rango de tiempo para spawn de avispas
	static constexpr int WASP_MIN_SPAWN = 10;
	static constexpr int WASP_MAX_SPAWN = 15;
	
	//Rango de tiempo de vida de avispas
	static constexpr int WASP_MIN_LIFE = 3;
	static constexpr int WASP_MAX_LIFE = 10;

	std::mt19937_64 randomGenerator;
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::array<Texture*, NUM_TEXTURES> textures;
	std::vector<bool> reachedHomes;
	std::list<SceneObject*> sceneObjects;
	std::vector<HomedFrog*> homedFrogs;
	Frog* frog;

	//Lista a la que se le meten los iteradores de los SceneObjects a borrar este ciclo
	std::vector<Anchor> toDelete;

	void render() const;
	void update();
	void handleEvents();

	bool exit;
	int waspSpawnTime;
	int currentTime;

	Point2D<float> frogSpawn;

public:
	Game();
	~Game();

	// Obtiene una textura por su nombre
	Texture* getTexture(TextureName name) const;

	// Ejecuta el bucle principal del juego
	void run();

	// Comprueba si hay algún objeto colocado en ese rectángulo
	Collision checkCollision(const SDL_FRect& rect) const;

	//Devuelve la posición de spawn de la rana
	Point2D<float> getFrogSpawn() const;

	//Cambia la posición de spawn de la rana
	void setFrogSpawn(float x, float y);

	//Comprueba con qué nido se ha chocado la rana, y si no ha sido alcanzado antes, marca que ahora sí
	//[IMPORTANTE] Este método sólo funciona porque se llama después de comprobar que ha habido una colisión de tipo HOME
	bool tryReachHome(const SDL_FRect& hitbox);

	//Comprueba que si todas las casas no cumplen el metodo GetReached(), devuelve false
	//a no ser que sea lo contrario y así seria todo true.
	bool allFrogsHome() const;

	//Devuelve un número aleatorio entre el rango
	int getRandomRange(int min, int max);

	//Destructor de TODO, simplificacion de un solo metodo
	void destroyAllElements();

	//Se llama en la constructora de Game y lee el archivo cuya ruta está en MAP_FILE
	void readFile(const char* file);
	
	//Añade un iterador al vector toDelete que será destruido al final del Update
	void deleteAfter(Anchor it);

	//Destrozar todos los elementos (menos ventana SDL) y que tiene dentro el init
	void reset();
	
	//Destroza los elementos visuales del juego
	void destroySceneObjects();

	//Inicializa lso recursos necesarios de nuevo para el juego
	void buildHomes();

	//Crea una ventana de error
	static void mostrarError(const GameError& e);
	};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
