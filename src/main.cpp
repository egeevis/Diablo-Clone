#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// Core
#include "core/constants.hpp"
#include "core/theme.hpp"
#include "core/coordinate_system.hpp"

// Entities
#include "entities/player.hpp"
#include "entities/map.hpp"

// Rendering & Systems
#include "rendering/debug_overlay.hpp"
#include "rendering/highlight.hpp"
#include "systems/camera_system.hpp"
#include "systems/movement_system.hpp"

// Global Değişkenler
Map* g_map = nullptr;
Player* g_player = nullptr;
Camera2D g_camera = { 0 };

int main() {
    // 1. PENCERE KURULUMU
    InitWindow(1280, 720, "Project ISO-RPG v0.1: Alignment & Polish");
    SetTargetFPS(60);
    SetTraceLogLevel(LOG_WARNING);

    // 2. ENTITY KURULUMU
    g_map = new Map();
    g_map->Initialize(40, 40); // 40x40 geniş bir harita
    
    g_player = new Player();
    g_player->Initialize();
    
    // v0.1: Karakteri dünya merkezinde (0,0) başlat
    g_player->SetWorldPosition({0, 0});

    // 3. KAMERA KURULUMU (v0.1: Offset ekran ortası, Target oyuncu)
    CameraSystem::Initialize(g_camera, g_player->GetWorldPosition(), 1280, 720);

    DebugOverlay& debug = DebugOverlay::GetInstance();

    // --- GAME LOOP ---
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // --- INPUT ---
        // Zoom Kontrolü
        float wheel = GetMouseWheelMove();
        if (wheel != 0) {
            g_camera.zoom += wheel * 0.1f;
            
            // DÜZELTME: Clamp identifier hatası için manuel kontrol
            if (g_camera.zoom < CameraConst::ZOOM_MIN) g_camera.zoom = CameraConst::ZOOM_MIN;
            if (g_camera.zoom > CameraConst::ZOOM_MAX) g_camera.zoom = CameraConst::ZOOM_MAX;
        }

        // Mouse -> Grid Dönüşümü
        Vector2 mouseGrid = CoordinateSystem::MouseToGrid(g_camera);
        
        // Hareket Emri (Sol Tık)
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (g_map->IsWithinBounds((int)mouseGrid.x, (int)mouseGrid.y)) {
                g_player->MoveToGrid(mouseGrid, g_camera);
            }
        }
        
        // Diğer Inputlar
        g_player->SetSprinting(IsKeyDown(KEY_LEFT_SHIFT));
        if (IsKeyPressed(KEY_F1)) debug.Toggle();

        // --- UPDATE ---
        // Karakter Hareketi
        if (g_player->IsMoving()) {
            Vector2 current = g_player->GetWorldPosition();
            Vector2 target = g_player->GetTargetWorldPosition();
            Vector2 nextPos = MovementSystem::MoveTowards(current, target, g_player->GetMoveSpeed(), dt);
            g_player->SetWorldPosition(nextPos);
            
            // Vector2Distance yerine VectorHelpers kullanıyoruz
            if (VectorHelpers::VectorDistance(nextPos, target) < MoveConst::ARRIVAL_THRESHOLD) {
                g_player->StopMoving();
            }
        }

        // Kamera Takibi (v0.1: Player world position takibi)
        CameraSystem::Update(g_camera, g_player->GetWorldPosition(), dt);

        // --- RENDER ---
        BeginDrawing();
            ClearBackground(Theme::VOID);
            
            BeginMode2D(g_camera);
                // Harita Çizimi
                g_map->Draw(g_camera);
                
                // Mouse Highlight
                if (g_map->IsWithinBounds((int)mouseGrid.x, (int)mouseGrid.y)) {
                    DrawPhantomHighlight(mouseGrid, g_camera);
                }
                
                // Oyuncu Çizimi
                g_player->Draw();
            EndMode2D();
            
            // UI ve Debug Katmanı
            DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, GREEN);
            if (debug.IsEnabled()) {
                debug.Draw(g_camera, mouseGrid, *g_player, (float)GetFPS());
            } else {
                DrawText("F1: Debug | Click: Move | Shift: Sprint", 10, 690, 20, DARKGRAY);
            }

        EndDrawing();
    }

    // Temizlik
    delete g_map;
    delete g_player;
    CloseWindow();
    
    return 0;
}