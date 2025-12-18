#ifndef COORDINATE_SYSTEM_HPP
#define COORDINATE_SYSTEM_HPP

#include "constants.hpp"
#include "raylib.h"
#include <cmath>

// main.cpp ve diğer yerlerde kullanılacak yardımcı matematik araçları
namespace VectorHelpers {
    inline float VectorDistance(Vector2 a, Vector2 b) {
        float dx = b.x - a.x;
        float dy = b.y - a.y;
        return sqrtf(dx * dx + dy * dy);
    }
}

class CoordinateSystem {
public:
    // 1. Grid (Cartesian) -> World (Isometric Pixel)
    // Formül: (x - y) * (W/2) , (x + y) * (H/2)
    static Vector2 GridToWorld(Vector2 gridPos) {
        return {
            (gridPos.x - gridPos.y) * (GridConst::TILE_WIDTH_F * 0.5f),
            (gridPos.x + gridPos.y) * (GridConst::TILE_HEIGHT_F * 0.5f)
        };
    }

    // 2. World (Pixel) -> Grid (Float)
    // İzometrik ters dönüşüm (v0.1 Hassasiyeti)
    static Vector2 WorldToGrid(Vector2 worldPos) {
        float halfW = GridConst::TILE_WIDTH_F * 0.5f;
        float halfH = GridConst::TILE_HEIGHT_F * 0.5f;

        float gx = (worldPos.x / halfW + worldPos.y / halfH) * 0.5f;
        float gy = (worldPos.y / halfH - worldPos.x / halfW) * 0.5f;

        return { gx, gy };
    }

    // 3. Mouse -> Grid (Integer/Floor)
    static Vector2 MouseToGrid(const Camera2D& camera) {
        // Raylib'in ScreenToWorld fonksiyonu Camera Offset'i otomatik çözer.
        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
        Vector2 gridPos = WorldToGrid(mouseWorld);
        
        return { floorf(gridPos.x), floorf(gridPos.y) };
    }

    // 4. Tile Köşeleri (Çizim için World Koordinatları)
    static void GetTileCorners(Vector2 gridPos, Vector2 corners[4]) {
        // Gelen gridPos zaten floor edilmiş olmalı (MouseToGrid'den gelen)
        corners[0] = GridToWorld(gridPos);                                 // Üst
        corners[1] = GridToWorld({gridPos.x + 1, gridPos.y});             // Sağ
        corners[2] = GridToWorld({gridPos.x + 1, gridPos.y + 1});         // Alt
        corners[3] = GridToWorld({gridPos.x, gridPos.y + 1});             // Sol
    }
};

#endif