#include "state_machine.h"

#include "state.h"

#include "core/core_bind.h"
#include "core/object/callable_method_pointer.h"
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
			if (get_owner() != nullptr)
			{
				get_owner()->connect("ready", callable_mp(this, &StateMachine::_prepare_states), CONNECT_ONE_SHOT);
			}
			else
			{
				_prepare_states();
			}
			break;
		}
		case NOTIFICATION_PROCESS: {
			GDVIRTUAL_CALL_PTR(state, process, get_process_delta_time());
			break;
		}
		case NOTIFICATION_PHYSICS_PROCESS: {
			GDVIRTUAL_CALL_PTR(state, physics_process, get_physics_process_delta_time());
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
	GDVIRTUAL_CALL_PTR(state, enter, initial_message);

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

	GDVIRTUAL_CALL_PTR(state, handle_input, event);
}


void StateMachine::transition_to(const NodePath& state_name, const Dictionary& msg)
{
	ERR_FAIL_COND_MSG(!has_node(state_name), vformat("StateMachine cannot transition to non-existent state: %s", state_name));

	State* new_state = Object::cast_to<State>(get_node(state_name));

	GDVIRTUAL_CALL_PTR(state, exit, new_state->get_name());
	state = new_state;
	GDVIRTUAL_CALL_PTR(state, enter, msg);

	emit_signal("transitioned", state->get_name());
}


PackedStringArray StateMachine::get_configuration_warnings() const {
	PackedStringArray warnings = Node::get_configuration_warnings();

	if (initial_state.is_empty())
	{
		warnings.push_back(RTR("StateMachine requires an initial state to be set."));
	}

	return warnings;
}

