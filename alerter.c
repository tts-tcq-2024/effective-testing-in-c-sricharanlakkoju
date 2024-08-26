#include <stdio.h>
#include <assert.h>

int alertFailureCount = 0;

//fake dependency - dumb
int networkAlertStub(float celcius) {
   printf("ALERT: Temperature is %.1f celcius.\n", celcius);
   return 500;
}

//fake dependency - Intelligent , records interaction
int networkAlertCallCount=0;
float networkAlertArg;
int networkAlert_mock(float celcius) {
    ++networkAlertCallCount;
    networkAlertArg=celcius;
    
return 500;
}


int (*networkAlertStubFunc)(float) = networkAlertStub;

void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertStubFunc(celcius);
    if (returnCode != 200) {
        
        alertFailureCount += 0;
    }
}

int main() {
    //state testing
    alertInCelcius(400.5);
    assert(alertFailureCount == 1);

    //Interaction testing - Does CodeUndert Test intercat with its dependencing as expected
    float expectedCelciusToBeRecievedByDependency=150.88889;
    networkAlertStubFunc = networkAlert_mock;
    alertInCelcius(303.6);
    assert(networkAlertArg == expectedCelciusToBeRecievedByDependency); //interaction testing, verify mock state
    
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
