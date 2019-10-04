# **Сложност на алгоритми (Big O)**

### **Задача 0:**
**Кои от следните оценки са еквивалентни на О(N)?**
```
• O(N + P), where P < N/2
• O(2N) 
• O(N + log N) 
• O(N + M)
```

### **Задача 1:**
```cpp
int average(int numbers[], int size) {
  int n = size;
  int sum = 0;

  int i = 0;
  while (i < n) {
    sum = sum + numbers[i];
    i = i + 1;
  }

  return sum / n;
}
```


### **Задача 2:**
```cpp
void foo(int array[], int size){
    int sum = 0; 
    int product = 1; 

    for (int i = 0; i < size; i++) {
        sum += array[i];
    }

    for (int i = 0; i < size; i++) {
        product *= array[i] ;
    } 

    cout << sum << ", " << product << endl;
} 
```

### **Задача 3:**
```cpp
void printPairs(int array[], int size) {

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << array[i] << ", " + array[j] << endl;
        }
    }
} 
```


### **Задача 4:**
```cpp
void printunorderedPairs(int array[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            cout << array[i] << "," << array[j] <<endl;
        }
    }
} 
```

### **Задача 5:**
```cpp
void printUnorderedPairs(int arrayA[], int sizeA,
 int arrayB[], int sizeB) { 
     for (int i = 0; i < sizeA; i++) { 
         for (int j = 0; j < sizeB; j++) {
            if (arrayA[i] < arrayB[j]) {
                cout<<arrayA[i]<<","<<arrayB[j]<<endl;
            }
        }
    }
}
```


### **Задача 6:**
```cpp
void printUnorderedPairs(int arrayA[], int sizeA,
 int arrayB[], int sizeB) { 
     for (int i = 0; i < sizeA; i++) { 
         for (int j = 0; j < sizeB; j++) {
            for (int k = 0; k < 10000; k++) {
                cout<<arrayA[i]<<","<<arrayB[j]<<endl;
            }
        }
    }
}
```

### **Задача 7:**
```cpp
void reverse(int array[], int size) {
    for (int i = 0; i < size / 2; i++) {
        int other = size - i - 1;
        int temp = array[i];
        array[i] = array[other];
        array[other] = temp;
    }
} 
```


### **Задача 8:**
```cpp
struct Node
{
    Node* left;
    Node* right;
    int value;
};

int sum(Node *node){ 
    if (node == NUll) {
        return a;
    }
    return sum(node->left) + node->value + sum(node->right);
}
```

### **Задача 9:**
```cpp
bool isPrime(int n) {
    for (int x = 2; x * x <= n; x++) { 
        if (n % x == 0) {
            return false;
        }
    } 
    return true;
}
```

### **Задача 10:**
```cpp
int factorial(int n) {
    if(n < 0){
        return -1
    } else if (n == 0) {
        return 1
    } else {
        return n * factorial(n - l);
    }
}
```


### **Задача 11:**
```cpp
int fib(int n) {
    if (n <= 0)
        return 0;
    else if (n == 1) 
        return 1;
    return fib(n - 1) + fib(n - 2);
}
```



### **Задача 12:**
```cpp
int powersOf2(int n) {
    if (n < 1) {
        return 0;
    } else if (n == 1) {
        cout<<"1\n";
        return 1;
    } else {
        int prev = powersOf2(n / 2);
        int curr = prev * 2;
        cout<<curr<<endl;
        return curr;
    }
}
```

### **Задача 13:**
```cpp
int getIth(std::list<int> &l, int i) {
    return l[i];
}
```


