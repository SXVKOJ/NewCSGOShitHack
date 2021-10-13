#pragma once

static struct Vec3
{
    float x, y, z;

    Vec3& operator+(Vec3 arg)
    {
        x += arg.x;
        y += arg.y;
        z += arg.z;

        return *this;
    }

    Vec3& operator-(Vec3 arg)
    {
        x -= arg.x;
        y -= arg.y;
        z -= arg.z;

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

static struct Vec4
{
    float x, y, z, w;

    Vec4& operator+(Vec4 arg)
    {
        x += arg.x;
        y += arg.y;
        z += arg.z;
        w += arg.w;

        return *this;
    }

    Vec4& operator*(float arg)
    {
        x *= arg;
        y *= arg;
        z *= arg;
        w *= arg;

        return *this;
    }
};