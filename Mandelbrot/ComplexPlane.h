#pragma once

#ifndef COMPLEXPLANE_H_INCLUDED
#define COMPLEXPLANE_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <vector>
#include <complex>
#include <cmath>
#include <thread>
#include <chrono>
#include <cmath>

using namespace sf;
using namespace std;

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;
enum State { CALCULATING, DISPLAYING };

class ComplexPlane : public Drawable
{
public:
    //ComplexPlane();
    ComplexPlane(int pixelWidth, int pixelHeight);
    void draw(RenderTarget& target, RenderStates states) const override;
    void zoomIn();
    void zoomOut();
    void setCenter(Vector2i mousePixel);
    void setMouseLocation(Vector2i mousePixel);
    void loadText(Text& text);
    //void updateRender();      
    void updateRender1();       //use this for multithreading, "void updateRender();" function must be disabled
    void updateRender2();       //use this for multithreading, "void updateRender();" function must be disabled
    void updateRender3();       //use this for multithreading, "void updateRender();" function must be disabled
    void updateRender4();       //use this for multithreading, "void updateRender();" function must be disabled
    void multiThread();         //use this for multithreading, "void updateRender();" function must be disabled
private:
    int countIteration(Vector2f coord);
    void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
    Vector2f mapPixelToCoords(Vector2i mousePixel);

    VertexArray m_vArray;
    State m_state;
    Vector2f m_mouseLocation, m_plane_center, m_plane_size;
    Vector2i m_pixel_size;
    int m_zoomCount;
    float m_aspectRatio;
};

#endif // CP_H_INCLUDE