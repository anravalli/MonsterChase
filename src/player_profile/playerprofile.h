/*
 * playerprofile.h
 *
 *  Created on: 5 nov 2024
 *      Author: andrea
 */

#ifndef SRC_PLAYER_PROFILE_PLAYERPROFILE_H_
#define SRC_PLAYER_PROFILE_PLAYERPROFILE_H_

namespace leap
{
	namespace network
	{

		class PlayerProfile
		{
		public:
			PlayerProfile ();
			virtual
			~PlayerProfile ();
			PlayerProfile (const PlayerProfile &other);
			PlayerProfile&
			operator= (const PlayerProfile &other);
		};

	} /* namespace network */
} /* namespace leap */

#endif /* SRC_PLAYER_PROFILE_PLAYERPROFILE_H_ */
