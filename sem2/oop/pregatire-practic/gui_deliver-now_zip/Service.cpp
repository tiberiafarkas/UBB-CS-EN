#include "Service.h"

Service::Service(PackageRepository& packagerepository, CourierRepository& courierRepository)
    : packageRepository{ packagerepository }, courierRepository{ courierRepository }
{
}

std::vector<Package> Service::getAllPackages()
{
    return this->packageRepository.getAllPackages();
}

std::vector<Courier> Service::getAllCouriers()
{
    return this->courierRepository.getAllCouriers();
}

void Service::addPackage(Package p)
{
    packageRepository.addPackage(p);
    this->notify();
}

void Service::addCourier(Courier c)
{
    courierRepository.addCourier(c);
    this->notify();
}

void Service::deliverPackage(std::string sender, std::string address)
{
    Package& p = packageRepository.getPackageBySenderAndAddress(sender, address);
    p.setStatus(true);
    this->notify();
}