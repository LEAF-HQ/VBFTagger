#include "LEAF/Analyzer/include/useful_functions.h"
#include "LEAF/VBFTagger/include/Utils.h"

using namespace std;

void PrintHeader(TString header, int max_lenght, TString color ){
  int header_length = header.Length();
  int left  = (max_lenght - header_length)/2;
  int right = max_lenght - header_length - left;
  if (color=="red")          cout << red << endl;
  else if (color=="green")   cout << green << endl;
  else if (color=="yellow")  cout << yellow << endl;
  else if (color=="blue")    cout << blue << endl;
  else if (color=="magenta") cout << magenta << endl;
  else if (color=="cyan")    cout << cyan << endl;
  else throw std::runtime_error("Unexpected color in PrintHeader.");
  cout << "+" << string(max_lenght-2, '-' ) <<"+" << endl;
  cout << string(left, ' ' ) << header << string(right, ' ' ) << endl;
  cout << "+" << string(max_lenght-2, '-' ) <<"+" << endl;
  cout << reset << endl;

}
