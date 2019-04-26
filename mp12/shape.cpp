#include "shape.hpp"

//group: hdeal2, stancs2, ma54

//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable 

string name_;
Shape::Shape(string name){
	name_ = name;
}
string Shape::getName(){ return name_; }
//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Rectangle::Rectangle(double width, double length) : Shape("Rectangle") {
	width_ = width;
	length_ = length;
	//printf("%lf %lf\n", width, length);
}
double Rectangle::getArea()const{ return length_*width_; }
double Rectangle::getVolume()const{ return 0; }

Rectangle Rectangle::operator + (const Rectangle& rec){
	Rectangle rec1;
	rec1.length_ = this->length_ + rec.getLength();
	rec1.width_ = this->width_ + rec.getWidth();
	return rec1;
}
Rectangle Rectangle::operator - (const Rectangle& rec){
	Rectangle rec1;	
	double length = this->length_ - rec.getLength();
	double width = this->width_ - rec.getWidth();
	if(length>0)
		rec1.length_ = length;
	else
		rec1.length_ = 0;
	if(width>0)
		rec1.width_ = width;
	else
		rec1.width_ = 0;
	return rec1;
}

double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Circle::Circle(double radius) : Shape("Circle") {
	radius_ = radius;
}
double Circle::getArea()const{ 
	const double pi = 3.14159265358979346846;
	return radius_ * radius_ * pi;
}
double Circle::getVolume()const{ return 0; } 

Circle Circle::operator + (const Circle& cir){
	double r = this->radius_ + cir.getRadius();
	Circle cir1(r);
	return cir1;
}
Circle Circle::operator - (const Circle& cir){
	double r = this->radius_ - cir.getRadius();
	if(r>0){
		Circle cir1(r);
		return cir1;
	}
	else{
		Circle cir1(0);
		return cir1;
	}
}

double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

Sphere::Sphere(double radius) : Shape("Sphere") {
	radius_ = radius;
}
double Sphere::getArea()const{ 
	const double pi = 3.1415926535897;
	return radius_ * radius_ * pi * 4;
}
double Sphere::getVolume()const{ return this->getArea() * this->getRadius() * (1.0/3.0) ; } 

Sphere Sphere::operator + (const Sphere& sph){
	Sphere sph1(0);
	sph1.radius_ = this->radius_ + sph.getRadius();
	return sph1;
}
Sphere Sphere::operator - (const Sphere& sph){
	Sphere sph1(0);	
	double radius = this->radius_ - sph.getRadius();
	if(radius>0)
		sph1.radius_ = radius;
	else
		sph1.radius_ = 0;
	return sph1;
}

double Sphere::getRadius()const{return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

RectPrism::RectPrism(double width, double length, double height) : Shape("RectPrism") {
	width_ = width;
	length_ = length;
	height_ = height;
}
double RectPrism::getArea()const{ return 2 * (width_*length_ + length_*height_ + width_*height_); }
double RectPrism::getVolume()const{ return length_ * width_ * height_; }

RectPrism RectPrism::operator + (const RectPrism& rectp){
	RectPrism rectp1(0,0,0);
	rectp1.length_ = this->length_ + rectp.getLength();
	rectp1.width_ = this->width_ + rectp.getWidth();
	rectp1.height_ = this->height_ + rectp.getHeight();
	return rectp1;
}
RectPrism RectPrism::operator - (const RectPrism& rectp){
	RectPrism rectp1(0,0,0);	
	double length = this->length_ - rectp.getLength();
	double width = this->width_ - rectp.getWidth();
	double height = this->height_ - rectp.getHeight();
	if(length>0)
		rectp1.length_ = length;
	if(width>0)
		rectp1.width_ = width;
	if(height>0)
		rectp1.height_ = height;
	return rectp1;
}

double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}


 
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here
	string name;
	int num;
	double radius;
	double length;
	double width;
	double height;
	Shape* ptr;
	
	vector<Shape*> shapes;
	

	ifstream ifs (file_name, std::ifstream::in);
	ifs >> num;

	while(num > 0)
	{
		ifs >> name;
	
		if(name == "Rectangle")
		{
			ifs >> width >> height;
			ptr = new Rectangle(width, height);
			//printf("%lf %lf\n", width, height);
		}
		else if(name == "Circle")
		{
			ifs >> radius;
			ptr = new Circle(radius);
			//printf("%lf\n", radius);
		}
		else if(name == "Sphere")
		{
			ifs >> radius;
			ptr = new Sphere(radius);
			//printf("%lf\n", radius);
		}
		else if(name == "RectPrism")
		{
			ifs >> width >> length >> height;
			ptr = new RectPrism(width, length, height);
			//printf("%lf %lf %lf\n", width, length, height);
		}

		shapes.push_back(ptr);
		num--;
	}
	
	ifs.close();	
	
	return shapes; // please remeber to modify this line to return the correct value
}

// call getArea() of each object 
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here	
	for(int i = 0; i < shapes.size(); i++)
	{
		if(shapes[i]->getArea() > max_area)
			max_area = shapes[i]->getArea();
	}
	return max_area;
}


// call getVolume() of each object 
// return the max volume
double MaxVolume(vector<Shape*> shapes){

	double max_volume = 0;	
	for(int i = 0; i < shapes.size(); i++)
	{
		if(shapes[i]->getVolume() > max_volume)
			max_volume = shapes[i]->getVolume();
	}
	return max_volume;
}

