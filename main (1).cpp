#include <iostream>
#include <math.h>
using namespace std;
char input[256];
int dirDot = 0;
class Sum {
  double sum;

  public:
    void clear(void);
    void set(int, int);
    void dot(int, int);
    void posDot(int, int); 
    double get(void);
    ~Sum(void);
};

int main() {
  Sum suma;
  cout << "Welcome to the new calculator!\n" << endl;
  cout << "Please enter the equation: ";
  cin >> input;
  double nums[128];
  for(int i = 0; i < 128; i++) {
    nums[i] = 0;
  }
  double numPar[64];
  for(int i = 0; i < 64; i++) {
    numPar[i] = 0;
  }
  double parSymbol[64];
  for(int i = 0; i < 64; i++) {
    parSymbol[i] = 0;
  }
  unsigned dirSymbol[128];
  for(int i = 0; i < 128; i++) {
    dirSymbol[i] = 0;
  }
  unsigned dirPar[128]; 
  for(int i = 0; i < 128; i++) {
    dirPar[i] = 0;
  }
  unsigned long int dirLast = 0;
  int var = 0;
  int parCount = 0;
  int x1 = 0;
  int safeSymbol = 0;
  int safePar = 0;

  
  for(int i = 0; i < 256; i++){
    if (input[i] == 0){
      if(!x1){
        dirLast = i;
        x1 = 1;
      }
    }
    if((input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') && !safePar && safeSymbol == 0){
      dirSymbol[var + 1] = i + 1;
      cout << "at adress " << dirSymbol[var + 1] << " Symbol: " << input[dirSymbol[var + 1]-1] << endl;
      var++;
      if(input[i + 1] == '-')safeSymbol = 1;
    }else if(input[i + 1] != '-' ){
      safeSymbol = 0;
    }
    if((input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') && safePar && safeSymbol == 0){
      parSymbol[var + 1] = i + 1;
      var++;
      if(input[i + 1] == '-')safeSymbol = 1;
    }else if(input[i + 1] != '-' ){
      safeSymbol = 0;
    }
    
    if(input[i] == '(' || input[i] == ')'){
      safePar = !safePar;
      dirPar[parCount] = i;
      parCount++;
    }
  }

  
  int safeDot = 0;
  int numParAdress[64];
  for(int i = 0; i < 64; i++){
    numParAdress[i] = 0;
  }
  int numParCount = 0;
  for(int i3 = 0; i3 < var + 1 && input[i3] != 0; i3++){
    suma.clear();
    unsigned char var3 = 0;
    unsigned char negative = 0;
    if(dirSymbol[i3 + 1] == 0) {
      var3 = dirLast;
    }else {
      var3 = (dirSymbol[i3 + 1] - 1);
    }
    safeDot = 0;
    for(int i4 = (dirSymbol[i3]); i4 < var3 && input[i4] != 0; i4++){
      if(input[i4] != '('){
        if(!safeDot && input[i4] == '-')negative = 1;
        else if(!safeDot && input[i4] != '.' && input[i4] != ','){
          suma.set(i4, var3);
        }else if(!safeDot){
          safeDot = 1;
          suma.dot(i4, var3);
        }else if(safeDot != 0){
          suma.posDot(i4, var3);
        }
      }else{
        numParAdress[numParCount] = i3;
        numParCount++;
      }
    }
    if(!negative){
      nums[i3] = suma.get();
    }else{
      nums[i3] = suma.get() * -1;
    
    }
  }
  double numsPost[128];
  for(int wiwi =  0; wiwi < 128; wiwi++){
    numsPost[wiwi] = nums[wiwi];
    cout << nums[wiwi] << endl;
  }

  int q = 0;
  int qPar = 0;
  for(q = dirPar[qPar] && dirPar[qPar + 2]; q <= 127 && dirSymbol[q] != ')'; q++){

    qPar += 2;
  }


  for(q =  1; q <= 127 && dirSymbol[q] != 0 && dirSymbol[q] != '('; q++){
    switch(input[dirSymbol[q] - 1]){
      case '*':
        cout << "Multiplication: " << numsPost[q-1] << " and " << nums[q] << endl;
        numsPost[q-1] *= nums[q];
        numsPost[q] = numsPost[q-1];
        numsPost[q-1] = 0;

        break;
      case '/':cout << "Division: " << numsPost[q-1] << " and " << nums[q] << endl;
        numsPost[q-1] /= nums[q];
        numsPost[q] = numsPost[q-1];
        numsPost[q-1] = 0;        
        break;
      default:
        break;
    }
  }
  
  double numLast = numsPost[0];
  bool lastOp = 0;
  for(int i =  1; i <= 127 && dirSymbol[i] != 0; i++){
    switch(input[dirSymbol[i] - 1]){
      case '-':
        cout << "substraction: " << numLast << " and " << numsPost[i] << endl;
        numLast -= numsPost[i];
        lastOp = 1;
        break;
      case '+':
        cout << "sum: " << numLast << " and " << numsPost[i] << endl;
        numLast += numsPost[i];
        lastOp = 0;
        break;
      default:
        if(!lastOp){
          cout << "sum: " << numLast << " and " << numsPost[i] << endl;
          numLast += numsPost[i];
        }else {
          cout << "substraction: " << numLast << " and " << numsPost[i] << endl;
          numLast -= numsPost[i];
        }
      break;
    }
  }
    




  
  cout << "Resultado: " << numLast << endl;
}
void Sum::clear() {
  sum = 0;
  dirDot = 0;
}
void Sum::set(int i, int var) {
  sum += ((input[i]-'0')*pow(10, var - i - 1));
}
void Sum::dot(int i, int var) {
  dirDot = i;
  sum /= (pow(10, var - i));
}
void Sum::posDot(int i, int var) {
  sum += ((input[i]-'0')*pow(10, dirDot - i));
}
double Sum::get() {
  return sum;
}
Sum::~Sum(void) {
}