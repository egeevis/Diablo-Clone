// state_machine.hpp - Finite State Machine sistemi
#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "types.hpp"
#include <functional>
#include <unordered_map>

class StateMachine {
public:
    using StateHandler = std::function<void(float deltaTime)>;
    using TransitionCheck = std::function<bool()>;
    
    struct State {
        EntityState id;
        StateHandler onEnter;
        StateHandler onUpdate;
        StateHandler onExit;
        std::unordered_map<EntityState, TransitionCheck> transitions;
    };
    
    StateMachine() : m_currentState(EntityState::IDLE) {}
    
    void AddState(EntityState state, StateHandler onEnter, 
                  StateHandler onUpdate, StateHandler onExit) {
        m_states[state] = {state, onEnter, onUpdate, onExit, {}};
    }
    
    void AddTransition(EntityState from, EntityState to, TransitionCheck condition) {
        if (m_states.find(from) != m_states.end()) {
            m_states[from].transitions[to] = condition;
        }
    }
    
    void SetState(EntityState newState) {
        if (m_currentState == newState) return;
        
        // Exit current state
        if (m_states.find(m_currentState) != m_states.end() && 
            m_states[m_currentState].onExit) {
            m_states[m_currentState].onExit(0);
        }
        
        // Enter new state
        m_currentState = newState;
        if (m_states.find(m_currentState) != m_states.end() && 
            m_states[m_currentState].onEnter) {
            m_states[m_currentState].onEnter(0);
        }
    }
    
    void Update(float deltaTime) {
        // Check transitions
        if (m_states.find(m_currentState) != m_states.end()) {
            auto& state = m_states[m_currentState];
            
            for (auto& [toState, condition] : state.transitions) {
                if (condition()) {
                    SetState(toState);
                    break;
                }
            }
            
            // Update current state
            if (state.onUpdate) {
                state.onUpdate(deltaTime);
            }
        }
    }
    
    EntityState GetCurrentState() const { return m_currentState; }
    const char* GetStateName() const {
        switch (m_currentState) {
            case EntityState::IDLE: return "IDLE";
            case EntityState::MOVING: return "MOVING";
            case EntityState::ATTACKING: return "ATTACKING";
            case EntityState::CASTING: return "CASTING";
            case EntityState::DEAD: return "DEAD";
            case EntityState::INTERACTING: return "INTERACTING";
            case EntityState::STUNNED: return "STUNNED";
            default: return "UNKNOWN";
        }
    }
    
private:
    EntityState m_currentState;
    std::unordered_map<EntityState, State> m_states;
};

#endif // STATE_MACHINE_HPP