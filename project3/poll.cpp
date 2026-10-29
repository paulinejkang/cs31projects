#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;

// Imported from assignment
bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
        "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NM.NJ.NY.NC.ND."
        "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

//Returns true if the pollData is a valid poll data string, false otherwise
bool hasCorrectSyntax (string pollData){
    int len = pollData.size();
    if (len == 0) return true; // empty string
    for (int i = 0; ; i++){
        //Checking for a two letter state code
        if (i+1 >= len) return false;
        char c1 = toupper(pollData[i]);
        char c2 = toupper(pollData[i+1]);  
        if (!isalpha(c1) || !isalpha(c2)) return false;
        string code = "";
        code += c1;
        code += c2;
        if (!isValidUppercaseStateCode(code)) return false;

        i += 2; 

        //Check the party results (1~2 digits followed by a letter)
        while (i < len && isdigit(pollData[i])){
            i++;
            if (i < len && isdigit(pollData[i])) i++;
            if (i >= len || !isalpha(pollData[i])) return false;
            i++;
        }

        //Forecast is followed by the end of the string or a comma
        if (i == len) return true;
        if (pollData[i] != ',') return false;
    }
    return false; //Should never be reached

}

//Total sets predicted to a party and returns 0;
//Return 1 if pollData is invalid or 2 if a party isn't a letter
int predictSeats(string pollData, char party, int& seatPrediction){
    if(!hasCorrectSyntax(pollData)) return 1;
    if(!isalpha(party)) return 2;
    int total = 0;
    int len = pollData.size();
    char target = toupper(party);

    //Syntax is already verified
    for(int i = 0; i< len; i++){
        i += 2; //Skip the state code

        while (i < len && isdigit(pollData[i])){
            // Convert the digit characters to a number
            int seats = pollData[i] - '0';
            i++;
            if (isdigit(pollData[i])){
                seats = seats * 10 + (pollData[i] - '0');
                i++;
            }
            // Add seats if this party letter matches 
            if (toupper(pollData[i]) == target) total += seats;

            i++;
        }
    }

    seatPrediction = total;
    return 0;


}


int main(){

assert(hasCorrectSyntax(""));                            // empty string is valid
assert(hasCorrectSyntax("CT5D,NY9R16D1I,VT,ne3r00D"));   // example from spec
assert(hasCorrectSyntax("vt"));                          // lowercase, no party results
assert(hasCorrectSyntax("cA5d"));                        // mixed case
assert(hasCorrectSyntax("NJ3D5R4D"));                    // same party twice in a state
assert(hasCorrectSyntax("CT0D"));                        // zero seats
assert(hasCorrectSyntax("CT01D"));                       // leading zero
assert(!hasCorrectSyntax("ZT5D"));                       // invalid state code
assert(!hasCorrectSyntax("5D"));                         // missing state code
assert(!hasCorrectSyntax("C"));                          // only one character
assert(!hasCorrectSyntax("CT5D,"));                      // trailing comma
assert(!hasCorrectSyntax(",CT5D"));                      // leading comma
assert(!hasCorrectSyntax("CT5D,,NY3R"));                 // double comma
assert(!hasCorrectSyntax("CT123D"));                     // three digits
assert(!hasCorrectSyntax("CT5"));                        // digit with no party letter
assert(!hasCorrectSyntax("CTD"));                        // party letter with no digits
assert(!hasCorrectSyntax("CT 5D"));                      // space inside forecast
assert(!hasCorrectSyntax("CT5D, NY3R"));                 // space after comma
assert(!hasCorrectSyntax("CT5%"));                       // non-letter party code  
	cerr << "All tests succeeded" << endl;

}