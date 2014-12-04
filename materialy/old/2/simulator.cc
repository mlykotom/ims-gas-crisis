#include "simulator.h"

/*****************************************************************/
/**************** GLOBAL VARIABLES AND FUNCTIONS *****************/
FILE *output;			// output file pro Print()
double sim_time;	// simulation time

// set and open output file (default is stdout)
void SetOutput(const char *file) {
	if(file) {
		if(output != stdout)
  		fclose(output);
		output = fopen(file, "wt");
		if(!output) output = stdout;
	}
}

// fprintf to output file
void Print(const char *fmt, ...) {
	va_list args;
	
	va_start(args, fmt);
	vfprintf(output, fmt, args);
	va_end(args);
}		
/**************** GLOBAL VARIABLES AND FUNCTIONS *****************/
/*****************************************************************/

/*****************************************************************/
/******************** ARITHMETIC BLOCKS **************************/
Operation::Operation(Input i1, Input i2) : input1(i1), input2(i2) {}

// we need to overload arithmetic operators
Input operator + (Input a, Input b) { return new Add(a,b); }
Input operator - (Input a, Input b) { return new Sub(a,b); }
Input operator * (Input a, Input b) { return new Mul(a,b); }
Input operator / (Input a, Input b) { return new Div(a,b); }
Input operator - (Input a) { return new Minus(a); }
/******************** ARITHMETIC BLOCKS **************************/
/*****************************************************************/

/*****************************************************************/
/*********************** SIMULATOR *******************************/
// initializes all integrator outputs
void Simulator::InitAll() {
	Print("%.3f ", sim_time); // Prints simulation start time
	for(iterator = integrators->begin(); iterator != integrators->end(); iterator++) {						
		(*iterator)->Init();
		Print("%.3f ", (*iterator)->Value());	// Prints initial values
	}
	Print("\n");
}

// evaluates all integrator input values
void Simulator::EvalAll() {
	for(iterator = integrators->begin(); iterator != integrators->end(); iterator++) {						
		(*iterator)->Eval();								
	}
}

void Simulator::Simulate() {
	sim_time = GetStart();	
	InitAll();	// initializes input values and prints them
	sim_time += GetStep();

	while(sim_time <= GetStop()) {
		method->Integrate(); 	// one step
		sim_time += GetStep();	
	}
}
/*********************** SIMULATOR *******************************/
/*****************************************************************/


/************************ EULER **********************************/
/*****************************************************************/
// one step with Euler method
void Euler::Integrate() {
	s.EvalAll(); // first of all we need to evaluate all integrator inputs

	Print("%.3f ", sim_time);

	for(s.iterator = s.integrators->begin(); s.iterator != s.integrators->end(); s.iterator++) {
		// y(t+h) = h*f(t, y(t))
		(*s.iterator)->SetValue((*s.iterator)->Value() + (s.GetStep() * (*s.iterator)->GetInput()));
		Print("%.3f ", (*s.iterator)->Value());
	}

	Print("\n");
}
/************************ EULER **********************************/
/*****************************************************************/

/************************ KUTTA **********************************/
/*****************************************************************/
// one step with Runge Kutta 4th order method
void RK4::Integrate() {
	int size = s.integrators->size();
	int i;
	double step = s.GetStep();
	double k1[size], k2[size], k3[size], k4[size], out[size]; // we need to store coefficients and default output values
	double def_time = sim_time; // stores default simulation time

	Print("%.3f ", sim_time);

	// save default output values
	for(s.iterator = s.integrators->begin(), i = 0; s.iterator != s.integrators->end(); s.iterator++, i++) {
		out[i] = (*s.iterator)->Value();
	}	

	s.EvalAll();
	// k1 = h*f(t, y(t))
	for(s.iterator = s.integrators->begin(), i = 0; s.iterator != s.integrators->end(); s.iterator++, i++) {
		k1[i] = step * (*s.iterator)->GetInput();
		(*s.iterator)->SetValue(out[i] + k1[i] / 2);
	}	

	sim_time += step / 2;
	s.EvalAll();
	// k2 = h * f(t + h/2, y(t) + k1/2)
	for(s.iterator = s.integrators->begin(), i = 0; s.iterator != s.integrators->end(); s.iterator++, i++) {
		k2[i] = step * (*s.iterator)->GetInput();
		(*s.iterator)->SetValue(out[i] + k2[i] / 2);
	}		

	// time remains the same
	s.EvalAll();
	// k3 = h * f(t + h/2, y(t) + k2/2)
	for(s.iterator = s.integrators->begin(), i = 0; s.iterator != s.integrators->end(); s.iterator++, i++) {
		k3[i] = step * (*s.iterator)->GetInput();
		(*s.iterator)->SetValue(out[i] + k3[i]);
	}					

	sim_time = def_time + step;
	s.EvalAll();
	// k4 = h * f(t + h, y(t) + k3)
	for(s.iterator = s.integrators->begin(), i = 0; s.iterator != s.integrators->end(); s.iterator++, i++) {
		k4[i] = step * (*s.iterator)->GetInput();
		// y(t+h) = y(t) + k1/6 + k2/3 + k3/3 + k4/6
		(*s.iterator)->SetValue(out[i] + k1[i]/6 + k2[i]/3 + k3[i]/3 + k4[i]/6);
		Print("%.3f ", (*s.iterator)->Value());
	}		

	sim_time = def_time;
	Print("\n");

}
/************************ KUTTA **********************************/
/*****************************************************************/