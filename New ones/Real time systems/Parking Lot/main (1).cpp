/******************************************************************************

        Parking Lot
        
        
+----------------------+
|       Vehicle        |
+----------------------+
| - number : string    |
| - type : VehicleType |
+----------------------+


+--------------------------+
|       ParkingSpot        |
+--------------------------+
| - id                     |
| - type : VehicleType     |
| - occupied               |
| - vehicle : Vehicle*     |
+--------------------------+
| + canFit()               |
| + park()                 |
| + removeVehicle()        |
+--------------------------+


+-------------------------+
|      ParkingTicket      |
+-------------------------+
| - ticketId              |
| - vehicle : Vehicle*    |
| - spot : ParkingSpot*   |
+-------------------------+


              <<interface>>
              PricingStrategy
                     ^
                     |
             +-------+-------+
             |               |
       HourlyPricing    PremiumPricing


+--------------------------------+
|          ParkingLot            |
+--------------------------------+
| - spots                        |
| - pricing : PricingStrategy*   |
+--------------------------------+
| + parkVehicle()                |
| + exitVehicle()                |
+--------------------------------+


*******************************************************************************/
#include <iostream>
#include <string>
#include <vector>

// ----------------------------
// Vehicle
// ----------------------------

enum class VehicleType {
    BIKE,
    CAR,
    TRUCK
};

class Vehicle {
private:
    std::string number;
    VehicleType type;

public:
    Vehicle(const std::string& number, VehicleType type)
        : number(number), type(type) {}

    VehicleType getType() const {
        return type;
    }

    const std::string& getNumber() const {
        return number;
    }
};


// ----------------------------
// Parking Spot
// ----------------------------

class ParkingSpot {
private:
    int id;
    VehicleType type;
    Vehicle* vehicle;

public:
    ParkingSpot(int id, VehicleType type)
        : id(id), type(type), vehicle(nullptr) {}

    bool isAvailable() const {
        return vehicle == nullptr;
    }

    bool canFit(const Vehicle& v) const {
        return isAvailable() &&
               type == v.getType();
    }

    void park(Vehicle* v) {
        vehicle = v;
    }

    void removeVehicle() {
        vehicle = nullptr;
    }

    int getId() const {
        return id;
    }
};


// ----------------------------
// Parking Ticket
// ----------------------------

class ParkingTicket {
private:
    int ticketId;
    Vehicle* vehicle;
    ParkingSpot* spot;

public:
    ParkingTicket(
        int ticketId,
        Vehicle* vehicle,
        ParkingSpot* spot)
        : ticketId(ticketId),
          vehicle(vehicle),
          spot(spot) {}

    int getTicketId() const {
        return ticketId;
    }

    Vehicle* getVehicle() const {
        return vehicle;
    }

    ParkingSpot* getSpot() const {
        return spot;
    }
};


// ----------------------------
// Pricing Strategy
// ----------------------------

class PricingStrategy {
public:
    virtual double calculatePrice(
        const Vehicle& vehicle,
        int hours) const = 0;

    virtual ~PricingStrategy() = default;
};


// ----------------------------
// Normal Pricing
// ----------------------------

class NormalPricing : public PricingStrategy {
public:

    double calculatePrice(
        const Vehicle& vehicle,
        int hours) const override {

        switch (vehicle.getType()) {

        case VehicleType::BIKE:
            return hours * 10;

        case VehicleType::CAR:
            return hours * 20;

        case VehicleType::TRUCK:
            return hours * 40;
        }

        return 0;
    }
};


// ----------------------------
// Parking Lot
// ----------------------------

class ParkingLot {
private:
    std::vector<ParkingSpot> spots;

    PricingStrategy* pricing;

    int nextTicketId = 1;

public:

    ParkingLot(PricingStrategy* pricing)
        : pricing(pricing) {}


    void addSpot(int id, VehicleType type) {

        spots.emplace_back(id, type);
    }


    ParkingTicket* parkVehicle(Vehicle* vehicle) {

        for (ParkingSpot& spot : spots) {

            if (spot.canFit(*vehicle)) {

                spot.park(vehicle);

                std::cout
                    << vehicle->getNumber()
                    << " parked at spot "
                    << spot.getId()
                    << '\n';

                return new ParkingTicket(
                    nextTicketId++,
                    vehicle,
                    &spot
                );
            }
        }

        std::cout << "No compatible spot available\n";

        return nullptr;
    }


    void exitVehicle(
        ParkingTicket* ticket,
        int hours) {

        if (ticket == nullptr)
            return;

        Vehicle* vehicle =
            ticket->getVehicle();

        ParkingSpot* spot =
            ticket->getSpot();


        double price =
            pricing->calculatePrice(
                *vehicle,
                hours
            );


        std::cout
            << vehicle->getNumber()
            << " exiting from spot "
            << spot->getId()
            << '\n';

        std::cout
            << "Parking fee: Rs."
            << price
            << '\n';


        spot->removeVehicle();

        delete ticket;
    }
};


// ----------------------------
// Main
// ----------------------------

int main() {

    NormalPricing pricing;

    ParkingLot parkingLot(&pricing);


    // Create parking spots

    parkingLot.addSpot(
        1,
        VehicleType::BIKE
    );

    parkingLot.addSpot(
        2,
        VehicleType::CAR
    );

    parkingLot.addSpot(
        3,
        VehicleType::CAR
    );

    parkingLot.addSpot(
        4,
        VehicleType::TRUCK
    );


    // Vehicles

    Vehicle car(
        "TS09AB1234",
        VehicleType::CAR
    );

    Vehicle bike(
        "TS10XY5678",
        VehicleType::BIKE
    );


    // Entry

    ParkingTicket* carTicket =
        parkingLot.parkVehicle(&car);

    ParkingTicket* bikeTicket =
        parkingLot.parkVehicle(&bike);


    // Exit

    parkingLot.exitVehicle(
        carTicket,
        3
    );

    parkingLot.exitVehicle(
        bikeTicket,
        2
    );


    return 0;
}