/* 
 * Match.h -- Match scene header file
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

#ifndef _SCENE_MATCH_H_
#define _SCENE_MATCH_H_

#include <OGF/OGF.h>

#include <OgreBulletCollisions.h>
#include <OgreBulletDynamics.h>
#include <OgreBulletDynamicsWorld.h>
#include <OgreBulletDynamicsRigidBody.h>

#include <Debug/OgreBulletCollisionsDebugDrawer.h>
#include <Shapes/OgreBulletCollisionsTrimeshShape.h>		
#include <Utils/OgreBulletCollisionsMeshToShapeConverter.h>

#include <vector>

#include "InputAdapter.h"
#include "Model.h"
#include "SceneFactory.h"
#include "data/PointStateListener.h"
#include "data/Match.h"
#include "widgets/Ball.h"
#include "widgets/Score.h"
#include "widgets/PlayerCpu.h"
#include "widgets/PlayerHuman.h"

namespace CrazyTennis {
	
	namespace Scene {

		typedef std::pair<Ogre::SceneNode *, OgreBulletDynamics::RigidBody *> DynamicObjectPair;

		class Match: public OGF::Scene, Data::PointState::Listener {

			private:
				
				Data::Match *_data;
				Data::PointState::Machine *_pointStateMachine;
				
				Ogre::Camera *_topCamera;
				Ogre::SceneNode *_topCameraNode;

				OgreBulletCollisions::DebugDrawer * _dynamicWorldDebugDrawer;
				OgreBulletDynamics::DynamicsWorld *_dynamicWorld;

				CrazyTennis::Widget::Ball *_ball;
				DynamicObjectPair _court;

				Ogre::Timer *_resetTimer;
				Widget::PlayerBase *_player1;
				Widget::PlayerBase *_player2;
				
				DynamicObjectPair _createPhysicObject(const Ogre::String &name, const OGF::ModelId &modelId, const float &restitution = 1.0);
				void _createDynamicWorld();
				void _createScene();

				void _loadCameras();
				void _loadDynamicObjects();
				void _loadLights();
				void _loadStaticObjects();
				void _loadUserInterface();

				/**
				 * Reset the point after a certain delay.
				 */
				void _resetPoint();
				
				void _onActionDone(const Controls::Action &action);

				/**
				 * Check the ball status to detect collisions.
				 *
				 * @return true if the ball has bounced, false otherwise.
				 */
				bool _checkBallStatus();

				/**
				 * Check the camera viewport to detect if the ball is visible and
				 * adjust it otherwise.
				 */
				void _checkCameraViewport();

				/**
				 * Convert from a 3D position to a court place.
				 *
				 * @param position 3D Absolute position.
				 * @return Place in court
				 */
				Data::PointState::BouncePlace _positionToCourtPlace(const Ogre::Vector3 &position);
			
			public:
				
				Match(Data::Match *data);
				~Match();

				void preload();
				void enter();
				void exit();
				void pause();
				void resume();

				bool frameEnded(const Ogre::FrameEvent& event);
				bool frameStarted(const Ogre::FrameEvent &event);

				bool keyReleased(const OIS::KeyEvent &event);
				bool buttonReleased(const OIS::JoyStickEvent &event, int button);

				void onChangeState(const Data::PointState::State &previousState, const Data::PointState::State &currentState);
		};
	};
};

#endif
