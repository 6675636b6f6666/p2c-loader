#pragma once
#include <fstream>
#include <cstring>
#include <filesystem>
#include <TlHelp32.h>

namespace user_information {
	static std::string username;
	static std::string created;
	static std::string last;
	static std::string sub;
	static std::string expiry;
	static std::string expiry_date;
}

namespace vars {
	int selected_tab = 0;
	int selected_cheat = 0;
	float spinner_timer = 0.0f;
	bool validlogin = false;
	bool spinner_active2 = false;
	bool finaltab = false;
	bool show_message_box = false;
	std::string message_box_title = "";
	std::string message_box_message = "";
	bool show_message_box2 = false;
	std::string message_box_title2 = "";
	std::string message_box_message2 = "";

	bool show_password = false;
	static char username[26];
	static char password[26];
	static char license[64];

	bool can_inject = false;
	bool cheat1, cheat2, cheat3;
}

#ifndef UNLEN
#define UNLEN 256
#endif

class UserData {
public:
	void saveToFile(const std::string& filename) {
		std::ofstream out(filename, std::ios::binary);
		out.write((char*)&vars::license, sizeof(vars::license));
		out.close();
	}

	void loadFromFile(const std::string& filename) {
		if (!std::filesystem::exists(filename)) {
			return;
		}

		std::ifstream in(filename, std::ios::binary);
		in.read((char*)&vars::license, sizeof(vars::license));
		in.close();
	}

		

};






namespace io {

	
	void log(std::string container) {

		static auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
		printf("[+] ");
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

		
		printf(container.c_str());

	}

	
	void log_error(std::string container) {

		static auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, FOREGROUND_RED);
		printf("[!] ");
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

		

		printf(container.c_str());

	}

	
}; 

