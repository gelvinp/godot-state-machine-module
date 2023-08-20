#include "state.h"

void State::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("set_state_machine", "state_machine"), &State::set_state_machine);
	ClassDB::bind_method(D_METHOD("get_state_machine"), &State::get_state_machine);

	GDVIRTUAL_BIND(enter);
	GDVIRTUAL_BIND(process);
	GDVIRTUAL_BIND(physics_process);
	GDVIRTUAL_BIND(handle_input);
	GDVIRTUAL_BIND(exit);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "state_machine", PROPERTY_HINT_NODE_TYPE, "StateMachine", PROPERTY_USAGE_NO_EDITOR), "set_state_machine", "get_state_machine");
}