#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Magma/Event/Event.h>
#include <Magma/Event/KeyCode.h>
#include <Magma/Core/Input.h>

namespace Magma
{
    class Camera
    {
    public:
        Camera(float fov, float width, float height)
        {
            m_Fov = fov / 2.0f;
            m_Projection = glm::perspective(m_Fov, width / height, 0.01f, 1000.0f);
            m_View = glm::mat4(1.0f);
            m_Position = glm::vec3(0.0f);
            Update();
        }
        
        glm::mat4 GetViewProj() { return m_ViewProj; }
        virtual void Translate(glm::vec3 v)
        {
            m_Position += v;
            m_View = glm::translate(m_View, v * -1.0f);
            Update();
        }
        
        virtual void UpdateAspectRation(float width, float height)
        {
            m_Projection = glm::perspective(m_Fov, width / height, 0.01f, 1000.0f);
            Update();
        }
        
    protected:
        virtual void Update()
        {
            m_ViewProj = m_Projection * m_View;
        }
        
        float m_Fov;
        glm::vec3 m_Position;
        glm::mat4 m_Projection;
        glm::mat4 m_View;
        glm::mat4 m_ViewProj;
    };

    class FPSCamera : public Camera
    {
    public:
        FPSCamera(float fov, float width, float height)
            : Camera(fov, width, height)
        {
            m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
            m_Yaw = -90.0f;
            m_Pitch = 0.0f;
            glm::vec3 front;
            front.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
            front.y = sin(glm::radians(m_Pitch));
            front.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));
            m_LookAt = glm::normalize(front);
            Update();
            
            m_OldMouseX = Input::GetMouseX();
            m_OldMouseY = Input::GetMouseY();
            EventDispatcher::Subscribe<MouseMoveEvent>(std::bind(&FPSCamera::OnMouseMoved, this, std::placeholders::_1));
        }
        
        void MoveFront(float amount) {
            
            Update();
        }

        void MoveSideways(float amount) {
            Translate(glm::normalize(glm::cross(m_LookAt, m_Up)) * amount);
            Update();
        }
        
    protected:
        void Update() override
        {
            m_View = glm::lookAt(m_Position, m_Position + m_LookAt, m_Up);
            m_ViewProj = m_Projection * m_View;
        }
        
        void OnMouseMoved(const Event &e)
        {
            const MouseMoveEvent &moveEvent = static_cast<const MouseMoveEvent&>(e);
            
            float relX = moveEvent.GetX() - m_OldMouseX;
            float relY = moveEvent.GetY() - m_OldMouseY;
            
            m_Yaw += relX * m_MouseSensitivity;
            m_Pitch -= relY * m_MouseSensitivity;
            if(m_Pitch > 89.0f)
                m_Pitch = 89.0f;
            if(m_Pitch < -89.0f)
                m_Pitch = -89.0f;

            glm::vec3 front;
            front.x = cos(glm::radians(m_Pitch)) * cos(glm::radians(m_Yaw));
            front.y = sin(glm::radians(m_Pitch));
            front.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));
            m_LookAt = glm::normalize(front);
            Update();
            
            m_OldMouseX = moveEvent.GetX();
            m_OldMouseY = moveEvent.GetY();
        }
        
        const float m_MouseSensitivity = 0.3f;
        float m_OldMouseX;
        float m_OldMouseY;
        float m_Yaw;
        float m_Pitch;
        glm::vec3 m_LookAt;
        glm::vec3 m_Up;
    };
}
