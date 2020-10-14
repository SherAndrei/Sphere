#include <fstream>
#include <iostream>
#include <string>

int main()
{
	std::ofstream file("./tests/somename.txt");
	
	if(!file.good()) { //пишем состояние файла
	 	std::cout << "Error in file" << std::endl;
		return -1;
	} else {
		std::cout << "Success!" << std::endl;
	}

	std::string data;

	// std::getline(std::cin, data); 	
	while(std::cin >> data) 		// считываем по слову
		file << data << std::endl;	

	// ожидается что программа выдаст последнее слово
	std::cout << data << std::endl; 
	file.close();
}