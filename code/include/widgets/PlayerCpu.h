/* 
 * PlayerCpu.h -- CPU Player header file
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

#ifndef _WIDGET_PLAYER_CPU_H_
#define _WIDGET_PLAYER_CPU_H_

#include <OGF/OGF.h>

#include "data/Match.h"
#include "data/PointStateMachine.h"
#include "dynamics/ShotSimulator.h"
#include "widgets/PlayerBase.h"
#include "widgets/ShotBuffer.h"

namespace CrazyTennis {
	
	namespace Widget {

		class PlayerCpu : public PlayerBase {
			
			protected:
				
				bool _hitting;

				bool _canStartHit();
				bool _canEndHit();

				void _startHit();
				void _endHit();

				Ogre::Vector3 _calculateShotDestination();
				Ogre::Vector3 _calculateServeDestination();
				void _shot();
			
			public:
				
				PlayerCpu(Ogre::SceneManager *sceneManager, Widget::Ball *ball, Data::Match *matchData,
					Data::Player *playerData, Data::PointState::Machine *pointStateMachine);
				~PlayerCpu();

				void enter();
				void exit();

				bool frameStarted(const Ogre::FrameEvent &event);
		};
	};
};

#endif
