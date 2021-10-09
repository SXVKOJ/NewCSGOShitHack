#pragma once

struct Vec3
{
    float x, y, z;

    Vec3& operator+(Vec3 arg)
    {
        x += arg.x;
        y += arg.y;
        z += arg.z;

        return *this;
    }

    Vec3& operator*(float arg)
    {
        x *= arg;
        y *= arg;
        z *= arg;

        return *this;
    }
};