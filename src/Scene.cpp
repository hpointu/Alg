#include "Scene.hpp"
#include "const.hpp"
#include <cstdlib>
#include "ContactListener.hpp"
#include <iostream>
#include "EntityManager.hpp"
#include <sstream>
#include "App.hpp"
#include "Launcher.hpp"

Scene::Scene(int w, int h, int x, int y) :
	width(w),
	height(h),
	posX(x),
	posY(y)
{
	alg = 0;
	physics = new b2World(b2Vec2(0, 0));
	physics->SetContactListener(new ContactListener());
	running = true;

	view = new sf::View(sf::Vector2f(0, 0), sf::Vector2f(width/2,
																		  height/2));

	view->zoom(2.f/SCALE);

	sf::FloatRect vp( (float)x/W_WIDTH,
							(float)y/W_HEIGHT,
							(float)width/W_WIDTH,
							(float)height/W_HEIGHT );
	view->setViewport(vp);
}

void Scene::initAlg(const Genome &genome)
{
	alg = new Alg(this->physics, genome);
}

bool Scene::isRunning()
{
	return running;
}

Scene::~Scene()
{
	std::vector<Particle*>::iterator it;
	for(it=particles.begin(); it!=particles.end(); it++)
	{
		Particle *p = *it;
		EntityManager::getInstance()->enqueueToDelete(p);
		EntityManager::getInstance()->deleteQueue();
	}
	if(alg)
		delete alg;
	delete physics;
	delete view;
	particles.clear();


	for(unsigned int i=0; i<particles.size(); i++)
	{
		EntityManager::getInstance()->enqueueToDelete(particles[i]);
	}
}

void Scene::_render(sf::RenderTarget *target)
{
	sf::RectangleShape border(sf::Vector2f(width/SCALE, height/SCALE));
	border.setPosition(-width/2.f/SCALE,-height/2.f/SCALE);
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineColor(sf::Color::Black);
	border.setOutlineThickness(1.f/SCALE);
	target->draw(border);

	// rendering
	alg->render(target);

	std::vector<Particle*>::iterator it;
	for(it=particles.begin(); it!=particles.end(); it++)
	{
		Particle *p = *it;
		p->render(target);

	}

	sf::RectangleShape bglt(sf::Vector2f(53.f/SCALE, 22.f/SCALE));
	bglt.setPosition((float)width/2.f/SCALE - 59.f/SCALE,
						  (float)height/2.f/SCALE - 24.f/SCALE);
	bglt.setFillColor(sf::Color(255,200,100,180));
	target->draw(bglt);

	// score
	std::stringstream sss;
	sss << getScore();
	sf::Text st(sss.str());
	st.setCharacterSize(10);
	st.setScale(0.1, 0.1);
	st.setColor(sf::Color::Black);
	st.setPosition((float)width/2.f/SCALE - 55.f/SCALE,
						(float)height/2.f/SCALE - 25.f/SCALE);

	// lifetime
	std::stringstream sslt;
	sslt << alg->getLifetime();
	sf::Text lt(sslt.str());
	lt.setCharacterSize(10);
	lt.setScale(0.1, 0.1);
	lt.setColor(sf::Color::Black);
	lt.setPosition((float)width/2.f/SCALE - 55.f/SCALE,
						(float)height/2.f/SCALE - 15.f/SCALE);


	target->draw(st);
	target->draw(lt);

	// physics step :
	float32 tstep = 1.0f/20.0f;
	if(alg->isAlive())
		physics->Step(tstep,20,20);
	else
		running = false;
}

void Scene::render(sf::RenderTarget *target)
{
	target->setView(*view);
//	target->clear(sf::Color(255,255,255));
	_render(target);

}

float Scene::getScore()
{
	float mod = 0;
	int maxSize = 2000;
	int size = alg->getSize();
	if(size>maxSize)
	{
		mod = (float)size/maxSize;
	}
	return alg->getLifetime()-mod;
}

void Scene::throwParticle(int nb)
{
	while(nb>0)
	{
		Launcher::Params l = App::getInstance()->getParticleParams();

		particles.push_back( new Particle(physics, l.x/SCALE, -l.y/SCALE, l.ix/SCALE, -l.iy/SCALE) );
		if(particles.size()>200)
			particles.erase(particles.begin());
		nb--;
	}
}

Genome Scene::getAlgGenome()
{
	return alg->getGenome();
}
