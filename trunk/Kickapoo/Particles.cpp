#include "Common.h"
#include "Particles.h"

Particle::Particle(IParticleSystem * _pSystem, const D3DXVECTOR2& pos, const D3DXVECTOR2& dir,
	 bool loop, float lifeTime, float velocity, D3DCOLOR color, float size)
	: start(pos),
	  dirVec(dir),
	  looping(loop),
	  lifeTime(lifeTime),
	  velocity(velocity),
	  color(color),
	  size(size),
	  particleSystem(_pSystem)
{
	respawnTime = particleSystem->currentTime();
	position = start;
}

Particle::~Particle()
{
}

bool Particle::updateState()
{
	float tt = particleSystem->currentTime();
	if(tt > (respawnTime + lifeTime))
	{
		if(!looping)
			return false;
		respawnTime = tt;
		position = start;
		return true;
	}

	position += dirVec * velocity * g_Timer()->getFrameTime();
	return true;
}

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
	for(std::list<Particle *>::iterator it = instances.begin() ; it != instances.end() ; ++it)
		delete *it;
}

void ParticleSystem::updateParticles()
{
	curTime = g_Timer()->getEngineTime();
	for(std::list<Particle *>::iterator it = instances.begin() ; it != instances.end() ; )
	{
		if((*it)->updateState())
		{
			++it;
		} else {
			delete *it;
			it = instances.erase(it);
		}
	}
}

void ParticleSystem::spawnParticle(const D3DXVECTOR2& pos, const D3DXVECTOR2& direction,
	bool looping, float lifeTime, float velocity, D3DCOLOR color, float size)
{
	instances.push_back(new Particle(this, pos, direction, looping, lifeTime, velocity, color, size));
}

float ParticleSystem::currentTime() const
{
	return curTime;
}

void ParticleSystem::renderParticles()
{
	g_Renderer()->setIdentity();
	for(std::list<Particle *>::const_iterator it = instances.begin() ; it != instances.end() ; ++it)
	{
		g_Renderer()->drawRect((*it)->pos().x, (*it)->pos().y, (*it)->size, (*it)->size, (*it)->color);
	}
}