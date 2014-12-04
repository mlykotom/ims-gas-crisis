#include "simulator.h"

int main() {
	Simulator sim;
	sim.SetStart(0.0);
	sim.SetStop(30.0);
	sim.SetStep(0.01);
	sim.SetMethod(new RK4(sim));	

	Constant sigma(10.0);
	Constant lambda(24.0);
	Constant b(2.0);
	Constant one(1.0);

	Integrator y1, y2, y3;	

	y1.SetInput(sigma*(y2 - y1), 1.0);
	y2.SetInput((one + lambda - y3) * y1 - y2, 1.0);
	y3.SetInput(y1*y2 - b*y3, 1.0);

	sim.AddIntegrator(&y1);
	sim.AddIntegrator(&y2);
	sim.AddIntegrator(&y3);

	Print("#cas    x    y    z\n");

	sim.Simulate();
}