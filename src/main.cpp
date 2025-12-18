#include "raylib.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// --- KRİTİK DÜZELTME: Include yolları "core/" ile başlamalı ---
#include "core/constants.hpp"
#include "core/theme.hpp"
#include "core/coordinate_system.hpp"

// Diğer include'lar
#include "entities/player.hpp"
#include "entities/map.hpp"
#include "rendering/debug_overlay.hpp"
#include "rendering/highlight.hpp"
#include "systems/camera_system.hpp"
#include "systems/movement_system.hpp"

// Global Değişkenler
Map* g_map = nullptr;
Player* g_player = nullptr;
Camera2D g_camera = { 0 };

int main() {
    // Console logu
    std::cout << "[BASLATILIYOR] Pencere aciliyor..." << std::endl;
    
    // Raylib Loglarını kapat (temiz konsol için)
    SetTraceLogLevel(LOG_WARNING);

    // 1. PENCERE
    InitWindow(1280, 720, "RPG Project - FINAL BUILD");
    SetTargetFPS(60);

    std::cout << "[BASLATILIYOR] Sistemler yukleniyor..." << std::endl;

    // 2. KURULUM
    CameraSystem::Initialize(g_camera, {0,0}, 1280, 720);
    
    g_map = new Map();
    g_map->Initialize(20, 20);
    
    g_player = new Player();
    g_player->Initialize();

    DebugOverlay& debug = DebugOverlay::GetInstance();

    std::cout << "[BASARILI] Oyun dongusune giriliyor!" << std::endl;

    // --- GAME LOOP ---
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Input
        float wheel = GetMouseWheelMove();
        if (wheel != 0) {
            g_camera.zoom += wheel * 0.1f;
            if (g_camera.zoom < 0.5f) g_camera.zoom = 0.5f;
            if (g_camera.zoom > 3.0f) g_camera.zoom = 3.0f;
        }

        Vector2 mouseGrid = CoordinateSystem::MouseToGrid(g_camera);
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (g_map->IsWithinBounds((int)mouseGrid.x, (int)mouseGrid.y)) {
                g_player->MoveToGrid(mouseGrid, g_camera);
            }
        }
        
        g_player->SetSprinting(IsKeyDown(KEY_LEFT_SHIFT));
        if (IsKeyPressed(KEY_F1)) debug.Toggle();

        // Update
        if (g_player->IsMoving()) {
            Vector2 current = g_player->GetWorldPosition();
            Vector2 target = g_player->GetTargetWorldPosition();
            Vector2 nextPos = MovementSystem::MoveTowards(current, target, g_player->GetMoveSpeed(), dt);
            g_player->SetWorldPosition(nextPos);
            
            if (VectorHelpers::VectorDistance(nextPos, target) < 2.0f) {
                g_player->StopMoving();
            }
        }

        CameraSystem::Update(g_camera, g_player->GetWorldPosition(), g_map->GetWorldSize(), dt);

        // Render
        BeginDrawing();
            ClearBackground(Theme::VOID);
            BeginMode2D(g_camera);
                g_map->Draw(g_camera);
                if (g_map->IsWithinBounds((int)mouseGrid.x, (int)mouseGrid.y)) {
                    DrawPhantomHighlight(mouseGrid, g_camera);
                }
                g_player->Draw();
            EndMode2D();
            
            DrawText(TextFormat("FPS: %i", GetFPS()), 10, 10, 20, GREEN);
            if (debug.IsEnabled()) debug.Draw(g_camera, mouseGrid, *g_player, (float)GetFPS());
        EndDrawing();
    }

    delete g_map;
    delete g_player;
    CloseWindow();
    return 0;
}