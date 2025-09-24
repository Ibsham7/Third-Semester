 #include <iostream>
 using namespace std;
 

int binarySearch(int arr[], int left, int right, int key){
    if (left > right){
        return -1;
    }
    int middle = (left + right) / 2;

    if(arr[middle] == key){
        return middle;
    }
    if (arr[middle] > key){
        return binarySearch(arr, left, middle - 1, key);
    }
    if (arr[middle] < key){
        return binarySearch(arr, middle + 1, right, key);
    }

    return -1;
    }


 int main() { 

    int arr[] = {2, 4, 6, 8, 10, 12};
    int key = 8 ;
    
    int n = sizeof(arr) / sizeof(arr[0]);
    int index = binarySearch(arr, 0, n - 1, key);

    if (index < 0){
        cout<<"index not found in array";
    }
    else{
        cout<<"index for key "<<key<<" found at index "<<index;
    }

 return 0 ;}