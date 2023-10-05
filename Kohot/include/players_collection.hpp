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
	size_t getIndexById(size_t id)
	{
		size_t ret_val;
		bool is_found ;
		if (!m_collection.empty())
		{
			size_t index = 0 ; 
			for (std::shared_ptr<Player> player : m_collection )
			{
				if(player->getId() == id)
				{
					ret_val = index;
					is_found = true;
				}
				index ++;
			}
			if (!is_found)
			{
			std::cerr << "Can not find player with id" << id << "in Players Collection" ; 
			}
		}
		else{
			std::cerr << "Players Collection is empty" ; 
		}
		return ret_val;
	}
private:
	Player::Config getPlayerConfigFromUser();
};

#endif // KOHOT_PLAYERS_COLLECTION_HPP