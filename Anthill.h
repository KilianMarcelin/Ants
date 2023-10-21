/*
 * Anthill.h
 *
 *  Created on: 2 mai 2023
 *      Author: arnicolas
 */

#ifndef SRC_ANTHILL_H_
#define SRC_ANTHILL_H_
#include "Agent.h"
#include "Renderer.h"

class Anthill : public Agent{
private:
	int quantitHill;
public:
	Anthill(Environment * environment, const Vector2<float> & position):Agent(environment, position, 10),quantitHill(0){};
	~Anthill(){}
	void update() {
		Renderer::getInstance()->drawCircle(this->getPosition(), this->getRadius(), Renderer::Color(0,0,255,255));
	}
	void depositFood(float quantity){
		quantitHill+=quantity;
	}
};

#endif /* SRC_ANTHILL_H_ */
