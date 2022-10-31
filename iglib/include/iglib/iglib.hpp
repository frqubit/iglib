#pragma once

#ifndef CRYPTIKK_IGLIB_H
#define CRYPTIKK_IGLIB_H

#include <SFML/Graphics.hpp>
#include <memory>


namespace iglib {

	void setGridSize(size_t size);

    class IsoVector {
        public:
			/**
			 * @brief Construct a new Iso Vector object
			 * 
			 * @param x The x coordinate
			 * @param y The y coordinate
			 * @param z The z coordinate
			 */
            IsoVector(float x, float y, float z);
			/**
			 * @brief Construct a new Iso Vector object
			 * 
			 * @param x The x coordinate
			 * @param y The y coordinate
			 * @param z The z coordinate
			 * @param rx The relative x coordinate
			 * @param ry The relative y coordinate
			 */
            IsoVector(float x, float y, float z, float rx, float ry);
			/**
			 * @brief Construct a new Iso Vector object
			 * 
			 * @param vec The vector to clone as an IsoVector
			 */
            IsoVector(sf::Vector3f vec);

            float rx;
            float ry;

            float x;
            float y;
            float z;

			/**
			 * @brief Convert the IsoVector to a sf::Vector3f
			 * 
			 * @return sf::Vector3f 
			 */
            sf::Vector3f toVector3f();

			/**
			 * @brief Convert the IsoVector to a sf::Vector2f
			 * 
			 * @return sf::Vector2f 
			 */
            sf::Vector2f toVector2f();
    };

    class IsoShape {

        public:
			/**
			 * @brief Construct a new Iso Shape object
			 * 
			 */
            IsoShape();

			/**
			 * @brief Construct a new Iso Shape object
			 * 
			 * @param size The size of the shape
			 */
            IsoShape(sf::Vector3f size);

			/**
			 * @brief Initialize the shape. Meant for internal use
			 * 
			 * @param size 
			 */
            void init(sf::Vector3f size);

			/**
			 * @brief Meant for internal use
			 * 
			 */
            void refreshpointpos();

			/**
			 * @brief Draw the shape to the target
			 * 
			 * @param target 
			 */
            void draw(sf::RenderTarget *target);

			/**
			 * @brief Draw the face to the target
			 * 
			 * @param target 
			 * @param face 
			 */
            void draw(sf::RenderTarget *target, int face);

			/**
			 * @brief Set the Position object
			 * 
			 * @param position 
			 */
            void setPosition(IsoVector position);

			/**
			 * @brief Set the Size object
			 * 
			 * @param size 
			 */
            void setSize(sf::Vector3f size);

			/**
			 * @brief Set the Color object
			 * 
			 * @param color 
			 */
            void setColor(sf::Color color[3]);

			/**
			 * @brief Set the Color object for a specific face
			 * 
			 * @param face 
			 * @param color 
			 */
            void setColor(int face, sf::Color color);

			/**
			 * @brief Set the Texture object for a face
			 * 
			 * @param face 
			 * @param texture 
			 */
            void setTexture(int face, sf::Texture *texture);

			/**
			 * @brief Meant for internal use
			 * 
			 * @param face 
			 * @param rect 
			 */
            void setTextureRect(int face, sf::IntRect rect);

            sf::Vector3f size;

        
        private:
            sf::VertexArray topface;
            sf::VertexArray leftface;
            sf::VertexArray rightface;
            sf::VertexArray lines[3];
            IsoVector position = IsoVector(0, 0, 0);
            sf::Texture *textures[3] = {nullptr, nullptr, nullptr};

    };

}

#endif
