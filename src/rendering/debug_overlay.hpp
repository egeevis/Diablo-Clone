#ifndef DEBUG_OVERLAY_HPP
#define DEBUG_OVERLAY_HPP

// DÜZELTME: Include yolları core/ öneki aldı
#include "core/constants.hpp"
#include "core/coordinate_system.hpp"
#include "core/theme.hpp"

#include "entities/player.hpp" // Player class'ını tanıması için
#include <string>
#include <vector>

class DebugOverlay {
    bool m_enabled = false;
    struct DebugInfo { std::string label; std::string value; };
    std::vector<DebugInfo> m_debugInfo;

    // Singleton private constructor
    DebugOverlay() = default;

public:
    static DebugOverlay& GetInstance() {
        static DebugOverlay instance;
        return instance;
    }
    
    // Kopyalamayı engelle
    DebugOverlay(const DebugOverlay&) = delete;
    void operator=(const DebugOverlay&) = delete;

    void Toggle() { m_enabled = !m_enabled; }
    bool IsEnabled() const { return m_enabled; }
    
    // Overlay'i çiz
    void Draw(const Camera2D& camera, Vector2 mouseGridPos, const Player& player, float fps) {
        if (!m_enabled) return;

        // Arkaplan
        DrawRectangle(10, 35, 300, 200, Theme::DEBUG_BACKGROUND);
        
        int y = 45;
        int x = 20;
        int spacing = 20;

        DrawText("--- DEBUG INFO ---", x, y, 10, Theme::GOLD_TEXT); y += spacing + 5;
        
        // FPS
        DrawText(TextFormat("FPS: %.0f", fps), x, y, 10, GREEN); y += spacing;
        
        // Mouse Grid
        DrawText(TextFormat("Grid: [%.0f, %.0f]", mouseGridPos.x, mouseGridPos.y), x, y, 10, WHITE); y += spacing;

        // World Pos
        Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);
        DrawText(TextFormat("World: [%.0f, %.0f]", mouseWorld.x, mouseWorld.y), x, y, 10, WHITE); y += spacing;
        
        // Player State
        DrawText(TextFormat("P. State: %s", player.GetStateString()), x, y, 10, YELLOW); y += spacing;
        DrawText(TextFormat("P. Grid: [%.0f, %.0f]", player.GetGridPosition().x, player.GetGridPosition().y), x, y, 10, YELLOW); y += spacing;

        // Zoom
        DrawText(TextFormat("Zoom: %.2f", camera.zoom), x, y, 10, LIGHTGRAY);
    }
};

#endif