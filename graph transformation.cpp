
#include <iostream>
#include "graph.h"
#include "functionForGraphs.h"
using namespace std;


int main()
{
    int counter;

    cout << "=====FIRST POINT=====\n";
    cout << "Enter quantity of vertexes: ";
    cin >> counter;
    incidenceMatrix iMatrix;
    KirchhoffMatrix kMatrix;
    adjacencyMatrix aMatrix;
    algebraicForm aForm;
    iMatrix.fillRandom(counter);
    transform(kMatrix, iMatrix);
    transform(aMatrix, kMatrix);
    transform(aForm, aMatrix);
    iMatrix.showMatrix();
    kMatrix.showMatrix();
    aMatrix.showMatrix();
    aForm.showForm();
    system("Pause>NULL");
    system("cls");

    cout << "=====SECOND POINT=====\n";
    cout << "=====VARIANT    4=====\n";
    cout << "Enter graph";
    listGraph graphV4;
    graphV4.introduce();
    graphV4.showList();
    cout <<endl<< "Parts: "<< graphV4.BFSforSeparatedParts()<<endl;
    system("Pause>NULL");
    system("cls");
    cout << "=====VARIANT    3=====\n";
    listGraph graphV3;
    cout << "Enter graph";
    graphV3.introduce();
    graphV3.showList();
    graphV3.BFSforRadiusAndDiameter();
    system("Pause>NULL");
    system("cls");
     cout << "=====VARIANT    2=====\n";
    graphV3.showList();
    graphV3.DFSfromXtoY();
    system("Pause>NULL");
     cout << "=====VARIANT    1=====\n";
    graphV3.DFSpass();
/*
    myForm graph;
    adjacencyMatrix A;
    graph.fillRandom(10);
    transform(A, graph);
    A.showMatrix();
    A.Melgrange();*/
    system("Pause>NULL");
    system("cls");
    return 0;
}
