#include <gglfw3/glfw3.h>

namespace gglfw3 {
    using gsp::gsp;
    using namespace gnumeric::types;

    static void _glfwInit() {
        static bool flag = false;

        if (!flag) {
            glfwInit();
            flag = true;
        }
    }

    struct Monitor {
        static Monitor MakePrimary() {
            _glfwInit();
            Monitor mon {};
            mon.monitor = glfwGetPrimaryMonitor();
            return mon;
        }

        int width() { return glfwGetVideoMode(monitor)->width; }
        int height() { return glfwGetVideoMode(monitor)->height; }
        int refreshRate() { return glfwGetVideoMode(monitor)->refreshRate; }

        private:
        GLFWmonitor* monitor;
    };

    struct Window {
        Window() = default;
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        std::function<void(double, double)> cursorPosCallback;
        std::function<void(int, int, int)> mouseButtonCallback;

        static gsp<Window> Make() {
            _glfwInit();
            auto* win = new Window();
            return gsp<Window>(win);
        }

        void create() {
            checkWindow(false);

            if (width == 0) width = 800;
            if (height == 0) height = 600;
            width += width % 2; height += height % 2;

            window = glfwCreateWindow(width, height, titleBeforeCreate.c_str(), nullptr, nullptr);
            glfwSetWindowUserPointer(window, this);

            glfwSetCursorPosCallback(window, [](GLFWwindow* win, double x, double y) {
                auto* self = (Window*)glfwGetWindowUserPointer(win);
                self->mouseX = x; self->mouseY = y;
                if (self->cursorPosCallback) self->cursorPosCallback(x, y);
            });

            glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods) {
                auto* self = (Window*)glfwGetWindowUserPointer(win);
                if (self->mouseButtonCallback) self->mouseButtonCallback(button, action, mods);
            });

            titleBeforeCreate = "";
            setHidden(isHiddenBeforeCreate);
            setSwapInterval(swapInterval);
            
            makeContextCurrent();
        }

        Window* hint(int hint, int value) {
            checkWindow(false);
            glfwWindowHint(hint, value);
            return this;
        }

        Window* hint330Core() { return hint(GLFW_CONTEXT_VERSION_MAJOR, 3)->hint(GLFW_CONTEXT_VERSION_MINOR, 3)->hint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); }
        Window* hintMsaa(int samples = 4) { return hint(GLFW_SAMPLES, samples); }

        Window* setWidth(int v) {
            if (window) {
                updateSize();
                glfwSetWindowSize(window, v, height);
            } else width = v;

            return this;
        }

        Window* setHeight(int v) {
            if (window) {
                updateSize();
                glfwSetWindowSize(window, width, v);
            } else height = v;

            return this;
        }

        Window* setSize(int w, int h) { return setWidth(w)->setHeight(h); }

        Window* setWidthOfMonitor(float64 ratio) { return setWidth(Monitor::MakePrimary().width() * ratio); }
        Window* setHeightOfMonitor(float64 ratio) { return setHeight(Monitor::MakePrimary().height() * ratio); }
        Window* setSizeOfMonitor(float64 ratio) { return setWidthOfMonitor(ratio)->setHeightOfMonitor(ratio); }
        Window* setSizeOfMonitor(float64 ratioW, float64 ratioH) { return setWidthOfMonitor(ratioW)->setHeightOfMonitor(ratioH); }

        std::pair<int, int> getSize() {
            updateSize();
            return { width, height };
        }

        Window* setTitle(const std::string& title) {
            if (!window) { titleBeforeCreate = title; }
            else glfwSetWindowTitle(window, title.c_str());
            return this;
        }

        void makeContextCurrent() {
            checkWindow(true);
            glfwMakeContextCurrent(window);
        }

        std::pair<double, double> getMousePos() {
            return { mouseX, mouseY };
        }

        bool shouldClose() {
            bool ret = glfwWindowShouldClose(window);
            glfwSetWindowShouldClose(window, false);
            return ret;
        }

        void swapBuffers() {
            checkWindow(true);
            glfwSwapBuffers(window);
        }

        void close() {
            checkWindow(true);
            glfwDestroyWindow(window);
            window = nullptr;
        }

        Window* setHidden(bool v) {
            if (!window) { isHiddenBeforeCreate = v; }
            else {
                if (v) glfwHideWindow(window);
                else glfwShowWindow(window);
            }

            return this;
        }

        Window* setSwapInterval(int v) {
            swapInterval = v;

            if (window) {
                makeContextCurrent();
                glfwSwapInterval(v);
            }

            return this;
        }

        int getSwapInterval() {
            return swapInterval;
        }

        Window* setFullscreen() {
            checkWindow(false);
            setSizeOfMonitor(1.0);
            hint(GLFW_DECORATED, GLFW_FALSE);
            return this;
        }

        ~Window() {
            if (window) {
                glfwDestroyWindow(window);
            }
        }

        private:
        GLFWwindow* window;
        int width, height;
        double mouseX, mouseY;
        std::string titleBeforeCreate = "title";
        bool isHiddenBeforeCreate = false;
        int swapInterval = 1;

        void updateSize() {
            if (!window) return;
            glfwGetWindowSize(window, &width, &height);
        }

        void checkWindow(bool shouldCreated) {
            if (window && !shouldCreated) throw std::runtime_error("Window already created");
            else if (!window && shouldCreated) throw std::runtime_error("Window not created");
        }
    };

    void* getProcAddress(const char* procName) {
        _glfwInit();
        return (void*)glfwGetProcAddress(procName);
    }

    void pollEvents() {
        _glfwInit();
        glfwPollEvents();
    }
}
