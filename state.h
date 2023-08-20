#ifndef STATE_H
#define STATE_H

#include "core/string/node_path.h"
#include "core/variant/dictionary.h"
#include "scene/main/node.h"

class StateMachine;

class State : public Node
{
	GDCLASS(State, Node);

public:
	GDVIRTUAL1(enter, const Dictionary&)
	GDVIRTUAL1(process, double)
	GDVIRTUAL1(physics_process, double)
	GDVIRTUAL1(handle_input, const Ref<InputEvent>&)
	GDVIRTUAL1(exit, const String&)

	void set_state_machine(StateMachine* p_machine) { _state_machine = p_machine; }
	StateMachine* get_state_machine() const { return _state_machine; }

protected:
	static void _bind_methods();

private:
	StateMachine* _state_machine = nullptr;

public:
	State() {};
};

#endif
