//----------------------------------------------------------------------------------------
#include "state.h"
//----------------------------------------------------------------------------------------


void cState::printInfo(){
	std::cout << this->getName() << std::endl;
	std::cout << this->getConsumSummer() << "|" << this->getConsumWinter() << std::endl;
	std::cout << this->getStorageCapacity() << "|" << this->getStorageMaxWithdraw() << "|" << this->getStorageMaxStore() << std::endl;
	std::cout << this->getProduction() << std::endl;
	std::cout << "--- IN ---" << std::endl;
	for (cPipe *pipe : this->getAllPipesIn()){
		std::cout << pipe->getLength() << "|" << pipe->getFlowSummer() << '|' << pipe->getFlowWinter() << std::endl;
	}
	std::cout << "--- OUT ---" << std::endl;
	for (cPipe *pipe : this->getAllPipesOut()){
		std::cout << pipe->getLength() << "|" << pipe->getFlowSummer() << '|' << pipe->getFlowWinter() << std::endl;
	}

	std::cout << "------------------------------" << std::endl;
	std::cout << "------------------------------" << std::endl;
}

//----------------------------------------------------------------------------------------

void cState::addPipelineIn(cPipe* pipe){
	this->mPipesIn.push_back(pipe);
}

void cState::addPipelineOut(cPipe* pipe){
	this->mPipesOut.push_back(pipe);
}