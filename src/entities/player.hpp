// player.hpp - Düzeltilmiş
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "raylib.h"
#include <string>

// Forward declaration
class Map;

class Player {
public:
    enum class State {
        IDLE,
        MOVING,
        ATTACKING,
        INTERACTING
    };
    
    // Constructor
    Player();
    
    // Initialization
    void Initialize();
    
    // Movement
    void MoveToGrid(Vector2 targetGrid, Camera2D camera);
    void SetWorldPosition(Vector2 position);
    void StopMoving();
    void SetSprinting(bool sprinting);
    
    // Drawing
    void Draw();
    
    // Getters
    Vector2 GetWorldPosition() const { return m_worldPos; }
    Vector2 GetGridPosition() const { return m_gridPos; }
    Vector2 GetTargetWorldPosition() const { return m_targetWorldPos; }
    State GetState() const { return m_currentState; }
    const char* GetStateString() const;
    float GetMoveSpeed() const { return m_moveSpeed; }
    bool IsMoving() const { return m_currentState == State::MOVING; }
    
    // Debug
    void ToggleDebug() { m_showDebug = !m_showDebug; }
    
private:
    // Position data
    Vector2 m_worldPos;
    Vector2 m_targetWorldPos;
    Vector2 m_gridPos;
    Vector2 m_targetGridPos;
    
    // Movement
    Vector2 m_velocity;
    float m_moveSpeed;
    float m_rotation;
    
    // State
    State m_currentState;
    
    // Physics
    Rectangle m_collisionRect;
    Color m_color;
    
    // Debug
    bool m_showDebug;
    
    // Internal state
    float m_attackTimer;
    float m_lastClickTime;
    bool m_isSprinting;
    
    // Helper functions
    void UpdateStateString();
    
    // Constants (inline static)
    static constexpr float COLLISION_WIDTH = 20.0f;
    static constexpr float COLLISION_HEIGHT = 40.0f;
    static constexpr float RADIUS = 15.0f;
};

#endif