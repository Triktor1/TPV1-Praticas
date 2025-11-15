#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <array>
#include <istream>
#include <vector>
#include "Vehicle.h"
#include "Log.h"
#include "Frog.h"
#include "Wasp.h"
#include <random>

// Declaraciones anticipadas
class Texture;
class Vehicle;
class Log;
class Frog;
class HomedFrog;
class Wasp;

/**
 * Clase principal del juego.
 */
class Game
{
public:
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
	std::vector<Vehicle*> vehicles;
	std::vector<Log*> logs;
	std::vector<HomedFrog*> homedFrogs;
	std::vector<bool> reachedHomes;
	std::vector<Wasp*> wasps;

	std::vector<SceneObject*> sceneObjects;

	Frog* frog;

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

	//metodos constructores con istream
};

inline Texture*
Game::getTexture(TextureName name) const
{
	return textures[name];
}

#endif // GAME_H
