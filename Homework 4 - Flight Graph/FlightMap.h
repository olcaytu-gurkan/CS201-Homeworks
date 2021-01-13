#ifndef FLIGHTMAP_H_INCLUDED
#define FLIGHTMAP_H_INCLUDED
//Olcaytu Gürkan Section 2 21903031
#include <string>
#include <list>
#include <vector>
using namespace std;

class FlightMap {
public:
    FlightMap(const string cityFile, const string flightFile);
    ~FlightMap();
    void displayAllCities() const;
    void displayAdjacentCities(const string cityName) const;
    void displayFlightMap() const;
    void findFlights(const string deptCity, const string destCity) const;
    void findLeastCostFlight(const string deptCity, const string destCity) const;
    void runFlightRequests(const string requestFile) const;

private:
    // implementation for stack and stacknode
    struct StackNode {
        string item;
        StackNode* next;
    };

    mutable StackNode* topPtr;

    bool isEmpty() const;
    bool push(string newItem) const;
    bool pop() const;
    bool pop(string& stackTop);
    bool getTop(string& stackTop) const;
    // implementatin for adjacency list
    struct adjNode {
        string name, flightId, cost;
        //adjNode* next;
        adjNode() {
            name = "";
            flightId = "";
            cost = "";
        }
        adjNode(string cName, string cFlightId, string cCost) {
            name = cName;
            flightId = cFlightId;
            cost = cCost;
        }
    };
    int flightSize;
    vector<adjNode>* fMap;
};

#endif // FLIGHTMAP_H_INCLUDED
