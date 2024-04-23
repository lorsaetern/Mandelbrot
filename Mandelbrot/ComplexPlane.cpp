#include "ComplexPlane.h"
//#include <SFML/Graphics/Text.hpp>
//#include <SFML/Graphics/RenderTarget.hpp>

using namespace sf;
using namespace std;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_aspectRatio = pixelHeight / (double)pixelWidth;
	m_plane_center = { 0,0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	m_pixel_size = { pixelWidth, pixelHeight };
	m_vArray.setPrimitiveType(Points);
	m_vArray.resize(pixelWidth * pixelHeight);
}
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}
void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { x, y };
	m_state = CALCULATING;
}
void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { x, y };
	m_state = CALCULATING;
}
void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_plane_center = mapPixelToCoords(mousePixel);
	m_state = CALCULATING;
}
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = mapPixelToCoords(mousePixel);
}
void ComplexPlane::loadText(Text& text)
{
	double a = m_plane_center.x;
	double b = m_plane_center.y;
	double mouse_x = m_mouseLocation.x;
	double mouse_y = m_mouseLocation.y;

	complex<double> c(a, b);
	complex<double> mouse(mouse_x, mouse_y);

	stringstream text_box;
	text_box << "Mandelbrot Set" <<
		"\nCenter: (" << c.real() << ", " << c.imag() << ")" <<
		"\nCursor: (" << mouse.real() << ", " << mouse.imag() << ")" <<
		"\nLeft-click to zoom in" << "\nRight-click to zoom out" << endl;
	text.setString(text_box.str());
}
void ComplexPlane::updateRender()
{
	int pixelHeight = m_pixel_size.y;
	int pixelWidth = m_pixel_size.x;

	if (m_state == CALCULATING)
	{
		for (int i = 0; i < pixelHeight; i++)
		{
			for (int j = 0; j < pixelWidth; j++)
			{
				m_vArray[i * m_pixel_size.x + j].position = { (float)j, (float)i };
				Vector2f complex_coords = mapPixelToCoords(Vector2i(j, i));
				int iterations = countIteration(complex_coords);
				Uint8 r, g, b;
				//cout << "Iteratoin Count : " << iterations << endl;
				iterationsToRGB(iterations, r, g, b);
				m_vArray[i * m_pixel_size.x + j].color = Color(r, g, b);
			}
		}
	}
	m_state = DISPLAYING;
}

int ComplexPlane::countIteration(Vector2f coord)
{
	complex<double> c(coord.x, coord.y);
	complex<double> z(0, 0);
	for (int i = 0; i < MAX_ITER; i++)
	{
		z = z * z + c;
		if (abs(z) > 2.0)
		{
			return i;
		}
	}
	return MAX_ITER;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count == MAX_ITER)
	{
		r = 225;
		g = 222;
		b = 222;
	}
	else
	{
		if (count >= 0 && count < 17) // Purple / blue for low iteration counts
		{
			r = 0;
			g = 102;
			b = 255;
		}
		else if (count >= 17 && count < 33) // Turquoise
		{
			r = 0;
			g = 221;
			b = 255;
		}
		else if (count >= 33 && count < 49) // Green
		{
			r = 0;
			g = 255;
			b = 128;
		}
		else if (count >= 49 && count < 64) // turq
		{
			r = 0;
			g = 255;
			b = 229;
		}
		else // Red for high iteration counts
		{
			r = 51;
			g = 220;
			b = 220;
		}
	}
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	float nX = mousePixel.x;
	float nY = mousePixel.y;
	float a = 0;
	float bX = m_pixel_size.x;
	float bY = m_pixel_size.y;

	float x = ((nX - a) / (bX - a)) * m_plane_size.x + (m_plane_center.x - m_plane_size.x * 0.5);
	float y = ((nY - a) / (bY - a)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y * 0.5);

	return Vector2f(x, y);
}
