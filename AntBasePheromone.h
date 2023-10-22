/*
 * AntBasePheromone.h
 *
 *  Created on: 25 mai 2023
 *      Author: arnicolas
 */

#ifndef SRC_ANTBASEPHEROMONE_H_
#define SRC_ANTBASEPHEROMONE_H_
#include "AntBase.h"
#include "Pheromone.h"

class AntBasePheromone  : public AntBase{

private:
	bool m_retour;
    int timeBeforeControl = 20;
public:

	AntBasePheromone(Environment * environment, Anthill * fourmiliere, int dureeVie) :
		AntBase(environment, fourmiliere, dureeVie)
		{
			//Revoir plus tard avec Vector2::random;
			m_direction = Vector2<float>(MathUtils::random(-1.0f, 1.0f), MathUtils::random(-1.0f, 1.0f)).normalized();
			m_retour = false;
		};
	~AntBasePheromone(){}

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

			Pheromone * pher = choosePheromone();
			 if(pher != NULL){
				 Vector2<float> posPher = pher->getPosition();
				 lookAt(posPher);
			 }else{
				 rotate(MathUtils::random(-(MathUtils::pi/10)*Timer::dt(),(MathUtils::pi/10)*Timer::dt()));
			 }


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
		putPheromone(10);
		move();
		render();

	}

	Pheromone * choosePheromone(){
		std::vector<Pheromone*> seenPher = perceive<Pheromone>(m_direction, MathUtils::pi/2, 2.0f);
		if(seenPher.size()>0){
			std::vector<float> weights;
			for (int i = 0; i < seenPher.size(); ++ i) {
				weights.push_back(seenPher[i]->getQuantity());
			}

			int i = MathUtils::randomChoose(weights);
			return seenPher[i];
		}
		else{
			return nullptr;
		}
	}

	void putPheromone(float q){
		std::vector<Pheromone*> onPheromone = perceive<Pheromone>();
		if(onPheromone.size() > 0){
			onPheromone[0]->addQuantity(q);
		}else{
			new Pheromone(q,getEnvironment(), getPosition());
		}

	}
};

#endif /* SRC_ANTBASEPHEROMONE_H_ */
