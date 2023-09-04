#ifndef KOHOT_PLAYERS_COLLECTION_HPP
#define KOHOT_PLAYERS_COLLECTION_HPP

#include "player.hpp"
#include "base_collection.hpp"

class PlayersCollection : public BaseCollection<Player>
{
public:
	void createItem() override;
	void display() override;
	std::vector<std::string> getPlayersNames()
	{
		std::vector<std::string> names;
		for (std::shared_ptr<Player> p : m_collection)
		{
			names.push_back(p->getName());
		}
		return names;
	}
private:
	Player::Config getPlayerConfigFromUser();
};

#endif // KOHOT_PLAYERS_COLLECTION_HPP