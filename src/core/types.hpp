// types.hpp - Tüm forward declarations
#ifndef TYPES_HPP
#define TYPES_HPP

// İleri bildirimler (bağımlılık önleme)
class Player;
class Map;
struct CameraController;
class ResourceManager;

// Temel yapılar (Raylib wrapper'ları)
struct Vector2Int {
    int x, y;
    Vector2Int(int x = 0, int y = 0) : x(x), y(y) {}
};

// Render queue için temel yapı
struct DrawCommand {
    int sortKey; // Z-order için (yükseklik + tür)
    void (*drawFunction)(void* context);
    void* context;
    
    bool operator<(const DrawCommand& other) const {
        return sortKey < other.sortKey;
    }
};

// FSM için state temelleri
enum class EntityState {
    IDLE,
    MOVING,
    ATTACKING,
    CASTING,
    DEAD,
    INTERACTING,
    STUNNED
};

// Coordinate spaces
enum class CoordinateSpace {
    GRID,      // Tile koordinatları (int)
    WORLD,     // Pixel koordinatları (float)
    SCREEN     // Ekran koordinatları (float)
};

#endif // TYPES_HPP