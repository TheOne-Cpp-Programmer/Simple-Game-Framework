#pragma once
#include <array>
#include <cstddef>
#include <raylib.h>
#include <string>
#include <vector>

namespace sgf {
// core.cpp declaration
//-------------------------------------------------
  #define GAME_LOOP while (!WindowShouldClose())

  class Log {
    public:
      static const int ERROR_LEVEL = 0;
      static const int WARN_LEVEL = 1;
      static const int INFO_LEVEL = 2;

    private:
      int level = ERROR_LEVEL;

    public:
      void ErrorMessage(std::string message);
      void WarningMessage(std::string message);
      void InfoMessage(std::string message);

      void SetLevel(int level);
  };

  typedef Vector2 Position2D;
  typedef Rectangle CollisionShape2D;
  typedef Texture2D Sprite;

  typedef struct Range {
      int min;
      int max;
  } Range;

  typedef struct Circle {
      Position2D center;
      float radius;
  } Circle;

  // This function only draws the the sorrounding lines of a
  // CollisionShape2D and not the full Rectangle, for that
  // raylib offers the DrawRectangleRec function.
  void DrawCollisionShape(CollisionShape2D &body, Color color);

  class Entity2D {
    protected:
      Position2D position = {0,0};
      Log entityLog;

    public:
      Position2D GetPosition() const;
      CollisionShape2D GetCollisionShape() const;
      void SetPosition(Position2D pos);
      void SetWidthAndHeight(float width, float height);

    public:
      static Position2D GetRandomPosition(Range xRange, Range yRange);

    protected:
      Entity2D(Position2D startingPosition);
  };

  class Sprite2D : public Entity2D {
    protected:
      Sprite pngImage;
      float scale = 1.f;
      float rotation = 0;
      Color tint = WHITE;
      CollisionShape2D collisionShape;
    public:
      void DrawSprite();
      void UnloadSprite();

    public:
      void SetRotation(float rotation);
      void SetScale(float scale);
      void SetTint(Color tint);
      void SetPosition(Position2D position);

    public:
      Sprite2D(const std::string &&filePath, float scale, Position2D stPos);
      Sprite2D(const std::string &&filePath, Position2D stPos);
  };

  class World2D {
    protected:
      int width = 0;
      int height = 0;

      Position2D topLeft = {0,0};
      Position2D bottomLeft= {0,0};
      Position2D center = {0,0};
      Position2D topRight = {0,0};
      Position2D bottomRight = {0,0};

      Log worldLog;
    public:
      World2D(int width,int height, Position2D topLeft);
      void DrawBorder(Color color);

    public: // Getter Functionality
      const Position2D& GetCenter() const {return center;}
      const Position2D& GetTopLeft() const {return topLeft;}
      const Position2D& GetTopRight() const {return topRight;}
      const Position2D& GetBottomLeft() const {return bottomLeft;}
      const Position2D& GetBottomRight() const {return bottomRight;}
  };

  template <size_t size>
  class StaticWorld2D : public World2D {
    protected:
      std::array<Entity2D, size> inhabitants;
      size_t x = 0;

    public:
      StaticWorld2D(int width,int height,Position2D topLeft)
        : World2D(width,height,topLeft) {}

      Entity2D& Index(size_t i) {
          return inhabitants.at(i);
      }

      size_t& Population() {
          return x;
      }
      size_t& SpaceLeft() {
          return inhabitants.size() - x;
      }
      size_t& Size() {
          return inhabitants.size();
      }

      void IncreasePopulation(Entity2D e) {
          if (x < inhabitants.size()) {
              inhabitants.at(x) = e;
              x++;
          } else {
              worldLog.ErrorMessage("Tried adding a Entity2D to a full StaticWorld2D");
          }
      }
  };

  class DynamicWorld2D : public World2D {
    protected:
      std::vector<Entity2D> inhabitants;

    public:
      DynamicWorld2D(int width, int height, Position2D topLeft);

      void IncreasePopulation(Entity2D e);
      void DecreasePopulation(size_t &i);

      Entity2D& Index(size_t i);
  };
//-------------------------------------------------
};
