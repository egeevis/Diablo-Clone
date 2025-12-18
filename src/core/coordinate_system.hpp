#ifndef COORDINATE_SYSTEM_HPP
#define COORDINATE_SYSTEM_HPP

#include "constants.hpp"
#include "raylib.h"
#include <cmath>

// main.cpp'deki hatayı çözmek için VectorHelpers'ı buraya kesin olarak ekliyoruz
namespace VectorHelpers {
    inline float VectorDistance(Vector2 a, Vector2 b) {
        float dx = b.x - a.x;
        float dy = b.y - a.y;
        return sqrtf(dx * dx + dy * dy);
    }
}

class CoordinateSystem {
public:
    static Vector2 GridToWorld(Vector2 gridPos) {
        return {
            (gridPos.x - gridPos.y) * (GridConst::TILE_WIDTH_F * 0.5f),
            (gridPos.x + gridPos.y) * (GridConst::TILE_HEIGHT_F * 0.5f)
        };
    }

    static Vector2 WorldToGrid(Vector2 worldPos) {
        float halfW = GridConst::TILE_WIDTH_F * 0.5f;
        float halfH = GridConst::TILE_HEIGHT_F * 0.5f;
        // İzometrik ters dönüşüm (Kaymayı önleyen hassas matematik)
        float gx = (worldPos.x / halfW + worldPos.y / halfH) * 0.5f;
        float gy = (worldPos.y / halfH - worldPos.x / halfW) * 0.5f;
        return { gx, gy };
    }

    static Vector2 MouseToGrid(const Camera2D& camera) {
        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
        Vector2 gridPos = WorldToGrid(mouseWorld);
        // floorf kullanarak negatif alanlarda (0,0'ın gerisi) doğru tile'ı seçiyoruz
        return { floorf(gridPos.x), floorf(gridPos.y) };
    }

    static void GetTileCorners(Vector2 gridPos, const Camera2D& camera, Vector2 corners[4]) {
        Vector2 baseGrid = { floorf(gridPos.x), floorf(gridPos.y) };
        corners[0] = GridToWorld(baseGrid);                                 // Üst
        corners[1] = GridToWorld({baseGrid.x + 1, baseGrid.y});             // Sağ
        corners[2] = GridToWorld({baseGrid.x + 1, baseGrid.y + 1});         // Alt
        corners[3] = GridToWorld({baseGrid.x, baseGrid.y + 1});             // Sol
    }
};

#endif