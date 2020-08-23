#ifndef DRUID_COORDINATES_H
#define DRUID_COORDINATES_H

#include <utility>

namespace Druid
{
    enum class OriginLocation
    {
        lowerLeft
    };

    std::pair<float, float> pixelCoordsToNDC(float a_x, float a_y, const unsigned int a_windowHeight, const unsigned int a_windowWidth);

    bool coordsInRect(const int a_rectPosX, const int a_rectPosY, const int a_rectHeight, const int a_rectWidth, const int a_coordX, const int a_coordY, const OriginLocation a_origin = OriginLocation::lowerLeft);
}

#endif
