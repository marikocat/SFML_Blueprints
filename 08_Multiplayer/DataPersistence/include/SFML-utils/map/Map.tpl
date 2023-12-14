namespace sfutils
{
	namespace map
	{
		template<typename GEOMETRY>
		Map<GEOMETRY>::Map(float size) : VMap(size)
		{
		}

		template<typename GEOMETRY>
		void Map<GEOMETRY>::loadFromJson(const utils::json::Object& root)
		{
			const utils::json::Array& layers = root["layers"].asArray();
			for (const utils::json::Value& value : layers)
			{ // loop through the layers
				const utils::json::Object& layer = value.asObject();
				std::string content = layer["content"].asString(); // get the content type

				int z = 0; // default value
				try
				{
					z = layer["z"].asInt(); // load value
				}
				catch (...) {}

				bool isStatic = false; //default value
				try
				{
					isStatic = layer["static"].asBool(); // load value
				}
				catch (...) {}

				if (content == "tile") //is a layer of tile?
				{
					auto current_layer = new Layer<Tile<GEOMETRY>>(content, z, isStatic); //create the layer
					const utils::json::Array& textures = layer["datas"].asArray();

					for (const utils::json::Value& value : textures)
					{ //loop through the textures
						const utils::json::Object& texture = value.asObject();
						int tex_x = texture["x"].asInt(); //get the tile position
						int tex_y = texture["y"].asInt();
						int height = std::max<int>(0, texture["height"].asInt()); //get the square size
						int width = std::max<int>(0, texture["width"].asInt());
						std::string img = texture["img"].asString(); //get texture path

						sf::Texture& tex = _textures.getOrLoad(img, img); // load the texture
						tex.setRepeated(true);

						for (int y = tex_y; y < tex_y + height; ++y)
						{ //create the tiles
							for (int x = tex_x; x < tex_x + width; ++x)
							{
								Tile<GEOMETRY> tile(x, y, _tileSize);
								tile.setTexture(&tex);
								tile.setTextureRect(GEOMETRY::getTextureRect(x, y, _tileSize));

								current_layer->add(std::move(tile), false); // add the new tile to the layer
							}
						}
					}

					add(current_layer, false); //add the new layer to the map
				}
				else if (content == "sprite") //if it's a layer of images
				{
					auto current_layer = new Layer<sf::Sprite>(content, z, isStatic); //create the layer
					const utils::json::Array& datas = layer["datas"].asArray();

					for (const utils::json::Value& value : datas)
					{ //loop on data
						const utils::json::Object& data = value.asObject();
						int x = data["x"].asInt(); //get the position
						int y = data["y"].asInt();
						float ox = 0.5; //default center value (bottom center)
						float oy = 1;
						try
						{ //get value
							ox = data["ox"].asFloat();
						}
						catch (...) {}

						try
						{ //get value
							oy = data["oy"].asFloat();
						}
						catch (...) {}

						std::string img = data["img"].asString(); //get texture path

						sf::Sprite spr{ _textures.getOrLoad(img, img) }; //load texture
						spr.setPosition(GEOMETRY::mapCoordsToPixel(x, y, _tileSize));

						sf::FloatRect rec = spr.getLocalBounds();
						spr.setOrigin(rec.width * ox, rec.height * oy);

						current_layer->add(std::move(spr), false); //add the sprite
					}

					add(current_layer, false); //add the new layer to the map
				}
			}

			sortLayers(); //finally sort the layers (recuively)
		}

		template<typename GEOMETRY>
		sf::Vector2i Map<GEOMETRY>::mapPixelToCoords(float x, float y) const
		{
			return GEOMETRY::mapPixelToCoords(x, y, _tileSize);
		}

		template<typename GEOMETRY>
		sf::Vector2f Map<GEOMETRY>::mapCoordsToPixel(int x, int y) const
		{
			return GEOMETRY::mapCoordsToPixel(x, y, _tileSize);
		}

		template<typename GEOMETRY>
		const sf::ConvexShape Map<GEOMETRY>::getShape() const
		{
			sf::ConvexShape shape = GEOMETRY::getShape();
			shape.setScale(_tileSize, _tileSize);
			return shape;
		}

		template<typename GEOMETRY>
		std::list<sf::Vector2i> Map<GEOMETRY>::getPath(const sf::Vector2i& origin, const sf::Vector2i& dest) const
		{
			int distance = GEOMETRY::distance(origin.x, origin.y, dest.x, dest.y);
			std::list<sf::Vector2i> res;

			sf::Vector2f p(dest.x - origin.x,
							dest.y - origin.y);
			float delta = 1.0 / distance;
			float cumul = 0;
			res.emplace_back(origin);
			for (int i = 0; i < distance; ++i)
			{
				sf::Vector2i pos = GEOMETRY::round(origin.x + p.x * cumul, origin.y + p.y * cumul);
				if (res.back() != pos)
					res.emplace_back(pos);
				cumul += delta;
			}
			if (res.back() != dest)
				res.emplace_back(dest);
			return res;
		}

		template<typename GEOMETRY>
		sf::Vector2i Map<GEOMETRY>::getPath1(const sf::Vector2i& origin, const sf::Vector2i& dest) const
		{
			int distance = GEOMETRY::distance(origin.x, origin.y, dest.x, dest.y);
			sf::Vector2i res = origin;

			sf::Vector2f p(dest.x - origin.x,
							dest.y - origin.y);
			float delta = 1.0 / distance;
			float cumul = 0;
			for (int i = 0; i < distance; ++i)
			{
				sf::Vector2i pos = GEOMETRY::round(origin.x + p.x * cumul, origin.y + p.y * cumul);
				if (pos != res)
				{
					res = pos;
					break;
				}
				cumul += delta;
			}
			return res;
		}

		template<typename GEOMETRY>
		int Map<GEOMETRY>::getDistance(const sf::Vector2i& origin, const sf::Vector2i& dest) const
		{
			return GEOMETRY::distance(origin.x, origin.y, dest.x, dest.y);
		}
	}
}