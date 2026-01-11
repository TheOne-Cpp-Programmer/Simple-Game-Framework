#include "../include/sgf.hpp"
#include <iostream>

using namespace sgf;

// Log Class Implementation
//----------------------------------------------------------------------------
void Log::ErrorMessage(std::string message) {
	if (level >= ERROR_LEVEL) {
		std::cout
		<< "\033[31m"
		<< "[SGF_ERROR]: " << message
		<< "\033[0m" << "\n";
	}
}
void Log::WarningMessage(std::string message) {
	if (level >= WARN_LEVEL) {
		std::cout
		<< "\033[91m"
		<< "[SGF_WARNING]: "<< message
		<< "\033[0m" << "\n";
	}
}
void Log::InfoMessage(std::string message) {
	if (level >= INFO_LEVEL) {
		std::cout
		<< "\033[32m"
		<< "[SGF_INFO]: " << message
		<< "\033[0m" << "\n";}
}

void Log::SetLevel(int level) {
	this->level = level;
}
//----------------------------------------------------------------------------

void DrawCollisionShape(CollisionShape2D &body, Color color) {
    DrawRectangleLines(body.x,body.y, body.width, body.height, color);
}

// Entity2D Class Implementation
//----------------------------------------------------------------------------
Position2D Entity2D::GetPosition() const {
    return (Position2D){this->body.x,this->body.y};
}
CollisionShape2D Entity2D::GetCollisionShape() const {
    return this->body;
}

void Entity2D::SetPosition(Position2D pos) {
    this->body.x = pos.x;
    this->body.y = pos.y;
}
void Entity2D::SetWidthAndHeight(float width, float height) {
    this->body.width = width;
    this->body.height = height;
}

Position2D Entity2D::GetRandomPosition(Range xRange, Range yRange) {
    Position2D pos = (Position2D) {
        static_cast<float>(GetRandomValue(xRange.min, xRange.max)),
        static_cast<float>(GetRandomValue(yRange.min, yRange.max))
    };
    return pos;
}

Entity2D::Entity2D(Position2D startingPosition, float width, float height) {
    this->body.x = startingPosition.x;
    this->body.y = startingPosition.y;
    this->body.width = width;
    this->body.height = height;
}
//----------------------------------------------------------------------------

// Sprite2D Class Implementation
//----------------------------------------------------------------------------
void Sprite2D::DrawSprite() {
    if (IsTextureValid(pngImage)){
        DrawTextureEx(pngImage,position,rotation,scale,tint);
    } else {
    	spriteLog.ErrorMessage("Invalid Sprite");
    }
}
void Sprite2D::UnloadSprite() {
	UnloadTexture(pngImage);
}

void Sprite2D::SetRotation(float rotation) {
	this->rotation = rotation;
}
void Sprite2D::SetScale(float scale) {
	this->scale = scale;
}
void Sprite2D::SetTint(Color tint) {
	this->tint = tint;
}
void Sprite2D::SetPosition(Position2D position) {
	this->position = position;
}

Sprite2D::Sprite2D(const std::string &&filePath,Position2D stPos) {
	this->pngImage = LoadTexture(filePath.c_str());
	this->position = stPos;
}
Sprite2D::Sprite2D(const std::string &&filePath, float scale, Position2D stPos) {
	this->pngImage = LoadTexture(filePath.c_str());
	this->position = stPos;
	this->scale = scale;
}
//----------------------------------------------------------------------------

// SpriteEntity2D Class Implementation
//----------------------------------------------------------------------------
SpriteEntity2D::SpriteEntity2D(const std::string &&filePath, float scale, Position2D startPos)
	: Entity2D(startPos, 10.f, 10.f), Sprite2D(std::string (filePath),scale,startPos)
{
	body.height = static_cast<float>(pngImage.height) * this->scale;
	body.width = static_cast<float>(pngImage.width) * this->scale;
}
SpriteEntity2D::SpriteEntity2D(const std::string &&filePath, Position2D startPos)
	: Entity2D(startPos, 10.f, 10.f), Sprite2D(std::string (filePath),startPos)
{
  entityLog.SetLevel(Log::WARN_LEVEL);
	body.height = static_cast<float>(pngImage.height) * this->scale;
	body.width = static_cast<float>(pngImage.width) * this->scale;
  if (body.height >= 1000.f || body.width >= 1000.f) {
    entityLog.WarningMessage("CollisionShape is incredibly tall");
  }
}
//----------------------------------------------------------------------------

// World2D Class Implementation
//----------------------------------------------------------------------------
World2D::World2D(int width, int height, Position2D topLeft) {
    this->height = height;
    this->width = width;
    this->topLeft = topLeft;

    this->topRight = (Vector2){
        this->topLeft.x+static_cast<float>(this->width),
        this->topLeft.y
    };

    this->center = (Vector2){
        this->topLeft.x + (static_cast<float>(this->width) / 2),
        this->topLeft.y + (static_cast<float>(this->height) / 2)
    };

    this->bottomLeft = (Vector2){
        this->topLeft.x,
        this->topLeft.y + static_cast<float>(this->height)
    };

    this->bottomRight = (Vector2) {
        this->topLeft.x + static_cast<float>(this->width),
        this->topLeft.y + static_cast<float>(this->height)
    };
}
//----------------------------------------------------------------------------

// DynamicWorld2D Class Implementation
//----------------------------------------------------------------------------
DynamicWorld2D::DynamicWorld2D(int width, int height, Position2D topLeft)
  : World2D(width,height,topLeft) {}
//----------------------------------------------------------------------------
