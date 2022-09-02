
#include<iostream>
#include<vector>
#include<algorithm>
#include<memory>
#include<omp.h>

#include"Curves.h"

int main()
{	
	std::vector<std::shared_ptr<BaseCurve>> curves;
	double t = Pi / 4;
	for (int i = 0; i < 20; ++i)
	{
		switch (rand() % 3)
		{
		case 0:
			curves.push_back(std::make_shared<Circle>(double(0.1 + rand() % 10000) / 1000));
			break;

		case 1:
			curves.push_back(std::make_shared<Ellipse>(double(0.1 + rand() % 10000) / 1000, double(0.1 + rand() % 10000) / 1000));
			break;

		case 2:
			curves.push_back(std::make_shared<Helixe>(double(0.1 + rand() % 10000) / 1000));
			break;

		default:
			break;
		}		
		std::cout << typeid(*curves.back()).name() << ":\t" << curves.back()->computePoint(t) << "\t\t" << curves.back()->computeDerative(t) << std::endl;
	}

	std::cout << "##########Circles#########" << std::endl;
	
	std::vector<std::shared_ptr<Circle>> circles;
	auto circleName = typeid(Circle).name();

	for (const auto el : curves)
	{
		
		if (typeid(*el).name() == circleName)
		{		
			circles.push_back(std::static_pointer_cast<Circle>(el));
			std::cout << circles.back()->computePoint(t) << "\t\t" << circles.back()->computeDerative(t) << "\tr = "<< circles.back()->r()<< std::endl;
		}		
	}

	std::cout << "##########Sorting#########" << std::endl;
	std::sort(circles.begin(), circles.end(), [](std::shared_ptr<Circle> first, std::shared_ptr<Circle> second)
		{
			return first->r() < second->r();
		});
	for (auto el : circles)
	{
		std::cout << el->r() << "\t\t"  << std::endl;

	}

	std::cout << "##########Summ#########" << std::endl;
	double summR{ 0 };
	omp_set_num_threads(4);
#pragma omp parallel for 
	for (int i = 0; i < circles.size(); ++i)
	{
#pragma omp atomic
		summR += circles[i]->r();
	}	
	std::cout  << "Radii summ = " << summR << std::endl;

	return 0;
}
