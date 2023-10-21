/*
 * Food.h
 *
 *  Created on: 2 mai 2023
 *      Author: arnicolas
 */

#ifndef SRC_FOOD_H_
#define SRC_FOOD_H_
#include "Agent.h"
#include "Vector2.h"
#include "MathUtils.h"
#include "Renderer.h"

class Food : public Agent{

private:
	int m_quantity;
public:

	Food(Environment * environment, const Vector2<float>& position, int quantity) :
		Agent(environment, position, MathUtils::circleRadius(quantity))
		{
			m_quantity = quantity;
		};
	~Food(){}
	float getFoodQuantity() const{
		return m_quantity;
	}
	float collectFood(float	quantity){
		if(m_quantity>quantity){
			m_quantity -= quantity;
			return quantity;
		}
		else{
			m_quantity = 0;
			return m_quantity;
		}
	}

	void update() {
		this->setRadius(MathUtils::circleRadius(m_quantity));
		Renderer::getInstance()->drawCircle(this->getPosition(), this->getRadius(), Renderer::Color(154,235,38,255));
		if(m_quantity == 0){
			setStatus(destroy);
		}
	}


};

#endif /* SRC_FOOD_H_ */
