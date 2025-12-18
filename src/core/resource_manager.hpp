// resource_manager.hpp - Asset yönetimi (Load/Unload tek yer)
#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include "raylib.h"
#include <string>
#include <unordered_map>
#include <memory>

class ResourceManager {
public:
    static ResourceManager& GetInstance() {
        static ResourceManager instance;
        return instance;
    }
    
    // Texture yükleme
    Texture2D LoadTexture(const std::string& path, const std::string& id) {
        if (m_textures.find(id) != m_textures.end()) {
            return m_textures[id];
        }
        
        Texture2D texture = LoadTexture(path.c_str());
        if (texture.id != 0) {
            m_textures[id] = texture;
            m_texturePaths[id] = path;
        }
        
        return texture;
    }
    
    // Texture al
    Texture2D GetTexture(const std::string& id) const {
        auto it = m_textures.find(id);
        return (it != m_textures.end()) ? it->second : Texture2D{};
    }
    
    // Font yükleme
    Font LoadFont(const std::string& path, const std::string& id, int fontSize = 20) {
        if (m_fonts.find(id) != m_fonts.end()) {
            return m_fonts[id];
        }
        
        Font font = LoadFontEx(path.c_str(), fontSize, nullptr, 0);
        if (font.texture.id != 0) {
            m_fonts[id] = font;
            m_fontPaths[id] = path;
        }
        
        return font;
    }
    
    // Tüm resource'ları temizle
    void UnloadAll() {
        for (auto& [id, texture] : m_textures) {
            UnloadTexture(texture);
        }
        m_textures.clear();
        m_texturePaths.clear();
        
        for (auto& [id, font] : m_fonts) {
            UnloadFont(font);
        }
        m_fonts.clear();
        m_fontPaths.clear();
        
        // Sound'lar vs. eklenebilir
    }
    
    // Resource var mı kontrol et
    bool HasTexture(const std::string& id) const {
        return m_textures.find(id) != m_textures.end();
    }
    
    bool HasFont(const std::string& id) const {
        return m_fonts.find(id) != m_fonts.end();
    }
    
private:
    ResourceManager() = default;
    ~ResourceManager() {
        UnloadAll();
    }
    
    std::unordered_map<std::string, Texture2D> m_textures;
    std::unordered_map<std::string, std::string> m_texturePaths;
    std::unordered_map<std::string, Font> m_fonts;
    std::unordered_map<std::string, std::string> m_fontPaths;
    
    // Singleton
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
};

#endif // RESOURCE_MANAGER_HPP