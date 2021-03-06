#include <SDL2/SDL.h>
#include <sstream>
#include <algorithm>
#include <cmath>

#include "../headers/Level.h"
#include "../headers/Graphics.h"
#include "../headers/tinyxml2.h"

using namespace tinyxml2;

Level::Level() {}

Level::Level(Graphics &graphics, std::string mapName, Vector2 spawn) :
		_mapName(mapName),
		_spawnPoint(spawn),
		_size(Vector2()),
		_background(nullptr)
{
	this->LoadMap(graphics, mapName);
}

Level::~Level() {}

void Level::LoadMap(Graphics &graphics, std::string mapName) {
		XMLDocument doc;
		std::stringstream ss;
		ss << "maps/" << mapName << ".tmx"; //Pass in Map 1, we get maps/Map 1.tmx
		doc.LoadFile(ss.str().c_str());

		XMLElement* mapNode = doc.FirstChildElement("map");

		//Get the width and the height of the whole map and store it in _size
		int width, height;
		mapNode->QueryIntAttribute("width", &width);
		mapNode->QueryIntAttribute("height", &height);
		this->_size = Vector2(width, height);

		//Get the width and the height of the tiles and store it in _tileSize
		int tileWidth, tileHeight;
		mapNode->QueryIntAttribute("tilewidth", &tileWidth);
		mapNode->QueryIntAttribute("tileheight", &tileHeight);
		this->_tileSize = Vector2(tileWidth, tileHeight);

		//Loading the tilesets
		XMLElement* pTileset = mapNode->FirstChildElement("tileset");
		if (pTileset != NULL) {
			while (pTileset) {
				int firstgid;
				const char* source = pTileset->FirstChildElement("image")->Attribute("source");
				char* path;
				std::stringstream ss;
				ss << source;
				pTileset->QueryIntAttribute("firstgid", &firstgid);
				SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.GetRenderer(), graphics.LoadImage(ss.str()));
				this->_tilesets.push_back(Tileset(tex, firstgid));

				pTileset = pTileset->NextSiblingElement("tileset");
			}
		}

		//Loading the layers
		XMLElement* pLayer = mapNode->FirstChildElement("layer");
		if (pLayer != NULL) {
			while (pLayer) {
				//Loading the data element
				XMLElement* pData = pLayer->FirstChildElement("data");
				if (pData != NULL) {
					while (pData) {
						//Loading the tile element
						XMLElement* pTile = pData->FirstChildElement("tile");
						if (pTile != NULL) {
							int tileCounter = 0;
							while (pTile) {
								//Build each individual tile here
								//If gid is 0, no tile should be drawn. Continue loop
								if (pTile->IntAttribute("gid") == 0) {
									tileCounter++;
									if (pTile->NextSiblingElement("tile")) {
										pTile = pTile->NextSiblingElement("tile");
										continue;
									}
									else {
										break;
									}
								}

								//Get the tileset for this specific gid
								int gid = pTile->IntAttribute("gid");
								Tileset tls;
								for (int i = 0; i < this->_tilesets.size(); i++) {
									if (this->_tilesets[i].FirstGid <= gid) {
										//This is the tileset we want
										tls = this->_tilesets.at(i);
										break;
									}
								}

								if (tls.FirstGid == -1) {
									//No tileset was found for this gid
									tileCounter++;
									if (pTile->NextSiblingElement("tile")) {
										pTile = pTile->NextSiblingElement("tile");
										continue;
									}
									else {
										break;
									}
								}

								//Get the position of the tile in the level
								int xx = 0;
								int yy = 0;
								xx = tileCounter % width;
								xx *= tileWidth;
								yy += tileHeight * (tileCounter / width);
								Vector2 finalTilePosition = Vector2(xx, yy);

								//Calculate the position of the tile in the tileset
								int tilesetWidth, tilesetHeight;
								SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
								int tsxx = gid % (tilesetWidth / tileWidth) - 1;
								tsxx *= tileWidth;
								int tsyy = 0;
								int amt = (gid / (tilesetWidth / tileWidth));
								tsyy = tileHeight * amt;
								Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);

								//Build the actual tile and add it to the level's tile list
								Tile tile(tls.Texture, Vector2(tileWidth, tileHeight),
										finalTilesetPosition, finalTilePosition);
								this->_tileList.push_back(tile);
								tileCounter++;

								pTile = pTile->NextSiblingElement("tile");
							}
						}

						pData = pData->NextSiblingElement("data");
					}
				}

				pLayer = pLayer->NextSiblingElement("layer");
			}
		}

		// Parse collisions
		XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
		if (pObjectGroup != NULL) {
			while (pObjectGroup) {
				const char* name = pObjectGroup->Attribute("name");
				std::stringstream ss;
				ss << name;
				if (ss.str() == "collisions") {
					XMLElement* pObject = pObjectGroup->FirstChildElement("object");
					if (pObject != NULL) {
						while (pObject) {
							float x, y, width, height;
							x = pObject->FloatAttribute("x");
							y = pObject->FloatAttribute("y");
							width = pObject->FloatAttribute("width");
							height = pObject->FloatAttribute("height");
							this->_collisionRects.push_back(Rectangle(
									std::ceil(x) * globals::SPRITE_SCALE,
									std::ceil(y) * globals::SPRITE_SCALE,
									std::ceil(width) * globals::SPRITE_SCALE,
									std::ceil(height) * globals::SPRITE_SCALE
							));

							pObject = pObject->NextSiblingElement("object");
						}
					}
				}
				// other object groups can be parsed here
				pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
			}
		}
}

void Level::Update(float elapsedTime) {

}

void Level::Draw(Graphics &graphics) {
	for (int i = 0; i < this->_tileList.size(); i++) {
		this->_tileList[i].Draw(graphics);
	}
}

std::vector<Rectangle> Level::CheckTileCollisions(const Rectangle &other) {
	std::vector<Rectangle> others;
	for (int i = 0; i < _collisionRects.size(); i++) {
		if (this->_collisionRects.at(i).CollidesWith(other)) {
			others.push_back(this->_collisionRects.at(i));
		}
	}

	return others;
}
