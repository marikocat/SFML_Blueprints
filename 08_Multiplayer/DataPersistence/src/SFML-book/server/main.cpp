#include <ORM/core/Tables.hpp>

#include <ORM/backends/MySql.hpp>

std::shared_ptr<orm::DB> orm::DB::Default = std::make_shared<orm::MySqlDB>("root", "123456", "isogame_db");



#include <SFML-book/server/Server.h>

#include <iostream>
#include <cstdlib>

#include <ORM/fields.hpp>
#include <ORM/models/SqlObject.hpp>

int main(int argc, char* argv[])
{
	int port = 5678;

	std::cout << "Usage is : " << argv[0] << " [port]" << std::endl;

	if (argc > 1)
		port = std::atoi(argv[1]);

	
	std::cout << "Server start on port " << port << std::endl;

	orm::DB::Default->connect(); // connect to the database
	std::cout << "The number of tables created: " << orm::Tables::create() << std::endl; // create all the tables if needed

	book::Server server(port);
	server.run();

	return 0;
}