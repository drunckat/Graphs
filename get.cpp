#include "graph.h"
#define exchange {adjacencyMatrix buffer; transform(buffer, sourceObject); transform(object, buffer);};
//I had many problems with that technique, therefore here is not template-function

void transform(adjacencyMatrix& object, incidenceMatrix& sourceObject)
{
	object.vertex = sourceObject.vertex;

	object.relation = new bool* [object.vertex];
	for (int x = 0; x < object.vertex; x++)
		object.relation[x] = new bool[object.vertex];

	for (int i=0; i<object.vertex; i++)
		for (int j = 0; j < object.vertex; j++)
			object.relation[i][j] = 0;

	for (int i = 0; i < sourceObject.connection; i++)
		for (int j = 0; j < sourceObject.vertex; j++)
		{
			if (sourceObject.relation[i][j])
				for (int m = j+1; m < object.vertex; m++)
				{
					if (sourceObject.relation[i][m])
					{
						object.relation[m][j] = 1;
						object.relation[j][m] = 1;
					}
				}
		}

}
void transform(incidenceMatrix& object, adjacencyMatrix& sourceObject)
{
	int counterConnection = 0;
	object.vertex = sourceObject.vertex;
	object.connection = sourceObject.sumRelation();
	
	object.relation = new bool* [object.connection];
	for (int i = 0; i < object.connection; i++)
	{
		object.relation[i] = new bool[object.vertex];
	}
	for (int i = 0; i < object.vertex; i++)
		for (int j = 0; j < object.connection; j++)
			object.relation[j][i] = 0;

	for (int i = 0; i < sourceObject.vertex; i++)
		for (int j = 0; j <= i; j++)
		{
			if (sourceObject.relation[i][j])
			{
				object.relation[counterConnection][i] = 1;
				object.relation[counterConnection][j] = 1;
				counterConnection++;
			}
		}
}
void transform(KirchhoffMatrix& object, adjacencyMatrix& sourceObject)
{
	int counter;
	object.vertex = sourceObject.vertex;
	object.relation = new int* [object.vertex];
	for (int x = 0; x < object.vertex; x++)
		object.relation[x] = new int[object.vertex];
	for (int i = 0; i < object.vertex; i++)
		for (int j = 0; j < object.vertex; j++)
			object.relation[i][j] = -sourceObject.relation[i][j];
	for (int i = 0; i < object.vertex; i++)
	{
		counter = 0;
		for (int j = 0; j < object.vertex; j++)
			if (object.relation[j][i])
				counter++;
		object.relation[i][i] = counter;
	}
}
void transform(adjacencyMatrix& object, KirchhoffMatrix& sourceObject)
{
	int counter;
	object.vertex = sourceObject.vertex;
	object.relation = new bool* [object.vertex];
	for (int x = 0; x < object.vertex; x++)
		object.relation[x] = new bool[object.vertex];
	for (int i = 0; i < object.vertex; i++)
		for (int j = 0; j < object.vertex; j++)
			if (i == j)
				object.relation[i][j] = 0;
			else
				object.relation[i][j] = sourceObject.relation[i][j];
}
void transform(KirchhoffMatrix& object, incidenceMatrix& sourceObject)
{
	object.vertex = sourceObject.vertex;

	object.relation = new int* [object.vertex];
	for (int x = 0; x < object.vertex; x++)
		object.relation[x] = new int[object.vertex];

	for (int i = 0; i < object.vertex; i++)
		for (int j = 0; j < object.vertex; j++)
			object.relation[i][j] = 0;

	for (int i = 0; i < sourceObject.connection; i++)
	{
		for (int j = 0; j < sourceObject.vertex; j++)
		{
			if (sourceObject.relation[i][j])
				for (int m = j + 1; m < object.vertex; m++)
				{
					if (sourceObject.relation[i][m])
					{
						object.relation[m][j] = -1;
						object.relation[j][m] = -1;
						object.relation[j][j]++;
						object.relation[m][m]++;
					}
				}

		}
	}
}
void transform(adjacencyMatrix& object, listGraph& sourceObject)
{
	object.vertex = sourceObject.items;
	object.relation = new bool* [object.vertex];
	for (int x = 0; x < object.vertex; x++)
		object.relation[x] = new bool[object.vertex];

	for (int i = 0; i < object.vertex; i++)
		for (int j = 0; j < object.vertex; j++)
			object.relation[i][j] = 0;

	for (int i = 0; i < object.vertex; i++)
	{
		sourceObject.beginning = sourceObject.objects[i];
		do
		{
			if (i!= sourceObject.objects[i]->number)
				object.relation[i][sourceObject.objects[i]->number] = 1;
			if (sourceObject.objects[i]->next != NULL)
				sourceObject.objects[i] = sourceObject.objects[i]->next;
		} while (sourceObject.objects[i]->next != NULL);
		if (i != sourceObject.objects[i]->number)
			object.relation[i][sourceObject.objects[i]->number] = 1;
		sourceObject.objects[i] = sourceObject.beginning;
	}
}
void transform(listGraph& object, adjacencyMatrix& sourceObject)
{
	listGraph::vertex* t;
	object.items = sourceObject.vertex;
	object.objects = new listGraph::vertex * [sourceObject.vertex];
	for (int i = 0; i < sourceObject.vertex; i++)
	{
		object.objects[i] = new listGraph::vertex;
		object.objects[i]->number = i;
		t = object.objects[i];
		for (int j = 0; j < sourceObject.vertex; j++)
		{
			if (sourceObject.relation[i][j])
			{
				object.objects[i]->next = new listGraph::vertex;
				object.objects[i] = object.objects[i]->next;
				object.objects[i]->number = j;
			}
		}
		object.objects[i] = t;
	}
}
void transform(adjacencyMatrix& object, algebraicForm& sourceObject)
{
	object.vertex = sourceObject.vertex;

	object.relation = new bool* [object.vertex];
	for (int x = 0; x < object.vertex; x++)
		object.relation[x] = new bool[object.vertex];

	for (int i = 0; i < object.vertex; i++)
		for (int j = 0; j < object.vertex; j++)
			object.relation[i][j] = 0;

	for (int i = 0; i < sourceObject.edges; i ++)
	{
		object.relation[sourceObject.edge[i].vertex1][sourceObject.edge[i].vertex2] = 1;
		object.relation[sourceObject.edge[i].vertex2][sourceObject.edge[i].vertex1] = 1;
	}
}
void transform(algebraicForm& object, adjacencyMatrix& sourceObject)
{
	object.vertex = sourceObject.vertex;

	object.edge = new algebraicForm::connection [sourceObject.sumRelation()];
	object.edges = sourceObject.sumRelation();
	for (int x = 0; x < sourceObject.sumRelation(); x++)
	{
		object.edge[x].vertex1 = -1;
		object.edge[x].vertex2 = -1;
	}
	int counter = 0;
	for (int i = 0; i < object.vertex; i++)
		for (int j = 0; j <= i; j++)
		{
			if (sourceObject.relation[i][j])
			{
				object.edge[counter].vertex1 = i;
				object.edge[counter].vertex2 = j;
				counter++;
			}
		}

}
void transform(adjacencyMatrix& object, myForm& sourceObject)
{
	object.vertex = sourceObject.vertexes;
	object.relation = new bool* [object.vertex];
	for (int x = 0; x < object.vertex; x++)
		object.relation[x] = new bool[object.vertex];

	for (int i = 0; i < object.vertex; i++)
		for (int j = 0; j < object.vertex; j++)
			object.relation[i][j] = 0;
	for (int i = 0; i < sourceObject.vertexes; i++)
	{
		for (int j = 0; j < sourceObject.nodes[i].n_counter; j++)
		{
			if (i == sourceObject.nodes[i].neighbors[j])
				continue;
			object.relation[i][sourceObject.nodes[i].neighbors[j]] = 1;
			object.relation[sourceObject.nodes[i].neighbors[j]][i] = 1;
		}
	}
}
void transform(myForm& object, adjacencyMatrix& sourceObject)
{
	object.edges = sourceObject.sumRelation();
	myForm::vertex T;
	object.vertexes = sourceObject.vertex;
	object.nodes.insert(object.nodes.begin(), sourceObject.vertex, T);
	for (int i = 0; i < sourceObject.vertex; i++)
	{
		for (int j = i; j < sourceObject.vertex; j++)
		{
			if (sourceObject.relation[i][j])
			{
				object.nodes[i].neighbors.push_back(j);
				object.nodes[j].neighbors.push_back(i);
				object.nodes[i].n_counter++;
				object.nodes[j].n_counter++;
			}
		}
	}
	object.sortForm();
}

void transform(incidenceMatrix& object, KirchhoffMatrix& sourceObject) exchange
void transform(incidenceMatrix& object, listGraph& sourceObject) exchange
void transform(incidenceMatrix& object, algebraicForm& sourceObject) exchange
void transform(incidenceMatrix& object, myForm& sourceObject) exchange

void transform(KirchhoffMatrix& object, algebraicForm& sourceObject) exchange
void transform(KirchhoffMatrix& object, listGraph& sourceObject) exchange
void transform(KirchhoffMatrix& object, myForm& sourceObject) exchange

void transform(listGraph& object, KirchhoffMatrix& sourceObject) exchange
void transform(listGraph& object, listGraph& sourceObject) exchange
void transform(listGraph& object, algebraicForm& sourceObject) exchange
void transform(listGraph& object, myForm& sourceObject) exchange

void transform(algebraicForm& object, KirchhoffMatrix& sourceObject) exchange
void transform(algebraicForm& object, listGraph& sourceObject) exchange
void transform(algebraicForm& object, incidenceMatrix& sourceObject) exchange
void transform(algebraicForm& object, myForm& sourceObject) exchange

void transform(myForm& object, KirchhoffMatrix& sourceObject) exchange
void transform(myForm& object, listGraph& sourceObject) exchange
void transform(myForm& object, incidenceMatrix& sourceObject) exchange
void transform(myForm& object, algebraicForm& sourceObject) exchange
