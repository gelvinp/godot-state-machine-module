/* state.h */

#ifndef STATE_H
#define STATE_H

#include "scene/main/node.h"
#include "core/variant/dictionary.h"
#include "core/string/node_path.h"

class StateMachine;

class State : public Node
{
	GDCLASS(State, Node);

	private:
	StateMachine* _state_machine = nullptr;

	friend class StateMachine;
	void set_state_machine(StateMachine* state_machine);
	StateMachine* get_state_machine();

	protected:
	GDVIRTUAL1(enter, const Dictionary&)
	GDVIRTUAL1(process, double)
	GDVIRTUAL1(physics_process, double)
	GDVIRTUAL1(handle_input, const Ref<InputEvent>&)
	GDVIRTUAL1(exit, const String&)

	friend class StateMachine;
	void _call_enter(const Dictionary&);
	void _call_process(double);
	void _call_physics_process(double);
	void _call_handle_input(const Ref<InputEvent>&);
	void _call_exit(const String&);

	static void _bind_methods();

	public:
	State() {};
};

#endif
