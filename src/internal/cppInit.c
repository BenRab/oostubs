/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                 Technische Informatik II                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                               *
 *                                   C P P I N I T                                               *
 *                                                                                               *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

typedef void(*ConstructorPointer)() ;
typedef void(*DestructorPointer)() ;

extern ConstructorPointer ConstructorListStart;
extern ConstructorPointer ConstructorListEnd;
extern DestructorPointer DestructorListStart;
extern DestructorPointer DestructorListEnd;

/**
 * 
 */
void constructObjects () {
  ConstructorPointer* start=&ConstructorListStart;
  ConstructorPointer* end  =&ConstructorListEnd;

  while(start<end)
      (*start++)();
}

/**
 * 
 */
void destructObjects () {
  DestructorPointer* start=&DestructorListStart;
  DestructorPointer* end  =&DestructorListEnd;

  while(start<end)
      (*start++)();
}

