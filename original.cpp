// Code for Project 1
	// Report poll results
	
	#include <iostream>
	using namespace std;
	
	int main()
	{
	    int numberSurveyed;
	    int likely;
	    int unlikely;
	
	    cout << "How many people were surveyed? ";
	    cin >> numberSurveyed;
	    cout << "How many of them think that AI is likely to lead to the end of humanity? ";
	    cin >> likely;
	    cout << "How many of them think that AI is not likely to lead to the end of humanity? ";
	    cin >> unlikely;
	
	    double pctLikely = 100.0 * likely / numberSurveyed;
	    double pctUnlikely = 100.0 * unlikely / numberSurveyed;

	    cout.setf(ios::fixed);
	    cout.precision(1);
	
	    cout << endl;
	    cout << pctLikely << "% say it's likely." << endl;
	    cout << pctUnlikely << "% say it's not likely." << endl;

	    if (likely > unlikely)
	        cout << "More people think AI is likely to be our doom than not." << endl;
	    else
	        cout << "Fewer people think AI is likely to be our doom than not." << endl;
	}