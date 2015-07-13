#include <iostream>
#include <string>

int main(void){
  using namespace std;
  string str = "";

  cin >> str;
  int str_length = str.length();
  for(int i = 0; i < str_length / 2; i++){
    if(str[i] != str[str_length - i - 1]){
      cout << "false" << endl;
      return 0;
    }
  }

  cout << "true" << endl;
  return 0;
}
