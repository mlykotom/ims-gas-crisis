#include "simulator.h"

int main() {
	Simulator sim;
	sim.SetStart(0.0);
	sim.SetStop(10.0);
	sim.SetStep(0.01);
	sim.SetMethod(new RK4(sim));	

	Constant a(3.0);
	Constant b(5.0);
	Constant c(8.0);
	Constant d(2.0);
	Time t(&sim_time);
	Variable y1, z2;
	Integrator y, z1, z;	

	y1.SetInput((a*y - b*z + t)/c);
	z2.SetInput((-z + b*y1)/d);

	y.SetInput((-a*y - b*z + t)/c, 1.0);
	z1.SetInput((-z - b*y1)/d, 2.0);
	z.SetInput(z1, 3.0);

	sim.AddIntegrator(&y);
	sim.AddIntegrator(&z1);
	sim.AddIntegrator(&z);

	Print("#cas    y    z'    z\n");

	sim.Simulate();
}