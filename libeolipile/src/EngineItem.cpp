
#include "EngineItem.h"

/* Constructors */

EngineItem::EngineItem() {
	this->_states = new std::map<std::string, EngineItemState>();
}

/* Item states */

void EngineItem::addState(EngineItemState state) {
	this->_states->insert(std::pair<std::string, EngineItemState>(*(state.getName()), state));
}

bool EngineItem::setState(std::string *stateName) {
	std::map<std::string, EngineItemState>::iterator it;
	it = this->_states->find(*stateName);

	if (it == this->_states->end()) {
		return false;
	} else {
		this->_currentItemStateName = stateName;
		this->_currentItemState = &(it->second);
		return true;
	}
}