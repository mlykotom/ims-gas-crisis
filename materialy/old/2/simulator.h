// ------------------------------------------------------
// Simulation Library for use in Modelling and Simulation
// Authors: Milan Seitler <xseitl01@stud.fit.vutbr.cz>
//					Martin Šafář <xsafar13@stud.fit.vutbr.cz>
// ------------------------------------------------------
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stdio.h>
#include <list>
#include <stdarg.h>

using namespace std;

/*****************************************************************/
/**************** GLOBAL VARIABLES AND FUNCTIONS *****************/
extern FILE *output;		// output file pro Print()
extern double sim_time;	// simulation time

void SetOutput(const char *file); // set and open output file (default is stdout)
void Print(const char *fmt, ...);	// fprintf to output file
/**************** GLOBAL VARIABLES AND FUNCTIONS *****************/
/*****************************************************************/

/*****************************************************************/
/***************** FORWARD CLASS DECLARATIONS ********************/
class Simulator;
class Block;
class 	Constant;
class 	Variable;
class 	Integrator;
class 	Operation;
class 		Add;
class 		Sub;
class 		Mul;
class 		Div;
class 		Minus;
class Input;
class Method;
class 	RK4;
class 	Euler;	
/***************** FORWARD CLASS DECLARATIONS ********************/
/*****************************************************************/

/*****************************************************************/
/********************** BASIC BLOCKS *****************************/
// base class for all blocks
class Block {
	public:
		// returns block output value
		virtual double Value() = 0;
};

// special class for wrapping blocks so they can be referenced
class Input {
		Block *bpointer;		
	public:
		Input();
		Input(const Input &i) : bpointer(i.bpointer) {}
		Input(Block &block) : bpointer(&block) {}
		Input(Block *block) : bpointer(block) {}		
		double Value() const { return bpointer->Value(); }
};

// block with constant value
class Constant : public Block {
		const double value;
	public:
		Constant(double v) : value(v)	{}
		virtual double Value()	{ return value; }
};

// block with changeable value
// also used for storing expressions
class Variable : public Block {
		Input input;
	public:
		Variable() : input(0) {}
		void SetInput(Input i)	{ input = i;}
		virtual double Value()	{ return input.Value(); }
};

// points to global simulation time (used in RK4)
class Time : public Block {
	private:
		double *value;
	public:
		Time(double *v) : value(v) {}
		virtual double Value() { return *value; }
};

// block used for numerical integration
class Integrator : public Block {
	private:
		double input_value;		// last computed value of input
		double output_value;	
		Input input;	
		double init_value;		// initial value (default = 0)		
	public:
		Integrator() : input(0), init_value(0.0) {}		
		void SetInput(Input i, double initval = 0) { input = i, init_value = initval;  }		
		void SetInput(Integrator &i, double initval = 0) { input = i, init_value = initval;  }				
		double Value() 					{ return output_value; }
		double GetInput()				{ return input_value; }		// returns last computed value of input
		double InputValue()			{ return input.Value(); }	// returns actual input value
		void SetValue(double v)	{ output_value = v; }
		void Eval() 						{ input_value = InputValue(); } // saves actual input value
		void Init()							{ output_value = init_value; }	// sets output value to initial value
};
/********************** BASIC BLOCKS *****************************/
/*****************************************************************/

/*****************************************************************/
/******************** ARITHMETIC BLOCKS **************************/
// base class for arithmetic operations
class Operation : public Block {
		Input input1;
		Input input2;
	public:
		Operation(Input i1, Input i2);
		double Input1Value() { return input1.Value(); }
		double Input2Value() { return input2.Value(); }
};

// used for adding two inputs
class Add : public Operation {
	public:
		Add(Input i1, Input i2) : Operation(i1, i2) {}
		virtual double Value() { return Input1Value() + Input2Value(); }
};

// used for subtracting two inputs
class Sub : public Operation {
	public:
		Sub(Input i1, Input i2) : Operation(i1, i2) {}
		virtual double Value() { return Input1Value() - Input2Value(); }
};

// used for multiplying two inputs
class Mul : public Operation {
	public:
		Mul(Input i1, Input i2) : Operation(i1, i2) {}
		virtual double Value() { return Input1Value() * Input2Value(); }
};

// used for dividing two inputs
class Div : public Operation {
	public:
		Div(Input i1, Input i2) : Operation(i1, i2) {}
		virtual double Value() { return Input1Value() / Input2Value(); }
};

// used for negating the value of input
class Minus : public Operation  {
	public:
		Minus(Input i1) : Operation(i1, 0) {}
		virtual double Value() { return -Input1Value(); }
};

// we need to overload arithmetic operators
Input operator + (Input a, Input b);
Input operator - (Input a, Input b);
Input operator * (Input a, Input b);
Input operator / (Input a, Input b);
Input operator - (Input a);
/******************** ARITHMETIC BLOCKS **************************/
/*****************************************************************/

/*****************************************************************/
/******************** NUMERICAL METHODS **************************/
// base class for numerical methods
class Method {
	public:
		virtual void Integrate() = 0;
};

// Runge Kutta 4th order method
class RK4 : public Method {
	private:
		Simulator &s; // reference to the main simulation class
	public:
		RK4(Simulator &sim) : s(sim) {}
		virtual void Integrate(); 
};

// Euler method
class Euler : public Method {
	private:
		Simulator &s; // reference to the main simulation class	
	public:
		Euler(Simulator &sim) : s(sim) {}
		virtual void Integrate();
};
/******************** NUMERICAL METHODS **************************/
/*****************************************************************/

/*****************************************************************/
/*********************** SIMULATOR *******************************/
// main simulation class
class Simulator {
	private:
		double start_time;
		double stop_time;
		double step_size;
		Method *method;   // method used for numerical integration
	public:		
		list<Integrator *> *integrators;				// list of integrators		
		list<Integrator *>::iterator iterator;	// integrator interation object
		Simulator() { output = stdout; integrators = new list<Integrator *>; }
		void SetStart(double start) { start_time = start; }
		void SetStop(double stop) 	{ stop_time = stop; }
		void SetStep(double step) 	{ step_size = step; }
		void SetMethod(Method *m) 	{ method = m; }
		double GetStart() { return start_time; }
		double GetStop() 	{ return stop_time; }
		double GetStep()	{ return step_size; }
		void AddIntegrator(Integrator *i) { integrators->insert(integrators->end(), i); }
		void SetOutput(const char *file);
		void InitAll();  // initializes all integrator outputs
		void EvalAll();	 // evaluates all integrator input values
		void Simulate(); //	 starts the simulation	
};
/*********************** SIMULATOR *******************************/
/*****************************************************************/

#endif