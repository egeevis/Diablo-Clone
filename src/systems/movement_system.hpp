#ifndef MOVEMENT_SYSTEM_HPP
#define MOVEMENT_SYSTEM_HPP

// DÜZELTME: Include yolları core/ öneki aldı
#include "core/constants.hpp"
#include "core/coordinate_system.hpp"
#include <cmath>

class MovementSystem {
public:
    // FPS-bağımsız sabit hızlı hareket
    static Vector2 MoveTowards(Vector2 current, Vector2 target, 
                               float speed, float deltaTime) {
        
        // Vektör farkı
        float dx = target.x - current.x;
        float dy = target.y - current.y;
        float distance = sqrtf(dx*dx + dy*dy);
        
        // DÜZELTME: Movement:: yerine MoveConst:: kullanıldı
        if (distance <= MoveConst::ARRIVAL_THRESHOLD) {
            return target;
        }
        
        // Normalize et ve hızla çarp
        float dirX = 0;
        float dirY = 0;
        
        if (distance > 0.0001f) {
            dirX = dx / distance;
            dirY = dy / distance;
        }
        
        float moveDistance = speed * deltaTime;
        
        // Hedefi geçmemek için kontrol
        if (moveDistance > distance) {
            return target;
        }
        
        return {
            current.x + dirX * moveDistance,
            current.y + dirY * moveDistance
        };
    }
    
    // Smooth hareket (Lerp - Kamera veya UI için)
    static Vector2 SmoothMoveTowards(Vector2 current, Vector2 target,
                                     float smoothTime, float deltaTime) {
        float dx = target.x - current.x;
        float dy = target.y - current.y;
        
        if (sqrtf(dx*dx + dy*dy) < 0.001f) {
            return target;
        }
        
        // Basit lerp
        float t = 1.0f - powf(0.001f, deltaTime / smoothTime);
        return {
            current.x + dx * t,
            current.y + dy * t
        };
    }
};

#endif