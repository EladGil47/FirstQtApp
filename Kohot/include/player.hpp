#ifndef KOHOT_PLAYER_HPP
#define KOHOT_PLAYER_HPP

#include <string>

class Player
{
public:
	enum class Role { GK, BALLER };
	struct Config
	{
		uint16_t id;
		std::string name;
		double rate;
		Player::Role role;
	};

	Player();
	Player(const Player::Config& config);

	std::string getRoleText() const;
	Player::Role getRole() const;
	std::string getName() const;
	double getRate()const ;
	uint16_t getId()const;
	void setId(uint16_t id);
	void setName(const std::string & name) ;
	void setRate(double rate) ;
	void setRole(std::string role_text) ;
	void setRole(Player::Role role) ;



	static Player::Role toPlayerRole(std::string role_text);

private:
	Config m_config;
};

#endif	//KOHOT_PLAYER_HPP