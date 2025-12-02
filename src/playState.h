#pragma once
#include "GameState.h"
#include "Vector2D.h"
#include <random>
#include <iostream>
#include <fstream>

class HomedFrog;
class Frog;
class SceneObject;
class SDLApplication;
struct Collision;

class PlayState :
	public GameState
{
public:
	using Anchor = std::list<SceneObject*>::iterator;
protected:
	std::vector<bool> reachedHomes;
	std::list<SceneObject*> sceneObjects;
	std::vector<Anchor> toDelete;
	std::vector<HomedFrog*> homedFrogs;
	Frog* frog;

	//Rango de tiempo para spawn de avispas
	static constexpr int WASP_MIN_SPAWN = 10;
	static constexpr int WASP_MAX_SPAWN = 15;

	//Rango de tiempo de vida de avispas
	static constexpr int WASP_MIN_LIFE = 3;
	static constexpr int WASP_MAX_LIFE = 10;

	std::mt19937_64 randomGenerator;

	int waspSpawnTime;
	int currentTime;

	Point2D<float> frogSpawn;

private:
	void render() const;
	void update();
	void handleEvent(const SDL_Event&) override;
	bool exit;
	std::string mapFile;

public:
	// Extremo inferior del río
	static constexpr int RIVER_LOW = 210;

	//Constructor
	PlayState(SDLApplication* game, std::string file);

	bool isActive = true; 
	//Destructor
	~PlayState();

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

	//Destroza los elementos visuales del juego
	void destroySceneObjects();

	//Devuelve un número aleatorio entre el rango
	int getRandomRange(int min, int max);

	//Destructor de TODO, simplificacion de un solo metodo
	void destroyAllElements();

	//Añade un iterador al vector toDelete que será destruido al final del Update
	void deleteAfter(Anchor it);

	//Inicializa lso recursos necesarios de nuevo para el juego
	void buildHomes();

	//Añade un SceneObject a la lista sceneObjects
	Anchor addSceneObject(SceneObject*);

	//Quita un SceneObject de la lista sceneObjects
	void removeSceneObject(Anchor);

	//Se llama en la constructora de Game y lee el archivo cuya ruta está en MAP_FILE
	void readFile(std::string file);

	std::string getFile() const;
};
