#include "CMS.h"

#define Loading "\n\n\n\n\n\tLoading\x1b[5m.....\x1b[25m\n\n\n\n\n\n"

int main() {
    cout << "\x1b[91m";
    cout << "\n\t\t\t\t\t\x1b[1m\x1b[3mWelcome to our Complaint Management System\n\n\n";
    cout << "\n\n\t\t\t\t\t MADE BY :" << endl;
    cout << "\t\t\t\t\t---------------------------------------" << endl;
    cout << "\t\t\t\t\t\t        Assignment-4           " << endl;
    cout << "\t\t\t\t\t\tAbdul-Rehman Naseer (23L-0787) " << endl;
    cout << "\t\t\t\t\t\tZain-ul-Abidin      (23L-0858) " << endl;
    cout << "\t\t\t\t\t---------------------------------------" << endl;
    cout << Loading;
    cout << "\x1b[0m";
    system("pause");
    CustomerServiceModule csm;
    csm.initializeWithDummyUsers();
    csm.run();
    return 0;
}