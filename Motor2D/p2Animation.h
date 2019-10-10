#ifndef __P2ANIMATION_H__
#define __P2ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#include "p2Point.h"
#define MAX_FRAMES 25

#include "j1App.h"
#include "PugiXml\src\pugixml.hpp"
#include "j1Map.h"
#include "p2List.h"
#include "p2SString.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "p2Log.h"

class Animation
{
public:
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];
	iPoint offset[MAX_FRAMES];

	bool loop = true;
	float current_frame;
	int last_frame = 0;


	bool lock = false;

	struct Animations
	{
		p2SString name;
		// list of Frames, each containing Tile_id(in tileset) of the frame 
		uint tile_id; //Animation Tile_Id(in tileset)

	};

	struct AnimationTileSet // MapTileSet renamed
	{

		SDL_Rect* Tilerect = new SDL_Rect;

		SDL_Rect* TileRect(uint tile_id) { // Tile id on the Tileset (starts from 0)
			
			SDL_Rect* ret = Tilerect;
			int x = ((tile_id - firstgid) % num_tiles_width);
			int y = ((tile_id - firstgid) / num_tiles_width);

			ret->x = x * tile_width + margin + spacing * x;
			ret->y = y * tile_height + margin + spacing * y;
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

	struct AnimationLayer
	{
		p2SString			name;
		uint				width;
		uint				height;
		uint*				data; //Tile gid
		inline uint Get(int x, int y) const
		{
			return x + y * width;
		}
	};

	enum AnimationTypes //MapTypes renamed
	{
		ANIMATIONTYPE_UNKNOWN = 0,
		ANIMATIONTYPE_ORTHOGONAL,
		ANIMATIONTYPE_ISOMETRIC,
		ANIMATIONTYPE_STAGGERED
	};
	// ----------------------------------------------------
	struct AnimationData  // Map Data renamed
	{
		int						width;
		int						height;
		int						tile_width;
		int						tile_height;
		AnimationTypes			type;
		p2List<AnimationTileSet*>	tilesets;
		p2List<AnimationLayer*>		layers;
		p2List<Animations*>		animations;
	};
	

	pugi::xml_document	animation_file;
	p2SString			folder;
	bool				animation_loaded;
	AnimationData		data;

private:
	int loops = 0;
public:

	bool LoadAnimation(const char* file_name)
	{
		bool ret = true; //bool returned
		pugi::xml_parse_result result = animation_file.load_file(file_name); //load new animation file

		if (result == NULL)
		{
			ret = false;
		}

		if (ret == true)
		{
			ret = LoadAnimationGeneral(); //Filled AnimationData
		}

		pugi::xml_node tileset;

		for (tileset = animation_file.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset")) // Iterate tilesets calling LoadTilesetDetails and LoadTilesetImage
		{ 
			AnimationTileSet* set = new AnimationTileSet();

			if (ret == true)
			{
				ret = LoadTilesetDetails(tileset, set);
			}

			if (ret == true)
			{
				ret = LoadTilesetImage(tileset, set);
			}

			data.tilesets.add(set);

		}

		pugi::xml_node layer;
		for (layer = animation_file.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
		{
			AnimationLayer* newLayer = new AnimationLayer();

			if (ret == true)
			{
				ret = LoadAnimationLayer(layer, newLayer);
			}

			data.layers.add(newLayer);
		}
		return ret;
	}


	bool LoadAnimationGeneral() {

		bool ret = true;
		pugi::xml_node animationFile = animation_file.child("map");

		if(animationFile == NULL)
		{
			ret = false;
		}
		else {
			data.width = animationFile.attribute("width").as_int();
			data.height = animationFile.attribute("height").as_int();
			data.tile_width = animationFile.attribute("tilewidth").as_int();
			data.tile_height = animationFile.attribute("tileheight").as_int();

			p2SString orientation(animationFile.attribute("orientation").as_string());

			if (orientation == "orthogonal") //check what orientation it is and equal the enum
			{
				data.type = ANIMATIONTYPE_ORTHOGONAL;
			}
			else if (orientation == "isometric")
			{
				data.type = ANIMATIONTYPE_ISOMETRIC;
			}
			else if (orientation == "staggered")
			{
				data.type = ANIMATIONTYPE_STAGGERED;
			}
			else
			{
				data.type = ANIMATIONTYPE_UNKNOWN;
			}
		}
		return ret;
	}
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, AnimationTileSet* set)
	{
		bool ret = true;
		set->name.create(tileset_node.attribute("name").as_string());
		set->firstgid = tileset_node.attribute("firstgid").as_int();
		set->tile_width = tileset_node.attribute("tilewidth").as_int();
		set->tile_height = tileset_node.attribute("tileheight").as_int();
		set->margin = tileset_node.attribute("margin").as_int();
		set->spacing = tileset_node.attribute("spacing").as_int();
		pugi::xml_node offset = tileset_node.child("tileoffset");

		if (offset != NULL)
		{
			set->offset_x = offset.attribute("x").as_int();
			set->offset_y = offset.attribute("y").as_int();
		}
		else
		{
			set->offset_x = 0;
			set->offset_y = 0;
		}

		return ret;
	}

	bool LoadTilesetImage(pugi::xml_node& tileset_node, AnimationTileSet* set)
	{
		bool ret = true;
		pugi::xml_node image = tileset_node.child("image");

		if (image == NULL)
		{
			LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
			ret = false;
		}
		else
		{
			p2SString debug = folder.GetString();
			debug += image.attribute("source").as_string();
			//PATH(folder.GetString(), image.attribute("source").as_string())
			set->texture = App->tex->Load(debug.GetString());
			int w, h;
			SDL_QueryTexture(set->texture, NULL, NULL, &w, &h);
			set->tex_width = image.attribute("width").as_int();

			if (set->tex_width <= 0)
			{
				set->tex_width = w;
			}

			set->tex_height = image.attribute("height").as_int();

			if (set->tex_height <= 0)
			{
				set->tex_height = h;
			}

			set->num_tiles_width = set->tex_width / set->tile_width;
			set->num_tiles_height = set->tex_height / set->tile_height;
		}

		return ret;
	}


	bool LoadAnimationLayer(pugi::xml_node& node, AnimationLayer* layer)
	{
		layer->name = node.attribute("name").as_string();
		layer->height = node.attribute("height").as_uint();
		layer->width = node.attribute("width").as_uint();

		layer->data = new uint[layer->height*layer->width];

		memset(layer->data, 0, layer->width * layer->height * sizeof(uint));

		int i = 0;
		for (pugi::xml_node iterator_node = node.child("data").child("tile"); iterator_node; iterator_node = iterator_node.next_sibling("tile"), i++) {
			layer->data[i] = iterator_node.attribute("gid").as_uint();
		}

		return true;
	}



	void PushBack(const SDL_Rect& rect, int offset_x = 0, int offset_y = 0)
	{
		frames[last_frame] = rect;
		offset[last_frame].x = offset_x;
		offset[last_frame].y = offset_y;
		last_frame++;
	}

	//NEW-------------------------------------
	void SetOffset(int frame, int offset_x = 0, int offset_y = 0) {
		offset[frame].x = offset_x;
		offset[frame].y = offset_y;
	}

	void SetSpeed(float new_speed) {
		speed = new_speed;
	}
	//---------------------------


	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if (current_frame >= last_frame)
		{
			current_frame = (loop) ? 0.0f : last_frame - 1;
			if (loop)
				loops++;

		}
		return frames[(int)current_frame];
	}

	iPoint& GetOffset()
	{

		return offset[(int)current_frame];
	}

	bool Finished() const
	{
		return loops > 0;
	}

	void Reset()
	{
		current_frame = 0;
		loops = 0;
	}
};

#endif
