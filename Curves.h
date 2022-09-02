
#ifndef CURVES_H
#define CURVES_H
static const double Pi = 3.14159265358979323846;

class Point 
{	
public:
	Point(double x = 0.0, double y = 0.0, double z = 0.0) : x_(x), y_(y),z_(z) {}

	double x() const;
	double y() const;
	double z() const;

private:
	double x_;
	double y_;
	double z_;
}; 

class Vector
{
public:
	Vector(const double x = 0.0, const double y = 0.0, const double z = 0.0):
		point(x, y, z)
	{}
	double x() const;
	double y() const;
	double z() const;
private:
	Point point;
};


class BaseCurve
{
public:
	BaseCurve(const Point& center = Point())
	{}

	BaseCurve(const double x = 0.0, const double y = 0.0, const double z = 0.0) :
		BaseCurve(Point(x, y, z))
	{}

	virtual ~BaseCurve() = default;

	Point computePoint(double t) const;	

	Vector computeDerative(double t) const;	

	virtual std::pair<Point, Vector> operator() (const double t) const;

	Point center() const;
protected:
	//We could have use some std::function objects and set them some lambda in inherited classes.
	//but it should be tested on lage volume of data
	//std::function<double(const double)> xFunction	 = [](const double t) {return .0; };
	//std::function<double(const double)> yFunction	 = [](const double t) {return .0; };
	//std::function<double(const double)> zFunction	 = [](const double t) {return .0; };

	//std::function<double(const double)> xFunctionDerative = [](const double t) {return .0; };
	//std::function<double(const double)> yFunctionDerative = [](const double t) {return .0; };
	//std::function<double(const double)> zFunctionDerative = [](const double t) {return .0; };

	virtual inline double xFunction(double t) const = 0;
	virtual inline double yFunction(double t) const = 0;
	virtual inline double zFunction(double t) const = 0;

	virtual inline double xFunctionDerative(double t) const = 0;
	virtual inline double yFunctionDerative(double t) const = 0;
	virtual inline double zFunctionDerative(double t) const = 0;

	//We declare the center_ varialbe in the base class, but this approache is correct only in this case.
	//If we had some curves that does not have a center, 
	//we can introduce some BaseCurveWithCenterClass : public BaseCurve class and inherit from it
	Point center_;	
};


class Circle : public BaseCurve
{
public:
	Circle(const double r = 0.0, const Point& center = Point()) :
		BaseCurve(center),
		r_(r) 
	{}
	

	Circle(const double r, const double x, const double y, const double z) :
		Circle (r, Point(x, y, z))
	{}

	double r() const;

protected:
	virtual double xFunction(const double t) const override;

	virtual double yFunction(const double t) const override;

	virtual double zFunction(const double) const override;

	virtual double xFunctionDerative(const double t) const override;

	virtual double yFunctionDerative(const double t) const override;

	virtual double zFunctionDerative(const double) const override;

private:
	double r_;
};


class Ellipse : public BaseCurve
{
public:
	Ellipse(const double a = 0.0, const double b = 0.0, const Point& center = Point()):
		BaseCurve(center),
		a_(a),
		b_(b)
	{}
	Ellipse(const double a, const double b, const double x, const double y, const double z) :
		Ellipse( a, b , Point(x, y, z))
	{}
	double a() const;
	double b() const;
protected:
	virtual double xFunction(const double t) const override;

	virtual double yFunction(const double t) const override;

	virtual double zFunction(const double) const override;

	virtual double xFunctionDerative(const double t) const override;

	virtual double yFunctionDerative(const double t) const override;

	virtual double zFunctionDerative(const double t) const override;
private:
	double a_;
	double b_;
};

//We inherite Helixe class from the Circle class,
//but we could also encapsulate or take as a parameter some kind of rotation curve.
//In this aproache we can't use dynamic_cast to identify the Circle object, because 
//the Helixe object will also successfully casts to Circle,
//but in this case we reduce the code
class Helixe : public Circle
{
public:
	Helixe(const double r = 0.0, const double step = 1.0, bool direction = true, const Point& center = Point()):
		Circle(r, center),
		step_(direction ? step : -step),
		param_(step_/ (2* Pi))
	{}

	Helixe( const double r, const double step, bool direction, const double x, const double y, const double z):
		Helixe(r,step, direction, Point(x,y,z))
	{}
	double step() const;
protected:

	virtual double zFunction(const double t) const override;

	virtual double zFunctionDerative(const double t) const override;
private:
	double step_;
	double param_;
};

std::ostream& operator<<(std::ostream& out, const Vector& v);
std::ostream& operator<<(std::ostream& out, const Point& p);

#endif // !CURVES_H
