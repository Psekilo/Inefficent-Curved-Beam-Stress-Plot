#include <iostream>
#include <math.h>
#include <fstream>
#include <cstdlib>

using namespace std;
using std::ofstream;

double log(double base, double x) {
  return std::log(x)/std::log(base);
}
class Circle{ 
  public:
    int f, d;//Force And Distance from Axis
    float rn, rc, e, ci, co, a, m, M, tost, tist, ri, ro, y, S[100], R[100];
    int inval () {
    	cout << "\nENTER Force(N): ";
		cin>>f;
		cout << "\nENTER Offset Perpendicular Distance from Axis(mm): ";
		cin>>d;
    	cout << "\nENTER Ri(mm)[Positive Values only]: ";
        cin>>ri;
        cout << "\nENTER Ro(mm)[Positive Values only]: ";
        cin>>ro;
        rn = pow ((sqrt (ro) + sqrt (ri)), 2) / 4;//Radius of Neutral Axis
        rc = (ri + ro) / 2;
        e = rc - rn;//Eccentricity
        ci = rn - ri;
        co = ro - rn;
        m = (ro-ri) / 2;//Radii of Circular Cross-section
        a = 3.141 * pow (m, 2) / 2;
        M = f*(d + rc); //Moment
        tost = f/a - (M*co / (a*e*ro));// Total Outer Stress
        tist = f/a + (M*ci / (a*e*ri));// Total Inner Stress
        return 0;
    }
    
    int plot () {

		ofstream output;
		output.open("values.csv"); // opens the file
   		if( !output ) { // file couldn't be opened
      		cerr << "Error: file could not be opened" << endl;
      		exit(1);
   		}
    	y = ri;//Variable Radius
    	cout << "\n";
		for (int i=0; i<=100; i++, y += (ro-ri) / 100) {
			if(y<=rn)
				S[i] = f/a + M*(rn - y) / (a*e*y);
			else
				S[i] = f/a - M*(y-rn) / (a*e*y);
			R[i] = y;//Variable Radius
			output << R[i] << ", " << S[i] <<"\n";  // in form x, y
		}

		output.close();
		system("python plotter.py");

        cout << "\nTotal Stress Acting On: " << "\n\tOuter Fiber(MPa): " << tost << "\n\tInner Fiber(MPa): " << tist;
		cout << "\nRadius: " << "\n\tOuter Radius(mm): " << ro << "\n\tInner Radius(mm): " << ri;
		return 0;
    }
};

class Rectangle{ 
  public:
    int f, d;//Force And Distance from Axis
    float rn, rc, e, ci, co, a, m, M, tost, tist, ri, ro, y, S[100], R[100],b;
    int inval () {
    	cout << "\nENTER Force(N): ";
		cin>>f;
		cout << "\nENTER Offset Perpendicular Distance from Axis(mm): ";
		cin>>d;
    	cout << "\nENTER Ri(mm)[Positive Values only]: ";
        cin>>ri;
        cout << "\nENTER Ro(mm)[Positive Values only]: ";
        cin>>ro;
		cout << "\nENTER B(mm)[Positive Values only]: ";
		cin>>b;
        rn = (ro - ri)/log(ro/ri);//Radius of Neutral Axis
        rc = (ri + ro) / 2;
        e = rc - rn;//Eccentricity
        ci = rn - ri;
        co = ro - rn;
        m = (ro-ri) / 2;//Radii of Circular Cross-section
        a = b*(ro-ri);
        M = f*(d + rc); //Moment
        tost = f/a - (M*co / (a*e*ro));// Total Outer Stress
        tist = f/a + (M*ci / (a*e*ri));// Total Inner Stress
        return 0;
    }
    
    int plot () {

		ofstream output;
		output.open("values.csv"); // opens the file
   		if( !output ) { // file couldn't be opened
      		cerr << "Error: file could not be opened" << endl;
      		exit(1);
   		}
    	y = ri;//Variable Radius
    	cout << "\n";
		for (int i=0; i<=100; i++, y += (ro-ri) / 100) {
			if(y<=rn)
				S[i] = f/a + M*(rn - y) / (a*e*y);//For variable radius less than Rn
			else
				S[i] = f/a - M*(y-rn) / (a*e*y);//For variable radius more than Rn
			R[i] = y;//Variable Radius
			output << R[i] << ", " << S[i] <<"\n";  // in form x, y
		}

		output.close();
		system("python plotter.py");

        cout << "\nTotal Stress Acting On: " << "\n\tOuter Fiber(MPa): " << tost << "\n\tInner Fiber(MPa): " << tist;
		cout << "\nRadius: " << "\n\tOuter Radius(mm): " << ro << "\n\tInner Radius(mm): " << ri;
		return 0;
    }
};
int main () {
	int check;
	cout<<"\nEnter 1 for Circular Cross-section or 2 for Rectangular Cross-section: ";
	cin>>check;
	if(check==1) {
		Circle c;
		c.inval ();//Input Ri and Ro values
		c.plot ();
	} else if(check==2) {
		Rectangle rect;
		rect.inval ();//Input Ri and Ro values
		rect.plot ();
	}
	else exit(0);
	
	return 0;
}