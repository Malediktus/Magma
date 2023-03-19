#include <Magma/pch.h>

#ifdef MG_PLATFORM_APPLE

#include <Magma/Event/Event.h>
#include <Magma/Core/Window.h>

#ifdef MG_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>

namespace Magma
{
    class MacWindow : public Window
    {
    public:
        MacWindow(const char *title, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
            : mTitle(title), mWidth(width), mHeight(height)
        {
            glfwInit();
#ifndef MG_OPENGL
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
#endif
            mWindow = glfwCreateWindow(mWidth, mHeight, title, nullptr, nullptr);

            glfwSetKeyCallback(mWindow, KeyCallback);
            glfwSetMouseButtonCallback(mWindow, ButtonCallback);
            glfwSetCursorPosCallback(mWindow, MotionCallback);
            glfwSetFramebufferSizeCallback(mWindow, ResizeCallback);
            glfwSetWindowCloseCallback(mWindow, CloseCallback);
            glfwSetScrollCallback(mWindow, ScrollCallback);
        }

        ~MacWindow()
        {
            glfwDestroyWindow(mWindow);
            glfwTerminate();
        }

        const int &GetWidth() override
        {
            glfwGetFramebufferSize(mWindow, &mWidth, &mHeight);
            return mWidth;
        }

        const int &GetHeight() override
        {
            glfwGetFramebufferSize(mWindow, &mWidth, &mHeight);
            return mHeight;
        }

        const std::string &GetTitle() const override
        {
            return mTitle;
        }

        void *GetWindowEventHandle() const override
        {
            return mWindow;
        }

        std::vector<const char *> GetVulkanExtensions() const override
        {
#ifdef MG_VULKAN
            uint32_t glfwExtensionCount = 0;
            const char **glfwExtensions;
            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifdef _DEBUG
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

            extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

            return extensions;
#else
            return std::vector<const char *>();
#endif
        }

        void Update() override
        {
            glfwPollEvents();
        }

        void Draw() override
        {
            glfwSwapBuffers(mWindow);
        }

    protected:
        static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
        {
            // TODO: Translate keycodes. Its ok for now because my keycodes match the ones from glfw
            if (action == GLFW_PRESS)
            {
                KeyPressEvent event((KeyCode &)key);
                EventDispatcher::Post(event);
                return;
            }
            else if (action == GLFW_REPEAT)
            {
                KeyRepeatEvent event((KeyCode &)key);
                EventDispatcher::Post(event);
                return;
            }
            KeyReleaseEvent event((KeyCode &)key);
            EventDispatcher::Post(event);
        }

        static void ButtonCallback(GLFWwindow *window, int button, int action, int mods)
        {
            // TODO: Translate keycodes. Its ok for now because my keycodes match the ones from glfw
            if (action == GLFW_PRESS)
            {
                MousePressEvent event((KeyCode &)button);
                EventDispatcher::Post(event);
                return;
            }
            MouseReleaseEvent event((KeyCode &)button);
            EventDispatcher::Post(event);
        }

        static void MotionCallback(GLFWwindow *window, double xpos, double ypos)
        {
            MouseMoveEvent event(xpos, ypos);
            EventDispatcher::Post(event);
        }

        static void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset)
        {
            MouseScrollEvent event(yoffset);
            EventDispatcher::Post(event);
        }

        static void ResizeCallback(GLFWwindow *window, int width, int height)
        {
            WindowResizeEvent event(width, height);
            EventDispatcher::Post(event);
        }

        static void CloseCallback(GLFWwindow *window)
        {
            WindowCloseEvent event;
            EventDispatcher::Post(event);
        }

        int mWidth;
        int mHeight;
        std::string mTitle;
        GLFWwindow *mWindow;
    };

    std::shared_ptr<Window> WindowCreate(const char *title, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
    {
        return std::shared_ptr<Window>(new MacWindow(title, x, y, width, height));
    }
}

#endif