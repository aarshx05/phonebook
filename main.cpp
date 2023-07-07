#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;

class Member {
public:
    char name[100];
    long long int mobno;

    void getdata() {
        cin.ignore();
        cout << "\nEnter Your Name: ";
        cin.getline(name, 100);

        l1: cout << "\nEnter Your Mobile Number: ";
        cin >> mobno;
        if (floor(log10(mobno) + 1) != 10) {
            cout << "\nInvalid Number---Re Enter";
            goto l1;
        }
    }

    void putdata() {
        cout << "\nName: " << name << endl;
        cout << "Mobile Number: " << mobno << endl;
    }

    void setobj(ofstream& outputFile) {
        outputFile << mobno << endl;
        outputFile << name << endl;
    }

    void getobj(ifstream& inputFile) {
        inputFile >> mobno;
        inputFile.ignore();
        inputFile.getline(name, 100);
    }
};

Member* readobjects(int& numObjects) {
    ifstream inputFile("phonebook.txt", ios::binary | ios::in);
    int count = 0;
    Member obj;
    while (inputFile.peek() != EOF) {
        obj.getobj(inputFile);
        count++;
    }
    inputFile.clear();
    inputFile.seekg(0, ios::beg);
Member objects[100];
    
    if (count > 0) {
        
        numObjects = count;
        for (int i = 0; i < count; i++) {
            obj.getobj(inputFile);
            objects[i] = obj;
        }
    }

    inputFile.close();

    return objects;
}

void updatecontact(char* name, long long int newNumber) {
    int objcnt = 0;
    Member* objects = readobjects(objcnt);
    if (objects != NULL) {
        for (int i = 0; i < objcnt; i++) {
            if (strcmp(name, objects[i].name) == 0) {
                objects[i].mobno = newNumber;
                break;
            }
        }
        ofstream outputFile("phonebook.txt", ios::binary | ios::trunc);
        for (int i = 0; i < objcnt; i++) {
            objects[i].setobj(outputFile);
        }

        outputFile.close();

    
    }
}

void deletecontact(const char* name) {
    int objcnt = 0;
    Member* objects = readobjects(objcnt);
    if (objects != NULL) {
        bool contactFound = false;
        for (int i = 0; i < objcnt; i++) {
            if (strcmp(name, objects[i].name) == 0) {
                contactFound = true;
                for (int j = i; j < objcnt - 1; j++) {
                    objects[j] = objects[j + 1];
                }
                objcnt--;
                ofstream outputFile("phonebook.txt", ios::binary | ios::trunc);

                for (int j = 0; j < objcnt; j++) {
                    objects[j].setobj(outputFile);
                }

                outputFile.close();

                break;
            }
        }

        if (!contactFound) {
            cout << "Contact not found." << endl;
        }

        
    }
}

int main() {
    long long int number;
    char newname[100];

    while (true) {
        int sw;
        cout << "\nEnter\n1 To find a mobile number\n2 To find a name\n3 To update a contact\n4 To add contacts\n5 To delete contacts\n6 To show the phonebook\n7 To Clear Phonebook:" << endl;
        cin >> sw;

        if (sw == 4) {
            int n, i;
            cin.ignore();
            cout << "\nEnter the number of contacts you want to enter: ";
            cin >> n;
            Member a[n];
            ofstream outputfile("phonebook.txt", ios::binary | ios::app);
            for (i = 0; i < n; i++) {
                a[i].getdata();
                a[i].setobj(outputfile);
            }
        } else if (sw == 6) {
            int objcnt = 0;
            Member* objects = readobjects(objcnt);
            if (objects != NULL) {
                for (int i = 0; i < objcnt; i++) {
                    objects[i].putdata();
                }
            }
           
        } else if (sw == 1) {
            cout << "\nEnter the name to find the phone number of: ";
            cin.ignore();
            cin.getline(newname, 100);

            int objcnt = 0;
            Member* objects = readobjects(objcnt);
            if (objects != NULL) {
                for (int i = 0; i < objcnt; i++) {
                    if (strcmp(newname, objects[i].name) == 0) {
                        cout << "\n\n" << objects[i].mobno;
                    }
                }
            }
           
        } else if (sw == 2) {
            cout << "\nEnter the mobile number to find the associated name: ";
            cin >> number;

            int objcnt = 0;
            Member* objects = readobjects(objcnt);
            if (objects != NULL) {
                for (int i = 0; i < objcnt; i++) {
                    if (objects[i].mobno == number) {
                        cout << "\n\n" << objects[i].name;
                    }
                }
            }
            
        } else if (sw == 3) {
            cout << "\nEnter the name to update the number of: ";
            cin.ignore();
            cin.getline(newname, 100);

            int objcnt = 0;
            Member* objects = readobjects(objcnt);
            if (objects != NULL) {
                for (int i = 0; i < objcnt; i++) {
                    if (strcmp(newname, objects[i].name) == 0) {
                        cout << "\nEnter the new number: ";
                        cin >> number;
                        updatecontact(newname, number);
                    }
                }
            }
            
        } else if (sw == 5) {
            cout << "\nEnter the name to delete: ";
            cin.ignore();
            cin.getline(newname, 100);

            int objcnt = 0;
            Member* objects = readobjects(objcnt);
            if (objects != NULL) {
                for (int i = 0; i < objcnt; i++) {
                    if (strcmp(newname, objects[i].name) == 0) {
                        deletecontact(newname);
                    }
                }
            }
            
        }
        else if(sw=7)
        {
        	fstream clearfile("phonebook.txt",ios::out);
        	cout<<"\nSuccess";
        	clearfile.close();
        	
		}
		 int u;
        cout << "\nExit? (1 - Yes, 0 - No): ";
       
        cin >> u;
        if (u == 1) {
            break;
        }
    }

    return 0;
}
