#include "player.hpp"

Player::Player()
{
	m_config = { 0,"",0,Player::Role::BALLER };
}

Player::Player( const Player::Config& config)
{
	m_config.id = config.id;
	m_config.name = config.name;
	m_config.role = config.role;
	m_config.rate = config.rate;
}

Player::Role Player::toPlayerRole(std::string role_text) {
	Player::Role role;
	if (role_text == "GK")
	{
		role = Player::Role::GK;
	}
	else if (role_text == "Baller")
	{
		role = Player::Role::BALLER;
	}
	else
	{
		role = Player::Role::BALLER;
	}
	return role;
}
std::string Player::getRoleText() const
{
	std::string role_text = "";
	switch (m_config.role)
	{
	case Player::Role::GK:
	{
		role_text = "GK";
		break;
	}
	case Player::Role::BALLER:
	{
		role_text = "Baller";
		break;
	}
	default:
		role_text = "undentified";
		break;
	}
	return role_text;
}
std::string Player::getName() const {
	return m_config.name;
}
double Player::getRate()const {
	return m_config.rate;
}
uint16_t Player::getId()const {
	return m_config.id;
}
 Player::Role Player::getRole() const 
{
	return m_config.role;
}
void Player::setId(uint16_t id) {
	m_config.id = id;
}
