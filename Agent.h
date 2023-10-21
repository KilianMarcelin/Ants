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

		for(std::set<Agent*>::iterator i = m_agents.begin(); i != m_agents.end(); ++i){
			if((*i)->getStatus()==running){
				(*i)->update();
			}
			else{
				m_agents.erase(*i);
				delete(*i);
			}
		}
	    // std::cout << "Agent count: " << s_agents.size() << std::endl;
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
