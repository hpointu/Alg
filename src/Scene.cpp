#include "Scene.hpp"
#include "const.hpp"
#include <cstdlib>
#include "ContactListener.hpp"
#include <iostream>
#include "EntityManager.hpp"

Scene::Scene(int w, int h, int x, int y) :
	width(w),
	height(h),
	posX(x),
	posY(y)
{
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
	alg = Alg(this->physics, genome);
}

bool Scene::isRunning()
{
	return running;
}

Scene::~Scene()
{
	delete physics;
}

void Scene::render(sf::RenderTarget *target)
{
	target->setView(*view);
//	target->clear(sf::Color(255,255,255));

	sf::RectangleShape border(sf::Vector2f(width/SCALE, height/SCALE));
	border.setPosition(-width/2.f/SCALE,-height/2.f/SCALE);
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineColor(sf::Color::Black);
	border.setOutlineThickness(1.f/SCALE);
	target->draw(border);

	// rendering
	alg.render(target);

	std::vector<Particle*>::iterator it;
	for(it=particles.begin(); it!=particles.end(); it++)
	{
		Particle *p = *it;
		p->render(target);

	}

	// physics step :
	float32 tstep = 1.0f/20.0f;
	if(alg.isAlive())
		physics->Step(tstep,20,20);
	else
		running = false;

//	// delete old particles :
//	if(particles.size() > 200)
//	{
//		for(unsigned int i=0; i<100; i++)
//		{
//			Particle *p = particles.front();
//			EntityManager::getInstance()->enqueueToDelete(p);
//			particles.erase(particles.begin());
//		}
//	}
}

void Scene::throwParticle(int nb)
{
	while(nb>0)
	{
		double x = width/2/SCALE;
		double y = rand()%height;
		y -= height/2;
		y /= SCALE;

		particles.push_back( new Particle(physics, x, y) );
		nb--;
	}
}
