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
	static void _bind_methods();

	public:
	void enter(const Dictionary& _msg) {}
	void process(float _delta) {}
	void physics_process(float _delta) {}
	void handle_input(const Ref<InputEvent>& _event) {}
	void exit(const String& _leaving_for) {}

	State() {};
};

#endif
