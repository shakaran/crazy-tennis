/* 
 * PlayerBase.h -- Base player widget header file
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

namespace CrazyTennis {
	namespace Widget {
		class PlayerBase;
	};
};

#ifndef _WIDGET_PLAYER_BASE_H_
#define _WIDGET_PLAYER_BASE_H_

#include <OGF/OGF.h>

#include "data/Match.h"
#include "data/Player.h"
#include "data/PointState.h"
#include "data/PointStateListener.h"
#include "data/PointStateMachine.h"
#include "widgets/Ball.h"
#include "widgets/PhysicalBase.h"
#include "widgets/PlayerMotion.h"
#include "Model.h"
#include "SoundPlayer.h"

namespace CrazyTennis {
	
	namespace Widget {

		class PlayerBase: public OGF::Widget, public Data::PointState::Listener {
			
			protected:
				
				Ogre::SceneNode *_sceneNode;

				Data::Match *_matchData;
				Data::Player *_playerData;
				Data::PointState::Machine *_pointStateMachine;

				Widget::Ball *_ball;
				Widget::PlayerMotion *_motionManager;

				Ogre::Real _speed;
				Ogre::Real _getSpeed() const;

				/**
				 * Calculate the serve destination
				 *
				 * @return Destination of the serve.
				 */
				virtual Ogre::Vector3 _calculateServeDestination() = 0;

				void _setInReturnState();
				void _setInServeState();

				/**
				 * Throw the ball up to start the serve.
				 */
				void _startToServe();
				void _serve();

			public:

				PlayerBase(Ogre::SceneManager *sceneManager, Widget::Ball *ball,
					Data::Match *matchData, Data::Player *playerData, Data::PointState::Machine *pointStateMachine);
				virtual ~PlayerBase();

				virtual void enter();
				void exit();

				bool frameStarted(const Ogre::FrameEvent &event);

				Ogre::Vector3 getPosition() const;
				void setPosition(const Ogre::Vector3 &position);
				void setPosition(const Ogre::Real &x, const Ogre::Real &y, const Ogre::Real& z);
        void rotate(const Ogre::Vector3 &axis, const Ogre::Degree& angle);
				void lookAt(const Ogre::Vector3 &point);

				virtual void onChangeState(const Data::PointState::State &previousState, const Data::PointState::State &currentState);
		};
	};
};

#endif
