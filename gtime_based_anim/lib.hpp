namespace gtime_based_anim {
    using namespace gnumeric::types;
    using ggeometry::Vec2;

    struct TimeBasedAnim {
        float64 duration;
        float64 lastTime;
        Vec2 value;
        std::function<float64(const Vec2&, float64)> easing = [](const Vec2& v, float64 p) { return v.x + (v.y - v.x) * p; };

        float64 get(float64 t) {
            auto p = std::clamp((t - lastTime) / duration, 0.0, 1.0);
            return easing(value, p);
        }

        TimeBasedAnim& set(float64 t, float64 nv = 0.0) {
            value = { get(t), nv };
            lastTime = t;
            return *this;
        }

        TimeBasedAnim& weakSet(float64 t, float64 nv = 0.0) {
            if (value.y != nv) set(t, nv);
            return *this;
        }

        TimeBasedAnim& reset(float64 nv = 0.0) {
            value = Vec2(nv);
            return *this;
        }
    };
    }
