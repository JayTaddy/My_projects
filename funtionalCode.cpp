#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

static double StatisticStorage[10] = {};

static double LinearStorage[100] = {};

static double QuadraticStorage[100] = {};

static double FibonacciStorage[100] = {};

static double ReversedStorage[100] = {};

static double MergeStorage[100] = {};

static double ThreeSigmasStorage[100] = {};

static double PolarCoordinatesStorage[100] = {};

static double RatioStorage[100] = {};

static double LogStorage[100] = {};

static double ArensStorage[100] = {};

enum {
  METHOD1 = 1,
  METHOD2,
  METHOD3,
  METHOD4,
  METHOD5,
  METHOD6,
  METHOD7,
  METHOD8,
  METHOD9,
  METHOD10,
};

void Frequency(double Value[], int Model) {
  if (Model == 1) {
    for (int FirstIndex = 0; FirstIndex < 10; FirstIndex++) {
      for (int SecondIndex = 0; SecondIndex < 100; SecondIndex++) {
        if (Value[SecondIndex] >= double(FirstIndex) / 10 && Value[SecondIndex] <= double(FirstIndex + 1) / 10) {
          StatisticStorage[FirstIndex]++;
       }
    }
  }
} else if (Model == 2) {
  double LeftBorder = -3, RightBorder = -2.4;
  int CurrentStorageCell = 0;
  for (int FirstIndex = 0; FirstIndex < 10; FirstIndex++) {
    for (int SecondIndex = 0; SecondIndex < 100; SecondIndex++) {
      if (Value[SecondIndex] >= LeftBorder && Value[SecondIndex] <= RightBorder) {
          StatisticStorage[CurrentStorageCell]++;
       }
     }
   LeftBorder += 0.6;
   RightBorder += 0.6;
   CurrentStorageCell++;
   }
  } else if (Model == 3) {
    for (int FirstIndex = 0; FirstIndex < 10; FirstIndex++) {
      for (int SecondIndex = 0; SecondIndex < 100; SecondIndex++) {
        if (Value[SecondIndex] >= FirstIndex * 10 && Value[SecondIndex] <= (FirstIndex + 1) * 10) {
          StatisticStorage[FirstIndex]++;
        }
      }
    }
  }
}

void ClearStatisticStorage(double Value[10]) {
  for (int Index = 0; Index < 10; Index++) {
    Value[Index] = 0;
  }
}

void Statistics(double Value[100], int Model) {
  Frequency(Value, Model);
  if (Model == 1) {
    for (int Index = 0; Index < 10; Index++) {
      cout << "[" << double(Index) / 10 << "," << double(Index + 1) / 10 << "]" << "  " << StatisticStorage[Index] / 100 << endl;
    }
  } else if (Model == 2) {
    double LeftBorder = -30, RightBorder = -24;
    for (int Index = 0; Index < 10; Index++) {
      cout << "[" << double(LeftBorder) / 10 << "," << double(RightBorder) / 10 << "]" << "  " << StatisticStorage[Index] / 100 << endl;
      LeftBorder += 6;
      RightBorder += 6;
    }
  } else if (Model == 3) {
    for (int Index = 0; Index < 10; Index++) {
      cout << "[" << Index * 10 << "," << (Index + 1) * 10 << "]" << "  " << StatisticStorage[Index] / 100 << endl;
    }
  }
  ClearStatisticStorage(StatisticStorage);
}

void LinearAlgorithm(int FirstValue = 17, int SecondValue = 29, int Division = 131,	int LinearSeed = 2) {
  for (int Index = 0; Index < 200; Index++) {
    LinearSeed = (FirstValue * LinearSeed + SecondValue) % Division;
    LinearStorage[Index] = double(LinearSeed) / Division;
   }
}

void QuadraticAlgorithm(int FirstValue = 16, int SecondValue = 33, int ThirdValue = 47,	int Division = 1000, int QuadraticSeed = 2) {
  for (int Index = 0; Index < 100; Index++) {
    QuadraticSeed = static_cast<int>(ThirdValue*pow(QuadraticSeed, 2) + FirstValue * QuadraticSeed + SecondValue) % Division;
    QuadraticStorage[Index] = double(QuadraticSeed) / Division;
  }
}

void FibonacciAlgorithm(int Division = 1553, int PreviousValue = 0, int FibonacciSeed = 2) {
  for (int Index = 0; Index < 100; Index++) {
    PreviousValue = FibonacciSeed;
    FibonacciSeed = (FibonacciSeed + PreviousValue) % Division;
    FibonacciStorage[Index] = double(FibonacciSeed) / Division;
  }
}

int FindResult(int Value, int AdditionalValue = 0, int Division = 1000, int FirstValue = 49, int SecondValue = 30) {
  while (Value * AdditionalValue % Division != 1) {
    AdditionalValue++;
  }
  if (AdditionalValue == Division) {
    AdditionalValue = 0;
  }
  return Value = (FirstValue * AdditionalValue + SecondValue) % Division;
}

void ReversedAlgorithm(int Division = 1000, int ReversedSeed = 3) {
  for (int Index = 0; Index < 100; Index++) {
    ReversedSeed = FindResult(ReversedSeed);
    ReversedStorage[Index] = double(ReversedSeed) / Division;
  }
}

void MergeAlgorithm() {
  double MergeSeed = 0;
  for (int Index = 0; Index < 100; Index++) {
    MergeSeed = abs(LinearStorage[Index] - FibonacciStorage[Index]);
    MergeStorage[Index] = MergeSeed;
  }
}

double Summition() {
  double ValueFromArray;
  double Sum {};
  for (int Index = 0; Index < 12; Index++) {
    ValueFromArray = LinearStorage[1 + rand() % 100];
    Sum += ValueFromArray;
  }
  return Sum;
}

void ThreeSigmasAlgorithm(double ThreeSigmasSeed = 0, double Sum = 0) {
  for (int Index = 0; Index < 100; Index++) {
    ThreeSigmasSeed = (Summition() - 6);
    ThreeSigmasStorage[Index] = ThreeSigmasSeed;
    Sum = 0;
  }
}
void SecondIteration1 (double FirstValue, double SecondValue, int Index); //prototype

void FirstIteration1(int Index) {
  double FirstValue {}, SecondValue {};
    FirstValue = FibonacciStorage[1 + rand() % 100] * 2 - 1;
    SecondValue = FibonacciStorage[1 + rand() % 100] * 2 - 1;
    SecondIteration1(FirstValue, SecondValue, Index);
}

void SecondIteration1(double FirstValue, double SecondValue, int Index) {
  double Sum = FirstValue * FirstValue + SecondValue * SecondValue;
  if (Sum >= 1) {
    FirstIteration1(Index);
  } else {
    FirstValue = FirstValue * pow((-2 * log(Sum) / Sum), 0.5);
    SecondValue = SecondValue * pow((-2 * log(Sum) / Sum), 0.5);
    PolarCoordinatesStorage[Index] = FirstValue; PolarCoordinatesStorage[100 - Index] = SecondValue;
  }
}

void PolarCoordinatesAlgorithm() {
  for (int Index = 0; Index < 50; Index++)
  {
    FirstIteration1(Index);
  }
}

double SecondIteration2(double FirstValue, double SecondValue); //prototype

double FirstIteration2(double RatioSeed = 0)
{
  RatioSeed = SecondIteration2(LinearStorage[0 + rand() % 100], QuadraticStorage[0 + rand() % 100]);

  return RatioSeed;
}

double SecondIteration2(double FirstValue, double SecondValue) {
  double RatioSeed = 0;
  bool ThirdCondition;
  RatioSeed = pow(abs(8 - M_E), 0.5)*((SecondValue - 0.5) / FirstValue);
  ThirdCondition = pow(RatioSeed, 2.0) <= -4 * log(FirstValue);
  if (ThirdCondition == true) {
    return RatioSeed;
  } else {
    FirstIteration2();
  }
}

void RatioAlgorithm() {
  for (int Index = 0; Index < 100; Index++) {
    RatioStorage[Index] = FirstIteration2();
  }
}

void LogAlgorithm() {
  double LogSeed = 0;
  for (int Index = 0; Index < 100; Index++) {
    LogSeed = -33 * log(LinearStorage[0 + rand() % 200]);
    LogStorage[Index] = LogSeed;
  }
}

double SecondIteration3(double Value); // prototype

double FirstIteration3() {
  double ArensSeed;
  double AdditionalValue = 2;
  double AdditionalValueY = 0;
  ArensSeed = LinearStorage[1 + rand() % 200];
  AdditionalValueY = tan(M_PI * ArensSeed);
  ArensSeed = AdditionalValueY * sqrt(2 * AdditionalValue - 1) + AdditionalValue - 1;
  return SecondIteration3(ArensSeed);
}

double SecondIteration3(double Value) {
  double AdditionalValue = 2;
  double Candidate = 0;
  double AdditionalValueY = 0;
  if (Value <= 0) {
    FirstIteration3();
  }
  Candidate = QuadraticStorage[1 + rand() % 100];
  if (Candidate > (1 + AdditionalValueY * AdditionalValueY)*exp((AdditionalValue - 1)*log((sqrt(Value / AdditionalValue - 1))) - sqrt(2 * AdditionalValue - 1)*AdditionalValueY)) {
    FirstIteration3();
   }
    else
    {
      return Value;
    }
 }
void ArensAlgorithm() {
  for (int Index = 0; Index < 100; Index++) {
    ArensStorage[Index] = abs(FirstIteration3());
  }
}

void GeneratingRandomNumbers() {
  LinearAlgorithm();
  QuadraticAlgorithm();
  FibonacciAlgorithm();
  ReversedAlgorithm();
  MergeAlgorithm();
  ThreeSigmasAlgorithm();
  PolarCoordinatesAlgorithm();
  RatioAlgorithm();
  LogAlgorithm();
  ArensAlgorithm();
}

int main() {
  cout << "Please, enter that number of the method you want to use :\n "
          "1) LinearAlgorithm\n"
          "2) QuadraticAlgorithm\n"
          "3) FibonacciAlgorithm\n"
          "4) ReversedAlgorithm\n"
          "5) MergeAlgorithm\n"
          "6) ThreeSigmasAlgorithm\n"
          "7) PolarCoordinatesAlgorithm\n"
          "8) RatioAlgorithm\n"
          "9) LogAlgorithm\n"
          "10) ArensAlgorithm\n" << endl;
  GeneratingRandomNumbers();
  size_t choise = 0;
  cin >> choise;

  switch (choise) {
    case METHOD1 :
    Statistics(LinearStorage, 1);
    break;
    case METHOD2 :
    Statistics(QuadraticStorage, 1);
    break;
    case METHOD3 :
    Statistics(FibonacciStorage, 1);
    break;
    case METHOD4 :
    Statistics(ReversedStorage, 1);
    break;
    case METHOD5 :
    Statistics(MergeStorage, 1);
    break;
    case METHOD6 :
    Statistics(ThreeSigmasStorage, 2);
    break;
    case METHOD7 :
    Statistics(PolarCoordinatesStorage, 2);
    break;
    case METHOD8 :
    Statistics(RatioStorage, 2);
    break;
    case METHOD9 :
    Statistics(LogStorage, 3);
    break;
    case METHOD10 :
    Statistics(ArensStorage, 3);
    break;
  }
}
