#pragma once
#include "Shapes.h"

const int N = 228;

class ShapeFactory
{
public:
	static shared_ptr<Shape> makeShape(uint8_t n) {
		Shape * shape = nullptr;
		switch (n)
		{
		case 0:
		{
			float x = createRF(N);
			float y = createRF(N);
			shape = new Point(x, y);
			break;
		}
		case 1:
		{
			float x = createRF(N);
			float y = createRF(N);
			float radius = createRF(N);
			Point * p = new Point(x, y);
			shape = new Circle(radius, *p);
			delete(p);
			break;
		}
		case 2:
		{
			float x1 = createRF(N);
			float y1 = createRF(N);
			float x2 = createRF(N);
			float y2 = createRF(N);
			Point * p1 = new Point(x1, y1);
			Point * p2 = new Point(x2, y2);
			shape = new Rect(*p1, *p2);
			delete(p1);
			delete(p2);
			break;
		}
		case 3:
		{
			float x = createRF(N);
			float y = createRF(N);
			float sideLength = createRF(N);
			Point * p = new Point(x, y);
			shape = new Square(*p, sideLength);
			delete(p);
			break;
		}
		case 4:
		{
			Container<Point> * container = new Container<Point>;
			Polyline * tmp = new Polyline(*container);
			uint32_t rand_range = createRUI(13);
			for (uint32_t i = 0; i < rand_range; i++)
			{
				float x = createRF(N);
				float y = createRF(N);
				Point * p = new Point(x, y);
				tmp->addPoint(*p);
				delete p;
			}
			shape = tmp;
			break;
		}
		case 5:
		{
			Container<Point> * container = new Container<Point>;
			Polygon * pl = new Polygon(*container);
			uint32_t rand_range = createRUI(13);
			for (uint32_t i = 0; i < rand_range; i++)
			{
				float x = createRF(N);
				float y = createRF(N);
				Point * p = new Point(x, y);
				pl->addPoint(*p);
				delete p;
			}
			shape = pl;
			break;
		}

		}
		return shared_ptr<Shape>(shape);
	};
	static float createRF(uint32_t max) 
	{
		return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / max));
	};
	static uint32_t createRUI(uint32_t max) 
	{
		return 1 + rand() / (RAND_MAX / max);
	};
};