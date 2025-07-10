#pragma once
#include "Service.h"

class UI {
private:
	Service service;
public:
	void print_menu();
	void add();
	void print_schools();
	void get_close_schools();
	void run();
};
