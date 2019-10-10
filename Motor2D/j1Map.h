#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// ----------------------------------------------------
// Object for Colliders
enum class ObjectType {
	UNKNOWN = 0,
	PLATFORM,
	SOLID,
	DAMAGE,
	PLAYER
};


struct Object 
{
	uint				id;
	p2SString			name;
	ObjectType			type;
	SDL_Rect*			box;

};


struct MapObjectgroup 
{
	uint				id;
	p2SString			name;
	Object*				objects;
	uint				objects_size;
};


// ----------------------------------------------------
struct MapLayer 
{
	p2SString			name;
	uint				width;
	uint				height;
	uint*				data; //Tile Ids
	inline uint Get(int x, int y) const
	{
		return x + y * width;
	}
};


// ----------------------------------------------------
struct TileSet
{
	
	SDL_Rect* Tilerect = new SDL_Rect;
	SDL_Rect* TileRect(uint tile_id) {
		SDL_Rect* ret = Tilerect; 
		int x = ((tile_id - firstgid) % num_tiles_width);
		int y = ((tile_id - firstgid) / num_tiles_width);

		ret->x = x*tile_width  + margin + spacing*x;
		ret->y = y*tile_height + margin + spacing*y;
		ret->w = tile_width;
		ret->h = tile_height;

		return ret;
	}

	inline p2Point<uint> GetPos(uint x, uint y) {
		p2Point<uint> ret;
		ret.x = x * tile_width;
		ret.y = y * tile_height;

		return ret;
	}

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
	int						width;
	int						height;
	int						tile_width;
	int						tile_height;
	SDL_Color				background_color;
	MapTypes				type;
	p2List<TileSet*>		tilesets;
	p2List<MapLayer*>		layers;
	p2List<MapObjectgroup*> objectgroups;

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

	// TODO 8: Create a method that translates x,y coordinates from map positions to world positions
	

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadObjectgroup(pugi::xml_node& node, MapObjectgroup* objectgroup);

public:

	MapData data;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__