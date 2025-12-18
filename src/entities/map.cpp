#include "map.hpp"
#include "core/coordinate_system.hpp"
#include "core/theme.hpp"
#include "core/constants.hpp"
#include <algorithm>
#include <cmath>

Map::Map() : m_width(0), m_height(0) {}

void Map::Initialize(int width, int height) {
    m_width = width;
    m_height = height;
    
    m_tiles.resize(m_height);
    for (int y = 0; y < m_height; y++) {
        m_tiles[y].resize(m_width);
        for (int x = 0; x < m_width; x++) {
            // Dama tahtası deseni
            Color c = ((x + y) % 2 == 0) ? Theme::GRID_DARK : Theme::GRID_LIGHT;
            m_tiles[y][x] = Tile(c);
            
            // Rastgele engel (Başlangıç noktası hariç)
            if (GetRandomValue(0, 100) < 10 && (x != 0 || y != 0)) {
                m_tiles[y][x].walkable = false;
                m_tiles[y][x].color = Theme::GRID_UNWALKABLE;
            }
        }
    }
}

void Map::Draw(Camera2D camera) const {
    // Tüm haritayı çiz (v0.1 Basitliği)
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            DrawTile(x, y);
        }
    }
}

void Map::DrawTile(int x, int y) const {
    Vector2 gridPos = {(float)x, (float)y};
    Vector2 corners[4];
    
    // v0.1: Koordinat sistemi üzerinden köşeleri al
    CoordinateSystem::GetTileCorners(gridPos, corners);
    
    const Tile& tile = m_tiles[y][x];
    
    // İzometrik Diamond Çizimi
    DrawTriangle(corners[0], corners[1], corners[2], tile.color);
    DrawTriangle(corners[0], corners[2], corners[3], tile.color);
    
    // Kenar çizgileri (Hafif belirginlik için)
    Color outline = {0, 0, 0, 30};
    DrawLineEx(corners[0], corners[1], 1.0f, outline);
    DrawLineEx(corners[1], corners[2], 1.0f, outline);
    DrawLineEx(corners[2], corners[3], 1.0f, outline);
    DrawLineEx(corners[3], corners[0], 1.0f, outline);
}

Tile::Tile(Color c, bool w, bool o) : color(c), walkable(w), hasObject(o) {}
Tile::Tile() : color(WHITE), walkable(true), hasObject(false) {}

bool Map::IsWithinBounds(int x, int y) const {
    return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

bool Map::IsWalkable(int x, int y) const {
    if (!IsWithinBounds(x, y)) return false;
    return m_tiles[y][x].walkable;
}

Vector2 Map::GetWorldSize() const {
    return { 
        m_width * GridConst::TILE_WIDTH_F, 
        m_height * GridConst::TILE_HEIGHT_F 
    }; 
}