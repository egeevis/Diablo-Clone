#ifndef MAP_HPP
#define MAP_HPP

#include "raylib.h"
#include <vector>

// Forward declaration for Tile
struct Tile {
    Color color;
    bool walkable;
    bool hasObject;
    
    Tile(Color c, bool w = true, bool o = false);
    Tile();
};

class Map {
public:
    // Constructor
    Map();
    
    // Initialization
    void Initialize(int width = 25, int height = 18);
    
    // Drawing
    void Draw(Camera2D camera) const;
    
    // Accessors
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    Vector2 GetWorldSize() const;
    
    // Tile operations
    bool IsWalkable(int x, int y) const;
    bool IsWithinBounds(int x, int y) const;
    
private:
    // v0.1 DÜZELTME: DrawTile parametre sayısı cpp ile eşitlendi (Camera kaldırıldı)
    void DrawTile(int x, int y) const;
    
    int m_width;
    int m_height;
    std::vector<std::vector<Tile>> m_tiles;
};

#endif