#ifndef CAMERA_SYSTEM_HPP
#define CAMERA_SYSTEM_HPP

#include "raylib.h"
// DÜZELTME: core/ öneki
#include "core/constants.hpp"
#include "core/coordinate_system.hpp"
#include <cmath>
#include <algorithm> // Clamp için

class CameraSystem {
public:
    // Kamera başlatma
    static void Initialize(Camera2D& camera, Vector2 target, 
                          int screenWidth, int screenHeight) {
        camera.target = target;
        camera.offset = {
            static_cast<float>(screenWidth) * 0.5f,
            static_cast<float>(screenHeight) * 0.5f
        };
        camera.rotation = 0.0f;
        camera.zoom = CameraConst::ZOOM_DEFAULT;
    }
    
    // Kamera güncelleme (player tracking)
    static void Update(Camera2D& camera, Vector2 target, 
                      const Vector2& worldBounds, float deltaTime) {
        // Smooth follow
        float smoothness = CameraConst::SMOOTHNESS;
        camera.target.x += (target.x - camera.target.x) * smoothness;
        camera.target.y += (target.y - camera.target.y) * smoothness;
        
        // Harita sınırları dışına çıkmasın
        ClampToBounds(camera, worldBounds);
    }
    
    // Kamerayı harita sınırlarına hapset
    static void ClampToBounds(Camera2D& camera, Vector2 worldSize) {
        // Ekran boyutunu zooma göre ölçekle
        float visibleW = GetScreenWidth() / camera.zoom;
        float visibleH = GetScreenHeight() / camera.zoom;
        
        // Yarım ekran boyutu (merkezden kenara)
        float halfW = visibleW * 0.5f;
        float halfH = visibleH * 0.5f;
        
        // Clamp X
        if (camera.target.x < halfW) camera.target.x = halfW;
        if (camera.target.x > worldSize.x - halfW) camera.target.x = worldSize.x - halfW;
        
        // Clamp Y
        if (camera.target.y < halfH) camera.target.y = halfH;
        if (camera.target.y > worldSize.y - halfH) camera.target.y = worldSize.y - halfH;
    }
};

#endif