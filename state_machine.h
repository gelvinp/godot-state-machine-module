#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "core/string/node_path.h"
#include "core/string/string_name.h"
#include "scene/main/node.h"

class State;

class StateMachine : public Node
{
	GDCLASS(StateMachine, Node);

public:
	void set_initial_state(NodePath p_state) { initial_state = p_state; }
	NodePath get_initial_state() const { return initial_state; }

	void set_initial_message(Dictionary p_msg) { initial_message = p_msg; }
	Dictionary get_initial_message() const { return initial_message; }

	virtual void unhandled_input(const Ref<InputEvent>& _event) override;
	void transition_to(const NodePath& state_name, const Dictionary& msg);

	State* get_state() const { return state; }

protected:
	static void _bind_methods();
	void _notification(int p_what);

private:
	NodePath initial_state;
	Dictionary initial_message;
	State* state;

	void _prepare_states();

public:
	StateMachine() {};
	PackedStringArray get_configuration_warnings() const override;
};

#endif
