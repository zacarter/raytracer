#ifndef COLOR_H
#define COLOR_H
#include <iostream>

class Color {
	public:
		Color();
		Color(float r, float g, float b);
		~Color();
		float getR();
		float getG();
		float getB();
		void setColor(float r, float g, float b);
		void operator=(const Color& rhs);
		Color operator+(const Color& rhs);
		Color operator*(const Color& rhs);
		Color operator*(const float& rhs);
	private:
		float _r; // XXX convert to floats
		float _g;
		float _b;
};

#endif
