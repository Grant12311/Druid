#include "../include/coordinates.h"

namespace Druid
{
    std::pair<float, float> pixelCoordsToNDC(float a_x, float a_y, const unsigned int a_windowHeight, const unsigned int a_windowWidth)
    {
        a_x = 2.0f * (a_x + 0.5f) / a_windowWidth - 1.0f;
        a_y = (2.0f * (a_y + 0.5f) / a_windowHeight - 1.0f) * -1.0f;

        return {a_x, a_y};
    }

    bool coordsInRect(const int a_rectPosX, const int a_rectPosY, const int a_rectHeight, const int a_rectWidth, const int a_coordX, const int a_coordY, const OriginLocation a_origin)
    {
        if (a_origin == OriginLocation::lowerLeft)
        {
            if (a_coordX >= a_rectPosX && a_coordX <= a_rectPosX + a_rectWidth && a_coordY >= a_rectPosY && a_coordY <= a_rectPosY + a_rectHeight)
                return true;
            else
                return false;
        }
    }
}
