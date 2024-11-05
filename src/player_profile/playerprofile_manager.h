/*
 * playerprofile_manager.h
 *
 *  Created on: 5 nov 2024
 *      Author: andrea
 */

#ifndef SRC_PLAYER_PROFILE_PLAYERPROFILE_MANAGER_H_
#define SRC_PLAYER_PROFILE_PLAYERPROFILE_MANAGER_H_

namespace leap
{
	namespace network
	{

		class PlayerProfileManager
		{
		public:
			virtual
			~PlayerProfileManager ();

		private:
			PlayerProfileManager ();
		};

	} /* namespace network */
} /* namespace leap */

#endif /* SRC_PLAYER_PROFILE_PLAYERPROFILE_MANAGER_H_ */
