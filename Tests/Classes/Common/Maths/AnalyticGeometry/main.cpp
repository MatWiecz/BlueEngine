#include <iostream>
#include "../../../../../Common/Maths/AnalyticGeometry/AnalyticGeometryHeaders.h"

using namespace std;
using namespace MatWiecz::BlueEngine;

int main()
{
    Point a(2, 0, 2);
    Point b(0, 2, 0);
    Vector ab(a, b);
    cout << string(a) << endl;
    cout << string(b) << endl;
    cout << string(ab) << endl;
    ab.RotVector(Vector(0,0,1), 180);
    cout << string(ab) << endl;
    ab.Normalize();
    cout << string(ab) << endl;
    return 0;
}