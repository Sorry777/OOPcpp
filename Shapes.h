#pragma once
#include "Base.h"
#include "Container.h"
#include <string>
#include <iostream>

#define pi 3.14159265358979323846

using namespace std;

class Shape : public Printable
{
public:
	Shape() { ++sm_NOShapes; }
	Shape( Shape const & shape ) 
	{ 
		if (&shape != nullptr) {++sm_NOShapes;}
	}
	virtual ~Shape() { --sm_NOShapes; }
	virtual void print( ostream & out ) const = 0;
	friend ostream & operator << ( ostream & ioStream, Shape const & p )
	{
		p.print( ioStream );
		return ioStream;
	}
	static int getCount() { return sm_NOShapes; }
private:
	static int sm_NOShapes;
};

class Point : public Shape, Named
{
public:
	Point( float x, float y ) : Named("Point"), sm_x(x), sm_y(y) {};
	float x() const { return sm_x; };
	float y() const { return sm_y; };
	void print( ostream & out ) const 
	{
		out << m_name << ":" << " (" << sm_x << ", " << sm_y << ")" << endl;
	};
	float sm_x, sm_y;
};

class Circle : public Shape, Named
{
public:
	Circle( float radius, Point p ) : Named("Circle"), sm_center(p), Sradius(radius)
	{
		sm_area = (float)pi * Sradius * Sradius;
	};
	~Circle() { ; };
	void print( ostream & out ) const 
	{
		out << m_name << ":" << endl;
		sm_center.print(out);
		out << "Radius: " << Sradius << endl;
		out << "Area: " << sm_area << endl;
	};
private:
	float Sradius, sm_area;
	Point sm_center;
};

class Rect : public Shape, Named
{
public:
	Rect( Point x1, Point x2 ) : Named("Rect"), sm_x1(x1), sm_x2(x2)
	{
		sm_area = abs((sm_x1.sm_x - sm_x2.sm_x) * (sm_x2.sm_y - sm_x1.sm_y));
	};
	~Rect() { ; };
	void print( ostream & out ) const
	{
		out << m_name << ":" << endl;
		sm_x1.print(out);
		sm_x2.print(out);
		out << "Area: " << sm_area << endl;
	};
private:
	Point sm_x1, sm_x2;
	float sm_area;
};

class Square : public Shape, Named
{
public:
	Square( Point center, float side ) : Named("Square"), sm_center(center), sm_side(side)
	{
		sm_area = side * side;
	};
	~Square() { ; };
	void print( ostream & out ) const
	{
		out << m_name << ":" << endl;
		sm_center.print(out);
		out << "Area: " << sm_area << endl;
	};
private:
	Point sm_center;
	float sm_side, sm_area;
};

class Polyline : public Shape, Named
{
public:
	Polyline( Container<Point> points ) : Slength(0), Spoints(points), Named("Polyline")
	{
		if (Spoints.size() == 0) return;
		calcLength();
	};
	~Polyline() {Spoints.clear();};
	void addPoint( Point & p ) 
	{
		Spoints.push(p);
		uint32_t s = Spoints.size();
		if (s <= 1) return;
		Point p1 = (Spoints)[Spoints.size() - 1];
		Point p2 = (Spoints)[Spoints.size() - 2];

		Slength += sqrt(pow(p1.y() - p2.y(), 2)
			+ pow(p1.x() - p2.x(), 2));
	};
	void calcLength()
	{
		uint32_t size = Spoints.size() - 1;
		for (uint32_t i = 0; i < size; i++)
		{
			Point p1 = (Spoints)[i];
			Point p2 = (Spoints)[i + 1];

			Slength += sqrt(pow(p1.y() - p2.y(), 2)
				+ pow(p1.x() - p2.x(), 2));
		}
	};
	Point & getStartPoint() const { return (Spoints)[0]; };
	float getLength() const { return Slength; };
	void print( ostream & out ) const 
	{
		out << m_name << ":" << endl;
		for (uint32_t i = 0; i < Spoints.size(); i++)
		{
			(Spoints)[i].print(out);
		}
		out << "Length: " << getLength() << endl;
	};
private:
	Container<Point> Spoints;
	float Slength;
};

class Polygon : public Shape, Named
{
public:
	Polygon( Polyline & shape ) : Sshape(&shape), Named("Polygon")
	{
		Point * startPoint = new Point(shape.getStartPoint().x(), shape.getStartPoint().y());
		shape.addPoint(*startPoint);
		delete startPoint;
	};
	~Polygon() { delete Sshape; };
	void print( ostream & out ) const
	{
		out << m_name << ":" << endl;
		Sshape->print(out);
	};
private:
	Polyline * Sshape;
};

int Shape::sm_NOShapes = 0;