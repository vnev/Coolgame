#include <SDL2/SDL.h>
#include <sstream>
#include <algorithm>
#include <cmath>

#include "Level.h"
#include "Graphics.h"
#include "tinyxml2.h"

using namespace tinyxml2;

Level::Level() {}

Level::Level(Graphics &graphics, std::string mapName, Vector2 spawn) :
		_mapName(mapName),
		_spawnPoint(spawn),
		_size(Vector2())
{
	this->LoadMap(graphics, mapName);
}

Level::~Level() {}

void Level::LoadMap(Graphics &graphics, std::string mapName) {
	XMLDocument doc;
	std::stringstream ss;
	ss << "maps/" << mapName << ".tmx";
	doc.LoadFile(ss.str().c_str());
	XMLElement* mapNode = doc.FirstChildElement("map");

	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	this->_size = Vector2(width, height);

	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	this->_tileSize = Vector2(tileWidth, tileHeight);

	XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset != NULL) {
		while (pTileset) {
			int firstgid;
			const char* source = pTileset->FirstChildElement("image")->Attribute("source");
			char* path;
			std::stringstream ss;
			ss << source;
			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture* tx = SDL_CreateTextureFromSurface(graphics.GetRenderer(),
					graphics.LoadImage(ss.str()));
			this->_tilesets.push_back(Tileset(tx, firstgid));

			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}

	XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer != NULL) {
		while (pLayer) {
			XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != NULL) {
				while (pData) {
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != NULL) {
						int tileCtr = 0;
						while (pTile) {
							if (pTile->IntAttribute("gid") == 0) {
								tileCtr++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							int gid = pTile->IntAttribute("gid");
							Tileset tls;
							for (int i = 0; i < this->_tilesets.size(); i++) {
								if (this->_tilesets[i].FirstGid <= gid) {
									tls = this->_tilesets[i];
									break;
								}
							}

							if (tls.FirstGid == -1) {
								tileCtr++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							int xx = 0, yy = 0;
							xx = tileCtr % width;
							xx *= tileWidth;
							yy += tileHeight * (tileCtr / width);
							Vector2 finalPos = Vector2(xx, yy);

							int tilesetWidth, tilesetHeight;
							SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
							int tsxx = gid % (tilesetWidth / tileWidth) - 1;
							tsxx *= tileWidth;
							int tsyy = 0;
							int amount = gid / (tileWidth / tileHeight);
							tsyy = tileHeight * amount;
							Vector2 finalTilesetPos = Vector2(tsxx, tsyy);

							Tile tile(tls.Texture, Vector2(tileWidth, tileHeight),
									finalTilesetPos, finalPos);
							this->_tileList.push_back(tile);
							tileCtr++;

							pTile = pTile->NextSiblingElement("tile");
						}
					}

					pData = pData->NextSiblingElement("data");
				}
			}

			pLayer = pLayer->NextSiblingElement("layer");
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
