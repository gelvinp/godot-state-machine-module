/* state_machine.cpp */

#include "state.h"
#include "state_machine.h"
#include "core/object/callable_method_pointer.h"
#include "core/core_bind.h"
#include "core/variant/typed_array.h"


void StateMachine::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("transition_to", "state_name", "message"), &StateMachine::transition_to, DEFVAL(Dictionary()));
    ClassDB::bind_method(D_METHOD("get_state"), &StateMachine::get_state);
	ClassDB::bind_method(D_METHOD("set_initial_state", "initial_state"), &StateMachine::set_initial_state);
	ClassDB::bind_method(D_METHOD("get_initial_state"), &StateMachine::get_initial_state);
	ClassDB::bind_method(D_METHOD("set_initial_message", "initial_message"), &StateMachine::set_initial_message);
	ClassDB::bind_method(D_METHOD("get_initial_message"), &StateMachine::get_initial_message);

	ADD_SIGNAL(MethodInfo("transitioned", PropertyInfo(Variant::STRING, "state_name")));

	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "initial_state", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "State"), "set_initial_state", "get_initial_state");
	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "initial_message", PROPERTY_HINT_NONE, ""), "set_initial_message", "get_initial_message");
}


void StateMachine::_notification(int p_what) {
	if (core_bind::Engine::get_singleton()->is_editor_hint())
	{
		return;
	}

	switch (p_what) {
		case NOTIFICATION_READY: {
			get_owner()->connect("ready", callable_mp(this, &StateMachine::_prepare_states), CONNECT_ONE_SHOT);
			break;
		}
		case NOTIFICATION_PROCESS: {
			state->get_script_instance()->call("process", get_process_delta_time());
			break;
		}
		case NOTIFICATION_PHYSICS_PROCESS: {
			state->get_script_instance()->call("physics_process", get_physics_process_delta_time());
			break;
		}
	}
}


void StateMachine::_prepare_states()
{
	TypedArray<Node> children = find_children("*", "State");

	for (int idx = 0; idx < children.size(); ++idx)
	{
		Object::cast_to<State>((Object*)children[idx])->set_state_machine(this);
	}

	state = Object::cast_to<State>(get_node(initial_state));
	state->get_script_instance()->call("enter", initial_message);

	set_process(true);
	set_physics_process(true);
	set_process_unhandled_input(true);
}


void StateMachine::unhandled_input(const Ref<InputEvent>& event)
{
	if (core_bind::Engine::get_singleton()->is_editor_hint())
	{
		return;
	}

	state->get_script_instance()->call("handle_input", event);
}


void StateMachine::transition_to(const NodePath& state_name, const Dictionary& msg)
{
	if (!has_node(state_name))
	{
		return;
	}

	State* new_state = Object::cast_to<State>(get_node(state_name));

	state->get_script_instance()->call("exit", new_state->get_name());
	state = new_state;
	state->get_script_instance()->call("enter", msg);

	emit_signal("transitioned", state->get_name());
}


NodePath StateMachine::get_initial_state()
{
	return initial_state;
}


void StateMachine::set_initial_state(NodePath new_initial_state)
{
	initial_state = new_initial_state;
}


Dictionary StateMachine::get_initial_message()
{
	return initial_message;
}


void StateMachine::set_initial_message(Dictionary new_initial_message)
{
	initial_message = new_initial_message;
}


State* StateMachine::get_state()
{
	return state;
}


PackedStringArray StateMachine::get_configuration_warnings() const {
	PackedStringArray warnings = Node::get_configuration_warnings();

	if (initial_state.is_empty())
	{
		warnings.push_back(RTR("StateMachine requires an initial state to be set."));
	}

	return warnings;
}

