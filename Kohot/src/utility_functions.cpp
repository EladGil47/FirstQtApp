#include "utility_functions.hpp"

// #include <libxl.h>
#include <iostream>

#if 0
void UtilityFunctions::readPlayers(std::shared_ptr <Group> group)
{
	libxl::Book* book = xlCreateXMLBook();
	if (book)
	{
		const wchar_t* filename = L"ranks_elad_short_name.xlsx";
		if (book->load(filename))
		{
			libxl::Sheet* sheet = book->getSheet(0);
			if (sheet)
			{
				int id = 0;
				const int FIRST_COL_OF_BALLER = 9;
				const int FIRST_COL_OF_GK = 3;

				for (int col = FIRST_COL_OF_GK; col <= sheet->lastCol(); col = col + 2)
				{
					Player::Config player_config;
					if (col < FIRST_COL_OF_BALLER)
					{
						player_config.role = Player::Role::GK;
						col = col - 1;
					}
					else
					{
						player_config.role = Player::Role::BALLER;
					}

					int row = 15;
					while (row < 17)
					{
						libxl::CellType cellType = sheet->cellType(row, col);
						switch (cellType)
						{
						case libxl::CELLTYPE_NUMBER:
						{
							double d = sheet->readNum(row, col);
							player_config.rate = d;
							break;
						}
						case libxl::CELLTYPE_STRING:
						{
							if (sheet->isFormula(row, col))
							{
								const wchar_t* s = sheet->readFormula(row, col);
								std::wcout << (s ? s : L"null") << " [formula]";
							}
							else
							{
								const wchar_t* s = sheet->readStr(row, col);
								std::wstring ws(s);
								std::string myString(ws.begin(), ws.end());
								player_config.name = myString;
								//std::wcout << (s ? s : L"null");
							}
							break;
						}
						case libxl::CELLTYPE_BOOLEAN:
						{
							bool b = sheet->readBool(row, col);
							std::wcout << (b ? "true" : "false");
							break;
						}
						default:
							break;
						}
						row++;
					}

					//Need to check if the player is ok
					if (!player_config.name.empty())
					{
						player_config.id = id++;
						std::shared_ptr<Player> additional_player = std::make_shared<Player>(player_config);
						group->getPlayersCollectionRef().addPlayer(additional_player);
					}
				}
			}
		}
		else
		{
			std::cout << "Fail to open file" << '\t';
		}
		book->release();
	}
}
void UtilityFunctions::addUnlistedPlayers(std::shared_ptr <Group> group)
{
	Player::Config player_config;
	player_config.role = Player::Role::BALLER;
	player_config.name = "Igor";
	player_config.rate = 2.0;
	player_config.id = static_cast<uint16_t>(group->getPlayersCollectionRef().getSize());
	std::shared_ptr<Player> additional_player_igor = std::make_shared<Player>(player_config);
	group->getPlayersCollectionRef().addPlayer(additional_player_igor);

	player_config.name = "Omri Rahamani";
	player_config.rate = 5.2;
	player_config.id = static_cast<uint16_t>(group->getPlayersCollectionRef().getSize());
	std::shared_ptr<Player> additional_player_omri = std::make_shared<Player>(player_config);
	group->getPlayersCollectionRef().addPlayer(additional_player_omri);

	player_config.name = "Avihay ";
	player_config.rate = 6;
	player_config.id = static_cast<uint16_t>(group->getPlayersCollectionRef().getSize());
	std::shared_ptr<Player> additional_player_avihay = std::make_shared<Player>(player_config);
	group->getPlayersCollectionRef().addPlayer(additional_player_avihay);
}

#endif
