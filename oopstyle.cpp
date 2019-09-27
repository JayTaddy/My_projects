#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <deque>

enum {
  METHOD_1 = 1,
  METHOD_2,
  METHOD_3,
  METHOD_4,
  METHOD_5,
  METHOD_6,
  METHOD_7,
  METHOD_8,
  METHOD_9,
  METHOD_10,
};

/*
 *  Programm that can generate random nubmers by using different algorithms
 *  Run the programm and read the menu to understand how to use it
*/



 //funtion used in menu to show user intervals in which we generating our numbers
void showIntervals (const double DIFFERENCE = 0.1,
                   double initialValueForMethodOfUniformDistribution = 0.0,
                   double initialValueForNormalDistributionMethods = -3,
                   int initialValueMethodOfGeneratingOtherDistributions = 0) {
  std::cout << "\t\t\t\t This is bar Chart for :\n " << std::endl
            << "{for [0;1] range}\t\t" << "{for [-3;3] range}\t\t" << "{for [0;100] range}" << std::endl;
  size_t iterationsCounter {};
  while(++iterationsCounter <= 10) {
    std::cout.precision(1);
    std::cout << std::fixed << "[" << initialValueForMethodOfUniformDistribution << "; " << initialValueForMethodOfUniformDistribution + DIFFERENCE << "] \t\t\t" << "["
              << initialValueForNormalDistributionMethods << "; " << initialValueForNormalDistributionMethods + 6 * DIFFERENCE << "] \t\t\t";
    std::cout << "[" << initialValueMethodOfGeneratingOtherDistributions << "; " << initialValueMethodOfGeneratingOtherDistributions + 10 << "]";
    std::cout << std::endl;
    initialValueMethodOfGeneratingOtherDistributions += 10;
    initialValueForNormalDistributionMethods += 6 * DIFFERENCE;
    initialValueForMethodOfUniformDistribution += DIFFERENCE;
  }
  std::cout << std::endl << std::endl;
}


 //funtion used to print vectors, int this programm you can use it to print all generated numbers
template<typename BidirectionalIterator>
void printVector (BidirectionalIterator begin, BidirectionalIterator end) {
  auto iterator = begin;
  for (; iterator < end; ++iterator) {
    std::cout << *iterator << " ";
  }
  std::cout << std::endl << std::endl;
}



 /*
  * If everything in creating our object is ok you will receive message that number are built
  * And destructor will send a message about deleting that object
  * All data is int std::vector, so you can see it by using function printVector();
 */
class MethodsOfGenerationOfDifferentlyDistributedNumbers {
  public:
    MethodsOfGenerationOfDifferentlyDistributedNumbers () {
      std::cout << "Rangom generated numbers are built" << std::endl;
    }
    MethodsOfGenerationOfDifferentlyDistributedNumbers (const MethodsOfGenerationOfDifferentlyDistributedNumbers &) = default;
    ~MethodsOfGenerationOfDifferentlyDistributedNumbers () {
      std::cout << "Memory successfully freed" << std::endl;
    }

    // This is the first method of uniform distribution. Default constants can not be changed there
    // if you think that they are wrong, you can contact me to replace them with proposed
    std::vector<double> linearCongruentMethod () {
      int nextAfterInitialNumber {};
      double generatedNumber {};
      int initialNumber {1};
      std::vector<double> resultVector;
      resultVector.reserve(AMOUNT_OF_GENERATED_NUMBERS);
      for (size_t counter {}; counter < AMOUNT_OF_GENERATED_NUMBERS; ++counter) {
        nextAfterInitialNumber = (MULTIPLIER * initialNumber + GROWTH) % ABSOLUTE_NUMBER_VALUE;
        generatedNumber = static_cast<double>(nextAfterInitialNumber) / ABSOLUTE_NUMBER_VALUE;
        resultVector.push_back(generatedNumber);
        initialNumber = nextAfterInitialNumber;
      }
      return resultVector;
    }

    // This is the second method of uniform distribution. Constants are the same
    std::vector<double> quadraticCongruentMethod () {
      std::vector<double> resultVector;
      int nextAfterInitialNumber {};
      double generatedNumber {};
      double initialNumber {2};
      const int temporaryMultiplier {16};
      const int temporaryGrowth {33};
      for (size_t counter {}; counter < AMOUNT_OF_GENERATED_NUMBERS; ++counter) {
        nextAfterInitialNumber = static_cast<int>((QUADRATIC_MULTIPLIER * pow(initialNumber, 2)
                                                  + temporaryMultiplier * initialNumber + temporaryGrowth)) % DIVISION;
        generatedNumber = static_cast<double>(nextAfterInitialNumber) / DIVISION;
        resultVector.push_back(generatedNumber);
        initialNumber = nextAfterInitialNumber;
      }
      return resultVector;
    }

    // The third method of uniform distribution. All constants in private section
    std::vector<double> fibonacciAlgorithm() {
      std::vector<double> resultVector;
      for (size_t counter = 0; counter < AMOUNT_OF_GENERATED_NUMBERS ; ++counter) {
        previousValue = presentValue;
        presentValue = (presentValue + previousValue) % DIVISION_FIBONACCI;
        resultVector.push_back(static_cast<double>(presentValue) / DIVISION_FIBONACCI);
      }
      return resultVector;
    }

    // The fourth method of uniform distribution. To calculate number uses function findResult()
    std::vector<double> reversedAlgorithm () {
      std::vector<double> resultVector;
      int generatedNumber {3};
      for (size_t counter = 0; counter < AMOUNT_OF_GENERATED_NUMBERS; ++counter) {
        generatedNumber = findResult(generatedNumber);
        resultVector.push_back(static_cast<double>(generatedNumber)/DIVISION);
      }
      return resultVector;
    }

    // The fifth method of uniform distribution. Uses first and third methods to generate numbers
    std::vector<double> mergeAlgorithm() {
      double generatedNumber {};
      std::vector<double> linearVector = linearCongruentMethod();
      std::vector<double> fibonacciVector = fibonacciAlgorithm();
      std::vector<double> resultVector;
      double difference {};
      for (size_t counter = 0; counter < AMOUNT_OF_GENERATED_NUMBERS; ++counter) {
        difference = linearVector.at(counter) - fibonacciVector.at(counter);
        generatedNumber = fabs(difference);
        resultVector.push_back(generatedNumber);
      }
      return  resultVector;
    }

    // The first method of normal distribution. Uses linear congruent method
    std::vector<double> threeSigmasMethod () {
      std::vector<double> linearVector = linearCongruentMethod();
      double sum {};
      std::vector<double> resultVector;
      for (size_t counter = 0; counter < AMOUNT_OF_GENERATED_NUMBERS; ++counter) {
        for (size_t counter = 0; counter < 12; ++counter) {
          sum += linearVector.at(1 + rand() % 100);
        }
        resultVector.push_back(sum - 6);
        sum = 0;
      }
      return resultVector;
    }

    // The second method of normal distribution. Uses fibonacci method to generate numbers
    std::vector<double> polarCoordinatesMethod() {
      double firstValue {};
      double secondValue {};
      size_t maximumIterations = AMOUNT_OF_GENERATED_NUMBERS / 2;
      std::deque<double> resultDeque;
      resultDeque.resize(maximumIterations);
      std::vector<double> fibonacciVector = fibonacciAlgorithm();
      for (size_t counter = 0; counter < AMOUNT_OF_GENERATED_NUMBERS / 2; ++counter) {
        firstValue = fibonacciVector[1 + rand() % 100] * 2 - 1;
        secondValue = fibonacciVector[1 + rand() % 100] *2 - 1;
        double sum = pow(firstValue, 2) + pow(secondValue,2);
        if (sum >= 1) {
          firstValue = fibonacciVector[1 + rand() % 100] * 2 - 1;
          secondValue = fibonacciVector[1 + rand() % 100] *2 - 1;
        } else {
          firstValue = firstValue * pow ((-2 * log(sum) / sum), 0.5);
          secondValue = secondValue * pow ((-2 * log(sum) / sum), 0.5);
          resultDeque.push_front(firstValue);
          resultDeque.at(maximumIterations) = secondValue;
          ++maximumIterations;
        }
      }
      std::vector<double> resultVector;
      for (auto value : resultDeque) {
        resultVector.push_back(value);
      }
      return resultVector;
    }

    // The third method of normal distribution. Uses first and second methods
    std::vector<double> ratioAlgorithm() {
      double generatedNumber {};
      bool thirdCondition {};
      double firstValue {};
      double secondValue {};
      std::vector<double> linearVector = linearCongruentMethod();
      std::vector<double> quadraticVector = quadraticCongruentMethod();
      std::vector<double> resultVector;
      for (size_t counter = 0; counter < AMOUNT_OF_GENERATED_NUMBERS; ++counter) {
        firstValue = linearVector.at(0 + rand() % 10000);
        secondValue = quadraticVector.at(0 + rand() % 10000);
        generatedNumber = pow(fabs(8 - M_E), 0.5) * ((secondValue - 0.5) / firstValue);
        thirdCondition = pow(generatedNumber, 2.0) <= -4 * log(firstValue);
        if (thirdCondition == true) {
          resultVector.push_back(generatedNumber);
        } else {

        }
      }
      return resultVector;
    }

    // The first method of other distributions. Uses linear cogruen method to generate numbers
    std::vector<double> logAlgorithm() {
      double generatedNumber = 0;
      std::vector<double> resultVector;
      std::vector<double> linearVector = linearCongruentMethod();
      for (size_t counter = 0; counter < AMOUNT_OF_GENERATED_NUMBERS; ++counter) {
        generatedNumber = -33 * log(linearVector.at(0 + rand() % 10000));
        resultVector.push_back(generatedNumber);
      }
      return resultVector;
    }

    // The second method of other distibutions. Uses first and second methods of normal distributions
    // and 2 fucntion in private section firstCheck() and secondCheck()
    std::vector<double> arensAlgorithm() {
      std::vector<double> resultVector;
      for (size_t counter = 0; counter < AMOUNT_OF_GENERATED_NUMBERS; ++counter) {
        resultVector.push_back(fabs(firstCheck()));
      }
      return resultVector;
    }

    // To use is correctly you have to enter 3rd parametr carefully
    // enter 1 for 1-5 methods
    //       2 for 6-8 methods
    //       3 for 9-10 methods
    template<typename Iterator>
    void showFrequency (Iterator begin, Iterator end, int modelOfMethod) {
      auto it = begin;
      size_t resultArray[10] { };
      if (1 == modelOfMethod) {
        for (; it != end; ++it) {
          if (*it >= 0.0 && *it <= 0.1) {
            resultArray[0]++;
          } else if (*it >= 0.1 && *it <= 0.2) {
            ++resultArray[1];
          } else if (*it >= 0.2 && *it <= 0.3) {
            ++resultArray[2];
          } else if (*it >= 0.3 && *it <= 0.4) {
            ++resultArray[3];
          } else if (*it >= 0.4 && *it <= 0.5) {
            ++resultArray[4];
          } else if (*it >= 0.5 && *it <= 0.6) {
            ++resultArray[5];
          } else if (*it >= 0.6 && *it <= 0.7) {
            ++resultArray[6];
          } else if (*it >= 0.7 && *it <= 0.8) {
            ++resultArray[7];
          } else if (*it >= 0.8 && *it <= 0.9) {
            ++resultArray[8];
          } else if (*it >= 0.9 && *it <= 1.0) {
            ++resultArray[9];
          }
        }
      } else if (2 == modelOfMethod) {
        for (; it != end; ++it) {
          if (*it >= -3.0 && *it <= -2.4) {
            resultArray[0]++;
          } else if (*it >= -2.4 && *it <= -1.8) {
            ++resultArray[1];
          } else if (*it >= -1.8 && *it <= -1.2) {
            ++resultArray[2];
          } else if (*it >= -1.2 && *it <= -0.6) {
            ++resultArray[3];
          } else if (*it >= -0.6 && *it <= 0.0) {
            ++resultArray[4];
          } else if (*it >= 0.0 && *it <= 0.6) {
            ++resultArray[5];
          } else if (*it >= 0.6 && *it <= 1.2) {
            ++resultArray[6];
          } else if (*it >= 1.2 && *it <= 1.8) {
            ++resultArray[7];
          } else if (*it >= 1.8 && *it <= 2.4) {
            ++resultArray[8];
          } else if (*it >= 2.4 && *it <= 3.0) {
            ++resultArray[9];
          }
        }
      } else if (3 == modelOfMethod) {
        for (; it != end; ++it) {
          if (*it >= 0 && *it <= 10) {
            resultArray[0]++;
          } else if (*it >= 10 && *it <= 20) {
            ++resultArray[1];
          } else if (*it >= 20 && *it <= 30) {
            ++resultArray[2];
          } else if (*it >= 30 && *it <= 40) {
            ++resultArray[3];
          } else if (*it >= 40 && *it <= 50) {
            ++resultArray[4];
          } else if (*it >= 50 && *it <= 60) {
            ++resultArray[5];
          } else if (*it >= 60 && *it <= 70) {
            ++resultArray[6];
          } else if (*it >= 70 && *it <= 80) {
            ++resultArray[7];
          } else if (*it >= 80 && *it <= 90) {
            ++resultArray[8];
          } else if (*it >= 90 && *it <= 100) {
            ++resultArray[9];
          }
        }
      }
      std::cout << "This is frequncy for random generated nubmers" << std::endl;
      for (size_t counter  = 1 ; counter <= 10; ++counter) {
        std::cout.precision(2);
        std::cout << "In interval #"<< counter << " " << "frequency is " << static_cast<double>(resultArray[counter - 1]) / AMOUNT_OF_GENERATED_NUMBERS
                  << std::endl;
      }
    }

  private:
    int presentValue = 2;
    int previousValue = 0;
    const int DIVISION_FIBONACCI = 1553;
    const int DIVISION = 1000;
    const int QUADRATIC_MULTIPLIER = 47;
    const int ABSOLUTE_NUMBER_VALUE = 131;
    const int MULTIPLIER = 29;
    const int GROWTH = 17;
    const size_t AMOUNT_OF_GENERATED_NUMBERS = 10000;

    //funtion used in 4rth method(reversed algorithm) to calculate generated number
    int findResult(int result, int additionalValue = 0, int firstValue = 49, int secondValue = 30) {
       while (result * additionalValue % DIVISION != 1) {
         additionalValue++;
       }
       if (additionalValue == DIVISION) {
         additionalValue = 0;
       }
       return result = (firstValue * additionalValue + secondValue) % DIVISION;
     }

    // the first iteration for arens method
    double firstCheck() {
      double arensSeed {};
      double AdditionalValue {2};
      double AdditionalValueY {};
      std::vector<double> linearVector = linearCongruentMethod();
      arensSeed = linearVector.at(1 + rand() % 2000);
      AdditionalValueY = tan(M_PI * arensSeed);
      arensSeed = AdditionalValueY * sqrt(2 * AdditionalValue - 1) + AdditionalValue - 1;
      return secondCheck(arensSeed);
    }

    // The second iteration for arens method
    double secondCheck(double Value) {
      double additionalValue {2};
      double candidate {};
      double additionalValueY {};
      if (Value <= 0) {
        firstCheck();
      }
      std::vector<double> quadraticVector = quadraticCongruentMethod();
      candidate = quadraticVector.at(1 + rand() % 1000);
      if (candidate > (1 + additionalValueY * additionalValueY) * exp((additionalValue - 1) * log((sqrt(Value / additionalValue - 1)))
                                                                    - sqrt(2 * additionalValue - 1) * additionalValueY)) {
        firstCheck();
       } else {
          return Value;
       }
     }
};

void showMenu() {
  std::cout << "\t\t\tThis is 10 random number's generators" << std::endl
            << "\tTo start generating numbers you have to choose one of 10 methods : " << std::endl
            << "1) Linear Congruent algorithm // is generetaing numbers in range [0;1] " << std::endl
            << "2) Quadratic Congruent algorithm // is generetaing numbers in range [0;1]" << std::endl
            << "3) Fibonacci's algorithm // is generating numbers in range [0;1] " << std::endl
            << "4) Reversed algorithm // is generating numbers in range [0;1]" << std::endl
            << "5) Merge algorithm // is generating numbers in range [0;1]" << std::endl
            << "6) Three Sigma's algorithm // is generating numbers in range [-3;3]" << std::endl
            << "7) Polar Coordinates algorithm // is generating numbers in range [-3;3]" << std::endl
            << "8) Ratio algorithm // is generating numbers in range [-3;3]" << std::endl
            << "9) Logarithm algorithm // is generating numbers in range [0;100]" << std::endl
            << "10) Arens algorithm // is generating numbers in range [0;100]" << std::endl
            << " There are an intervals for methods : " << std::endl;
  showIntervals();
}

int main() {
  showMenu();
  std::cout << "If numbers are generated you will receive the message about it " << std::endl
            << "You will also receive message that memory is freed is programm successfully closed" << std::endl <<std::endl
            << "Please enter the number of the method that you want tot use : " << std::endl
            << "To close the programm enter '0' " << std::endl << std::endl;
  size_t choise {11};
  MethodsOfGenerationOfDifferentlyDistributedNumbers someObject;
  std::vector<double> methods;
  while (choise != 0) {
    std::cin >> choise;
    switch (choise) {
      case METHOD_1 :
      methods = someObject.linearCongruentMethod();
      std::cout << "Linear method" << std::endl;
      someObject.showFrequency(methods.begin(), methods.end(), 1);
      break;
      case METHOD_2 :
      methods = someObject.quadraticCongruentMethod();
      std::cout << "Quadratic method" << std::endl;
      someObject.showFrequency(methods.begin(), methods.end(), 1);
      break;
      case METHOD_3 :
      methods = someObject.fibonacciAlgorithm();
      std::cout << "Fibonacci's method" << std::endl;
      someObject.showFrequency(methods.begin(), methods.end(), 1);
      break;
      case METHOD_4 :
      methods = someObject.reversedAlgorithm();
      std::cout << "Reversed method" << std::endl;
      someObject.showFrequency(methods.begin(), methods.end(), 1);
      break;
      case METHOD_5 :
      methods = someObject.mergeAlgorithm();
      std::cout << "Merge method" << std::endl;
      someObject.showFrequency(methods.begin(), methods.end(), 1);
      break;
      case METHOD_6 :
      methods = someObject.threeSigmasMethod();
      std::cout << "Three Sigma's method" << std::endl;
      someObject.showFrequency(methods.begin(), methods.end(), 2);
      break;
      case METHOD_7 :
      methods = someObject.polarCoordinatesMethod();
      std::cout << "Polar Coordinates method" << std::endl;
      someObject.showFrequency(methods.begin(), methods.end(), 2);
      break;
      case METHOD_8 :
      methods = someObject.ratioAlgorithm();
      std::cout << "Ratio method" << std::endl;
      someObject.showFrequency(methods.begin(), methods.end(), 2);
      break;
      case METHOD_9 :
      methods = someObject.logAlgorithm();
      std::cout << "Logarithm method" << std::endl;
      someObject.showFrequency(methods.begin(), methods.end(), 3);
      break;
      case METHOD_10 :
      methods = someObject.arensAlgorithm();
      std::cout << "Aren's method" << std::endl;
      someObject.showFrequency(methods.begin(), methods.end(), 3);
      break;
      default :
      std::cout << "Thanks for using programm! =)" << std::endl;
      break;
    }
  }
}
