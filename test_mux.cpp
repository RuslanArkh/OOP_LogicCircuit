#include "component.h"
#include "filecommandhandler.h"

#include <iostream>
#include <typeinfo>

int main()
{
	std::cout.setf(std::ios::boolalpha);

	std::unique_ptr<Component> Comp{ new Component (Component::ComponentType::MUX, "a b c d e f g h a1 a2 a3", "q") };
	Comp.get()->addV("v", true);
	FileCommandHandler fcHandler{ Comp, "commands_mux.txt" };
	fcHandler.RunFileCommands(std::cout);

	const std::type_info & type1 = typeid(fcHandler.RunFileCommands(std::cout));
	std::cout << "\nType: " << type1.name() << std::endl;
}