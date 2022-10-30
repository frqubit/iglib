#pragma once

#ifndef CRYPTIKK_IGLIB_H
#define CRYPTIKK_IGLIB_H

#include <SFML/Graphics.hpp>
#include <memory>

#define GRID_SIZE 50

namespace iglib {

    class IsoVector {
        public:
            IsoVector(float x, float y, float z);
            IsoVector(float x, float y, float z, float rx, float ry);
            IsoVector(sf::Vector3f vec);

            float rx;
            float ry;

            float x;
            float y;
            float z;

            sf::Vector3f toVector3f();
            sf::Vector2f toVector2f();
    };

    class IsoShape {

        public:
            IsoShape();
            IsoShape(sf::Vector3f size);

            void init(sf::Vector3f size);
            void refreshpointpos();

            void draw(sf::RenderTarget *target);
            void draw(sf::RenderTarget *target, int face);

            void setPosition(IsoVector position);
            void setSize(sf::Vector3f size);

            void setColor(sf::Color color[3]);
            void setColor(int face, sf::Color color);

            void setTexture(int face, sf::Texture *texture);

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
