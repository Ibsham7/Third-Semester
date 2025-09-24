    int arr[] = {2, 4, 6, 8, 10, 12};
    int key = 8 ;
    
    int index = binarySearch(arr , 0 , 5 , key);

    if (index < 0){
        cout<<"index not found in array";
    }
    else{
        cout<<"index for key "<<key<<"found at index "<<index;
    }