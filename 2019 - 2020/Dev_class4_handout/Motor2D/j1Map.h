#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
// ----------------------------------------------------

struct TilesetInfo
{
	int firstgid = 0;
	const char* name = nullptr;
	int tilewidth = 0;
	int tileheight = 0;
	int spacing = 0;
	int margin = 0;
	int tilecount = 0;
	int columns = 0;
	const char* imageSource = nullptr;
	int imageWidth = 0;
	int imageHeight = 0;
};


// TODO 1: Create a struct needed to hold the information to Map node

struct MapInfo
{
	const char* orientation = nullptr;
	const char* renderorder = nullptr;
	int width = 0;
	int height = 0;
	int tileWidth = 0;
	int tileHeight = 0;
	int nextobjectid = 0;
};


// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

private:

	//Load and fill map data
	pugi::xml_node LoadFillMapData(pugi::xml_document&);

	//Load a Tileset
	pugi::xml_node LoadTileset(pugi::xml_document&);

public:

	// TODO 1: Add your struct for map info as public for now
	MapInfo				helloMap;
	TilesetInfo			helloMapTileset;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__