#include "rendering/highlight.hpp"
#include "core/coordinate_system.hpp"
#include "core/theme.hpp"
#include <cmath>

void DrawPhantomHighlight(Vector2 gridPos, Camera2D camera) {
    Vector2 corners[4];
    
    // v0.1 DÜZELTME: Sınıf ismini (CoordinateSystem::) ekledik
    CoordinateSystem::GetTileCorners(gridPos, corners);
    
    // Yarı saydam dolgu (Elmasın içini boya)
    Color fillColor = Theme::HIGHLIGHT;
    fillColor.a = static_cast<unsigned char>(Theme::HIGHLIGHT_ALPHA * 255);
    
    DrawTriangle(corners[0], corners[1], corners[2], fillColor);
    DrawTriangle(corners[0], corners[2], corners[3], fillColor);
    
    // Kenar çizgileri (Altın sarısı / Tema rengi)
    Color borderColor = Theme::GOLD_TEXT;
    borderColor.a = 230; // %90 opaklık
    
    DrawLineEx(corners[0], corners[1], 2.0f, borderColor);
    DrawLineEx(corners[1], corners[2], 2.0f, borderColor);
    DrawLineEx(corners[2], corners[3], 2.0f, borderColor);
    DrawLineEx(corners[3], corners[0], 2.0f, borderColor);
    
    // Köşe noktaları (Daha belirgin durması için küçük noktalar)
    for (int i = 0; i < 4; i++) {
        DrawCircleV(corners[i], 2.0f, Theme::GOLD_TEXT);
    }

    // --- POLISH: Procedural Glow (Kodla Çizilen Parlama) ---
    static float pulseTime = 0.0f;
    pulseTime += GetFrameTime();
    float pulse = (sinf(pulseTime * 4.0f) * 0.5f + 0.5f); // 0 ile 1 arası dalgalanma
    
    // DÜZELTME: GridToWorld çağrısı CoordinateSystem:: ile yapıldı
    Vector2 worldCenter = CoordinateSystem::GridToWorld(gridPos);
    
    Color glowColor = Theme::HIGHLIGHT;
    glowColor.a = (unsigned char)(40 * pulse); // Hafif parlama
    DrawCircleV(worldCenter, 10.0f + (5.0f * pulse), glowColor);
}