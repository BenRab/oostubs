/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                       K E Y B O A R D                                         * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include <sstream>
#include <iostream>

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * \~english
 * \brief Post-mortem log to track debugging information
 *
 * The log can be written to like an STL ostream object(cout). However compared
 * to kout it allows not color specification and all manipulators need to be
 * prefixed with std:: (std::endl, std::hex ...).
 *
 **/
class Log : public std::stringstream
{
    public:
    /**
     * \~english
     * \brief Post-mortem debug Destructor
     *
     * Prints the log's content to the terminal after termination of the operating system.
     **/
    ~Log()
    {
        std::cout << str();
    }
};
