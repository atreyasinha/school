// updated Mon Nov  9 22:38:22 PST 2020

#include <memory>
#include <cassert>
#include "Event_manager.h"
#include "Statement.h" 
using namespace std;


/* static */ Event_manager&  Event_manager::instance()
{
  static Event_manager the_manager;
  return the_manager;
}

Event_manager::Event_manager() : event_statement(Window::Keystroke::NUMBER_OF_KEYS){}

Event_manager::~Event_manager() {
  // vector<const Statement*>::const_iterator it;
  // for (int i = 0; i < (int) event_statement.size(); i++) {
  //   for (it = event_statement[i].begin(); it != event_statement[i].end(); ++it)   delete *it;
  // }
}

void Event_manager::execute_handlers(Window::Keystroke keystroke) const
{
    vector<const Statement*>::const_iterator it;

    for (it = event_statement[keystroke].begin(); it != event_statement[keystroke].end(); ++it)   (*it)->execute();
}

void Event_manager::add_handler(Window::Keystroke key, const Statement* s) {
    event_statement[key].push_back(s);
    assert(event_statement[key].size() > 0);
}


