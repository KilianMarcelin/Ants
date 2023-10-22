
#ifndef SRC_SILLYANT_H_
#define SRC_SILLYANT_H_
#include "Agent.h"
#include "Vector2.h"
#include "MathUtils.h"
#include "Renderer.h"
#include "AntBase.h"

class SillyAnt : public AntBase{

private:
	bool m_retour;
    int timeBeforeControl = 20;
public:

	SillyAnt(Environment * environment, Anthill * fourmiliere, int dureeVie) :
		AntBase(environment, fourmiliere, dureeVie)
		{
			//Revoir plus tard avec Vector2::random;
			m_direction = Vector2<float>(MathUtils::random(-1.0f, 1.0f), MathUtils::random(-1.0f, 1.0f)).normalized();
			m_retour = false;
		};
	~SillyAnt(){}

	void foodControl(){
		std::vector<Food*> seenFood = see();
		if(seenFood.size() > 0){
			Vector2<float> posFood = seenFood[0]->getPosition();
			lookAt(posFood);
			m_retour = false;

			float dist = this->getPosition().distance(posFood);
			if(dist < seenFood[0]->getRadius()){
				getFood(seenFood[0]);
                m_retour = true;
			}
		}
	}

	void update() {

        if(timeBeforeControl > 0) timeBeforeControl--;
        else {
            foodControl();
            timeBeforeControl = 20;
        }

		checkLife();
		if(!m_retour){
			rotate(MathUtils::random(-(MathUtils::pi/10)*Timer::dt(),(MathUtils::pi/10)*Timer::dt()));
		}
		else{
			Vector2<float> posFourm = m_fourmiliere->getPosition();
			lookAt(posFourm);
			float dist = this->getPosition().distance(posFourm);
				if(dist < m_fourmiliere->getRadius()){
					depose();
					turn();
					m_retour = false;
				}
		}
		move();
		render();

	}


};

#endif
