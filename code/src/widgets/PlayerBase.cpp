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

void 
PlayerBase::_setInServeState()
{
	Ogre::Vector3 servePosition(0, 1.5, 0);
	Ogre::Real xOffset = _configValue<float>("courtLength") +
		_configValue<float>("serveXOffset");
	Ogre::Real zOffset = _configValue<float>("serveZOffset");
	
	Data::PointState::BouncePlace whereToServe = _matchData->getWhereToServe();

	servePosition.x = getPosition().x > 0 ? xOffset : -xOffset;

	if (whereToServe == Data::PointState::BOUNCE_IN_RIGHT_SERVE_AREA) {
		servePosition.z = getPosition().x > 0 ? -zOffset : zOffset;
	} else {
		servePosition.z = getPosition().x < 0 ? -zOffset : zOffset;
	}

	setPosition(servePosition);
}

PlayerBase::PlayerBase(Ogre::SceneManager *sceneManager, OgreBulletDynamics::DynamicsWorld *dynamicWorld,
	Widget::Ball *ball, Data::Match *matchData, Data::Player *playerData,
	Data::PointState::Machine *pointStateMachine)
:	PhysicalBase(sceneManager, dynamicWorld), _matchData(matchData), _playerData(playerData), _ball(ball), _pointStateMachine(pointStateMachine)
{
_initConfigReader("widgets/player.cfg");
_speed = _playerData->getSkills()["speed"] * _configValue<float>("maximumRunSpeed");
_pointStateMachine->addListener(this);
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
	
	Ogre::Vector3 size = static_cast<Ogre::Entity *>(_sceneNode->getAttachedObject(0))->getBoundingBox().getHalfSize();
	OgreBulletCollisions::CollisionShape *bodyShape =
		new OgreBulletCollisions::BoxCollisionShape(size);
	
	_rigidBody = new OgreBulletDynamics::RigidBody(_playerData->getName(), _dynamicWorld);
	_rigidBody->setShape(_sceneNode, bodyShape, 0.6, 0.6, 80.0);
	_rigidBody->disableDeactivation();

	/*
		Ogre::AnimationState *animState = static_cast<Ogre::Entity *>(_sceneNode->getAttachedObject(0))->getAnimationState("shot");
		animState->setLength(5);
		animState->setEnabled(true);
		animState->setLoop(true);
		animState->setTimePosition(0.0);
	*/
}

void
PlayerBase::exit()
{

}

bool
PlayerBase::frameStarted(const Ogre::FrameEvent &event)
{
	/*
	Ogre::AnimationState *animState = static_cast<Ogre::Entity *>(_sceneNode->getAttachedObject(0))->getAnimationState("shot");
	if (!animState->hasEnded()) {
		animState->addTime(event.timeSinceLastFrame * 2.0);
	} else {
		animState->setEnabled(true);
		animState->setTimePosition(0.0);
	}
	*/

	return true;
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

void
PlayerBase::rotate(const Ogre::Vector3& axis, const Ogre::Degree& angle)
{
	PhysicalBase::rotate(axis, angle);
	_sceneNode->rotate(axis, Ogre::Radian(angle));
}

void
PlayerBase::onChangeState(const Data::PointState::State &previousState, const Data::PointState::State &currentState)
{
	std::cout << "FROM: " << previousState << " TO " << currentState << std::endl;

	switch(currentState) {
		case Data::PointState::STATE_BEFORE_SERVE:
			if (_matchData->getCurrentServer() == _playerData) {
				_setInServeState();
			} else {
				//_setInReturnState();
			}
			break;
	}
}
