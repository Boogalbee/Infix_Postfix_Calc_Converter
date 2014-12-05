#include <iostream>
#include<stack>
#include <algorithm>
#include <string>
using namespace std;

#define MAX_SIZE 100

// global initilizations
static int leftp=0; //open parenthesis counter
static int rightp=0;//close parenthesis counter
static int size=0; //size of the user input equation
stack<char> eq; //global stack

class equation //class to contain the functions used
{
public:
	static void input_equation(char Input[]); 
	static void check_parenthesis(char Input[]);
	static string convert_to_postfix(char Input[]); //all the functions made are public
	static void displaychar(char Input[]);
};

int precedence(char input) //function to return the precedence of operators
{
	int weight;
	switch(input)
	{
	case '+':
	case '-':
		weight = 1; //precedence of + and - are 1
		break;
	case '*':
	case '/':
		weight = 2; //precedence of * and / is 2
		break;
	case '(':
		weight = 3; //precedence of parenthesis is 3
		break;
	default:
		weight = 0;
	}
	return weight; //return the precedence of the input operator
}

void equation::input_equation(char Input[]) //function to ask for the equation and tkae in the equation
{
	cout << "Input Equation: " << endl;
    cin >> Input; // input array of characters

    while(Input[size]) // determintes size of the array that is filled
        size++;
}

void equation::check_parenthesis(char Input[]) //function to check if the parenthesis in the equation are balanced
{
	for(int i=0; i<(size+1); i++) // checks left and right ()
	{
		if(Input[i]=='(') // find an open parenthesis
		{
			leftp++; //increase the left parenthesis counter
			int j = i+1; //int to check the next index in the array
			if(Input[j] == ')') //if the next input in the array is a closed parenthesis, meaning the user input ()
			{
				cout << "Empty parenthesis, please try again" << endl; //alert the user that they input a set of empty parenthesis
				leftp = rightp = 0;
				equation::input_equation(Input);
				equation::check_parenthesis(Input); //Rerun the input and check parenthesis functions
			}
		}
		if(Input[i]==')') //if the array at this index is a closed parenthesis
		{
			rightp++; //increase the right parenthesis counter
			if(rightp > leftp) //if there are more close parenthesis than open parenthesis
			{
				cout << "Parethesis are not balanced, please try again" << endl; //alert the user that there are more close parenthesis than open parenthesis
				leftp = rightp = 0;
				equation::input_equation(Input);
				equation::check_parenthesis(Input); //take in a new equation and check parenthesis again
				break;
			}
			
		}
	}

	if(leftp != rightp) //if the number of left and right parenthesis are not equal
	{
		cout << "Parethesis are not balanced, please try again" << endl; //alert the user that the input equation has unbalanced equations
		leftp = rightp = 0;
		equation::input_equation(Input);
		equation::check_parenthesis(Input); //take in a new equation and check parenthesis again
	}
}

bool comparePrecendence(char in1,char in2) // function to compare the precedence of two operators
{
	int in1precedence = precedence(in1);
	int in2precedence = precedence(in2); //get the precedence of the first and second operators
	
	if(in1precedence == in2precedence) //if they have the same precedence return true
		return true;	//this will cause the first operator to preform and then the second one
	else
		return in1precedence > in2precedence ? true:false; // if the precedence of the first operator is greater return true, if it is less return false
} //This will cause the first operator to preform first if it has higher precedence or the second operator to preform first if that has higher precedence

string equation::convert_to_postfix(char Input[]) //function to convert from infix to postfix
{

	string postfix = ""; //create an empty string to save the postfix to
	for(int i=0;i<size;i++) //run for the size of the user input equation
	{
		if(Input[i] == '+' || Input[i] == '-' || Input[i] == '*' || Input[i] == '/') // if the current section of the array is an operator
		{
			while(!eq.empty() && eq.top() != '(' && comparePrecendence(eq.top(),Input[i])) //while the stack is not empty, and the top of the stack is not an open parenthesis and while the top of the stack has higher precedence than the current index of the array
			{
				postfix += eq.top(); //the next char in the string is the current position in the array
				eq.pop(); //pop the top of the stack
			}
			eq.push(Input[i]); //if the function does not enter this while loop then simply push the current array index
		}

		else if(Input[i] >= '0' && Input[i] <= '9') //else if the current index is a char representing a number
		{
			postfix += Input[i]; //the next char in the string is the the current index in the array
		}
		else if(Input[i] == '(') // if the current index of the equation array is an open parenthesis
			eq.push(Input[i]); //push it to the top of the stack
		else if(Input[i] == ')') // if the current index of the equation array is a closed parenthesis
		{
			while(!eq.empty() && eq.top() != '(') //while the stack is not empty and the top of the stack is not an open parenthesis
			{
				postfix += eq.top(); //the next char in the string is the top of the stack
				eq.pop(); //pop the top of the stack off
			}
			eq.pop(); //else pop the stack
		}
	}

	while(!eq.empty()) //while the stack is not empty
	{
		postfix += eq.top();
		eq.pop(); //pop the stack 
	}
	return postfix; //return the string containing the postfix equation
}

void equation::displaychar(char Input[]) //equation to display char arrays
{
	for(int i=0;i<size;i++)
		cout<<Input[i];
	cout<<endl;
}


void importantPart()//This is the most important part of the entire project: displays the header (Mathworks please don't sue us)
{
	//Nick Herrmann
	cout<< "\t\t/-------------------------------------\\" <<endl;
	cout<< "\t\t| #1 infix to postfix calculator 2014 |"<<endl;
	cout<< "\t\t|\"Calculator of the decade\"- Mathworks|"<<endl;
	cout<< "\t\t| Nick Herrmann		  Neil Howarth|"<<endl;
	cout<< "\t\t| Paul Rose	       Jordan Fredsall|"<<endl;
	cout<< "\t\t|    Alec 'THE Milk-Man' Bewsee       |"<<endl;
	cout<< "\t\t\\____________________________________/"<<endl;
	cout<< endl;
}
 
bool IsO(char x) // Checks to see if a character is an operator 
{
	// returns true if the character is +-*/, false otherwise
	bool iso = false;
	if(x == '+' || x == '-' || x == '/' || x == '*')
		iso = true;
	return iso; 
}

void Calculate(string p) // using the string that holds postfix, calculate the equation
{
	// local variables
	char x;
	int i = 0;
	double answer = 0;
	char Postfix[MAX_SIZE];
	double A[MAX_SIZE];

	// convert string to double[]
	for (int j=0; j<size-rightp-leftp; j++)
    {
		Postfix[j]=p[j]; // convert string to char[]
		A[j] = (double)Postfix[j] - '0'; // convert char[] to double[]
	}

	//Perform calculations
	while(Postfix[i]) // while the char[] location is filled
	{
		x = Postfix[i]; //x is the "i"th element of the array

		if(IsO(x)) // the x is an operator, perform calculation
		{
			double b = A[i-1]; // variable "b" is the element 1 before the operator
			double a = A[i-2]; // variable "a" is the element 2 before the operator

			// perform the correct mathematical operation
			if(x == '+')
				answer = a+b;
			if(x == '-')
				answer = a-b;
			if(x == '*')
				answer = a*b;
			if(x == '/')
				answer = a/b;

			A[i] = answer; // replace the location of the operator with the new answer
			A[i-1] = A[i-3]; // replace 1 element before the operation with the number that is 3 before the operation
			A[i-2] = A[i-4]; // replace 2 elements before the operation with the number that is 4 before the operation
		}
		i++; // go to the next position of the equation
	}
	cout << "Answer: " << answer << endl; // Output the numerical answer
}

int main() // main loop
{
	importantPart(); // display header
	char end; // user input if they want to run the program again

	// loop that runs until the user wants to stop it
	do{
		// reset global initializations
		leftp=0;
		rightp=0;
		size=0;

		equation equation; // creates a variable of class type equation
		char Input[MAX_SIZE]; // initialize array at a large number, since we only need a little bit
	
		equation.input_equation(Input); // user inputs infix equation
		equation.check_parenthesis(Input); // checks parenthesis of equation
		string postfix = equation.convert_to_postfix(Input); // converts user infix equation to postfix equation
		cout<<endl;

		equation.displaychar(Input); // displays the users infix equation
		cout<<"Postfix: "<<postfix; // displays postfix equation
		cout<<endl;

		Calculate(postfix); // gets numerical answer for equation

		// prompts user if they want to run it again
		cout<<"Would you like to run the program again? (y/n)"<<endl; 
		cin>>end;
	
	}while(end == 'y' || end == 'Y');

	// fin
}

