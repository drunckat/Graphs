#pragma once
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>

using namespace std;

struct adjacencyMatrix
{
	int vertex=0;
	bool **relation;

	void showMatrix()
	{
		cout << endl;
		cout << "     ";
		for (int x = 0; x < vertex; x++)
		{
			cout << "  x";
			printf("%-2i", x);
			cout << " ";
		}
		for (int x = 0; x < vertex; x++)
		{
			cout << endl << " x" << x << " ";
			for (int j = 0; j < vertex; j++)
			{
				cout << "  ";
				printf("%3i", relation[j][x]);
				cout << " ";
			}
		}
	}
	void fillRandom(int n)
	{
		srand(time(NULL));
		relation = new bool* [n];
		for (int x = 0; x < n; x++)
			relation[x] = new bool[n];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				relation[i][j] = 0;

		for (int i=0; i<n; i++)
			for (int j = 0; j < i; j++)
			{
					relation[i][j] = rand() % 2;
					relation[j][i] = relation[i][j];
			}
		vertex = n;
	}
	int sumRelation()
	{
		int counter = 0;
		for (int i=0; i<vertex; i++)
			for (int j = 0; j <= i; j++)
				if (relation[i][j])
					counter++;
		return counter;
	}
	~adjacencyMatrix()
	{
		for (int i = 0; i < vertex; i++)
		{
			delete[] relation[i];
		}
	}
	void Melgrange()
	{
		struct combination
		{
			vector<int> lines;
			vector<int> columns;
			
			//A<=B
			combination()
			{
			}
			combination(int i)
			{
				lines.push_back(i);
			}
			combination(const combination& copy)
			{
				this->lines = copy.lines;
				this->columns = copy.columns;
			}
			combination& operator= (const combination& CopySource)
			{
				this->lines = CopySource.lines;
				this->columns = CopySource.columns;
				return *this;
			}
			combination& operator+= (const combination& compare)//overload operator += for U
			{
				int key;
				for (int i = 0; i < compare.lines.size(); i++)
				{
					this->lines.push_back(compare.lines[i]);//unite lines
				}
				for (int i = 0; i < this->columns.size(); i++)
				{
					key = 0;
					for (int j = 0; j < compare.columns.size(); j++)
					{
						if (compare.columns[j] == this->columns[i])
						{
							key = 1;
							break;
						}
					}
					if (!key)
					{
						this->columns.erase(i + this->columns.begin()); //it ramains only crossing of columns
					}
				}
				sort(this->lines.begin(), this->lines.end());
				this->lines.erase(std::unique(this->lines.begin(), this->lines.end()), this->lines.end()); //delete duplicates
				return *this;
			}
			combination& operator-= (const combination& compare) //overload operator -= for func crossing
			{
				int key;
				for (int i = 0; i < compare.columns.size(); i++)
				{
					this->columns.push_back(compare.columns[i]);  //unite columns
				}
				for (int i = 0; i < this->lines.size(); i++)
				{
					key = 0;
					for (int j = 0; j < compare.lines.size(); j++)
					{
						if (compare.lines[j] == this->lines[i])
						{
							key = 1;
							break;
						}
					}
					if (!key)
					{
						this->lines.erase(this->lines.begin() + i); //it remains only crossing of lines
					}
				}
				sort(this->columns.begin(), this->columns.end());
				this->columns.erase(std::unique(this->columns.begin(), this->columns.end()), this->columns.end()); //delete duplicates
				return *this;
			} 
			bool operator<= ( combination& compare)//it's overload operator == is necessary to compare combinations
			{
				sort(compare.lines.begin(), compare.lines.end());  //it is not necessary, just makes comparison more comfortable
				sort(compare.columns.begin(), compare.columns.end());

				sort(this->lines.begin(), this->lines.end());
				sort(this->columns.begin(), this->columns.end());

				bool key = 0;
				
				for (int i = 0; (i != this->lines.size()); i++)
				{
					for (int j = 0, key=0; (j != compare.lines.size()); j++)
					{
						if (this->lines[i] == compare.lines[j])
						{
							key = 1;
							break;
						}
					}
				}
				if (key == 0)
					return 0;
				for (int i = 0; (i != this->columns.size()); i++)
				{
					for (int j = 0, key = 0; (j != compare.columns.size()); j++)
					{
						if (this->columns[i] == compare.columns[j])
						{
							key = 1;
							break;
						}
					}
				}
				return key;
			}
			bool operator== ( combination& compare)//it's overload operator == is necessary to compare combinations
			{
				sort(compare.lines.begin(), compare.lines.end());  //it is not necessary, just makes comparison more comfortable
				sort(compare.columns.begin(), compare.columns.end());

				sort(this->lines.begin(), this->lines.end());
				sort(this->columns.begin(), this->columns.end());
				bool key = ((this->lines.size()== compare.lines.size()) and (this->columns.size() == compare.columns.size()));
				if (!key)
					return 0;
				for (int i = 0; i < this->lines.size(); i++)
				{
					if (this->lines[i] != compare.lines[i])
					{
						key = 0;
						break;
					}
				}
				if (!key)
					return 0;
				for (int i = 0; i < this->columns.size(); i++)
				{
					if (this->columns[i] != compare.columns[i])
					{
						key = 0;
						break;
					}
				}
				return key;
			}
			bool full()
			{
				return (lines.empty() and columns.empty());  //if one of them is empty we can drop this combination;
			}
			bool columnsAreLikeLines()
			{
				sort(this->lines.begin(), this->lines.end());
				sort(this->columns.begin(), this->columns.end());
				int key = 0;
				if (!(columns.size() == lines.size()))
					return key;
				else
				{
					for (int i = 0, key=1; i < columns.size(); i++)
					{
						if (columns[i] != lines[i])
							key = 0;
						break;
					}
				}
				return key;
			}
		};
		combination T;
		vector<combination> family(vertex);
		vector<combination> copy/*(vertex)*/;
		for (int i = 0; i < vertex; i++)
		{
			family[i].lines.push_back(i);
			for (int j = 0; j < vertex; j++)
			{
				if (!relation[i][j])
					family[i].columns.push_back(j);
			}
			copy.push_back(family[i]);

		}
		int key=0;
		do
		{
			for (int i = 0; i < copy.size(); i++) //we will find all combinations
			{
				for (int j = i+1; j < copy.size(); j++)
				{
					T = copy[i];
					T += copy[j];
					family.push_back(T);
					if (T.full())
					{
						family.push_back(T);
					}
					T = copy[i];
					T -= copy[j];
					if (T.full())
					{
						family.push_back(T);
					}
				}
			}
			
			for (int i = 0; i < copy.size(); i++) //and now we delete duplicates and subArray
			{
				for (int j = 0; j < copy.size(); j++)
				{
					if (i == j) continue;
					if ((family[i] <= family[j]) or !family[i].full())
					{
						family.erase(family.begin() + i);
					}
				}
			}
			key = 1;
			if (family.size()==copy.size())
			for (int i = 0; i < family.size(); i++)
			{
				key = 1;
				for (int j = 0; j < copy.size(); j++)
				{
					key = !(family[i] == copy[j]);
					if (!key)
						break;
				}
				if (key)
					break;
			}
			copy = family;
			/*
			for (int i = 0; i < family.size(); i++)
			{
				{
					cout << endl;
					for (int j = 0; j < family[i].lines.size(); j++)
					{
						cout << family[i].lines[j] << " ";
					}
					cout << "| ";
					for (int j = 0; j < family[i].columns.size(); j++)
					{
						cout << family[i].columns[j] << " ";
					}
				}
			}*/
			cout << endl<<"iteration ends"<<endl;

		} while (key);
		
		for (int i = 0; i < family.size(); i++)
		{
			if (family[i].columnsAreLikeLines())
			{
				cout<<endl;
				for (int j = 0; j < family[i].lines.size(); j++)
				{
					cout << family[i].lines[j] << " ";
				}
			}
		}
		cout << endl;
	}
};
struct incidenceMatrix
{
	int vertex = 0;
	int connection = 0;
	bool** relation;

	void showMatrix()
	{
		cout << endl;
		cout << "     ";
		for (int x = 0; x < connection; x++)
		{
			cout << "  u";
			printf("%-2i", x);
			cout << " ";
		}
		for (int x = 0; x < vertex; x++)
		{
			cout << endl << " x" << x << " ";
			for (int j = 0; j < connection; j++)
			{
				cout << "  ";
				printf("%3i", relation[j][x]);
				cout << " ";
			}
		}
	}
	bool connectionDone(int j)
	{
		int sum = 0;
		for (int i = 0; i < vertex; i++)
		{
			if (relation[j][i])
				sum++;
		}
		if (sum >= 2)
			return 1;
		else
			return 0;
	}

	void fillRandom(int n)
	{
		int counter;
		srand(time(NULL));
		vertex = n;
		int randomNumber1=0, randomNumber2=0;
		connection = rand()% (n * (n - 1) / 2 + 1);
		
		relation = new bool* [connection];
		for (int x = 0; x < connection; x++)
			relation[x] = new bool[n];

		for (int i = 0; i < connection; i++)
			for (int j = 0; j < n; j++)
				relation[i][j] = 0;

		for (int i = 0; i < connection; i++)
		{
			do 
			{
				counter=0;
				do
				{
					randomNumber1 = abs(rand() % n);
					randomNumber2 = abs(rand() % n);
				} while (randomNumber1 == randomNumber2);

				for (int subI = 0; subI < i; subI++)
				{
					if (relation[subI][randomNumber1] and relation[subI][randomNumber2]) 
						counter++;
				}
			} while(counter);

			relation[i][randomNumber1] = 1;
			relation[i][randomNumber2] = 1;
		}
	}
	~incidenceMatrix()
	{
		for (int i = 0; i < connection; i++)
		{
			delete[] relation[i];
		}
	}
};
struct KirchhoffMatrix
{
	int vertex = 0;
	int** relation;

	void showMatrix()
	{
		cout << endl;
		cout << "     ";
		for (int x = 0; x < vertex; x++)
		{
			cout << "  x";
			printf("%-2i", x);
			cout << " ";
		}
		for (int x = 0; x < vertex; x++)
		{
			cout << endl << " x" << x << " ";
			for (int j = 0; j < vertex; j++)
			{
				cout << "  ";
				printf("%3i", relation[j][x]);
				cout << " ";
			}
		}
	}

	void fillRandom(int n)
	{
		int counter;
		srand(time(NULL));
		relation = new int* [n];

		for (int x = 0; x < n; x++)
			relation[x] = new int[n];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				relation[i][j] = 0;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < i; j++)
			{
				relation[i][j] = -(rand() % 2);
				relation[j][i] = relation[i][j];
			}
		for (int i = 0; i < n; i++)
		{
			counter = 0;
			for (int j = 0; j < n; j++)
				if (relation[j][i])
					counter++;
			relation[i][i] = counter;
		}
		vertex = n;
	}
	~KirchhoffMatrix()
	{
		for (int i = 0; i < vertex; i++)
		{
			delete[] relation[i];
		}
	}
};
struct listGraph
{
	int items;
	struct vertex
	{
		int mark = 0;
		int number;
		vertex* next = nullptr;
		~vertex()
		{
			if (next != NULL)
			delete next;
		}
	};
	vertex** objects;
	vertex* beginning;

	void fillRandom(int n)
	{
		srand(time(NULL));
		items = n;
		int randomGraph, randomNumber, counter=0;
		objects = new vertex*[n];
		for (int i = 0; i < n; i++)
			objects[i] = new vertex;

		vertex* tPointer;

		int* collections = new int[n*n];

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				collections[i*n+j] = -1;

		int* countersCollections = new int[n];

		for (int i = 0; i < n; i++)
		{
			collections[i*n] = i;
			countersCollections[i] = 1;
		}
		for (int i = 0; i < n; i++)
		{
			randomNumber = rand() % n;
			for (; countersCollections[i] < randomNumber;)
			{
				do
				{
					randomGraph = rand() % n;
					for (int l = 0; l < n; l++)
					{
						counter = 0;
						if (collections[i*n+l] == randomGraph)
						{
							counter++;
							break;
						}
					}
				} while (counter);
				collections[i*n+countersCollections[i]] = randomGraph;
				countersCollections[i]++;

				counter = 0;
				for (int l = 0; l < countersCollections[randomGraph]; l++)
				{
					if (collections[randomGraph * n + l] == i)
					{
						counter++;
						break;
					}
				}
				if (!counter)
				{
					collections[randomGraph * n + countersCollections[randomGraph]] = i;
					countersCollections[randomGraph]++;
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			tPointer = objects[i];
			for (int j = 0; j < countersCollections[i]; j++)
			{
				objects[i]->number = collections[i*n+j];
				if (j!= (countersCollections[i]-1))
				{
					objects[i]->next = new vertex;
					objects[i] = objects[i]->next;
				}
			}
			objects[i] = tPointer;
		}

		delete[] countersCollections;
		delete[] collections;
	}
	void introduce()
	{
		int n, t;
		do
		{
			cout << "\nEnter number of vertexes: ";
			cin >> n;
		} while (n < 1);
		items = n;
		objects = new vertex * [n];
		vertex** pointer = new vertex* [n];
		for (int i = 0; i < n; i++)
		{
			objects[i] = new vertex;
			pointer[i] = objects[i];
			objects[i]->number = i;
		}

		for (int i = 0; i < n; i++)
		{
			do
			{
				objects[i] = pointer[i];
				do
				{
					cout << "Enter the number of the neighboring of X[" << i << "] vertex(-1 is exit): ";
					cin >> t;
				} while (t == i);
				if ((t >= n) or (t < 0))
					break;

				if (objects[i]->next != NULL)
				{
					do
					{
						objects[i] = objects[i]->next;
						if (objects[i]->number == t)
						{
							objects[i] = pointer[i];
							t = -1;
							break;
						}
					} while (objects[i]->next != NULL);
				}

				if (t == -1)
				{
					continue;
				}
				else
				{
					objects[i]->next = new vertex;
					objects[i] = objects[i]->next;
					objects[i]->number = t;
					
					while (objects[t]->next != NULL)
					{
						if (objects[t]->number == i)
						{
							t = -1;
							break;
						}
						objects[t] = objects[t]->next;
					}
					if (t != -1)
					{
						objects[t]->next = new vertex;
						objects[t] = objects[t]->next;
						objects[t]->number = i;
					}
					objects[t] = pointer[t];
				}
			} while (1);
			objects[i] = pointer[i];
		}
		delete[]pointer;
	}
	void showList()
	{
		for (int j = 0; j < items; j++)
		{
			beginning = objects[j];
			cout << endl;
			for (int i = 0;  objects[j]->next != NULL; i++)
			{
				if (i)
					cout << "->";
				cout << objects[j]->number;

				objects[j] = objects[j]->next;
			}
			if (objects[j]->number!=j)
				cout<< "->";
			cout << objects[j]->number;
			objects[j] = beginning;
		}
		cout << endl;
	}
	int sumRelations()
	{
		vertex* pointer;
		int sum = 0;
		for (int i = 0; i < items; i++)
		{
			pointer = objects[i];
			for (; objects[i]!= NULL;)
			{
				if (objects[i]->number>pointer->number)
					sum++;
				objects[i] = objects[i]->next;
			}
			objects[i] = pointer;
		}
		return sum;
	}
	void transformInEdgeGraph()
	{
		int n = sumRelations(), j;
		vertex** edges = new vertex*[n];
		vertex** pointer = new vertex*[n];
		vertex* p;
		int* number = new int[n * 2];
		for (int i = 0; i < n; i++)
		{
			edges[i] = new vertex;
			edges[i]->number = i;
			pointer[i] = edges[i];
		}
		j = 0;
		for (int i = 0; i < items; i++)
		{
			p= objects[i];
			for (; (objects[i]->next != nullptr) and (j!=n);)
			{
				if (objects[i]->next->number > i)
				{
					number[j * 2] = i;
					number[j * 2 + 1] = objects[i]->next->number;
					j++;
					
				}
				objects[i] = objects[i]->next;
			}
			objects[i]=p;
		}
		for (int j=0; j<n; j++)
			cout << "\n" << j << " (" << number[j * 2] << ", " << number[j * 2 + 1] << ")";
		for (int i = 0; i < items; i++)
		{
			delete objects[i];
		}
		delete[]objects;

		for (int i = 0; i < n; i++)
		{
			for (int j = i+1; j < n; j++)
			{
				if (((number[j * 2] == number[i*2]) or (number[j * 2] == number[i * 2+1]) or 
					(number[j * 2 + 1] == number[i * 2]) or (number[j * 2 + 1] == number[i * 2 + 1])) 
					and !((number[j * 2 + 1] == number[i * 2]) and (number[j * 2] == number[i * 2+1]))
					and !((number[j * 2 ] == number[i * 2]) and (number[j * 2+1] == number[i * 2 + 1])))
				{
					edges[i]->next = new vertex;
					edges[j]->next = new vertex;
					edges[i]->next->number = j;
					edges[j]->next->number = i;
					edges[i] = edges[i]->next;
					edges[j] = edges[j]->next;
				}
			}
			edges[i] = pointer[i];
		}

		items = n;
		objects = edges;
		delete[]pointer;
		delete[]number;
	}
	int BFSforSeparatedParts()
	{
		for (int i = 0; i < items; i++)
		{
			objects[i]->mark = 0;
		}
		bool* number = new bool[items];
		number[0] = 1; //each cell match one vertex by index
		for (int i = 1; i < items; i++)
			number[i] = 0;
		
		vertex* pointer;
		int counter=1, counterVertexes=0, helper;
		bool transitionIsDone = 1;

		objects[0]->mark = 1;
		for (int i=1; counterVertexes<items; i++)
		{
			helper = counterVertexes;
			for (int j = 0; j < items; j++)
			{

				/*This IF research one vertex and its neighborhoods*/
				if (objects[j]->mark == i)
				{
					pointer = objects[j];
					if (transitionIsDone)
					{
						counterVertexes++;  //vertex is found
																		       /*SUFAR*/cout << "\n " << objects[j]->number << " |";
						transitionIsDone = 0;
					}
					if (objects[j]->next == NULL) helper++;
					for (objects[j] = objects[j]->next; objects[j] != NULL; objects[j] = objects[j]->next) //by this way we make list traversal
					{
						if (objects[objects[j]->number]->mark == 0)             //if this list is untousched - we find him here by help of its neighb.
						{
							number[objects[j]->number] = 1;                     //in array of vertex we has found one more
							objects[objects[j]->number]->mark = i + 1;          //we need to find it in the next iteration of "i" (not this)
																				/*SUGAR*/cout << " " << objects[j]->number << " ";
							counterVertexes++;                                   //vertex is found
						}
					}
					objects[j] = pointer;
				}
			}

			if (helper != counterVertexes)  /*check changes*/
				{
				/*next step*/	cout << "|";
				}
			else if (counterVertexes!=items) /*Exit if graph traversal is made*/
			{
				for (int j = 0;; j++) /*searching unpassed vertex*/
				{
					if (!number[j])  //first untouched vertex 
					{
						number[j] = 1; /*now it is found*/
						objects[j]->mark = i + 1;  /*in the next iteration we'll find it*/
						counter++; /*new separated part*/
						transitionIsDone = 1; /*for line 419*/
						break;
					}
				}
				if (i>(items*items*items)) /*Exit in case if cycle is cycled - need to save memory below*/
					break;		
			}
		}
		delete[]number;
		return counter;
	}
	void BFSforRadiusAndDiameter()
	{
		bool* number = new bool[items];
		for (int i = 0; i < items; i++)
		{
			objects[i]->mark = 0;
		}
		vertex* pointer;
		int counter = 1, counterVertexes = 0, helper, radius=INT_MAX, diameter=0, maxI=-1, minI=-1, i = 0;
		bool transitionIsDone;
		for (int index = 0; index < items; index++)
		{
			for (int i = 0; i < items; i++)
				number[i] = 0;
			number[index] = 1;
			for (int l=0; l<items; l++)
				objects[l]->mark = 0;

			objects[index]->mark = 1;
			transitionIsDone = 1;
			counterVertexes = 0;

			for (i = 1; counterVertexes < items; i++)
			{
				helper = counterVertexes;
				for (int j = 0; j < items; j++)
				{

					/*This IF research one vertex and its neighborhoods*/
					if (objects[j]->mark == i)
					{
						pointer = objects[j];
						if (transitionIsDone)
						{
							counterVertexes++;
							/*SUFAR*/cout << "\n " << objects[j]->number << " |";
							transitionIsDone = 0;
						}
						if (objects[j]->next == NULL) helper++;
						for (objects[j] = objects[j]->next; objects[j] != NULL; objects[j] = objects[j]->next)
						{
							if (objects[objects[j]->number]->mark == 0)
							{
								number[objects[j]->number] = 1;
								objects[objects[j]->number]->mark = i + 1;
								/*SUGAR*/cout << " " << objects[j]->number << " ";
								counterVertexes++;
							}
						}
						objects[j] = pointer;
					}
				}

				if (helper != counterVertexes)  /*check changes*/
				{
					/*next step*/	cout << "|";
				}
				else if (counterVertexes != items) /*Exit if graph traversal is made*/
				{
					for (int j = 0;; j++) /*searching unpassed vertex*/
					{
						if (!number[j])  //first untouched vertex 
						{
							number[j] = 1; /*now it is found*/
							objects[j]->mark = i + 1;  /*in the next iteration we'll find it*/
							counter++; /*new separated part*/
							transitionIsDone = 1; /*for line 419*/
							break;
						}
					}
				}
			}
			if ((i-1) > diameter)
			{
				maxI = index;
				diameter = i-1;
			}
			if ((i-1) < radius)
			{
				minI = index;
				radius = i-1;
			}
		}
		delete[]number;
		if (sumRelations() == 0)
		{
			radius--;
			diameter--;
		}
		cout <<endl<< "Radius: " << radius << " (vertex " << minI << ")"<<endl;
		cout << "Diameter: " << diameter << " (vertex " << maxI << ")" << endl;
	}
	void DFSpass()
	{
		int start;
		bool exit = 0;
		cout << "Enter start-vertex: ";
		cin >> start;
		for (int i = 0; i < items; i++)
		{
			objects[i]->mark = 0;
		}

		vertex* currentPosition = objects[start];
		vertex* list = new vertex;
		vertex* startPosition=list;
		int counter = 0;
		cout << endl;
		while (counter != items) 
		{
			if (currentPosition != NULL)
			{
				if (!currentPosition->mark)
				{
					if (counter)
					{
						list->next = new vertex;
						list = list->next;
						cout << "->";
					}
					cout << currentPosition->number;

					list->number = currentPosition->number;
					counter++;
					currentPosition->mark = 1;
				}
				do
				{
					if (!objects[currentPosition->number]->mark)
					{
						currentPosition = objects[currentPosition->number];
						exit = 0;
						break;
					}
					else
						currentPosition = currentPosition->next;
				} while (currentPosition != NULL);
			}
			else
			{
				if ((exit) or (counter==1))
					break;
				list = startPosition;
				while (list->next!=NULL)
				{
					currentPosition = list;
					list = list->next;
				}
				delete list;
				list = currentPosition;
				list->next = NULL;
				currentPosition = objects[list->number];
				if (startPosition->next == NULL)
					exit = 1;
			}
		}
		delete startPosition;
		cout << endl;
	}
	void DFSfromXtoY()
	{
		int start, end;
		bool exit = 0;
		
		cout << "Enter start-vertex: ";
		cin >> start;
		cout << "Enter end-vertex: ";
		cin >> end;

		for (int i = 0; i < items; i++)
		{
			objects[i]->mark = 0;
		}

		vertex* currentPosition = objects[start];
		vertex* list = new vertex;
		list->number = -1;
		vertex* startPosition = list;
		int counter = 0;
		cout << endl;
		while ((counter != items) and (end!=list->number))
		{
			//cout << "here";
			if (currentPosition != NULL)
			{
				if (!currentPosition->mark)
				{
					if (counter)
					{
						list->next = new vertex;
						list = list->next;
				//		cout << "->";
					}
				//	cout << currentPosition->number;

					list->number = currentPosition->number;
					counter++;
					currentPosition->mark = 1;
					if (end == list->number)
						break;
				}
				do
				{
					if (!objects[currentPosition->number]->mark)
					{
						currentPosition = objects[currentPosition->number];
						exit = 0;
						break;
					}
					else
						currentPosition = currentPosition->next;
				} while (currentPosition != NULL);
			}
			else
			{
				if ((exit) or (counter == 1))
					break;
				list = startPosition;
				while (list->next != NULL)
				{
					currentPosition = list;
					list = list->next;
				}
				delete list;
				list = currentPosition;
				list->next = NULL;
				currentPosition = objects[list->number];
				if (startPosition->next == NULL)
					exit = 1;
			}
		}
		cout << endl;
		list = startPosition;
		for (int i = 0; list != NULL; i++)
		{
			if (i)
				cout << "->";
			cout << list->number;
			list = list->next;
		}
		delete startPosition;
		cout << endl;
	}
	
	~listGraph()
	{
		cout << endl;
		for (int j = 0; j < items; j++)
				delete objects[j];
		delete objects;
	}
};
struct algebraicForm
{
	struct connection
	{
		int vertex1 = -1;
		int vertex2 = -1;
	};

	int vertex;
	connection* edge;
	int edges;
	void fillRandom(int n)
	{
		int counter = 0;
		int randomVertex1, randomVertex2;

		srand(time(NULL));
		vertex = n;
		edges = abs(rand() % (n * (n - 1) / 2 + 1));
		edge = new connection[edges];
		for (int i = 0; i < edges; i++)
		{
			edge[i].vertex1 = -1;
			edge[i].vertex2 = -1;
		}
		for (int i = 0; i < edges; i++)
		{
			do
			{
				do
				{
					counter = 0;
					randomVertex1 = abs(rand() % n);
					randomVertex2 = abs(rand() % n);

					for (int j = 0; j < i; j++)
					{
						if ((edge[j].vertex1 == randomVertex1 and edge[j].vertex2 == randomVertex2) or (edge[j].vertex1 == randomVertex2 and edge[j].vertex2 == randomVertex1))
						{
							counter = 1;
							break;
						}
					}
				} while ((randomVertex1 == randomVertex2) or counter);
			} while (counter);
			edge[i].vertex1 = randomVertex1;
			edge[i].vertex2 = randomVertex2;

		}

	}
	void showForm()
	{
		for (int i = 0; i < vertex; i++)
		{
			if (!i)
				cout << "\n X = {";
			cout << " x" << i;
			if (i != (vertex - 1))
				cout << ",";
		}
		if (vertex)
			cout << "}\n";
		for (int i = 0; i < edges; i++)
		{
			if (!i)
				cout << "U = {";
			cout << " (x" << edge[i].vertex1 << ", x" << edge[i].vertex2 << ")";
			if (i != (edges - 1))
				cout << ",";
		}
		if (edges)
			cout << "}\n";
	}
	~algebraicForm()
	{
		delete[] edge;
	}
};
struct myForm
{
	struct vertex
	{
		int n_counter; //it counts number of neighbors
		vector<int> neighbors; //it contains indexes of neughbors
		vertex()
		{
			n_counter = 0;
		}
		~vertex() {};
	};
	int edges; //It counts number of edges in graph
	int vertexes; //It counts number of vertexes in graph
	vector<vertex> nodes; //It contains information about each vertex;
	myForm()
	{
		vertexes = 0;
	}
	void fillRandom(int n) //this func fills graph randomly
	{
		int t, one_more_t;
		bool key;
		vertexes = n;
		srand(time(NULL));
		vertex T;
		nodes.insert(nodes.begin(), n, T);
		for (int i = 0; i < n; i++)
		{
			t = abs(rand() % n-1); //in such way we find number of edges that are incedent to vertex[i]
			for (int j = nodes[i].n_counter; j <= t; j++)
			{
				do                                               //
				{                                                //
					key = 0;                                     //
					do                                           //
						one_more_t = abs(rand() % n);            //in such way we avoid loops
					while (one_more_t == i);                     //

					for (int l = 0; l < nodes[i].n_counter; l++) //
					{                                            //
						if (one_more_t == nodes[i].neighbors[l]) //here we are checking if this neig. already exists
						{                                        //
							key = 1;                             //
							break;                               //
						}                                        //
					}                                            //
				} while (key);                                   //
				nodes[i].neighbors.push_back(one_more_t);//add a vertex in the end of neig. of this vertex
				nodes[one_more_t].neighbors.push_back(i);//add a vertex in the end of neig. of that vertex
				nodes[i].n_counter++;     
				nodes[one_more_t].n_counter++;
				edges++;
			}
		}
		sortForm();
	}
	void introduce()
	{
		int t=0, key;
		string line; //if u'r absent-minded and input letter :D
		
			cout << "Enter number of vertexes\n>> ";
			cin >> line;
			for (int j = 0; line[j] != '\0'; j++)        //   //
			{                                            //   //this moment will save your execution when u input "w2"
				t = t * 10 + int(line[j]) - 48;          //   //
			} 
			vertexes = t;
		    line.clear();

		vertex T;
		nodes.insert(nodes.begin(), vertexes, T);
		
		for (int i = 0; i < vertexes; i++)
		{
			cout << "Enter index of neighbors of " << i << " vertex (-1 if there not more neighbors)\n";
			for (int j = nodes[i].n_counter;; j++)
			{
				do                                               //
				{                                                //
					key = 0;                                     //
 					cout <<">> ";                                //
					cin >> line;                                 //
					t = 0;                                       //   //
					for (int l = 0; line[l] != '\0'; l++)        //   //
					{                                            //   //this moment will save your execution when u input "w2"
						t = t * 10 + int(line[l]) - 48;          //   //
					}                                            //   //
					key = 0;                                     //
					for (int l = 0; l < nodes[i].n_counter; l++) //
					{                                            //
						if ((t == nodes[i].neighbors[l]) or (t==i))//here we are checking if this neig. already exists
						{                                        //
							key = 1;                             //
							break;                               //
						}                                        //
					}											 //
					line.clear();                                //
					
				} while (key);                                   //
				
				if (t < 0 or t >= vertexes)
					break;
				nodes[i].neighbors.push_back(t);//add a vertex in the end of neig. of this vertex
				nodes[t].neighbors.push_back(i);//add a vertex in the end of neig. of that vertex
				nodes[i].n_counter++;           //one more neig of node[i]
				nodes[t].n_counter++;           //one more neig of node[t]
				edges++;                        //one more edge
				
			}
		}
		sortForm();
	}
	void sortForm()
	{
		for (int i = 0; i < vertexes; i++)
			sort(nodes[i].neighbors.begin(), nodes[i].neighbors.end());
	}
	void showForm()
	{
		cout << "\nVERTEX |QUANTITY OF NEIGHBORS| ITS NEIGHBORS";
		for (int i = 0; i < vertexes; i++)
		{
			cout << endl;
			for (int j = 0; j < (10 + 21 + nodes[i].n_counter * 5); j++) cout << "-";
			printf("\n%7i|%21i|", i,nodes[i].n_counter);
			for (int j = 0; j < nodes[i].n_counter; j++)
			{
				printf("%5i", nodes[i].neighbors[j]);
			}
		}
	}
	~myForm(){};
};