#include <iostream>

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
			{
				const utils::json::Object& layer = value.asObject();
				std::string content = layer["content"].asString();

				int z = 0;
				try
				{
					z = layer["z"].asInt();
				} catch(...) {}

				bool isStatic = false;
				try
				{
					isStatic = layer["static"].asBool();
				} catch(...) {}

				if (content == "tile")
				{
					std::cout << content << " z = " << z << "\n";

					auto current_layer = new Layer<Tile<GEOMETRY>>(content, z, isStatic);

					const utils::json::Array& textures = layer["datas"].asArray();
					for (const utils::json::Value& value : textures)
					{
						const utils::json::Object& texture = value.asObject();
						int tex_x = texture["x"].asInt();
						int tex_y = texture["y"].asInt();
						int height = std::max<int>(0, texture["height"].asInt());
						int width = std::max<int>(0, texture["width"].asInt());
						std::string img = texture["img"].asString();

						std::cout << tex_x << " " << tex_y << " " << height << " " << width << " " << img << "\n";
						std::cout << _tileSize << "\n";
						sf::Texture& tex = _textures.getOrLoad(img, img);
						tex.setRepeated(true);

						for (int y = tex_y; y < tex_y + height; ++y)
						{
							for (int x = tex_x; x < tex_x + width; ++x)
							{
								Tile<GEOMETRY> tile(x, y, _tileSize);
								tile.setTexture(&tex);
								tile.setTextureRect(GEOMETRY::getTextureRect(x, y, _tileSize));

								current_layer->add(std::move(tile), false);
								//std::cout << "tile at " << x << ", " << y << " added\n";
							}
						}
					}
					add(current_layer, false);
				}
				else if (content == "sprite")
				{
					auto current_layer = new Layer<sf::Sprite>(content, z, isStatic);

					const utils::json::Array& datas = layer["datas"].asArray();
					for (const utils::json::Value& value : datas)
					{
						const utils::json::Object& data = value.asObject();
						int x = data["x"].asInt();
						int y = data["y"].asInt();
						float ox = 0.5;
						float oy = 1;
						try
						{
							ox = data["ox"].asFloat();
						}
						catch (...) {}

						try
						{
							oy = data["oy"].asFloat();
						}
						catch (...) {}

						std::string img = data["img"].asString();

						sf::Sprite spr(_textures.getOrLoad(img, img));
						spr.setPosition(GEOMETRY::mapCoordsToPixel(x, y, _tileSize));

						sf::FloatRect rec = spr.getLocalBounds();
						spr.setOrigin(rec.width * ox, rec.height * oy);

						current_layer->add(std::move(spr), false);
					}
					add(current_layer, false);
				}
			}
			sortLayers();
		}

		template<typename GEOMETRY>
		sf::Vector2i Map<GEOMETRY>::mapPixelToCoords(float x, float y)const
		{
			return GEOMETRY::mapPixelToCoords(x, y, _tileSize);
		}

		template<typename GEOMETRY>
		sf::Vector2f Map<GEOMETRY>::mapCoordsToPixel(int x, int y)const
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

		/*template<typename GEOMETRY>
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
		}*/

		template<typename GEOMETRY>
        std::list<sf::Vector2i> Map<GEOMETRY>::getPath(const sf::Vector2i& origin,const sf::Vector2i& dest)const
        {
            int distance = GEOMETRY::distance(origin.x,origin.y,dest.x,dest.y);
            std::list<sf::Vector2i> res;

            sf::Vector2f p(dest.x - origin.x,
                           dest.y - origin.y);
            float delta = 1.0/distance;
            float cumul = 0;
            res.emplace_back(origin);
            for(int i = 0; i<distance;++i)
            {

                sf::Vector2i pos = GEOMETRY::round(origin.x + p.x * cumul,origin.y + p.y * cumul);
                if(res.back() != pos)
                    res.emplace_back(pos);
                cumul +=delta;
            }
            if(res.back() != dest)
                res.emplace_back(dest);
            return res;
        }

        template<typename GEOMETRY>
        sf::Vector2i Map<GEOMETRY>::getPath1(const sf::Vector2i& origin,const sf::Vector2i& dest)const
        {
            int distance = GEOMETRY::distance(origin.x,origin.y,dest.x,dest.y);
            sf::Vector2i res = origin;

            sf::Vector2f p(dest.x - origin.x,
                           dest.y - origin.y);
            float delta = 1.0/distance;
            float cumul = 0;
            for(int i = 0; i<distance;++i)
            {

                sf::Vector2i pos = GEOMETRY::round(origin.x + p.x * cumul,origin.y + p.y * cumul);
                if(pos != res)
                {
                    res = pos;
                    break;
                }
                cumul +=delta;
            }
            return res;
        }

        template<typename GEOMETRY>
        int Map<GEOMETRY>::getDistance(const sf::Vector2i& origin,const sf::Vector2i& dest) const
        {
            return GEOMETRY::distance(origin.x,origin.y,dest.x,dest.y);
        }
	}
}