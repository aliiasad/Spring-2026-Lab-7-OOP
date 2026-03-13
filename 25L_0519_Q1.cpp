# include <iostream>
using namespace std;

int length(const char*);
char* cpy(const char*);


class HealthcareDevice  {
    private:
        char* name;
        int energyLevel;
        static int totalDevices;
    public:
        HealthcareDevice(); // default
        HealthcareDevice(char*, int); // parameterized
        HealthcareDevice(const HealthcareDevice&);  // copy constructor
        HealthcareDevice& operator=(const HealthcareDevice&);   // overloaded = oprtr
        ~HealthcareDevice(); // destructor

        // static function
        static int getTotalDevices();

        // getters and setters
        void setName(const char*);
        void setEnergyLevel();

        char* getName();
        int getEnergyLevel();

        // methods
        void display();
        void analyzeEfficiency();

};

int HealthcareDevice :: totalDevices = 0;

HealthcareDevice :: HealthcareDevice()  {
    name = cpy("Unknown");
    energyLevel = 0;
    totalDevices++;
}

HealthcareDevice :: HealthcareDevice(char* n, int energy)    {
    name = cpy(n);

    if (energy < 0 || energy > 100) energyLevel = 0;
    else energyLevel = energy;
    totalDevices++;
}
HealthcareDevice :: HealthcareDevice(const HealthcareDevice& dummy) {

    name = cpy(dummy.name);
    
    if (dummy.energyLevel < 0 || dummy.energyLevel > 100) energyLevel = 0;
    else energyLevel = dummy.energyLevel;
    totalDevices++;
}

HealthcareDevice :: ~HealthcareDevice() {
    delete[] name;
    totalDevices--;
}

HealthcareDevice& HealthcareDevice :: operator=(const HealthcareDevice& dummy)   {
    if (this == &dummy) return *this;
    delete[] name;

    name = cpy(dummy.name);
    energyLevel = dummy.energyLevel;

    return *this;
}

int HealthcareDevice :: getTotalDevices() {
    return totalDevices;
}

char* HealthcareDevice :: getName() {
    return name;
}

int HealthcareDevice :: getEnergyLevel()    {
    return energyLevel;
}

void HealthcareDevice :: display()  {
    cout << "\nName: " << name << "\nEnergy Level: " << energyLevel;
}

void HealthcareDevice::setName(const char* n) {
    if (n[0] == '\0')    {
        cout << "Name cannot be empty!" << endl;
        return;
    }
    delete[] name;
    name = cpy(n);
}

void HealthcareDevice :: setEnergyLevel()   {
    int energy;
    cout << "Enter energy level: ";
    cin >> energy;
    while (energy < 0 || energy > 100) {
        cout << "Invalid. Enter between 0 and 100: ";
        cin >> energy;
    }
    energyLevel = energy;
}

void HealthcareDevice :: analyzeEfficiency()    {
    int estimatedHours = energyLevel / 5;
    cout << "\nDevice Efficiency Analysis" << endl;
    cout << "Device Name: " << name << endl; 
    cout << "Energy Level: " << energyLevel << endl;
    cout << "Efficiecy Status: ";

    if (energyLevel >= 75) cout << "High Efficiency" << endl;
    else if (energyLevel >= 40 && energyLevel <= 74) cout << "Moderate Efficiency" << endl;
    else if (energyLevel >= 10 && energyLevel <= 39) cout << "Low Efficiency" << endl;
    else if (energyLevel < 10) cout << "Critical Level" << endl;

    cout << "Estimated Operating Hours Remaining: " << estimatedHours << endl;

}

int main() {
    // get number of devices
    int size;
    cout << "Enter number of devices: ";
    cin >> size;
    while (size <= 0) {
        cout << "Invalid. Enter a value greater than 0: ";
        cin >> size;
    }

    HealthcareDevice* devices = new HealthcareDevice[size];

    char temp[100];
    cin.ignore();
    for (int i = 0; i < size; i++) {
        cout << "\nEnter details for device " << i + 1 << ":" << endl;
        
        cout << "Enter name: ";
        cin.getline(temp, 100);

        while (temp[0] == '\0') {
            cout << "Name cannot be empty. Enter name: ";
            cin.getline(temp, 100);
        }

        (*(devices + i)).setName(temp);
        (*(devices + i)).setEnergyLevel();
        cin.ignore();
    }

    cout << "\n--- All Devices ---" << endl;
    for (int i = 0; i < size; i++) {
        (*(devices + i)).display();
        (*(devices + i)).analyzeEfficiency();
    }

    //overloaded operator testing
    if (size >= 2) {
        cout << "\n--- Testing operator= (assigning device 2 to device 1) ---" << endl;
        *(devices + 0) = *(devices + 1);
        cout << "After assignment:" << endl;
        (*(devices + 0)).display();
    }

    cout << "\nTotal Devices Created: " << HealthcareDevice :: getTotalDevices() << endl;

    delete[] devices;
    devices = nullptr;

    return 0;
}

int length(const char*str) {
    int len = 0;
    while (str[len] != '\0')    len++;
    return len;
}

char* cpy(const char* src)   {
    
    int i = 0;
    char* dest = new char [length(src) + 1];
    while (src[i] != '\0')  {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}