/*
 * Pheromone.h
 *
 *  Created on: 25 mai 2023
 *      Author: arnicolas
 */

#ifndef SRC_PHEROMONE_H_
#define SRC_PHEROMONE_H_

class Pheromone : public Agent{
	double m_quantity;

public:
	Pheromone(double quantity, Environment * environment, const Vector2<float>& position) :	Agent(environment, position, 1), m_quantity(quantity){

	}

public:
	double getQuantity(){
		return m_quantity;
	}
	void addQuantity(float q){
        if(m_quantity < 255) m_quantity+=q;
	}
	void update(){
		m_quantity-=0.01*m_quantity*Timer::dt();
        if(m_quantity <= 5){
            setStatus(destroy);
        }
		Renderer::getInstance()->drawCircle(this->getPosition(), this->getRadius(), Renderer::Color(0,128,128,m_quantity));

	}
};

#endif /* SRC_PHEROMONE_H_ */
