#include<iostream>

int main(void){
  using namespace std;
  int price  = 0;
  int change = 0;
  int coin_count[6] = {};
  static int coin_list[6]  = {500, 100, 50, 10, 5, 1};

  cin >> price;
  change = 1000 - price;

  while(change != 0){
    if(change >= 500){
      change -= 500;
      coin_count[0]++;
    }else if(change >= 100){
      change -= 100;
      coin_count[1]++;
    }else if(change >= 50){
      change -= 50;
      coin_count[2]++;
    }else if(change >= 10){
      change -= 10;
      coin_count[3]++;
    }else if(change >= 5){
      change -= 5;
      coin_count[4]++;
    }else if(change >= 1){
      change -= 1;
      coin_count[5]++;
    }
  }

  for(int i=0;i<6;i++){
    cout << coin_list[i] << " * " << coin_count[i] << endl;
  }
  return 0;
}
