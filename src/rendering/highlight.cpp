#include "rendering/highlight.hpp"
// DÜZELTME: Include yolları core/ öneki aldı
#include "core/coordinate_system.hpp"
#include "core/theme.hpp"
#include <cmath>

void DrawPhantomHighlight(Vector2 gridPos, Camera2D camera) {
    Vector2 corners[4];
    // MouseToGrid'den gelen floor edilmiş gridPos'u kullanıyoruz
    CoordinateSystem::GetTileCorners(gridPos, camera, corners);
    
    // Elmasın (Diamond) içini doldur
    Color fillColor = Theme::HIGHLIGHT;
    fillColor.a = 80; // Saydamlık
    
    DrawTriangle(corners[0], corners[1], corners[2], fillColor);
    DrawTriangle(corners[0], corners[2], corners[3], fillColor);
    
    // Kenar çizgileri
    DrawLineEx(corners[0], corners[1], 2.0f, Theme::GOLD_TEXT);
    DrawLineEx(corners[1], corners[2], 2.0f, Theme::GOLD_TEXT);
    DrawLineEx(corners[2], corners[3], 2.0f, Theme::GOLD_TEXT);
    DrawLineEx(corners[3], corners[0], 2.0f, Theme::GOLD_TEXT);
}