#ifndef TODO_CLI_TEST_WRAPPER_H
#define TODO_CLI_TEST_WRAPPER_H

#include "TodoCLI.h"

class TodoCLITestWrapper : public TodoCLI {
public:
  TodoCLITestWrapper();
  ~TodoCLITestWrapper();

  void refreshList();
  void setAmountOfTestItems(int _amtOfItems);
};

#endif /* end of include guard: TODO_CLI_TEST_WRAPPER_H */
