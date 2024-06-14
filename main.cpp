#include <QApplication>

#include "windows_manager.h"
#include "kohot.hpp"

#include <fstream>
#include "sqlite3.h"

#include "json_utils.hpp"

using json = nlohmann::json;

int runWithJsonData(int argc, char* argv[])
{
    Kohot kohot;
    kohot.loadGroups();
    std::shared_ptr<GroupsCollection> groups_collection = kohot.getGroupsCollection();

    QApplication   a(argc, argv);
    WindowsManager window(groups_collection);
    QObject::connect(&window, &QObject::destroyed, [&kohot]() { kohot.saveGroups(); });

    int ret_val = a.exec();
    return ret_val;
}

void createTables(sqlite3* db)
{
    char* errMsg = 0;

    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS Groups (
            Id INTEGER PRIMARY KEY,
            Name TEXT,
            Players_in_team INTEGER,
            Teams INTEGER
        );
        CREATE TABLE IF NOT EXISTS Players (
            Id INTEGER,
            GroupId INTEGER,
            Name TEXT,
            Rate REAL,
            Role TEXT,
            FOREIGN KEY(GroupId) REFERENCES Groups(Id)
        );
    )";

    int ret_val = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (ret_val != SQLITE_OK)
    {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else
    {
        std::cout << "Tables created successfully" << std::endl;
    }
}

void insertData(sqlite3* db, const json& j)
{
    sqlite3_stmt* stmt;

    // Insert Groups
    const char* groupSql = "INSERT INTO Groups (Id, Name, Players_in_team, Teams) VALUES (?, ?, ?, ?)";
    sqlite3_prepare_v2(db, groupSql, -1, &stmt, 0);
    for (const auto& group : j["Groups"])
    {
        sqlite3_bind_int(stmt, 1, group["Id"]);
        sqlite3_bind_text(stmt, 2, group["Name"].get<std::string>().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, group["Players_in_team"]);
        sqlite3_bind_int(stmt, 4, group["Teams"]);
        if (sqlite3_step(stmt) != SQLITE_DONE)
        {
            std::cerr << "Error inserting group: " << sqlite3_errmsg(db) << std::endl;
        }
        sqlite3_reset(stmt);
    }
    sqlite3_finalize(stmt);

    // Insert Players
    const char* playerSql = "INSERT INTO Players (Id, GroupId, Name, Rate, Role) VALUES (?, ?, ?, ?, ?)";
    sqlite3_prepare_v2(db, playerSql, -1, &stmt, 0);
    for (const auto& group : j["Groups"])
    {
        int groupId = group["Id"];
        for (const auto& player : group["Players"])
        {
            sqlite3_bind_int(stmt, 1, player["Id"]);
            sqlite3_bind_int(stmt, 2, groupId);
            sqlite3_bind_text(stmt, 3, player["Name"].get<std::string>().c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_double(stmt, 4, player["Rate"]);
            sqlite3_bind_text(stmt, 5, player["Role"].get<std::string>().c_str(), -1, SQLITE_STATIC);
            if (sqlite3_step(stmt) != SQLITE_DONE)
            {
                std::cerr << "Error inserting player: " << sqlite3_errmsg(db) << std::endl;
            }
            sqlite3_reset(stmt);
        }
    }
    sqlite3_finalize(stmt);
}

void printTable(sqlite3* db, const char* tableName)
{
    std::string   sql = "SELECT * FROM " + std::string(tableName) + ";";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0) == SQLITE_OK)
    {
        int cols = sqlite3_column_count(stmt);
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            for (int col = 0; col < cols; col++)
            {
                std::cout << sqlite3_column_text(stmt, col) << " ";
            }
            std::cout << std::endl;
        }
        sqlite3_finalize(stmt);
    }
    else
    {
        std::cerr << "Failed to execute statement: " << sqlite3_errmsg(db) << std::endl;
    }
}

void loadDataFromDatabase(const std::string& db_path, GroupsCollection& groups_collection)
{
    sqlite3* db;
    int      ret_val = sqlite3_open(db_path.c_str(), &db);
    if (ret_val)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    const char*   group_query = "SELECT Id, Name, Teams, Players_in_team FROM Groups";
    sqlite3_stmt* group_stmt;

    if (sqlite3_prepare_v2(db, group_query, -1, &group_stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to prepare group query: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    while (sqlite3_step(group_stmt) == SQLITE_ROW)
    {
        uint16_t    group_id        = sqlite3_column_int(group_stmt, 0);
        std::string group_name      = reinterpret_cast<const char*>(sqlite3_column_text(group_stmt, 1));
        uint16_t    teams           = sqlite3_column_int(group_stmt, 2);
        uint16_t    players_in_team = sqlite3_column_int(group_stmt, 3);

        Group::Config          group_config = {group_id, group_name, teams, players_in_team};
        std::shared_ptr<Group> group_ptr    = std::make_shared<Group>(group_config);

        std::string   player_query = "SELECT Id, Name, Rate, Role FROM Players WHERE GroupId = " + std::to_string(group_id);
        sqlite3_stmt* player_stmt;

        if (sqlite3_prepare_v2(db, player_query.c_str(), -1, &player_stmt, nullptr) != SQLITE_OK)
        {
            std::cerr << "Failed to prepare player query: " << sqlite3_errmsg(db) << std::endl;
            continue;
        }

        while (sqlite3_step(player_stmt) == SQLITE_ROW)
        {
            uint16_t     player_id   = sqlite3_column_int(player_stmt, 0);
            std::string  player_name = reinterpret_cast<const char*>(sqlite3_column_text(player_stmt, 1));
            double       player_rate = sqlite3_column_double(player_stmt, 2);
            Player::Role player_role = Player::toPlayerRole(reinterpret_cast<const char*>(sqlite3_column_text(player_stmt, 3)));

            Player::Config          player_config = {player_id, player_name, player_rate, player_role};
            std::shared_ptr<Player> player_ptr    = std::make_shared<Player>(player_config);
            group_ptr->getPlayersCollectionRef().addItem(player_ptr);
        }

        sqlite3_finalize(player_stmt);
        groups_collection.addItem(group_ptr);
    }

    sqlite3_finalize(group_stmt);
    sqlite3_close(db);
}

// int main(int argc, char* argv[])
// {
//     int ret_val = runWithJsonData(argc, argv);
//     return ret_val;
// }

// Function for write json to data base using sqlite
/*
int main(int argc, char* argv[])
{
    // Load JSON data from a file (you can change this to your actual JSON string if needed)
    std::ifstream inputFile("Data/groups.json");
    json          jsonData;
    inputFile >> jsonData;

    // Open database
    sqlite3* db;
    int      ret_val = sqlite3_open("test.db", &db);
    if (ret_val)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return ret_val;
    }
    else
    {
        std::cout << "Opened database successfully" << std::endl;
    }

    // Create tables
    createTables(db);

    // Insert data
    insertData(db, jsonData);

    // Close database
    sqlite3_close(db);
    return 0;
}
*/
// Function for print data base using sqlite
/*
int main()
{
    sqlite3* db;
    int      ret_val = sqlite3_open("test.db", &db);
    if (ret_val)
    {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return ret_val;
    }
    else
    {
        std::cout << "Opened database successfully" << std::endl;
    }

    std::cout << "Groups:" << std::endl;
    printTable(db, "Groups");

    std::cout << "\nPlayers:" << std::endl;
    printTable(db, "Players");

    sqlite3_close(db);
    return 0;
}
*/

int main(int argc, char* argv[])
{
    GroupsCollection groups_collection;
    loadDataFromDatabase("test.db", groups_collection);

    QApplication   a(argc, argv);
    WindowsManager window(std::make_shared<GroupsCollection>(groups_collection));
    // TODO add function for save on database

    int ret_val = a.exec();
    return ret_val;
}