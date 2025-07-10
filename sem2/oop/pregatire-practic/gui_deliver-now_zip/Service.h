#pragma once
#include "PackageRepository.h"
#include "CourierRepository.h"
#include <vector>
#include "Package.h"
#include "Courier.h"
#include "Signal.h"

class Service : public Signal
{
private:
	PackageRepository& packageRepository;
	CourierRepository& courierRepository;
public:
	Service(PackageRepository& packagerepository, CourierRepository& courierRepository);
	std::vector<Package> getAllPackages();
	std::vector<Courier> getAllCouriers();
	void addPackage(Package p);
	void addCourier(Courier c);
	void deliverPackage(std::string sender, std::string address);
	~Service() = default;
};

