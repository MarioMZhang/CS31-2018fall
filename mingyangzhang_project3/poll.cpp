#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

bool isValidUppercaseStateCode(string stateCode){
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
    "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
    "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

int string2int(string s){
    int sum = 0;
    for(int i = 0; i != s.size(); i++){
        sum += s[i] - '0';
        sum *= 10;
    }
    sum /= 10;
    return sum; //convert string characters to integers
}

bool formatOfPoll(string pollData){
    if(pollData.size() == 0)
        return true;    // true when pollData string is empty, which is allowed
    else if(pollData.size() == 1)
        return false;  // false when pollData string has only one char
    else{
        if(!isValidUppercaseStateCode(pollData.substr(0,2)))
            return false;   // fasle when the stateCode is invalid
        else{
            if(pollData.size() == 2)
                return true;    // true if the pollData string has only a stateCode
        }
        
        for(int i = 2; i != pollData.size(); i++){
            if(pollData[i] == ','){
                i++;
                if(!(i <= pollData.size()-1 && isValidUppercaseStateCode(pollData.substr(i,2))))
                    return false; // return false if the stateCode is invalid after comma
                else
                    i+=1;
            }
            else{
                if(!isdigit(pollData[i]))
                    return false; // return false if the character following the state code isn't a digit
                else{
                    i++;
                    if(isdigit(pollData[i])) // check if there are two digits for certain party
                        i++;
                    if(!isalpha(pollData[i]))
                        return false; // return false if party code is invalid
                }
            }
        }
    }
    return true;
}

bool hasProperSyntax(string pollData){
    int comma = 0, digit = 0, alpha = 0;
    for(int i = 0; i != pollData.size(); i++){
        pollData[i] = toupper(pollData[i]); // convert all the statecode and party code to upper-case letters
        if(isalpha(pollData[i]))
            alpha++;
        if(isdigit(pollData[i]))
            digit++;
        if(pollData[i] == ',')
            comma++;
    }
    if(pollData.size() != comma + digit + alpha)
        return false; // false if there are characters other than digits, alpha, or comma
    return formatOfPoll(pollData); // false if the format is wrong, true if otherwise
}
int tallySeats(string pollData, char party, int& seatTally){
    if(!hasProperSyntax(pollData))
        return 1;
    if(!isalpha(party))
        return 2;
    seatTally = 0;
    for(int k = 0; k != pollData.size(); k++){
        if(toupper(pollData[k]) == toupper(party) && isdigit(pollData[k-1])){
            if(isdigit(pollData[k-2]))
                seatTally += string2int(pollData.substr(k-2,2)); // calculate the seats for party
            else
                seatTally += string2int(pollData.substr(k-1,1)); // calculate the seats for party
        }
    }
    return 0;
}

int main(){
//    string pollData = "MA";
//    if(hasProperSyntax(pollData))
//        cout << "true" << endl;
//    else
//        cout << "false" << endl;
//    int seats  = -111;
//    cout << tallySeats(pollData, 'd', seats) << endl << seats << endl;
//
//    assert(hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r00D"));
//
//    assert(!hasProperSyntax("Ut8x,"));
//    int seats;
//    seats = -999;    // so we can detect whether tallySeats sets seats
//    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 22);
//    seats = -999;    // so we can detect whether tallySeats sets seats
//    assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999);
//    assert(hasProperSyntax("MA9D,KS4R")  &&  hasProperSyntax("KS4R,MA9D"));
//    assert(hasProperSyntax("MA9D,,KS4R") == hasProperSyntax("KS4R,,MA9D"));
//    cout << "All tests succeeded" << endl;
}
