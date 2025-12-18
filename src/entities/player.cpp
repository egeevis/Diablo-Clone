#include "player.hpp"
#include "core/constants.hpp"
#include "core/coordinate_system.hpp"
#include "core/theme.hpp"
#include "rendering/debug_overlay.hpp"
#include <cmath>
#include <cstdio> // snprintf için

Player::Player() {
    // Başlangıç pozisyonu (Grid ortaları)
    m_worldPos = {400.0f, 300.0f};
    m_targetWorldPos = m_worldPos;
    m_gridPos = CoordinateSystem::WorldToGrid(m_worldPos);
    m_targetGridPos = m_gridPos;
    
    m_velocity = {0, 0};
    m_moveSpeed = MoveConst::BASE_SPEED; // DÜZELTİLDİ: Movement -> MoveConst
    m_rotation = 0.0f;
    
    m_currentState = State::IDLE;
    
    m_color = Theme::PLAYER_PRIMARY;
    m_showDebug = true;
    m_isSprinting = false;
}

void Player::Initialize() {
    // Gerekirse ek init işlemleri
}

void Player::MoveToGrid(Vector2 targetGrid, Camera2D camera) {
    m_targetGridPos = targetGrid;
    
    // Grid -> World dönüşümü (Merkeze hizala)
    Vector2 targetWorld = CoordinateSystem::GridToWorld(targetGrid);
    
    // Tile'ın tam ortasına gitmesi için offset eklemiyoruz, GridToWorld zaten köşeyi verebilir
    // Isometric merkezleme için manuel ayar gerekebilir ama şimdilik doğrudan kullanıyoruz.
    m_targetWorldPos = targetWorld;
    
    m_currentState = State::MOVING;
}

void Player::StopMoving() {
    m_currentState = State::IDLE;
    m_velocity = {0, 0};
}

void Player::SetWorldPosition(Vector2 position) {
    m_worldPos = position;
    // Grid pozisyonunu güncelle
    m_gridPos = CoordinateSystem::WorldToGrid(m_worldPos);
}

void Player::SetSprinting(bool sprinting) {
    m_isSprinting = sprinting;
    m_moveSpeed = sprinting ? MoveConst::SPRINT_SPEED : MoveConst::BASE_SPEED;
}

void Player::Draw() {
    // 1. Gölge (Basit elips)
    DrawEllipse((int)m_worldPos.x, (int)m_worldPos.y + 10, 15, 8, {0, 0, 0, 100});

    // 2. Karakter Gövdesi
    DrawCircleV(m_worldPos, 12.0f, m_color); // Yarıçap sabiti yerine doğrudan değer girdim şimdilik
    DrawCircleV(m_worldPos, 10.0f, Theme::PLAYER_SECONDARY);

    // 3. Debug Bilgileri
    if (m_showDebug) {
        // Hedef çizgisi
        if (m_currentState == State::MOVING) {
            DrawLineEx(m_worldPos, m_targetWorldPos, 1.0f, Fade(GREEN, 0.5f));
            DrawCircleV(m_targetWorldPos, 3.0f, GREEN);
        }
        
        // State yazısı
        DrawText(GetStateString(), (int)m_worldPos.x - 20, (int)m_worldPos.y - 40, 10, WHITE);
    }
}

const char* Player::GetStateString() const {
    switch (m_currentState) {
        case State::IDLE: return "IDLE";
        case State::MOVING: return "MOVING";
        case State::ATTACKING: return "ATTACKING";
        default: return "UNKNOWN";
    }
}