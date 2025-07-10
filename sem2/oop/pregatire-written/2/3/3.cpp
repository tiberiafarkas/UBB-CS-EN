#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

/*
	Memory flows down like:

MenuBar
 └── unique_ptr<Menu>
	   └── unique_ptr<MenuItem>
			  └── raw Action*

*/

class Action {
public:
	Action() {};
	virtual void execute() = 0;
	virtual ~Action() {}
};

class CreateAction : public Action {
public:
	CreateAction() {};
	void execute() override {
		cout << "Create File\n";
	}
	~CreateAction() {};
};

class ExitAction : public Action {
public:
	ExitAction() {};
	void execute() override {
		cout << "Exit application\n";
	}
	~ExitAction() {};
};

class MenuItem {
private:
	string text;
	Action* action;
public:
	MenuItem() {
		text = "";
		action = nullptr;
	}
	MenuItem(string t, Action* a) : text(t), action(a) {}
	string getText() {
		return text;
	}
	void print() {
		cout << text << '\n';
	}
	void click() {
		print();
		if ( action != nullptr )
			action->execute();
	}
	~MenuItem() {
		if (action != nullptr)
			delete action;
	}
};

class Menu : public MenuItem {
private:
	vector<unique_ptr<MenuItem>> menus;
public:
	Menu(string t, Action* a) : MenuItem{ t, a } {}
	void add(MenuItem *m) {
		menus.emplace_back(m);
	}
	void print() {
		cout << "=====" << getText() << "=====\n" ;
		for (auto& m : menus) {
			m->print();
		}
	}
};

class MenuBar {
private:
	vector<unique_ptr<Menu>> menus;
public:
	void add(Menu *m) {
		menus.emplace_back(m);
	}
	void print() {
		for (auto& m : menus) {
			m->print();
		}
	}
};

int main()
{
	MenuItem* text = new MenuItem("Text", new CreateAction()); 
	MenuItem* c = new MenuItem("C++", new CreateAction());

	//Submenus
	Menu* New = new Menu("New", nullptr);
	New->add(text);
	New->add(c);

	MenuItem* Exit = new MenuItem("Exit", new ExitAction());

	Menu* file = new Menu("File", nullptr);
	file->add(New);
	file->add(Exit);

	Menu* about = new Menu("about", nullptr);

	MenuBar bar;
	bar.add(file);
	bar.add(about);

	file->print();
	New->print();
	c->print();
	Exit->print();
}

//the same thing could have been done using raw pointers:

/*
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Abstract Action
class Action {
public:
	virtual void execute() = 0;
	virtual ~Action() {}
};

// Concrete Actions
class CreateAction : public Action {
public:
	void execute() override {
		cout << "Create File\n";
	}
};

class ExitAction : public Action {
public:
	void execute() override {
		cout << "Exit application\n";
	}
};

// MenuItem base class
class MenuItem {
protected:
	string text;
	Action* action;

public:
	MenuItem(const string& t, Action* a = nullptr) : text(t), action(a) {}

	string getText() const {
		return text;
	}

	virtual void print() const {
		cout << text << '\n';
	}

	virtual void click() {
		print();
		if (action) action->execute();
	}

	virtual ~MenuItem() {
		if (action)
			delete action;
	}
};

// Menu (composite)
class Menu : public MenuItem {
	vector<MenuItem*> items;

public:
	Menu(const string& t, Action* a = nullptr) : MenuItem(t, a) {}

	void add(MenuItem* item) {
		items.push_back(item);
	}

	void print() const override {
		cout << getText() << '\n';
		for (auto& item : items)
			item->print();
	}

	void click() override {
		print(); // clicking a menu just prints its contents
	}

	~Menu() override {
		for (auto item : items)
			delete item;
	}
};

// MenuBar (container of Menus)
class MenuBar {
	vector<Menu*> menus;

public:
	void add(Menu* menu) {
		menus.push_back(menu);
	}

	void print() const {
		for (auto& menu : menus)
			menu->print();
	}

	~MenuBar() {
		for (auto menu : menus)
			delete menu;
	}
};


int main() {
	// Create actions
	Action* create = new CreateAction();
	Action* exit = new ExitAction();

	// Create leaf menu items
	MenuItem* textItem = new MenuItem("Text", create);           // owns `create`
	MenuItem* cppItem = new MenuItem("C++", new CreateAction()); // owns its own action

	// Create submenu "New"
	Menu* newMenu = new Menu("New");
	newMenu->add(textItem);
	newMenu->add(cppItem);

	// Exit item
	MenuItem* exitItem = new MenuItem("Exit", exit); // owns `exit`

	// File menu
	Menu* fileMenu = new Menu("File");
	fileMenu->add(newMenu);
	fileMenu->add(exitItem);

	// About menu
	Menu* aboutMenu = new Menu("About");

	// Menu bar
	MenuBar bar;
	bar.add(fileMenu);
	bar.add(aboutMenu);

	// Simulate: File -> New -> C++ then Exit
	cout << "Simulation:\n";
	fileMenu->click();       // Show "File" and its submenus
	newMenu->click();        // Show "New" and its submenus
	cppItem->click();        // Show "C++", execute CreateAction
	exitItem->click();       // Show "Exit", execute ExitAction

	// Memory is cleaned up by destructors of Menu, MenuItem, MenuBar
	return 0;
}

*/


