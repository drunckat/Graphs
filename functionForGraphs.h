#pragma once
#include "graph.h"
void transform(adjacencyMatrix&, incidenceMatrix&);
void transform(adjacencyMatrix&, KirchhoffMatrix&);
void transform(adjacencyMatrix&, listGraph&);
void transform(adjacencyMatrix&, algebraicForm&);
void transform(adjacencyMatrix&, myForm&);
void transform(incidenceMatrix&, adjacencyMatrix&);
/*add*/
void transform(incidenceMatrix&, KirchhoffMatrix&);
void transform(incidenceMatrix&, listGraph&);
void transform(incidenceMatrix&, algebraicForm&);
void transform(incidenceMatrix&, myForm&);
/*no add*/
void transform(KirchhoffMatrix&, adjacencyMatrix&);
void transform(KirchhoffMatrix&, incidenceMatrix&);
/*add*/
void transform(KirchhoffMatrix&, algebraicForm&);
void transform(KirchhoffMatrix&, listGraph&);
void transform(KirchhoffMatrix&, myForm&&);
/*no add*/
void transform(listGraph&, adjacencyMatrix&);
/*add*/
void transform(listGraph&, KirchhoffMatrix&);
void transform(listGraph&, listGraph&);
void transform(listGraph&, algebraicForm&);
void transform(listGraph&, myForm&);
/*no add*/
void transform(algebraicForm&, adjacencyMatrix&);
/*add*/
void transform(algebraicForm&, KirchhoffMatrix&);
void transform(algebraicForm&, listGraph&);
void transform(algebraicForm&, incidenceMatrix&);
void transform(algebraicForm&, myForm&);
/*no add*/
void transform(myForm&, adjacencyMatrix&);
/*add*/
void transform(myForm&, KirchhoffMatrix&);
void transform(myForm&, listGraph&);
void transform(myForm&, incidenceMatrix&);
void transform(myForm&, algebraicForm&);