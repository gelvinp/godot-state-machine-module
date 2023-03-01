/* state.cpp */

#include "state.h"
#include "state_machine.h"

void State::_bind_methods()
{
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


void State::_call_enter(const Dictionary& msg)
{
	if (GDVIRTUAL_IS_OVERRIDDEN(enter))
	{
		GDVIRTUAL_CALL(enter, msg);
	}
}


void State::_call_process(double delta)
{
	if (GDVIRTUAL_IS_OVERRIDDEN(process))
	{
		GDVIRTUAL_CALL(process, delta);
	}
}


void State::_call_physics_process(double delta)
{
	if (GDVIRTUAL_IS_OVERRIDDEN(physics_process))
	{
		GDVIRTUAL_CALL(physics_process, delta);
	}
}


void State::_call_handle_input(const Ref<InputEvent>& event)
{
	if (GDVIRTUAL_IS_OVERRIDDEN(handle_input))
	{
		GDVIRTUAL_CALL(handle_input, event);
	}
}


void State::_call_exit(const String& leaving_for)
{
	if (GDVIRTUAL_IS_OVERRIDDEN(exit))
	{
		GDVIRTUAL_CALL(exit, leaving_for);
	}
}
