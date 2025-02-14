#include <iostream>

class FlightBookingSystem
{
public:
    static void book_flight()
    {
        std::cout << "Booking a flight ticket..." << std::endl;
        std::cout << "Successful flight ticket booked!" << std::endl;
    }
};
class HotelBookingSystem
{
public:
    static void book_hotel()
    {
        std::cout << "Booking a hotel room..." << std::endl;
        std::cout << "Successful hotel room booked!" << std::endl;
    }
};
class CarRentalSystem
{
public:
    static void rent_car()
    {
        std::cout << "Renting Car..." << std::endl;
        std::cout << "Successful car rented!" << std::endl;
    }
};

class TravelFacade
{
public:
    ~TravelFacade() = default;

    static void book_trip()
    {
        FlightBookingSystem::book_flight();
        HotelBookingSystem::book_hotel();
        CarRentalSystem::rent_car();
    }
};

int main()
{
    TravelFacade::book_trip();
    return 0;
}
