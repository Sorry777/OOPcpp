#include <iostream>
#include "Container.h"
#include "Shapes.h"
#include "ShapeFactory.h"
#include <time.h>
using namespace std;

int main()
{
	srand((uint32_t)time(NULL));
	int d;
	cin >> d;

	Container<shared_ptr<Shape>> shapes;
	for (uint8_t i = 0; i < d; i++)
	{
		try
		{
			shared_ptr<Shape> s = ShapeFactory::makeShape(i % 6);
			shapes.push(s);
		}
		catch (std::exception e)
		{
			cout << e.what();
		}
	}

	shapes.print(cout);
	cout << Shape::getCount() << endl;
	shapes.clear();
	cout << Shape::getCount() << endl;
	system("pause");

}