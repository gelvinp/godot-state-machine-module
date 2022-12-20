/* state_machine.h */

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "scene/main/node.h"
#include "core/string/node_path.h"
#include "core/string/string_name.h"

class State;

class StateMachine : public Node
{
	GDCLASS(StateMachine, Node);

	private:
	NodePath initial_state;
	Dictionary initial_message;
	State* state;

	void _prepare_states();

	protected:
	static void _bind_methods();
	void _notification(int p_what);

	public:
	virtual void unhandled_input(const Ref<InputEvent>& _event) override;
	void transition_to(const NodePath& state_name, const Dictionary& msg);

	NodePath get_initial_state();
	void set_initial_state(NodePath new_initial_state);

	Dictionary get_initial_message();
	void set_initial_message(Dictionary new_initial_message);

	State* get_state();

	PackedStringArray get_configuration_warnings() const override;

	StateMachine() {};
};

#endif
