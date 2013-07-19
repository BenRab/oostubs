/*---------------------------------------------------------------------------*
 * Technical Computer Science II                                             *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *                         T A S K 5                                         *
 *                                                                           *
 *---------------------------------------------------------------------------*/

#ifndef __task5_header__
#define __task5_header__

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */

#include "user/task4.h"

#include <map>
#include <string>

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    CLASSES                      #
\* * * * * * * * * * * * * * * * * * * * * * * * */

/** \brief Fifth test Application 
 *
 * This application shows the usage of blocking system calls to synchornize
 * I/O-operations with individual threads.
 *
 **/
class Task5 : public Task4{
  /** \brief Task specific parameters **/
  enum Parameters
  {
    cmdX = 0, /**< x-coordinate of the commandline**/
    cmdY = 15 /**< y-ccordinate of the commandline**/
  };
  
  /** \brief Command line application
   *
   *  This application delivers command line like behaviour. It supports
   *  printing of a help text, listing available applications as well as
   *  starting and stopping of individual applications.
   *
   **/
  class Cmd : public Application{
    private:
    /** \brief Type definition of the application storage**/
    typedef std::map<std::string, Application*> ApplicationStorage;
    /** \brief Iterator type defintion on the application storage**/
    typedef ApplicationStorage::iterator ApplicationIterator;
    /** \brief Type definition of the application execution storage**/
    typedef std::map<std::string, bool> ExecutionStorage;
    /** \brief Iterator type defintion on the application execution storage**/
    typedef ExecutionStorage::iterator ExecutionIterator;

    /** \brief internal current position of cursor **/
    unsigned short x,y;
    /** \brief buffer of user entered key **/
    std::string buffer;
    /** \brief the application storage **/
    ApplicationStorage apps;
    /** \brief Storage of current execution state for each application **/
    ExecutionStorage appState;
    
    /** \brief Possible commands supported by the commandline **/
    enum Commands
    {
      start, /**< start a registered application**/
      stop,  /**< stop a registered application**/
      list,  /**< list all registered application**/
      help   /**< print a help text**/
    };

  public:
    /** \brief Default constructor
     *
     *  \param x,y initial position of the command line
     **/
    Cmd(unsigned short x, unsigned short y) : x(x),y(y){}
    /** \brief Register an existing application for management
     *
     * \param app the Application to be registered
     * \param name the name used to refer to this application
     **/
    void registerApp(Application& app, const char* name);
    /** \brief Start the command line **/
    virtual void action();
  private:
    /** \brief Parse the internal buffer for commands and parameters **/
    void parseBuffer();
    /** \brief Execute a parsed command
     *
     * \param cmd The Command to be executed
     * \param argPos The position of the next argument in the buffer
     **/
    void handleCommand(Commands cmd, std::size_t argPos);
    /** \brief Parse an argument to an application
     *
     *  \param argPos The position of the argument in the buffer
     *  \param i The iterator pointing to the parsed application
     *  \param j The iterator pointing to the execution state of the application
     *  \return true iff an application was found
     **/
    bool parseApp(std::size_t argPos, ApplicationIterator& i, ExecutionIterator& j);
    /** \brief Start an application
     *
     *  Start the application, which name should be contained in buffer at position argPos.
     *  If the buffer contains no valid application name nothing is done.
     *
     *  \param argPos The position of the application name in the buffer
     **/
    void startApp(std::size_t argPos);
    /** \brief Stop an application
     *
     *  Stop the application, which name should be contained in buffer at position argPos.
     *  If the buffer contains no valid application name nothing is done.
     *
     *  \param argPos The position of the application name in the buffer
     **/
    void stopApp(std::size_t argPos);
    /** \brief list all available applications by name **/
    void listApps();
    /*** \brief print a help text containing possible commands and arguments**/
    void printHelp();
  };
  
  /** \brief An instance of the command line **/
  Cmd cmd;

  public:
  /** \brief Default Constructor **/
	  Task5();
  /** \brief Functionality of the fifth test application
   *
   * Starts the command line and registers the 3 applications inherited from Task4: Counter1, Counter2 and RotatingCursor
   **/
	  virtual void action();
};

#endif
