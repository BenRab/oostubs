/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                      T A S K 3 A                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "user/task3A.h"
#include "object/fixedPointNumber.h"

#include "useful/kout.h"
#include "useful/cpu.h"
#include "useful/keyboard.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                   FUNCTIONS                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
Task3A::Task3A() : Application(){
  kout.setpos(31,1);
  kout << "OOStuBs - Task 3A" << endl << endl;
  
  keyboard.plugin();
  cpu.enable_int();
}

Task3A::~Task3A(){
  
  cpu.disable_int();
}


void Task3A::testFPN(){
  //Var init
  SFixedPointNumber x,y;
  
  /* * * * * * * * * * * * * * * * * * * *\
  #  Normale Zahl                         #
  \* * * * * * * * * * * * * * * * * * * */
  x = genFPN(7, 250); //7.25
  y = genFPN(1,  10); //1.01  ACHTUNG 010 ist oktal, also 8 dez.; ACHTUNG nur rund 1.01
  
  kout << "tests with fixed point arithmetic" << endl;
  kout << "x: " << x << endl;
  kout << "y: " << y << endl;
}

void Task3A::testFPNAdd(){
  //Var init
  SFixedPointNumber x,y;
  
  /* * * * * * * * * * * * * * * * * * * *\
  #  Addition                             #
  \* * * * * * * * * * * * * * * * * * * */
  x = genFPN(-1,002);  //ACHTUNG Werte sind oktal
  y = genFPN(1,002);
  kout << "x: " << x << ", y: " << y << ", x+y: " << (x+y) << endl;
  x = genFPN(-1,002);
  y = genFPN(1,001);
  kout << "x: " << x << ", y: " << y << ", x+y: " << (x+y) << endl;
  x = genFPN(-1,002);
  y = genFPN(1,003);
  kout << "x: " << x << ", y: " << y << ", x+y: " << (x+y) << endl;
}

void Task3A::testFPNMul(){
  //Var init
  SFixedPointNumber x,y;
  
  /* * * * * * * * * * * * * * * * * * * *\
  #  Multiplikation                       #
  \* * * * * * * * * * * * * * * * * * * */
  x = genFPN(-1,500);
  y = genFPN(1,500);
  kout << "x: " << x << ", y: " << y << ", x*y: " << (x*y) << endl;
  x = genFPN(1,500);
  y = genFPN(1,500);
  kout << "x: " << x << ", y: " << y << ", x*y: " << (x*y) << endl;
  x = genFPN(-1, 0,500);
  y = genFPN(-1, 0,500);
  kout << "x: " << x << ", y: " << y << ", x*y: " << (x*y) << endl;
}

void Task3A::testFPNDiv(){
  //Var init
  SFixedPointNumber x,y;
  
  /* * * * * * * * * * * * * * * * * * * *\
  #  Division                             #
  \* * * * * * * * * * * * * * * * * * * */
  x = genFPN(-1, 0,500);
  y = genFPN(-1, 0,500);
  kout << "x: " << x << ", y: " << y << ", x/y: " << (x/y) << endl;
  x = genFPN(1,500);
  y = genFPN(0,500);
  kout << "x: " << x << ", y: " << y << ", x/y: " << (x/y) << endl;
  x = genFPN(0,500);
  y = genFPN(1,500);
  kout << "x: " << x << ", y: " << y << ", x/y: " << (x/y) << endl;
}

void Task3A::testFPNPow(){
  //Var init
  SFixedPointNumber x,y;
  
  /* * * * * * * * * * * * * * * * * * * *\
  #  Potenz                               #
  \* * * * * * * * * * * * * * * * * * * */
  x = genFPN(2,000);
  y = genFPN(2,000);
  kout << "x: " << x << ", y: " << y << ", x^y: " << (x^y) << endl;
  x = genFPN(4,000);
  y = genFPN(4,000);
  kout << "x: " << x << ", y: " << y << ", x^y: " << (x^y) << endl;
  x = genFPN(3,000);
  y = genFPN(2,000);
  kout << "x: " << x << ", y: " << y << ", x^y: " << (x^y) << endl;
  x = genFPN(0,500);
  y = genFPN(1,500);
  kout << "x: " << x << ", y: " << y << ", x^y: " << (x^y) << endl;
  x = genFPN(1,500);
  y = genFPN(0,500);
  kout << "x: " << x << ", y: " << y << ", x^y: " << (x^y) << endl;
}

void Task3A::testFPNSqrt(){
  //Var init
  SFixedPointNumber x,y;
  
  /* * * * * * * * * * * * * * * * * * * *\
  #  Quadrahtwurzel                       #
  \* * * * * * * * * * * * * * * * * * * */
  x = genFPN(1,500);
  kout << "x: " << x << ", sqrt(x): " << x.sqrt() << endl;
  x = genFPN(0,250);
  kout << "x: " << x << ", sqrt(x): " << x.sqrt() << endl;
  x = genFPN(133546,345);
  kout << "x: " << x << ", sqrt(x): " << x.sqrt() << endl;
  x = genFPN(0,  1);
  kout << "x: " << x << ", sqrt(x): " << x.sqrt() << endl;
  x = genFPN(0, 10);
  kout << "x: " << x << ", sqrt(x): " << x.sqrt() << endl;
  x = genFPN(0, 65);
  kout << "x: " << x << ", sqrt(x): " << x.sqrt() << endl;
}



/** \brief first part of task 3
 * 
 * <hr>
 * <h2>Ausgabenstellung</h2> 
 * 
 * In dieser Teil-Aufgabe geht es um die Analyse eines Prozedurestacks für eine Hardware-Exception.
 * Diese funktion produziert einen Fehler. Aber anstatt dass die Funktion \ref handleException
 * aufgerufen wird, wird die Funktion \ref analyseException aufgerufen. Sie dient der Analyse.
 * 
 * Als Parameter enthält sie einen Zeiger auf einen Stack. Dieser ist aufgebaut als wäre die
 * Funktion \ref handleException aufgerufen worden, es ist allerding noch keine einzelne Zeile 
 * davon abgearbeitet worden. In Folge dessen hat die Funktion \ref handleException den Stack
 * noch nicht verändert.
 * 
 * Geben Sie in der Funktion analyseException die ersten 24 Byte vom Stack in hexadezimaler Form 
 * in Blöcken von je vier Byte aus.
 * Geben Sie diesen Daten eine Bedeutung.
 * Welcher Fehler ist aufgetreten?
 * In welcher cc-Datei, in welcher Zeile ist der Fehler aufgetreten? Der GDB-Befehl 
 * "l *[Adresse]" könnte sich dafür als nützlich erweisen.
 * Woran könnte es liegen, dass dieser Fehler aufgetreten ist?
 * 
 * Wie ist der Stack bei einer x86 CPU-Exception normalerweise aufgebaut? 
 * Welche Daten befinden sich auf diesem in welcher Reihenfolge?
 * Was sind traps, faults und was aborts? Worin unterscheiden sie sich?
 * 
 * <hr>
 * 
 */
void Task3A::action(){
  testFPN();
  testFPNAdd();
  testFPNMul();
  testFPNDiv();
  testFPNPow();
  testFPNSqrt();
}
