#include <SFML/Graphics.hpp>
#include <iostream>
#include <iglib/iglib.hpp>
#include <memory>

using namespace iglib;
using namespace sf;

//============================================================================
//                            iglib::IsoShape
//============================================================================

void IsoShape::refreshpointpos() {
    Vector2f truePos = this->position.toVector2f();

    // Point of reference: Top corner of the top face

    topface[0].position = Vector2f(0, 0);
    topface[1].position = Vector2f(size.x, size.x / 2);
    topface[2].position = Vector2f(-size.z, size.z / 2);
    topface[3].position = Vector2f(
        size.x - size.z,
        (size.x + size.z) / 2
    );

    for (int i = 0; i < 4; i++) {
        topface[i].position.x += truePos.x;
        topface[i].position.y += truePos.y;
    }

    // Point of reference: Left corner of the top face

    leftface[0].position = topface[2].position;
    leftface[1].position = Vector2f(topface[2].position.x, topface[2].position.y + size.y);
    leftface[2].position = topface[3].position;
    leftface[3].position = Vector2f(topface[3].position.x, topface[3].position.y + size.y);

    // Point of reference: Right corner of the top face

    rightface[0].position = topface[1].position;
    rightface[1].position = topface[3].position;
    rightface[2].position = Vector2f(topface[1].position.x, topface[1].position.y + size.y);
    rightface[3].position = leftface[3].position;

    lines[0][0].position = topface[0].position;
    lines[0][1].position = topface[1].position;
    lines[0][2].position = topface[3].position;
    lines[0][3].position = topface[2].position;

    lines[1][0].position = leftface[0].position;
    lines[1][1].position = leftface[1].position;
    lines[1][2].position = leftface[3].position;
    lines[1][3].position = leftface[2].position;

    lines[2][0].position = rightface[0].position;
    lines[2][1].position = rightface[1].position;
    lines[2][2].position = rightface[3].position;
    lines[2][3].position = rightface[2].position;

    for (int a=0; a<3; a++) {
        for (int i = 0; i < 4; i++) {
            lines[a][i].color = Color::Black;
        }
    }
}

void IsoShape::init(Vector3f size) {
    this->size = size;
    this->position = IsoVector(0, 0, 0);
    topface = VertexArray(TriangleStrip, 4);
    leftface = VertexArray(TriangleStrip, 4);
    rightface = VertexArray(TriangleStrip, 4);
    lines[0] = VertexArray(LineStrip, 4);
    lines[1] = VertexArray(LineStrip, 4);
    lines[2] = VertexArray(LineStrip, 4);
    refreshpointpos();
}

IsoShape::IsoShape() {
    init(Vector3f(100, 100, 100));
}

IsoShape::IsoShape(Vector3f size) {
    init(size);
}

void IsoShape::setPosition(IsoVector position) {
    this->position = position;
    refreshpointpos();
}

void IsoShape::setColor(Color colors[3]) {
    for (int i = 0; i < 4; i++) {
        topface[i].color = colors[0];
        leftface[i].color = colors[1];
        rightface[i].color = colors[2];
    }
}

void IsoShape::setColor(int face, Color color) {
    switch (face) {
        case 0:
            for (int i = 0; i < 4; i++) {
                topface[i].color = color;
            }
            break;
        case 1:
            for (int i = 0; i < 4; i++) {
                leftface[i].color = color;
            }
            break;
        case 2:
            for (int i = 0; i < 4; i++) {
                rightface[i].color = color;
            }
            break;
    }
}

void IsoShape::setSize(Vector3f size) {
    this->size = size;
    refreshpointpos();
}

void IsoShape::setTexture(int face, Texture *texture) {
    this->textures[face] = texture;
    setTextureRect(face, IntRect(0, 0, texture->getSize().x, texture->getSize().y));
}

void IsoShape::setTextureRect(int face, IntRect rect) {

    float xMult = size.x / GRID_SIZE;
    float yMult = size.y / GRID_SIZE;
    float zMult = size.z / GRID_SIZE;

    switch (face) {
        case 0:
            topface[0].texCoords = Vector2f(rect.left, rect.top);
            topface[1].texCoords = Vector2f((rect.left + rect.width) * xMult, rect.top);
            topface[2].texCoords = Vector2f(rect.left, (rect.top + rect.height) * zMult);
            topface[3].texCoords = Vector2f((rect.left + rect.width) * xMult, (rect.top + rect.height) * zMult);
            break;
        case 1:
            leftface[0].texCoords = Vector2f(rect.left, rect.top);
            leftface[1].texCoords = Vector2f(rect.left, (rect.top + rect.height) * yMult);
            leftface[2].texCoords = Vector2f((rect.left + rect.width) * xMult, rect.top);
            leftface[3].texCoords = Vector2f((rect.left + rect.width) * xMult, (rect.top + rect.height) * yMult);
            break;
        case 2:
            rightface[0].texCoords = Vector2f(rect.left, rect.top);
            rightface[1].texCoords = Vector2f((rect.left + rect.width) * zMult, rect.top);
            rightface[2].texCoords = Vector2f(rect.left, (rect.top + rect.height) * yMult);
            rightface[3].texCoords = Vector2f((rect.left + rect.width) * zMult, (rect.top + rect.height) * yMult);
            break;
    }
}

void IsoShape::draw(RenderTarget *target) {
    for (int i=0; i<3; i++) {
        draw(target, i);
    }
}

void IsoShape::draw(RenderTarget *target, int face) {
    switch (face) {
        case 0:
            target->draw(topface, textures[0]);
            target->draw(lines[0]);
            break;
        case 1:
            target->draw(leftface, textures[1]);
            target->draw(lines[1]);
            break;
        case 2:
            target->draw(rightface, textures[2]);
            target->draw(lines[2]);
            break;
    }
}

//============================================================================
//                          iglib::IsoVector
//============================================================================

IsoVector::IsoVector(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;

    this->rx = 0;
    this->ry = 0;
}

IsoVector::IsoVector(Vector3f vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;

    this->rx = 0;
    this->ry = 0;
}

IsoVector::IsoVector(float x, float y, float z, float rx, float ry) {
    this->x = x;
    this->y = y;
    this->z = z;

    this->rx = rx;
    this->ry = ry;
}

Vector3f IsoVector::toVector3f() {
    return Vector3f(x, y, z);
}

Vector2f IsoVector::toVector2f() {
    float realx = rx;
    float realy = ry;
    realx += (x - y);
    realy += (x + y) / 2;
    realy += z;
    return Vector2f(realx, realy);
}