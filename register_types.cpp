#include "register_types.h"

#include "state.h"
#include "state_machine.h"

#include "core/object/class_db.h"


void initialize_state_machine_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}

	ClassDB::register_class<State>();
	ClassDB::register_class<StateMachine>();
}


void uninitialize_state_machine_module(ModuleInitializationLevel p_level) {}
