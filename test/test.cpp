#include <iostream>             // for cout
#include <vector>

#include "commander.hpp"        // the commander++ api

/**
 * test.cpp - exercise the commander++ api
 *
 * The `MyCommand` class derives from `Command` and specifies command option
 * callbacks which set member variables based on command line options.
 */

using namespace std;

/**
 * An external option callback
 *
 * Deal with a command line switch that may or may not have an associated
 * argument.
 *
 * For simple use cases you may not need a custom `Command` class.  If so you
 * can pass callbacks along the following line to `Command.option()`.
 */
static void
optional(command_t *self) {
  if (self->arg != NULL) {
    cout << "Optional: " << self->arg << endl;
  } else {
    cout << "Optional: enabled" << endl;
  }
}

/**
 * A custom MyCommand class deriving from the base Command
 *
 * This contains private members which are set by static member functions.
 */
class MyCommand : public Command {
public:
  // A constructor setting appropriate defaults
  MyCommand(const char *name, const char *version, bool verboseEnabled = false) :
    Command(name, version),
    verboseEnabled(verboseEnabled),
    required(NULL)
  {}

  /**
   * An option callback setting the verbose flag
   */
  static void
  setVerbose(command_t *command) {
    static_cast<MyCommand *>(Command::self(command))->verboseEnabled = true;
  }

  /**
   * An option callback setting the required value
   */
  static void
  setRequired(command_t *command) {
    static_cast<MyCommand *>(Command::self(command))->required = command->arg;
  }

  /**
   * Get the required value
   */
  const char *
  getRequired() {
    return required;
  }  

  /**
   * Get the verbosity setting
   */
  bool
  isVerbose() {
    return verboseEnabled;
  }
  
private:
  // members set by the option callbacks
  bool verboseEnabled;
  const char* required;
};


int main(int argc, char *argv[]) {
  // Instantiate the command with program name and version strings
  MyCommand command = MyCommand(argv[0], "0.0.1");

  // optionally set a more descriptive usage string
  command.setUsage("[options] [ARG1 [ARG2 [ARG3]]");

  // Set the various options
  command.option("-v", "--verbose", "enable verbose stuff", MyCommand::setVerbose);
  command.option("-r", "--required <arg>", "required arg", MyCommand::setRequired);
  command.option("-o", "--optional [arg]", "optional arg", optional);

  // Parse the arguments
  command.parse(argc, argv);

  // Get and print any additional arguments specified after the callbacks
  std::vector<const char *> args = command.additionalArgs();

  if (args.size() > 3) {
    cerr << "Too many command line arguments were specified" << endl;
    command.help();                 // this exits the program

  } else if (args.size()) {
    cout << "Additional args:" << endl;
    for (vector<const char *>::iterator it = args.begin(); it != args.end(); ++it) {
      cout << "  - '" << *it << "'" << endl;
    }

  } else {
    cout << "No additional args" << endl;
  }

  // If a required option is set, output it
  if (command.getRequired() != NULL) {
    cout << "Required is: " << command.getRequired() << endl;
  }

  // Output the verbosity setting
  cout << "Verbose status is " << ((command.isVerbose()) ? "enabled" : "disabled") << endl;

  return 0;
}
