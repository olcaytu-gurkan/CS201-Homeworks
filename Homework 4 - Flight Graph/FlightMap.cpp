//Olcaytu Gürkan Section 2 21903031
#include "FlightMap.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <sstream>

FlightMap::FlightMap(const string cityFile, const string flightFile) {
    topPtr = NULL;
    flightSize = 0;
    string fileName = cityFile;
    string sizeText;
    ifstream inputFile;
    //Open the stream for the input file
    inputFile.open(fileName.c_str(), ios_base::in);
    //Continue until the end of the file
    while (inputFile.eof() == false) {
        //Read until the end of the line
        getline(inputFile, sizeText, '\n');
        sizeText = sizeText.substr(0, sizeText.size()-1);
        flightSize++;
    }
    //Close the input file stream
    inputFile.close();
    fMap = new vector<adjNode>[flightSize];

    string fileName2 = cityFile;
    string sizeText2;
    ifstream inputFile2;
    //Open the stream for the input file
    inputFile2.open(fileName2.c_str(), ios_base::in);
    //Continue until the end of the file

    int y = 0;
    while (inputFile2.eof() == false) {
        //Read until the end of the line
        getline(inputFile2, sizeText2, '\n');
        if (y != flightSize - 1)
            sizeText2 = sizeText2.substr(0, sizeText2.size()-1);
        fMap[y].push_back(adjNode(sizeText2, "",""));
        y++;
    }
    //Close the input file stream
    inputFile2.close();


    ///////---------- this block is for finding the size of flightFile
    int secSize = 0;
    string ctrf = flightFile;
    string ctrText;
    ifstream inputFile33;
    //Open the stream for the input file
    inputFile33.open(ctrf.c_str(), ios_base::in);
    //Continue until the end of the file
    while (inputFile33.eof() == false) {
        //Read until the end of the line
        getline(inputFile33, ctrText, '\n');
        secSize++;
    }

    inputFile33.close();
    //////--------------
    string fileName3 = flightFile;
    string sizeText3;
    ifstream inputFile3;
    //Open the stream for the input file
    inputFile3.open(fileName3.c_str(), ios_base::in);
    //Continue until the end of the file
    int skipCtr = 0;
    while (inputFile3.eof() == false) {
        //Read until the end of the line
        getline(inputFile3, sizeText3, '\n');
        if (skipCtr != secSize -1)
           sizeText3 = sizeText3.substr(0, sizeText3.size()-1);
        int firstComma = sizeText3.find(",");
        int secondComma = sizeText3.find(",", firstComma + 1, 1);
        int thirdComma = sizeText3.find(",", secondComma + 1 ,1);

        skipCtr++;

        string originCity = sizeText3.substr(0, firstComma);
        string destCity = sizeText3.substr(firstComma+1, secondComma - firstComma - 1);
        string flightId = sizeText3.substr(secondComma+1, thirdComma - secondComma - 1);
        string flightCost = sizeText3.substr(thirdComma+1);

        int origLoc = 0;
        for (int i = 0; i < flightSize; i++) {
            if ((fMap[i].front()).name.compare(originCity) == 0) {
                origLoc = i;
                break;
            }
        }

        fMap[origLoc].push_back(adjNode(destCity,flightId,flightCost));
    }
    //Close the input file stream
    inputFile3.close();
}

FlightMap::~FlightMap() {
    while (!isEmpty()) {
        pop();
    }
    delete topPtr;
    delete [] fMap;
}

void FlightMap::displayAllCities () const {
    //cout << "The list of the cities that HPAir serves is given below:" << endl;
    for (int i = 0; i < flightSize; i++) {
      cout << ((fMap[i].front()).name) << ", ";
    }
    cout << endl;

}

void FlightMap::displayAdjacentCities(const string cityName) const {
    //cout << "The cities adjacent to " << cityName << " are:" << endl;
    int cityLoc = 0;
    for (int i = 0; i < flightSize; i++) {
        if ((fMap[i].front()).name.compare(cityName) == 0)
            cityLoc = i;
    }
    cout << cityName << " -> ";
    vector<adjNode> :: iterator it;
    int cnt = 0;
    for(it = fMap[cityLoc].begin(); it != fMap[cityLoc].end(); ++it) {
        if (cnt != 0)
            cout << (*it).name << ", ";
        cnt++;
    }
    cout << endl;

}

void FlightMap::displayFlightMap() const {
   // cout << "The whole flight map is shown below:" << endl;
    for (int i = 0; i < flightSize; i++) {
        cout << fMap[i].front().name << " - > ";
        vector<adjNode> :: iterator it;
        int cnt = 0;
        for(it = fMap[i].begin(); it != fMap[i].end(); ++it) {
            if (cnt != 0)
                cout << (*it).name << ", ";
            cnt++;
        }
        cout << endl;
    }
}

void FlightMap::findFlights(const string deptCity, const string destCity) const {
    vector <string> fOutput;
    cout << "Request is to fly from " << deptCity << " to " << destCity << ":" << endl;
    int oSentinel = 0;
    for (int i = 0; i < 50; i++) { //algorithm run 50 times to find all possible flights.
        push(deptCity);
        string visitedCities = "";
        visitedCities = visitedCities + deptCity;
        string temp = "";
        getTop(temp);
        string cityCheck = deptCity;
        while (!isEmpty() && temp != destCity) {
            int cityLoc = 0;
            for (int i = 0; i < flightSize; i++) {
                if (fMap[i].front().name == cityCheck) {
                    cityLoc = i;
                    random_shuffle(++(fMap[i].begin()), (fMap[i].end()));
                }
            }
            bool posGo = false;
            vector<adjNode> :: iterator it;
            random_shuffle(++(fMap[cityLoc].begin()), (fMap[cityLoc].end())); //list is shuffled for finding other paths.
            for(it = fMap[cityLoc].begin(); it != fMap[cityLoc].end(); ++it) {
                if ((visitedCities.find((*it).name)) == -1) {
                    posGo = true;

                }
            }

            if (!posGo) {
                getTop(temp);
                if (temp != destCity)
                    pop();
                getTop(cityCheck);

            }
            else {
                vector<adjNode> :: iterator it2;
                int senti = true;
                random_shuffle(++(fMap[cityLoc].begin()), (fMap[cityLoc].end()));
                for(it2 = fMap[cityLoc].begin(); (it2 != fMap[cityLoc].end()) && senti; ++it2) {
                    if ((visitedCities.find((*it2).name)) == -1) {
                        push((*it2).name);
                        visitedCities = visitedCities + (*it2).name;
                        cityCheck = (*it2).name;
                        senti = false;
                    }
                }
            }
        }

        if (isEmpty()) {
            if (oSentinel == 0)
                cout << "Sorry. HPAir does not fly from " << deptCity << " to " << destCity <<endl;
            oSentinel++;
        }
        else {
            StackNode* temp = topPtr;
            int totalCost = 0;
            string modiPut = "";
            list<string> oput;
            string s = "";
            while (temp -> next!= NULL) {
                string tempdest = temp->item;
                string tempdept = temp->next->item;
                int tempLoc = 0;
                for (int i = 0; i < flightSize; i++) {
                    if (fMap[i].front().name == tempdept)
                        tempLoc = i;
                }
                vector<adjNode> :: iterator it;
                for(it = fMap[tempLoc].begin(); it != fMap[tempLoc].end(); ++it) {
                    if ( (*it).name == tempdest) {
                        totalCost = atoi(((*it).cost).c_str()) + totalCost;
                    }
                }
                vector<adjNode> :: iterator it2;
                for(it2 = fMap[tempLoc].begin(); it2 != fMap[tempLoc].end(); ++it2) {
                    if ( (*it2).name == tempdest) {
                        s = "Flight #" + (*it2).flightId +  " from " +  tempdept +  " to " +  tempdest +  " costs " +  (*it2).cost +  " TL" + "\n" + s;
                    }
                }
                temp = temp -> next;
            }
            string e;
            stringstream eout;
            eout << totalCost;
            e = eout.str();
            string tcost = "Total cost is........." + e + " TL";
            s = s + tcost;
            oput.push_front(s);
            list<string> :: iterator it;
            for (it = oput.begin(); it != oput.end(); ++it)
                if (!(find(fOutput.begin(), fOutput.end(), *it) != fOutput.end())) {
                    fOutput.push_back(*it);

                }
            while (!isEmpty())
                pop();
        }
    }
    vector<string> :: iterator it5;
    for(it5 = fOutput.begin(); it5 != fOutput.end(); ++it5) {
            cout << *it5 << endl;
            cout << endl;
    }
}

void FlightMap::findLeastCostFlight(const string deptCity, const string destCity) const {
    vector <string> fOutput;
    cout << "Request is to fly from " << deptCity << " to " << destCity << ":" << endl;
    int oSentinel = 0;
    for (int i = 0; i < 50; i++) {
        push(deptCity);
        string visitedCities = "";
        visitedCities = visitedCities + deptCity;
        string temp = "";
        getTop(temp);
        string cityCheck = deptCity;
        while (!isEmpty() && temp != destCity) {
            int cityLoc = 0;
            for (int i = 0; i < flightSize; i++) {
                if (fMap[i].front().name == cityCheck) {
                    cityLoc = i;
                    random_shuffle(++(fMap[i].begin()), (fMap[i].end()));
                }
            }
            bool posGo = false;
            vector<adjNode> :: iterator it;
            random_shuffle(++(fMap[cityLoc].begin()), (fMap[cityLoc].end()));
            for(it = fMap[cityLoc].begin(); it != fMap[cityLoc].end(); ++it) {
                if ((visitedCities.find((*it).name)) == -1) {
                    posGo = true;

                }
            }

            if (!posGo) {
                getTop(temp);
                if (temp != destCity)
                    pop();
                getTop(cityCheck);

            }
            else {
                vector<adjNode> :: iterator it2;
                int senti = true;
                random_shuffle(++(fMap[cityLoc].begin()), (fMap[cityLoc].end()));
                for(it2 = fMap[cityLoc].begin(); (it2 != fMap[cityLoc].end()) && senti; ++it2) {
                    if ((visitedCities.find((*it2).name)) == -1) {
                        push((*it2).name);
                        visitedCities = visitedCities + (*it2).name;
                        cityCheck = (*it2).name;
                        senti = false;
                    }
                }
            }
        }

        if (isEmpty()) {
            if (oSentinel == 0) {
                cout << "Sorry. HPAir does not fly from " << deptCity << " to " << destCity <<endl;
                oSentinel++;
            }
        }
        else {
            StackNode* temp = topPtr;
            int totalCost = 0;
            string modiPut = "";
            list<string> oput;
            string s = "";
            string way = " ";
            int parseSize = 0;
            while (temp -> next!= NULL) {
                string tempdest = temp->item;
                string tempdept = temp->next->item;
                int tempLoc = 0;
                for (int i = 0; i < flightSize; i++) {
                    if (fMap[i].front().name == tempdept)
                        tempLoc = i;
                }
                vector<adjNode> :: iterator it;
                for(it = fMap[tempLoc].begin(); it != fMap[tempLoc].end(); ++it) {
                    if ( (*it).name == tempdest) {
                        totalCost = atoi(((*it).cost).c_str()) + totalCost;
                    }
                }
                vector<adjNode> :: iterator it2;
                for(it2 = fMap[tempLoc].begin(); it2 != fMap[tempLoc].end(); ++it2) {
                    if ( (*it2).name == tempdest) {
                        s = "Flight #" + (*it2).flightId +  " from " +  tempdept +  " to " +  tempdest +  " costs " +  (*it2).cost +  " TL" + "\n" + s;
                    }
                }
                way =  tempdept + "->" +  tempdest + way.substr(parseSize);
                parseSize = tempdept.size();
                temp = temp -> next;
            }
            string e;
            stringstream eout;
            eout << totalCost;
            e = eout.str();
            string tcost = "Total cost is........." + e + " TL";
            s = s + tcost + way;
            oput.push_front(s);
            list<string> :: iterator it;
            for (it = oput.begin(); it != oput.end(); ++it)
                if (!(find(fOutput.begin(), fOutput.end(), *it) != fOutput.end())) {
                    fOutput.push_back(*it);

                }
            while (!isEmpty())
                pop();
        }
    }
    if(!(fOutput.empty())) {
        vector<string> :: iterator it5;
        for(it5 = fOutput.begin(); it5 != fOutput.end(); ++it5) {
            int verPos = (*it5).rfind("TL");
            cout << (*it5).substr(0, verPos + 2) << endl;
            cout << endl;
        }

        vector<string> :: iterator it6;
        int index = 0;
        int mincost = 999999;
        string mintext = "";
        for (it6 = fOutput.begin(); it6 != fOutput.end(); ++it6) {
            string s = *it6;
            int dotPos = s.find("....");
            int tlPos = s.find("TL", dotPos + 1, 2);

            string costie = s.substr(dotPos + 9, tlPos - dotPos - 10);
            if (atoi(costie.c_str()) < mincost) {
                mintext = s;
                mincost = atoi(costie.c_str());
            }
            index++;
        }
        int fromPos = mintext.find("from");
        int toPos = mintext.find(" to ");
        string dept1 = mintext.substr(fromPos + 5, toPos - fromPos - 5);
        int costsPos = mintext.find(" costs ");
        int gVerPos = mintext.rfind("TL");
        string dest1 = mintext.substr(toPos + 4, costsPos - toPos - 4);
        cout << "A least cost path from " << dept1 << " to " << dest1 << " is " << mintext.substr(gVerPos + 2) << " and its cost is " << mincost << " TL" << endl;
    }
}

void FlightMap::runFlightRequests(const string requestFile) const {
    string fileName2 = requestFile;
    string sizeText2;
    ifstream inputFile2;
    int sizeCtr = 0;
    //Open the stream for the input file
    inputFile2.open(fileName2.c_str(), ios_base::in);
    //Continue until the end of the file
    while (inputFile2.eof() == false) {
        //Read until the end of the line
        getline(inputFile2, sizeText2, '\n');
        sizeCtr++;
    }
    //Close the input file stream
    inputFile2.close();
    //----
    string fileName = requestFile;
    string text;
    ifstream inputFile;
    vector <string> reqList;
    int ctr = 0;
    //Open the stream for the input file
    inputFile.open( fileName.c_str(), ios_base::in );
    //Continue until the end of the file
    while ( inputFile.eof() == false ) {
    //Read until a comma
    //getline( inputFile, text, ',' );
    //Read until the end of the line
        getline( inputFile, text, '\n' );
        if (ctr != sizeCtr - 1)
            text = text.substr(0, text.size()-1);
        reqList.push_back(text);
        ctr++;
    }
    inputFile.close();

    vector<string> :: iterator it;
    for (it = reqList.begin(); it != reqList.end(); ++it) {
        int commaPos = (*it).find(",");
        const string dept = (*it).substr(0, commaPos);
        const string dest = (*it).substr(commaPos+1);
        findLeastCostFlight(dept, dest);
    }
}

bool FlightMap::isEmpty() const {
    return topPtr == NULL;
}

bool FlightMap::push(string newItem) const{
    StackNode* temp = new StackNode;
    temp->item = newItem;
    temp->next = topPtr;
    topPtr = temp;
    // ????? delete temp;
    return true;
}

bool FlightMap::pop() const{
    if (isEmpty()) {
        return false;
    }
    else {
        StackNode* temp = topPtr;
        topPtr = topPtr->next;
        temp->next = NULL;
        delete temp;
        return true;
    }
}

bool FlightMap::pop(string& stackTop) {
    if (isEmpty()) {
        return false;
    }
    else {
        stackTop = topPtr->item;
        StackNode* temp = topPtr;
        topPtr = topPtr->next;
        temp->next = NULL;
        delete temp;
        return true;
    }
}

bool FlightMap::getTop(string& stackTop) const {
    if (isEmpty()) {
        return false;
    }
    else {
        stackTop = topPtr->item;
        return true;
    }
}

