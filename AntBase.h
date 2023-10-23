
#ifndef SRC_ANTBASE_H_
#define SRC_ANTBASE_H_
#include "Agent.h"
#include "Vector2.h"
#include "MathUtils.h"
#include "Renderer.h"
#include "Anthill.h"

class AntBase : public Agent{

protected:
	int m_quantity;
	Anthill * m_fourmiliere;
	float m_vitesse;
	int m_dureeVie;
	Vector2<float> m_direction;

public:

	AntBase(Environment * environment, Anthill * fourmiliere, int dureeVie) :
		Agent(environment, fourmiliere->getPosition(), 1)
		{
			m_dureeVie = dureeVie;
			m_fourmiliere = fourmiliere;
			m_vitesse = 1;
			m_quantity = 0;
			m_direction = Vector2<float>(0,0);
		};
	~AntBase(){}


	void rotate(float rad){
		m_direction = m_direction.rotate(rad);
		m_direction = m_direction.normalized();
	}

	void turn(){
		m_direction = -m_direction;
	}

	void lookAt(Vector2<float>& pos){
		float xPos = pos[0];
		float yPos = pos[1];
		float x = getPosition()[0];
		float y = getPosition()[1];

		m_direction = Vector2<float>(xPos-x, yPos-y);
		m_direction = m_direction.normalized();
	}

	void depose(){
		m_fourmiliere->depositFood(m_quantity);
		m_quantity = 0;
	}

	void getFood(Food * food){
		m_quantity += food->collectFood(10-m_quantity);
	}

	void move(){
		translate(m_direction*m_vitesse*Timer::dt());
	}

	std::vector<Food*> see(){
		std::vector<Food*> seenFood = perceive<Food>(m_direction, MathUtils::pi/2, 25.0f);
		return seenFood;
	}

	void checkLife(){
		if(m_dureeVie == 0){
			setStatus(destroy);
		}
	}

	void render(){
		if(m_quantity == 0){
						Renderer::getInstance()->drawCircle(this->getPosition(), this->getRadius(), Renderer::Color(255,255,255,255));
		}
		else{
			Renderer::getInstance()->drawCircle(this->getPosition(), this->getRadius(), Renderer::Color(128,255,128,255));
		}
	}

	virtual void update()=0;


};

#endif
