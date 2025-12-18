#ifndef CAMERA_SYSTEM_HPP
#define CAMERA_SYSTEM_HPP

#include "raylib.h"
#include "core/constants.hpp"
#include "core/coordinate_system.hpp"
#include <cmath>
#include <algorithm>

class CameraSystem {
public:
    // Kamera başlatma
    static void Initialize(Camera2D& camera, Vector2 playerWorldPos, int screenWidth, int screenHeight) {
        // v0.1: Offset ekranın tam ortası. 
        // Bu sayede camera.target (oyuncu) ekranın tam merkezinde görünür.
        camera.offset = { (float)screenWidth / 2.0f, (float)screenHeight / 2.0f };
        
        // v0.1: Target doğrudan oyuncunun dünya pozisyonu.
        camera.target = playerWorldPos;
        
        camera.rotation = 0.0f;
        camera.zoom = CameraConst::ZOOM_DEFAULT;
    }

    // Kamera güncelleme (player tracking)
    static void Update(Camera2D& camera, Vector2 targetWorldPos, float deltaTime) {
        // Smooth follow: Kamera hedefe doğru yumuşakça süzülür
        float smoothness = CameraConst::SMOOTHNESS;
        camera.target.x += (targetWorldPos.x - camera.target.x) * smoothness;
        camera.target.y += (targetWorldPos.y - camera.target.y) * smoothness;
    }
    
    // Kamerayı harita sınırlarına hapsetmek gerekirse v0.2'de burayı aktifleştirebiliriz.
    static void ClampToBounds(Camera2D& camera, Vector2 worldSize) {
        float visibleW = GetScreenWidth() / camera.zoom;
        float visibleH = GetScreenHeight() / camera.zoom;
        float halfW = visibleW * 0.5f;
        float halfH = visibleH * 0.5f;
        
        if (camera.target.x < halfW) camera.target.x = halfW;
        if (camera.target.x > worldSize.x - halfW) camera.target.x = worldSize.x - halfW;
        if (camera.target.y < halfH) camera.target.y = halfH;
        if (camera.target.y > worldSize.y - halfH) camera.target.y = worldSize.y - halfH;
    }
};

#endif