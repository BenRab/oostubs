#include "user/appl.h"

/** \brief Fourth test application
 *
 * Showing the functionality of coroutine scheduling, by starting 3 coroutine
 * based applications.
 **/
class Task4 : public Application{
	private:

enum Constants{
	rotCursorX=79,
	rotCursorY=0,
	counter1X=10,
	counter1Y=10,
	counter2X=10,
	counter2Y=15,
};
    bool coop;

/** \brief %Rotating symbol application
 *
 * This coroutine creates a rotating symbol in the upper left corner of the
 * screen, to show "quasi"-parallel execution of coroutines
 **/
class RotCursor : public Application
{
	private:
		/**\brief internal state to save current symbol **/
		unsigned char i;
		unsigned short x, y;
        bool coop;
        
        void enableCoop(){coop=true;}
	public:
		/** \brief Default constructor
		 *
		 * Setting the start symbol
		 **/
		RotCursor(unsigned short x, unsigned short y);

		/** \brief start outputting the symbol
		 *
		 * This method resumes after each interation
		 **/
		virtual void action();
    friend class Task4;
};

/** \brief Counting application
 *
 * This coroutine counts a value on a fixed position on the screen
 **/
class Counter : public Application
{
	private:
		/** \brief current counter value **/
		unsigned int i;
		unsigned short x, y;
        bool coop;

        void enableCoop(){coop=true;}
	public:
		/** \brief Default constructor
		 *
		 * Setting the counter to 0
		 **/
		Counter(unsigned short x, unsigned short y);

		/** \brief start outputting and incrementing the counter value
		 *
		 * This method resumes after each interation
		 **/
		virtual void action();

   friend class Task4;
};

		/** \brief Application for a rotating symbol **/
		RotCursor rotCursor;
		/** \brief Application for a printed out counter **/
		Counter counter1;
		/** \brief Application for a printed out counter **/
		Counter counter2;

	public:
		/** \brief Default Constructor 
		 *
		 * Setting the applications up
         *
         * \param coop enables or disables cooperative multitasking
		 **/
		Task4(bool coop);

		/** \brief start operation
		 *
		 * registers the applications with the scheduler and exit afterwards
		 **/
		virtual void action();
};
