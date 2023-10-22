#include "Environment.h"
#include "Vector2.h"
#include <iostream>

/*
 * Agent.h
 *
 *  Created on: 2 mai 2023
 *      Author: arnicolas
 */

#ifndef SRC_AGENT_H_
#define SRC_AGENT_H_

class Agent : public Environment::LocalizedEntity{

public:
	typedef enum { running, destroy } Status;
private:
	static std::set<Agent*> m_agents;
	Status m_status;

public:

	Agent(Environment * environment, const Vector2<float>& position, float rayon):
		Environment::LocalizedEntity(environment, position, rayon){
		m_status = running;
		m_agents.insert(this);
		std::set<Agent*>::iterator i = m_agents.begin();
	}
	virtual void update()=0;

	void setStatus(Status status){
		m_status = status;
	}

	Status getStatus(){
		return m_status;
	}

	static void simulate(){
        if (!m_agents.empty()) {
            for (auto i = m_agents.begin(); i != m_agents.end();) {
                if ((*i)->getStatus() == running) {
                    (*i)->update();
                    ++i;  // Avancez l'itérateur s'il n'y a pas d'effacement
                } else {
                    delete (*i);
                    i = m_agents.erase(i);  // Supprime l'élément et met à jour l'itérateur
                }
            }
        }

        std::cout<<m_agents.size()<<std::endl;
    }
	static void finalize(){
		std::set<Agent*>::iterator i;
		for(i = m_agents.begin(); i!=m_agents.end();i++){
			m_agents.erase(*i);
			delete(*i);
			i--;
		}
	}
};

#endif /* SRC_AGENT_H_ */
