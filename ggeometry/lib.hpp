namespace ggeometry {
    using namespace gnumeric::types;

    struct Vec2 {
        float64 x, y;

        Vec2() = default;
        template <typename A, typename B> Vec2(A a, B b) : x((float64)a), y((float64)b) {}
        template <typename T> Vec2(T v) : x((float64)v), y((float64)v) {}

        float64 sum() const noexcept { return x + y; }
        float64 length() const noexcept { return std::sqrt(x * x + y * y); }
        float64 lengthSquared() const noexcept { return x * x + y * y; }
        float64 xyDiff() const noexcept { return std::abs(x - y); }
        float64 max() const noexcept { return std::max(x, y); }
        float64 min() const noexcept { return std::min(x, y); }
        Vec2 abs() const noexcept { return { std::abs(x), std::abs(y) }; }
        float64 atanDegrees() const noexcept { return std::atan2(y, x) / std::numbers::pi * 180.0; }

        Vec2 operator+(const Vec2& v) const noexcept { return { x + v.x, y + v.y }; }
        Vec2 operator-(const Vec2& v) const noexcept { return { x - v.x, y - v.y }; }
        Vec2 operator*(const Vec2& v) const noexcept { return { x * v.x, y * v.y }; }
        Vec2 operator/(const Vec2& v) const noexcept { return { x / v.x, y / v.y }; }
        Vec2 operator+(float64 v) const noexcept { return { x + v, y + v }; }
        Vec2 operator-(float64 v) const noexcept { return { x - v, y - v }; }
        Vec2 operator*(float64 v) const noexcept { return { x * v, y * v }; }
        Vec2 operator/(float64 v) const noexcept { return { x / v, y / v }; }
        Vec2 operator-() const noexcept { return { -x, -y }; }

        Vec2& operator+=(const Vec2& v) noexcept { x += v.x; y += v.y; return *this; }
        Vec2& operator-=(const Vec2& v) noexcept { x -= v.x; y -= v.y; return *this; }
        Vec2& operator*=(const Vec2& v) noexcept { x *= v.x; y *= v.y; return *this; }
        Vec2& operator/=(const Vec2& v) noexcept { x /= v.x; y /= v.y; return *this; }
        Vec2& operator+=(float64 v) noexcept { x += v; y += v; return *this; }
        Vec2& operator-=(float64 v) noexcept { x -= v; y -= v; return *this; }
        Vec2& operator*=(float64 v) noexcept { x *= v; y *= v; return *this; }
        Vec2& operator/=(float64 v) noexcept { x /= v; y /= v; return *this; }

        bool operator==(const Vec2& v) const noexcept { return x == v.x && y == v.y; }
        bool operator!=(const Vec2& v) const noexcept { return x != v.x || y != v.y; }

        Vec2 rotate(float64 angle, float64 length) const noexcept {
            float64 c = std::cos(angle); float64 s = std::sin(angle);
            return Vec2 { x + c * length, y + s * length };
        }

        Vec2 rotateDegrees(float64 angle, float64 length) const noexcept { return rotate(angle / 180.0 * std::numbers::pi, length); }
        bool isZeroZone() const noexcept { return x == y; }
        bool include(float64 v) const noexcept { return x <= v && v <= y; }
        std::pair<float64, float64> toPair() const noexcept { return { x, y }; }
    };

    struct Rect {
        float64 x, y, w, h;

        static Rect MakeCenter(float64 x, float64 y, float64 w, float64 h) noexcept {
            return { x - w / 2, y - h / 2, w, h };
        }

        Vec2 position() const noexcept { return { x, y }; }
        Vec2 size() const noexcept { return { w, h }; }
        Vec2 center() const noexcept { return { x + w / 2, y + h / 2 }; }

        Rect extend(float64 padding) const noexcept {
            return {
                x - padding, y - padding,
                w + padding * 2, h + padding * 2
            };
        }
    };

    struct Transform2D {
        float64 mat[6];

        Transform2D(float64 a, float64 b, float64 c, float64 d, float64 e, float64 f) noexcept {
            set(a, b, c, d, e, f);
        }

        Transform2D() noexcept {
            set(1, 0, 0, 1, 0, 0);
        }

        Transform2D& set(float64 a, float64 b, float64 c, float64 d, float64 e, float64 f) noexcept {
            mat[0] = a; mat[1] = b;
            mat[2] = c; mat[3] = d;
            mat[4] = e; mat[5] = f;
            return *this;
        }

        Transform2D& transform(float64 a, float64 b, float64 c, float64 d, float64 e, float64 f) noexcept {
            set(
                mat[0] * a + mat[2] * b,
                mat[1] * a + mat[3] * b,
                mat[0] * c + mat[2] * d,
                mat[1] * c + mat[3] * d,
                mat[0] * e + mat[2] * f + mat[4],
                mat[1] * e + mat[3] * f + mat[5]
            );
            return *this;
        }

        Transform2D& transform(const Transform2D& o) noexcept {
            transform(o.mat[0], o.mat[1], o.mat[2], o.mat[3], o.mat[4], o.mat[5]);
            return *this;
        }

        Transform2D& scale(float64 x, float64 y) noexcept {
            transform(x, 0.0, 0.0, y, 0.0, 0.0);
            return *this;
        }

        Transform2D& scale(const Vec2& v) noexcept {
            scale(v.x, v.y);
            return *this;
        }

        Transform2D& scale(float64 s) noexcept {
            scale(s, s);
            return *this;
        }

        Transform2D& translate(float64 x, float64 y) noexcept {
            transform(1.0, 0.0, 0.0, 1.0, x, y);
            return *this;
        }

        Transform2D& translate(const Vec2& v) noexcept {
            translate(v.x, v.y);
            return *this;
        }

        Transform2D& rotate(float64 angle) noexcept {
            float64 c = std::cos(angle);
            float64 s = std::sin(angle);
            transform(c, s, -s, c, 0.0, 0.0);
            return *this;
        }

        Transform2D& rotateDegrees(float64 angle) noexcept {
            rotate(angle / 180.0 * std::numbers::pi);
            return *this;
        }

        Vec2 transformPoint(float64 x, float64 y) const noexcept {
            return Vec2 {
                mat[0] * x + mat[2] * y + mat[4],
                mat[1] * x + mat[3] * y + mat[5]
            };
        }

        Vec2 transformPoint(const Vec2& v) const noexcept {
            return transformPoint(v.x, v.y);
        }

        Transform2D getInverse() const noexcept {
            float64 det = mat[0] * mat[3] - mat[1] * mat[2];
            float64 invDet = det != 0 ? 1.0 / det : 1e9;
            return Transform2D(
                mat[3] * invDet, -mat[1] * invDet,
                -mat[2] * invDet, mat[0] * invDet,
                (mat[2] * mat[5] - mat[3] * mat[4]) * invDet,
                (mat[1] * mat[4] - mat[0] * mat[5]) * invDet
            );
        }
    };

    bool pointStrictlyInConvexQuad(const Vec2& p, const Vec2 quad[4]) noexcept {
        auto cross = [](float64 ax, float64 ay, float64 bx, float64 by) {
            return ax * by - ay * bx;
        };

        auto x = p.x, y = p.y;
        auto cross0 = cross(quad[1].x - quad[0].x, quad[1].y - quad[0].y, x - quad[0].x, y - quad[0].y);
        auto cross1 = cross(quad[2].x - quad[1].x, quad[2].y - quad[1].y, x - quad[1].x, y - quad[1].y);
        auto cross2 = cross(quad[3].x - quad[2].x, quad[3].y - quad[2].y, x - quad[2].x, y - quad[2].y);
        auto cross3 = cross(quad[0].x - quad[3].x, quad[0].y - quad[3].y, x - quad[3].x, y - quad[3].y);
        
        if (cross0 < 0 && cross1 < 0 && cross2 < 0 && cross3 < 0) return true;
        if (cross0 > 0 && cross1 > 0 && cross2 > 0 && cross3 > 0) return true;
        
        return false;
    }

    bool pointStrictlyInRect(const Vec2& p, const Rect& r) noexcept {
        return (
            r.x < p.x && p.x < r.x + r.w &&
            r.y < p.y && p.y < r.y + r.h
        );
    }

    bool lineIsIntersectLineSeg(const Vec2& linePoint, float64 lineDeg, const Vec2 seg[2]) noexcept {
        float64 angle = lineDeg / 180.0 * std::numbers::pi;
        Vec2 dir = { std::cos(angle), std::sin(angle) };
        
        Vec2 s = seg[1] - seg[0];
        Vec2 q = seg[0] - linePoint;
        
        float64 rxs = dir.x * s.y - dir.y * s.x;
        float64 qxs = q.x * s.y - q.y * s.x;
        
        constexpr float64 eps = 1e-9;
        
        if (std::abs(rxs) < eps) {
            if (std::abs(qxs) >= eps) return false;
            return true;
        }
        
        float64 u = (q.x * dir.y - q.y * dir.x) / rxs;
        return u >= -eps && u <= 1.0 + eps;
    }

    bool lineSegIsIntersectLineSeg(const Vec2 seg1[2], const Vec2 seg2[2]) noexcept {
        constexpr float64 eps = 1e-9;

        Vec2 p1 = seg1[0], p2 = seg1[1];
        Vec2 q1 = seg2[0], q2 = seg2[1];

        Vec2 r = p2 - p1;
        Vec2 s = q2 - q1;
        Vec2 qp = q1 - p1;

        float64 rxs = r.x * s.y - r.y * s.x;
        float64 qpxr = qp.x * r.y - qp.y * r.x;

        if (std::abs(rxs) < eps) {
            if (std::abs(qpxr) >= eps) return false;

            float64 t1 = 0.0, t2 = 1.0;
            float64 u1 = 0.0, u2 = 1.0;

            auto project = [](const Vec2& a, const Vec2& b, const Vec2& dir) -> std::pair<float64, float64> {
                float64 dot_a = a.x * dir.x + a.y * dir.y;
                float64 dot_b = b.x * dir.x + b.y * dir.y;
                return {std::min(dot_a, dot_b), std::max(dot_a, dot_b)};
            };

            Vec2 axis = (std::abs(r.x) > std::abs(r.y)) ? Vec2{1, 0} : Vec2{0, 1};
            auto [proj1_min, proj1_max] = project(p1, p2, axis);
            auto [proj2_min, proj2_max] = project(q1, q2, axis);

            return proj1_max + eps >= proj2_min && proj2_max + eps >= proj1_min;
        }

        float64 u = (qp.x * s.y - qp.y * s.x) / rxs;
        float64 v = (qp.x * r.y - qp.y * r.x) / rxs;

        return u >= -eps && u <= 1.0 + eps && v >= -eps && v <= 1.0 + eps;
    }

    bool quadStrictlyIntersectRect(const Vec2 quad[4], const Rect& r) noexcept {
        const Vec2 ql1[2] = { quad[0], quad[1] };
        const Vec2 ql2[2] = { quad[1], quad[2] };
        const Vec2 ql3[2] = { quad[2], quad[3] };
        const Vec2 ql4[2] = { quad[3], quad[0] };

        const Vec2 rl1[2] = { Vec2 { r.x, r.y }, Vec2 { r.x + r.w, r.y } };
        const Vec2 rl2[2] = { Vec2 { r.x + r.w, r.y }, Vec2 { r.x + r.w, r.y + r.h } };
        const Vec2 rl3[2] = { Vec2 { r.x + r.w, r.y + r.h }, Vec2 { r.x, r.y + r.h } };
        const Vec2 rl4[2] = { Vec2 { r.x, r.y + r.h }, Vec2 { r.x, r.y } };

        return (
            pointStrictlyInRect(quad[0], r) ||
            pointStrictlyInRect(quad[1], r) ||
            pointStrictlyInRect(quad[2], r) ||
            pointStrictlyInRect(quad[3], r) ||

            pointStrictlyInConvexQuad(Vec2 {r.x, r.y}, quad) ||
            pointStrictlyInConvexQuad(Vec2 {r.x + r.w, r.y}, quad) ||
            pointStrictlyInConvexQuad(Vec2 {r.x + r.w, r.y + r.h}, quad) ||
            pointStrictlyInConvexQuad(Vec2 {r.x, r.y + r.h}, quad) ||

            lineSegIsIntersectLineSeg(ql1, rl1) ||
            lineSegIsIntersectLineSeg(ql1, rl2) ||
            lineSegIsIntersectLineSeg(ql1, rl3) ||
            lineSegIsIntersectLineSeg(ql1, rl4) ||

            lineSegIsIntersectLineSeg(ql2, rl1) ||
            lineSegIsIntersectLineSeg(ql2, rl2) ||
            lineSegIsIntersectLineSeg(ql2, rl3) ||
            lineSegIsIntersectLineSeg(ql2, rl4) ||

            lineSegIsIntersectLineSeg(ql3, rl1) ||
            lineSegIsIntersectLineSeg(ql3, rl2) ||
            lineSegIsIntersectLineSeg(ql3, rl3) ||
            lineSegIsIntersectLineSeg(ql3, rl4) ||

            lineSegIsIntersectLineSeg(ql4, rl1) ||
            lineSegIsIntersectLineSeg(ql4, rl2) ||
            lineSegIsIntersectLineSeg(ql4, rl3) ||
            lineSegIsIntersectLineSeg(ql4, rl4)
        );
    }

    bool lineIsIntersectRect(const Vec2& linePoint, float64 lineDeg, const Rect& r) noexcept {
        return (
            lineIsIntersectLineSeg(linePoint, lineDeg, (Vec2[2]) { Vec2 { r.x, r.y }, Vec2 { r.x + r.w, r.y } }) ||
            lineIsIntersectLineSeg(linePoint, lineDeg, (Vec2[2]) { Vec2 { r.x + r.w, r.y }, Vec2 { r.x + r.w, r.y + r.h } }) ||
            lineIsIntersectLineSeg(linePoint, lineDeg, (Vec2[2]) { Vec2 { r.x + r.w, r.y + r.h }, Vec2 { r.x, r.y + r.h } }) ||
            lineIsIntersectLineSeg(linePoint, lineDeg, (Vec2[2]) { Vec2 { r.x, r.y + r.h }, Vec2 { r.x, r.y } })
        );
    }

    bool pointIsLeavingPoint(const Vec2& point, float64 deg, const Vec2& targetPoint) noexcept {
        float64 rad = deg / 180.0 * std::numbers::pi;
        Vec2 dir = {std::cos(rad), std::sin(rad)};
        Vec2 toTarget = targetPoint - point;
        return toTarget.x * dir.x + toTarget.y * dir.y > 0;
    }

    bool lineIsLeavingScreen(const Vec2& linePoint, float64 lineDeg, const Rect& screenArea) noexcept {
        return !lineIsIntersectRect(linePoint, lineDeg, screenArea) && pointIsLeavingPoint(linePoint, lineDeg + 90, screenArea.center());
    }

    Rect getCoveredOrContainRect(const Rect& dst, const Vec2& size, bool isCovered) {
        float64 dst_ratio = dst.w / dst.h;
        float64 src_ratio = size.x / size.y;

        float64 w, h;
        if (isCovered ? (src_ratio < dst_ratio) : (src_ratio > dst_ratio)) {
            w = dst.w;
            h = dst.w / src_ratio;
        } else {
            w = dst.h * src_ratio;
            h = dst.h;
        }

        return Rect::MakeCenter(dst.x + dst.w / 2, dst.y + dst.h / 2, w, h);
    }

    struct RectInfo {
        Vec2 position, size;
        float64 rotation;
        Vec2 anchor = { 0.5, 0.5 };
    };

    std::array<Vec2, 4> makeQuadFromRectInfo(const RectInfo& info) {
        auto r = info.rotation / 180.0 * std::numbers::pi;
        auto s = std::sin(r), c = std::cos(r);
        auto h = info.size / 2.0;
        auto b = info.position - info.size * (info.anchor - 0.5);

        return std::array<Vec2, 4> {
            b + Vec2 { h.x * c - h.y * s, h.x * s + h.y * c },
            b + Vec2 { h.x * c - -h.y * s, h.x * s - h.y * c },
            b + Vec2 { -h.x * c + h.y * s, -h.x * s - h.y * c },
            b + Vec2 { -h.x * c - h.y * s, -h.x * s + h.y * c }
        };
    }
}
