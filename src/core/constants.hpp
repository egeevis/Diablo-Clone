// constants.hpp - Sabitler (Raylib çakışmaları düzeltildi)
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// === GRID ===
namespace GridConst {
    constexpr int TILE_WIDTH = 64;
    constexpr int TILE_HEIGHT = 32;
    constexpr float TILE_WIDTH_F = 64.0f;
    constexpr float TILE_HEIGHT_F = 32.0f;
}

// === MOVEMENT ===
namespace MoveConst {
    constexpr float BASE_SPEED = 200.0f;
    constexpr float SPRINT_SPEED = 320.0f;
    constexpr float MIN_SPEED = 90.0f;
    constexpr float ARRIVAL_THRESHOLD = 2.5f;
    constexpr float SNAP_DISTANCE = 0.5f;
}

// === INPUT ===
namespace InputConst {
    constexpr float CLICK_TOLERANCE = 8.0f;
    constexpr float MIN_RETARGET_TIME = 0.1f;
}

// === COMBAT ===
namespace CombatConst {
    constexpr float MELEE_REACH = 1.15f;
    constexpr float INTERACTION_RANGE = 1.2f;
    constexpr float ATTACK_LOCK_DIST = 0.8f;
    constexpr float PRE_ATTACK_DELAY = 0.1f;
}

// === CAMERA ===  
namespace CameraConst {
    constexpr float SMOOTHNESS = 0.1f;
    constexpr float ZOOM_MIN = 0.5f;
    constexpr float ZOOM_MAX = 2.0f;
    constexpr float ZOOM_DEFAULT = 1.0f;
}

// === UI ===
namespace UIConst {
    constexpr int DEBUG_FONT_SIZE = 18;
    constexpr int DEBUG_PADDING = 20;
    constexpr int DEBUG_LINE_HEIGHT = 24;
    constexpr float DEBUG_BG_ALPHA = 0.7f;
}

// === PLAYER CONSTANTS ===
namespace PlayerConst {
    constexpr float COLLISION_WIDTH = 20.0f;
    constexpr float COLLISION_HEIGHT = 40.0f;
    constexpr float RADIUS = 15.0f;
    constexpr float SELECTION_RADIUS = 25.0f;
}

// === MAP CONSTANTS ===
namespace MapConst {
    constexpr int DEFAULT_WIDTH = 25;
    constexpr int DEFAULT_HEIGHT = 18;
    constexpr int MAX_WIDTH = 100;
    constexpr int MAX_HEIGHT = 100;
}

#endif