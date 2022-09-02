
#include<iostream>
#include<iomanip>
#include<cmath>
#include<limits>
#include<functional>
#include<utility>

#include "Curves.h"

Point BaseCurve::computePoint(double t) const
{
	return Point(xFunction(t), yFunction(t), zFunction(t));
}

Vector BaseCurve::computeDerative(double t) const
{
	return Vector(xFunctionDerative(t), yFunctionDerative(t), zFunctionDerative(t));
}

std::pair<Point, Vector> BaseCurve::operator()(const double t) const
{
	return std::make_pair(computePoint(t), computeDerative(t));
}

Point BaseCurve::center() const
{
	return center_;
}

double Circle::r() const
{
	return r_;
}

double Circle::xFunction(const double t) const
{
	return center_.x() + r_ * sin(t);
}

double Circle::yFunction(const double t) const
{
	return center_.y() + r_ * cos(t);
}

double Circle::zFunction(const double) const
{
	return 0.0;
}

double Circle::xFunctionDerative(const double t) const
{
	return  r_ * cos(t);
}

double Circle::yFunctionDerative(const double t) const
{
	return  -r_ * sin(t);
}

double Circle::zFunctionDerative(const double) const
{
	return 0.0;
}

double Ellipse::a() const
{
	return a_;
}

double Ellipse::b() const
{
	return b_;
}

double Ellipse::xFunction(const double t) const
{
	return center_.x() + a_ * sin(t);
}

double Ellipse::yFunction(const double t) const
{
	return center_.y() + b_ * cos(t);
}

double Ellipse::zFunction(const double) const
{
	return 0.0;
}

double Ellipse::xFunctionDerative(const double t) const
{
	return  a_ * cos(t);
}

double Ellipse::yFunctionDerative(const double t) const
{
	return  -b_ * sin(t);
}

double Ellipse::zFunctionDerative(const double t) const
{
	return 0.0;
}

inline double Helixe::step() const
{
	return step_;
}

double Helixe::zFunction(const double t) const
{
	return center_.z() + param_ * t;
}

double Helixe::zFunctionDerative(const double t) const
{
	return param_;
}

std::ostream& operator<<(std::ostream& out, const Point& p)
{
	out << std::fixed << std::setprecision(2);
	out << "( " << p.x() << "; " << p.y() << "; " << p.z() << ")";
	return out;
}

std::ostream& operator<<(std::ostream& out, const Vector& v)
{
	out << std::fixed << std::setprecision(2);
	out << "{ " << v.x() << "; " << v.y() << "; " << v.z() << "}";
	return out;
}

double Point::x() const
{
	return x_;
}

double Point::y() const
{
	return y_;
}

double Point::z() const
{
	return z_;
}

inline double Vector::x() const
{
	return point.x();
}

inline double Vector::y() const
{
	return point.y();
}

inline double Vector::z() const
{
	return point.z();
}
