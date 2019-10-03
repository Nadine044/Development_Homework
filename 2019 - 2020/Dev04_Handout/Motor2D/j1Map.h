#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 1: Create a struct for the map layer

struct MapLayer
{
	const char* name = nullptr;
	uint width;
	uint height;
	uint* gidData = nullptr;
	uint gid;
	const char* dataEncoding = nullptr;

	~MapLayer() {
		RELEASE_ARRAY(gidData);
	};

	inline uint Get(int x, int y) const
	{
		int result = ((y * height) + x);
		LOG("Result: %i", result);
		return result;

	}

};



// ----------------------------------------------------

	// TODO 6: Short function to get the value of x,y



// ----------------------------------------------------
struct TileSet
{
	// TODO 7: Create a method that receives a tile id and returns it's Rect

	p2SString			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;

	SDL_Rect GetRectFromID(const int id)
	{
		SDL_Rect ret;

		int tileID = id - firstgid;

		int width_with_margin = tile_width + spacing;
		int height_with_margin = tile_height + spacing;

		ret.x = (tileID % num_tiles_width) * width_with_margin + margin;
		ret.y = (tileID / num_tiles_width) * height_with_margin + margin;
		ret.w = tile_width;
		ret.h = tile_height;

		return ret;

	}
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	p2List<TileSet*>	tilesets;
	// TODO 2: Add a list/array of layers to the map!

	p2List<MapLayer*> layers;


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

	TileSet* GetTilesetFromID(int id) const;

	// TODO 8: Create a method that translates x,y coordinates from map positions to world positions
	
	iPoint j1Map::MapToWorld(int x, int y) const
	{
		iPoint ret;

		ret.x = x * data.tile_width;
		ret.y = y * data.tile_height;

		return ret;
	}
private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	// TODO 3: Create a method that loads a single laye
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);

public:

	MapData data;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__