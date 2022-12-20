/* state.cpp */

#include "state.h"
#include "state_machine.h"

void State::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("enter", "message"), &State::enter, DEFVAL(Dictionary()));
    ClassDB::bind_method(D_METHOD("process", "delta"), &State::process);
    ClassDB::bind_method(D_METHOD("physics_process", "delta"), &State::physics_process);
    ClassDB::bind_method(D_METHOD("handle_input", "event"), &State::handle_input);
    ClassDB::bind_method(D_METHOD("exit", "leaving_for"), &State::exit);
	ClassDB::bind_method(D_METHOD("set_state_machine", "state_machine"), &State::set_state_machine);
	ClassDB::bind_method(D_METHOD("get_state_machine"), &State::get_state_machine);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "state_machine", PROPERTY_HINT_NODE_TYPE, "StateMachine", PROPERTY_USAGE_NO_EDITOR), "set_state_machine", "get_state_machine");
}


void State::set_state_machine(StateMachine* state_machine)
{
	_state_machine = state_machine;
}


StateMachine* State::get_state_machine()
{
	return _state_machine;
}
