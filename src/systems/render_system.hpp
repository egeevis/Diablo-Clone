#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

// DÜZELTME: core/types.hpp
#include "core/types.hpp"
#include "raylib.h"
#include <vector>
#include <algorithm>

class RenderSystem {
public:
    static RenderSystem& GetInstance() {
        static RenderSystem instance;
        return instance;
    }
    
    // Basit çizim kuyruğu ekleme
    void SubmitDrawCommand(int sortKey, void (*drawFunc)(void*), void* context) {
        m_drawQueue.push_back({sortKey, drawFunc, context});
    }
    
    // Çizim
    void FlushDrawQueue() {
        std::sort(m_drawQueue.begin(), m_drawQueue.end());
        
        for (auto& cmd : m_drawQueue) {
            if (cmd.drawFunction) {
                cmd.drawFunction(cmd.context);
            }
        }
        m_drawQueue.clear();
    }
    
private:
    RenderSystem() = default;
    std::vector<DrawCommand> m_drawQueue;
};

#endif