/* 
 * PlayerBase.h -- Base player widget implementation file
 *
 * Copyright (C) 2013 Javier Angulo Lucerón <javier.angulo1@gmail.com>
 * 
 * This file is part of Crazy Tennis
 *
 * Crazy Tennis is free software: you can redistribute it and/or modify it under the terms of 
 * the GNU General Public License as published by the Free Software Foundation, either 
 * version 3 of the License, or (at your option) any later version.
 * Crazy Tennis is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with Crazy Tennis. 
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include "widgets/PlayerBase.h"

using namespace CrazyTennis::Widget;

Ogre::Real
PlayerBase::_getSpeed() const
{
	return _speed;
}

PlayerBase::PlayerBase(Ogre::SceneManager *sceneManager, OgreBulletDynamics::DynamicsWorld *dynamicWorld, Widget::Ball *ball, Data::Player *data)
	:	PhysicalBase(sceneManager, dynamicWorld), _data(data), _ball(ball)
{
	_initConfigReader("widgets/player.cfg");
	_speed = _data->getSkills()["speed"] * _configValue<float>("maximumRunSpeed");
}

PlayerBase::~PlayerBase()
{

}

void
PlayerBase::enter()
{
	OGF::ModelBuilderPtr builder(OGF::ModelFactory::getSingletonPtr()->getBuilder(_sceneManager, Model::PLAYER));

	_sceneNode = builder->castShadows(true)
		->parent(_sceneManager->getRootSceneNode()->createChildSceneNode())
		->buildNode();
	
	Ogre::Vector3 size = static_cast<Ogre::Entity *>(_sceneNode->getAttachedObject(0))->getBoundingBox().getSize() / 2.0;
	OgreBulletCollisions::CollisionShape *bodyShape =
		new OgreBulletCollisions::BoxCollisionShape(size);

	_rigidBody = new OgreBulletDynamics::RigidBody(_data->getName(), _dynamicWorld);
	_rigidBody->setShape(_sceneNode, bodyShape, 0.6, 0.6, 80.0);
}

void
PlayerBase::exit()
{

}

bool
PlayerBase::frameStarted(const Ogre::FrameEvent &event)
{

}

void
PlayerBase::setPosition(const Ogre::Vector3 &position)
{
	PhysicalBase::setPosition(position);
	_sceneNode->setPosition(getPosition());
}

void
PlayerBase::setPosition(const Ogre::Real &x, const Ogre::Real &y, const Ogre::Real& z)
{
	setPosition(Ogre::Vector3(x, y, z));
}