#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if (map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)

	SDL_Texture* text = nullptr;
	text = App->tex->Load(helloMapTileset.imageSource);

	App->render->Blit(text, 0, 0);
	
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map

	//delete[] &helloMap;
	//delete[] &helloMapTileset;



	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data

		LoadFillMapData(map_file);

	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!

	LoadTileset(map_file);
	

	if(ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything

		LOG("Map ----");
		LOG("orientation: %s renderorder: %s", helloMap.orientation, helloMap.renderorder);
		LOG("width: %i height: %i", helloMap.width, helloMap.height);
		LOG("tile_width: %i tile_height: %i", helloMap.tileWidth, helloMap.tileHeight);
		LOG("nextobjectid: %i", helloMap.nextobjectid);
		LOG("Tileset ----");
		LOG("name: %s, firstid: %i", helloMapTileset.name, helloMapTileset.firstgid);
		LOG("tile width: %i tile height: %i", helloMapTileset.tilewidth, helloMapTileset.tileheight);
		LOG("spacing: %i margin: %i", helloMapTileset.spacing, helloMapTileset.margin);
		LOG("tilecount: %i columns: %i", helloMapTileset.tilecount, helloMapTileset.columns);
		LOG("imageSource: %s", helloMapTileset.imageSource);
		LOG("imageWidth: %i imageHeight: %i", helloMapTileset.imageWidth, helloMapTileset.imageHeight);
		LOG("imageSource: %s", helloMapTileset.imageSource);
	}

	map_loaded = ret;

	return ret;
}

pugi::xml_node j1Map::LoadFillMapData(pugi::xml_document& mapData)
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = mapData.load_file("maps/hello.tmx");

	if (result == NULL)
		LOG("Could not load map tmx file hello.tmx. pugi error: %s", result.description());

	else

		helloMap.orientation = mapData.child("map").attribute("orientation").as_string();
		helloMap.renderorder = mapData.child("map").attribute("renderorder").as_string();
		helloMap.width = mapData.child("map").attribute("width").as_int();
		helloMap.height = mapData.child("map").attribute("height").as_int();
		helloMap.tileWidth = mapData.child("map").attribute("tilewidth").as_int();
		helloMap.tileHeight = mapData.child("map").attribute("tileheight").as_int();
		helloMap.nextobjectid = mapData.child("map").attribute("nextobjectid").as_int();

	return ret;
}

pugi::xml_node j1Map::LoadTileset(pugi::xml_document& Tileset)
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = Tileset.load_file("maps/hello.tmx");

	if (result == NULL)
		LOG("Could not load map tmx file hello.tmx to find the map tileset. pugi error: %s", result.description());

	else

		for (pugi::xml_node tileset = Tileset.child("map").child("tileset") ; tileset ; tileset = tileset.next_sibling("tileset"))
		{
				helloMapTileset.firstgid = tileset.attribute("firstgid").as_int();
				helloMapTileset.name = tileset.attribute("name").as_string();
				helloMapTileset.tilewidth = tileset.attribute("tilewidth").as_int();
				helloMapTileset.tileheight = tileset.attribute("tileheight").as_int();
				helloMapTileset.spacing = tileset.attribute("spacing").as_int();
				helloMapTileset.margin = tileset.attribute("margin").as_int();
				helloMapTileset.tilecount = tileset.attribute("tilecount").as_int();
				helloMapTileset.columns = tileset.attribute("columns").as_int();
				helloMapTileset.imageSource = tileset.child("image").attribute("source").as_string();
		}
		return ret;
}

