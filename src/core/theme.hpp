// theme.hpp - Tema ve renkler
#ifndef THEME_HPP
#define THEME_HPP

#include "raylib.h"

namespace Theme {
    // Renkler
    constexpr Color VOID = {10, 10, 15, 255};
    constexpr Color GOLD_TEXT = {255, 215, 0, 255};
    constexpr Color HIGHLIGHT = {255, 255, 100, 255};
    
    // Grid renkleri
    constexpr Color GRID_DARK = {60, 60, 70, 255};
    constexpr Color GRID_LIGHT = {80, 80, 90, 255};
    constexpr Color GRID_UNWALKABLE = {120, 60, 40, 255};
    
    // Oyuncu renkleri
    constexpr Color PLAYER_PRIMARY = {65, 105, 225, 255};
    constexpr Color PLAYER_SECONDARY = {30, 144, 255, 255};
    
    // Debug
    constexpr Color DEBUG_BACKGROUND = {0, 0, 0, 178};
    
    // Alpha değerleri
    constexpr float HIGHLIGHT_ALPHA = 0.2f;
}

#endif