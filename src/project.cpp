#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <string>
#include <climits> // for using INT_MAX
#include <stdlib.h>
#include <map>

using namespace std;

const int infinity = INT_MAX; // for dijstras setting default to infinity

// Cafe Ordering Management System
// Customer data type struct
struct customer
{
    int age;           // age of customer
    string name;       // name of customer
    string coffeeName; // COFFEE of customer
    int quantity;      // no of coffees
    double bill;

    customer() {}
    // constructor
    customer(int age, string name, int quantity, string coffeeName, double bill)
    {
        this->age = age;
        this->name = name;
        this->coffeeName = coffeeName;
        this->quantity = quantity;
        this->bill = bill;
    }
};

struct takeAwayCustomer //MAX HEAP
{
    customer cusotomer;
    takeAwayCustomer *next = NULL;

    takeAwayCustomer(int age, string name, int quantity, string coffeeName, double bill)
    {
        this->cusotomer = customer(age, name, quantity, coffeeName, bill);
    }
};

struct dineInCustomer   //QUEUE AND FIFO
{
    customer cusotomer;
    dineInCustomer *next = NULL;

    dineInCustomer(int age, string name, int quantity, string coffeeName, double bill)
    {
        this->cusotomer = customer(age, name, quantity, coffeeName, bill);
    }
};

struct homeDeliveryCustomer     // LIFO STACK
{

    customer cusotomer;
    string address;
    double deliveryCharges;
    int distanceDelivery;
    struct homeDeliveryCustomer *next = NULL;

    homeDeliveryCustomer(int age, string name, int quantity, string coffeeName, double bill, string address, double deliveryCharges, int distanceDelivery)
    {
        this->cusotomer = customer(age, name, quantity, coffeeName, bill);
        this->address = address;
        this->deliveryCharges = deliveryCharges;
        this->distanceDelivery = distanceDelivery;
    }
};

struct Cafe //HANDLES ALL THE CUSTOMER STRUCTS MADE, 
{

    string shopName;
    string *menu;
    int *price;
    string address;
    takeAwayCustomer *nextTakeAwayCustomer = NULL;
    dineInCustomer *nextDineInCustomer = NULL;
    homeDeliveryCustomer *nextHomeDeliveryCustomer = NULL;
};

// Globally declaring the Coffee Shop's pointer
Cafe *myCafe = NULL;

// Globally Declaring the Current Customer's Pointers for all three Types
takeAwayCustomer *currentTakeAwayCustomer = NULL;
dineInCustomer *currentDineInCustomer = NULL;
homeDeliveryCustomer *currentHomeDeliveryCustomer = NULL;

// Globally declaring the variables for the total of all the orders in queue
double total, takeAway, dineIn, homeDelivery;
// Globally declaring the variables for the total of all the orders serve
double servedTotal;

// In case of Serving , to keep the record of Customers Served, implementing AVL Tree for efficient Search
// to search the record of Customers by Name
// It can also Display all the customers Served

struct servedCustomer
{

    int age;
    string name;
    int quantity;
    string coffeeName;
    double bill;
    string customerType;
    servedCustomer *left;
    servedCustomer *right;

    // Constructor
    servedCustomer(int age, string name, int quantity, string coffeeName, double bill, string customerType)
    {
        // setting customers details

        this->age = age;
        this->name = name;
        this->quantity = quantity;
        this->coffeeName = coffeeName;
        this->bill = bill;
        this->customerType = customerType;

        // child to NULL
        this->left = NULL;
        this->right = NULL;
    }
};

servedCustomer *root = NULL; // Global pointer for the root of AVLTree

// isEmpty or not
int isEmpty(servedCustomer *root)
{
    return root == NULL;
}

// display Customers Details

void display(servedCustomer *root)  // LINKED LIST
{
    cout << "Name :" << root->name << endl;
    cout << "Age  :" << root->age << endl;
    cout << "Coffee :" << root->coffeeName << endl;
    cout << "Quantity : " << root->quantity << endl;
    cout << "Bill : " << root->bill << endl;
    cout << "Customer Type: " << root->customerType << endl;
}

// Traversal for the served Customers

servedCustomer *displayAllServedOrders(servedCustomer *root)
{

    if (root)
    {
        displayAllServedOrders(root->left);
        display(root); // will display all the served Customers
        displayAllServedOrders(root->right);
    }

    return root;
}

// Height of servedCustomer tree

int height(servedCustomer *root)
{
    if (!root)
        return 0;

    return max(height(root->left), height(root->right)) + 1;
}

// Balance Factor for each ServedCustomer node

int balanceFactor(servedCustomer *root)
{
    if (!root)
        return 0;

    return height(root->left) - height(root->right);
}

// Maximum of two integers as a helper function for height
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Searching in servedCustomer tree

servedCustomer *search(servedCustomer *root, string keyName)
{
    if (root == NULL)
    {
        return NULL;
    }
    else if (root->name == keyName)
    {
        return root;
    }
    else if (root->name < keyName)
    {
        return search(root->right, keyName);
    }
    else if (root->name > keyName)
    {
        return search(root->left, keyName);
    }

    return root;
}

// Finding Maximum Node of servedCustomer tree

servedCustomer *maxservedCustomer(servedCustomer *root)
{
    // Maximum Node is Present in the most Right Node  of the served Customer Tree
    servedCustomer *p = root;
    servedCustomer *temp = NULL;

    while (p != NULL)
    {
        temp = p;
        p = p->right;
    }

    return temp;
}

// Balancing the ServedCustomer's Tree thorugh AVL Rotations

// LL Rotation
servedCustomer *LLRotation(servedCustomer *root)
// rotate wese right per krna hai!
{
    // saving the new root and the lost element in case of rotation
    servedCustomer *x = root->left;
    servedCustomer *temp = x->right;

    // Performing rotation
    x->right = root;
    root->left = temp;

    // updating the root
    root = x;
    // returning the root
    return x;
}

// RR Rotation
servedCustomer *RRRotation(servedCustomer *root)
{
    // rotate wese left per krna hai!

    // saving the new root and the lost element in case of rotation

    servedCustomer *x = root->right;
    servedCustomer *temp = x->left;

    // Performing rotation
    x->left = root;
    root->right = temp;

    // updating the root
    root = x;

    // returning the root
    return x;
}

// LR Rotation
servedCustomer *LRRotation(servedCustomer *root)
{
    root->left = RRRotation(root->left);
    return LLRotation(root);
}

// RL Rotation
servedCustomer *RLRotation(servedCustomer *root)
{
    root->right = LLRotation(root->right);
    return RRRotation(root);
}

//  INSERTION in servedCustomer Tree

servedCustomer *insertion(int age, string name, int quantity, string coffeeName, double bill, string customerType, servedCustomer *root)
{
    servedCustomer *newNode = new servedCustomer(age, name, quantity, coffeeName, bill, customerType);

    if (root == NULL)
    {
        root = newNode;
    }

    else if (root->name > newNode->name)
    {
        root->left = insertion(age, name, quantity, coffeeName, bill, customerType, root->left);
    }
    else if (root->name < newNode->name)
    {
        root->right = insertion(age, name, quantity, coffeeName, bill, customerType, root->right);
    }

    else
    {
        cout << "No duplicates values are allowed!" << endl;
        return root;
    }

    int bf = balanceFactor(root);

    if (bf == 2)
    {
        // LL
        if (root->left->name > newNode->name)
        {
            return LLRotation(root);
        }

        // LR
        if (root->left->name < newNode->name)
        {
            return LRRotation(root);
        }
    }
    else if (bf == -2)
    {
        // RR
        if (root->right->name < newNode->name)
        {
            return RRRotation(root);
        }

        // RL
        if (root->right->name > newNode->name)
        {
            return RLRotation(root);
        }
    }

    return root; // in case there is no need of rotation
}

servedCustomer *deleteNode(servedCustomer *root, string key)
{
    if (root == NULL)
        return root;
    else if (key < root->name)
        root->left = deleteNode(root->left, key);
    else if (key > root->name)
        root->right = deleteNode(root->right, key);
    else
    {
        // if delete root has one child or zero child
        if ((root->left == NULL) || (root->right == NULL))
        {
            servedCustomer *temp = root->left ? root->left : root->right;
        //leaf node1117
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            delete (temp);
        }
        else
        {
            // if deleteroot has two or more childs
            servedCustomer *temp = maxservedCustomer(root->right);
            root->name = temp->name;
            root->right = deleteNode(root->right, temp->name);
        }
    }

    if (root == NULL)
        return root;

    // getting the balance factor
    int balance = balanceFactor(root);

    // Rotation Cases
    // LEFT LEFT CASE
    if (balance > 1 && key < root->left->name)
        return LLRotation(root);

    // LEFT RIGHT CASE
    if (balance > 1 && key > root->left->name)
    {
        root->left = LLRotation(root->left);
        return LRRotation(root);
    }

    // RIHGT RIGHT CASE
    if (balance < -1 && key > root->right->name)
        return RRRotation(root);

    // RIGHT LEFT CASE
    if (balance < -1 && key < root->right->name)
    {
        return RLRotation(root);
    }

    return root;
}

void deleteAllServedCustomers(servedCustomer *root)
{

    while (root)
    {
        root = deleteNode(root, root->name);
    }

    cout << "The Served Customer's List is Cleared " << endl;
}

// Now defining Order Placing and Serving of Take Away Customer
// Based on : Older person will be served first (PRIORITY QUEUE)
// Now defining Order Placing and Serving of Take Away Customer
// Based on : Older person will be served first (PRIORITY QUEUE)

// Custom Priority Queue Implementation Using Max-Heap
// Custom Max-Heap Class for Priority Queue
class MaxHeap
{
private:
    vector<takeAwayCustomer *> heap; // Store pointers to takeAwayCustomer nodes

    // Helper function to get parent index
    int parent(int i) { return (i - 1) / 2; }

    // Helper function to get left child index
    int leftChild(int i) { return 2 * i + 1; }

    // Helper function to get right child index
    int rightChild(int i) { return 2 * i + 2; }

    // Helper function to heapify up (for insertion)
    void heapifyUp(int index)
    {
        while (index > 0 && heap[parent(index)]->cusotomer.age < heap[index]->cusotomer.age)
        {
            swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }

    // Helper function to heapify down (for deletion)
    void heapifyDown(int index)
    {
        int largest = index;
        int left = leftChild(index);
        int right = rightChild(index);

        if (left < heap.size() && heap[left]->cusotomer.age > heap[largest]->cusotomer.age)
        {
            largest = left;
        }

        if (right < heap.size() && heap[right]->cusotomer.age > heap[largest]->cusotomer.age)
        {
            largest = right;
        }

        if (largest != index)
        {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    // Insert a new take-away customer into the heap
    void push(takeAwayCustomer *customerNode)
    {
        heap.push_back(customerNode);
        heapifyUp(heap.size() - 1);
    }

    // Get the highest-priority customer (oldest)
    takeAwayCustomer *top()
    {
        if (heap.empty())
        {
            throw runtime_error("Heap is empty!");
        }
        return heap[0];
    }

    // Remove the highest-priority customer
    void pop()
    {
        if (heap.empty())
        {
            throw runtime_error("Heap is empty!");
        }
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    // Check if the heap is empty
    bool empty() { return heap.empty(); }
};

// Global priority queue for Take Away Customers
MaxHeap takeAwayQueue;

void placeOrderTakeAwayCustomer(int age, string name, string coffeeName, int quantity, double bill)
{
    // Create a new takeAwayCustomer node and push to the priority queue
    takeAwayCustomer *newCustomer = new takeAwayCustomer(age, name, quantity, coffeeName, bill);
    takeAwayQueue.push(newCustomer);

    cout << "Order placed for: " << name << " (Age: " << age << ") for " << quantity << " " << coffeeName << "." << endl;
    cout << "Amount due: Rs. " << bill << endl;
}
void serveOrderTakeAwayCustomer()
{
    if (takeAwayQueue.empty())
    {
        cout << "No Take Away Customer to Serve" << endl;
        return;
    }

    // Get the customer with the highest priority (oldest customer)
    takeAwayCustomer *servedCustomer = takeAwayQueue.top();
    takeAwayQueue.pop();

    cout << "Take Away Customer Served: " << servedCustomer->cusotomer.name
         << " (Age: " << servedCustomer->cusotomer.age << ")" << endl;

    // Update served customer record (e.g., insert into a served customer tree or list)
    string customerType = "Take-Away";
    root = insertion(servedCustomer->cusotomer.age, servedCustomer->cusotomer.name,
                     servedCustomer->cusotomer.quantity, servedCustomer->cusotomer.coffeeName,
                     servedCustomer->cusotomer.bill, customerType, root);

    delete servedCustomer; // Free memory
}
// Now defining Order Placing and Serving of Dine-In Customer
// Based on : First Come First Served (FIFO) (QUEUE)

void placeOrderDineInCustomer(int age, string name, string coffeeName, int quantity, double bill)
{
    // making new Customer
    currentDineInCustomer = new dineInCustomer(age, name, quantity, coffeeName, bill);

    if (myCafe->nextDineInCustomer == NULL)
    {
        // if first insert in front
        myCafe->nextDineInCustomer = currentDineInCustomer;
    }
    else
    {
        // finding the last Node
        dineInCustomer *temp = myCafe->nextDineInCustomer;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = currentDineInCustomer;
        currentDineInCustomer->next = NULL;
    }
    cout << "------------------------------------------------------------------------------" << endl;
    // cout << "Your Order has been Placed! Mr/Mrs. " << name << " for  " << coffeeName << " with " << quantity << " quantity and total bill is " << bill << endl;
    cout << "Order placed for:  " << name << " for " << quantity << " " << coffeeName << "." << endl;
    cout << "Amount due: " << bill << endl;
}
void serveOrderDineInCustomer()
{
    if (myCafe->nextDineInCustomer == NULL)
    {
        cout << "No dine-in customer to serve!" << endl;
    }
    else
    {
        // serving the first customer
        dineInCustomer *temp = myCafe->nextDineInCustomer;
        if (temp->next != NULL)
        {
            myCafe->nextDineInCustomer = temp->next;
        }
        else
        {
            myCafe->nextDineInCustomer = NULL;
        }

        cout << "Dine-In Customer Served! " << temp->cusotomer.name << endl;

        string customerType = "Dine-In";
        // Now before deleting the node we need to update the servedCustomer Tree
        root = insertion(temp->cusotomer.age, temp->cusotomer.name, temp->cusotomer.quantity, temp->cusotomer.coffeeName, temp->cusotomer.bill, customerType, root);

        delete temp; // deleting the customer
    }
}

// Now defining Order Placing and Serving of Home Delivery Customer
// Based on : (when all orders are ready)(LIFO)(Stack)

void placeOrderHomeDeliveryCustomer(int age, string name, string coffeeName, int quantity, double bill, string address, int deliveryCharges, int distanceDelivery)
{
    // making new Customer
    currentHomeDeliveryCustomer = new homeDeliveryCustomer(age, name, quantity, coffeeName, bill, address, deliveryCharges, distanceDelivery);

    if (myCafe->nextHomeDeliveryCustomer == NULL)
    {
        // if first insert in front
        myCafe->nextHomeDeliveryCustomer = currentHomeDeliveryCustomer;
    }
    else
    {
        // finding the last Node
        homeDeliveryCustomer *temp = myCafe->nextHomeDeliveryCustomer;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = currentHomeDeliveryCustomer;
        currentHomeDeliveryCustomer->next = NULL;
    }
    cout << "Order placed for:  " << name << " for " << quantity << " " << coffeeName << "." << endl;
    cout << "Amount due: " << bill << endl;
}

void serveOrderHomeDeliveryCustomer()
{
    if (myCafe->nextHomeDeliveryCustomer == NULL)
    {
        cout << "No Home Delivery Customer to Serve" << endl;
    }
    else
    {

        // serving the last customer first
        homeDeliveryCustomer *first = myCafe->nextHomeDeliveryCustomer;

        if (first->next == NULL)
        {
            // if it is the only customer

            myCafe->nextHomeDeliveryCustomer = NULL;

            cout << "Home Delivery Customer Served : " << first->cusotomer.name << endl;
            string customerType = "Home-Delivery Customer";
            root = insertion(first->cusotomer.age, first->cusotomer.name, first->cusotomer.quantity, first->cusotomer.coffeeName, first->cusotomer.bill, customerType, root);

            // now deleting the node
            delete (first);
        }
        else
        {
            homeDeliveryCustomer *s = first->next;
            while (s->next != NULL)
            {
                first = first->next;
                s = s->next;
            }

            first->next = NULL;

            cout << "Home Delivery Customer Served : " << s->cusotomer.name << endl;
            string customerType = "Home-Delivery Customer";
            root = insertion(s->cusotomer.age, s->cusotomer.name, s->cusotomer.quantity, s->cusotomer.coffeeName, s->cusotomer.bill, customerType, root);

            // deleting the node

            delete (s);
        }

        // deleting the customer
    }
}

// It will serve all the waiting orders

void serveAllOrders()
{

    while (myCafe->nextTakeAwayCustomer != NULL)
    {
        serveOrderTakeAwayCustomer();
    }
    while (myCafe->nextDineInCustomer != NULL)
    {
        serveOrderDineInCustomer();
    }
    while (myCafe->nextHomeDeliveryCustomer != NULL)
    {
        serveOrderHomeDeliveryCustomer();
    }
}
void displayAllOrdersTakeAwayCustomers()
{
    if (takeAwayQueue.empty())
    {
        cout << "No orders for Take-Away Customers yet!" << endl;
        return;
    }

    // Make a copy of the heap to display customers without altering the original heap
    MaxHeap tempQueue = takeAwayQueue;

    cout << "Displaying all Take-Away Orders:" << endl;
    while (!tempQueue.empty())
    {
        takeAwayCustomer *customer = tempQueue.top();
        tempQueue.pop();

        cout << "-----------------------------------------------------" << endl;
        cout << "Take-Away Customer: " << customer->cusotomer.name << endl;
        cout << "Age: " << customer->cusotomer.age << endl;
        cout << "Coffee Name: " << customer->cusotomer.coffeeName << endl;
        cout << "Quantity: " << customer->cusotomer.quantity << endl;
        cout << "Bill: " << customer->cusotomer.bill << " Rs" << endl;
        cout << "-----------------------------------------------------" << endl;
    }
}

void displayAllOrdersHomeDeliveryCustomers()
{
    if (myCafe->nextHomeDeliveryCustomer == NULL)
    {
        cout << "No order for Home Delivery Customer yet!" << endl;
    }
    else
    {
        homeDeliveryCustomer *traversal = myCafe->nextHomeDeliveryCustomer;
        while (traversal != NULL)
        {
            cout << "-----------------------------------------------------" << endl;
            cout << "Home Delivery Customer : " << traversal->cusotomer.name << endl;
            cout << "Age : " << traversal->cusotomer.age << endl;
            cout << "Coffee Name : " << traversal->cusotomer.coffeeName << endl;
            cout << "Quantity : " << traversal->cusotomer.quantity << endl;
            cout << "Delivery Distance : " << traversal->deliveryCharges << "KM" << endl;
            cout << "Delivery Charges : " << traversal->distanceDelivery << endl;
            cout << "Bill : " << traversal->cusotomer.bill << " Rs" << endl;
            cout << "Delivery Address : " << traversal->address << endl;
            cout << "-----------------------------------------------------" << endl;

            traversal = traversal->next;
        }
    }
}

void displayAllOrdersDineInCustomers()
{
    if (myCafe->nextDineInCustomer == NULL)
    {
        cout << "There is no Order for Dine-In Customer till yet" << endl;
    }
    else
    {
        dineInCustomer *traversal = myCafe->nextDineInCustomer;
        while (traversal != NULL)
        {
            cout << "-----------------------------------------------------" << endl;
            cout << "Walk-in Customer : " << traversal->cusotomer.name << endl;
            cout << "Age : " << traversal->cusotomer.age << endl;
            cout << "Coffee Name : " << traversal->cusotomer.coffeeName << endl;
            cout << "Quantity : " << traversal->cusotomer.quantity << endl;
            cout << "Bill : " << traversal->cusotomer.bill << " Rs" << endl;
            cout << "-----------------------------------------------------" << endl;

            traversal = traversal->next;
        }
    }
}

void displayAllOrders()
{

    cout << "The Take-Away Customers Are :" << endl;
    displayAllOrdersTakeAwayCustomers();

    cout << "The Dine-In Customers Are :" << endl;
    displayAllOrdersDineInCustomers();

    cout << "The Home Delivery Customers Are :" << endl;
    displayAllOrdersHomeDeliveryCustomers();
}

void totalbillofPendingOrders()
{
    takeAwayCustomer *p = myCafe->nextTakeAwayCustomer;
    while (p != NULL)
    {
        takeAway += p->cusotomer.bill;
        p = p->next;
    }
    dineInCustomer *q = myCafe->nextDineInCustomer;
    while (q != NULL)
    {
        dineIn += q->cusotomer.bill;
        q = q->next;
    }
    homeDeliveryCustomer *r = myCafe->nextHomeDeliveryCustomer;
    while (r != NULL)
    {
        homeDelivery += r->cusotomer.bill;
        r = r->next;
    }
    total = takeAway + dineIn + homeDelivery;

    cout << "The total bill of pending orders for Take-Away customers are : " << takeAway << " RS/_" << endl;
    cout << "The total bill of pending orders for Dine-In customers are : " << dineIn << " RS/_" << endl;
    cout << "The total bill of pending orders for Delivery customers are : " << homeDelivery << " RS/_" << endl;
    cout << "The Total orders pending are : " << total << " Rs" << endl;
}

double totalEarnings(servedCustomer *root)
{

    if (root)
    {
        totalEarnings(root->left);
        servedTotal += root->bill;
        totalEarnings(root->right);
    }

    return servedTotal;
}

// making a graph for the available delivery options

//                           0              1             2        3          4           5
string deliveryPoints[] = {"Cafe", "NUST University", "Lahore", "Islamabad", "Karachi", "Multan"};

// first value in the pair is vertex and second is the distance (weight) in KM

vector<vector<pair<int, int>>> deliveryMap = {

    // first value in the pair is vertex and second is the distance (weight) in KM
    {{1, 2}, {2, 3}, {3, 5}, {5, 4}}, //  0  (Coffee Shop)
    {{0, 2}, {5, 1}},                 //  1  (NUST University)
    {{0, 3}, {3, 1}},                 //  2  (Lahore)
    {{0, 5}, {4, 2}, {5, 2}, {2, 1}}, //  3  (Islamabad)
    {{3, 2}, {5, 2}},                 //  4  (Karachi)
    {{0, 4}, {1, 1}, {3, 2}, {4, 2}}  //  5  (Multan)

};

vector<int> dijkstra(int sourceNode)
{
    vector<int> distance(6, infinity);
    set<pair<int, int>> s;
    distance[sourceNode] = 0; // Coffee Shop
    s.insert(make_pair(0, sourceNode));

    while (!s.empty())
    {
        auto top = *(s.begin());
        int u = top.first;  //   current weight
        int v = top.second; //  current vertex

        s.erase(s.begin());

        // traversing the adjacency list of v
        for (auto child : deliveryMap[v])
        {
            int childVertex = child.first;
            int childWeight = child.second;

            if (u + childWeight < distance[childVertex])
            {
                distance[childVertex] = u + childWeight;
                s.insert(make_pair(distance[childVertex], childVertex));
            }
        }
    }

    return distance;
}
class Feedback
{
public:
    string customerName;
    int rating; // Rating can be an integer from 1-5
    string reviewText;

    Feedback(string name, int rate, string review)
    {
        customerName = name;
        rating = rate;
        reviewText = review;
    }
};
class FeedbackBST
{
public:
    struct Node
    {
        Feedback feedback;
        Node *left;
        Node *right;
        Node(Feedback fb) : feedback(fb), left(nullptr), right(nullptr) {}
    };

    Node *root;

    FeedbackBST() : root(nullptr) {}

    void insert(Feedback feedback)
    {
        root = insertRec(root, feedback);
    }

    Node *insertRec(Node *node, Feedback feedback)
    {
        if (node == nullptr)
        {
            return new Node(feedback);
        }

        if (feedback.rating < node->feedback.rating)
        {
            node->left = insertRec(node->left, feedback);
        }
        else
        {
            node->right = insertRec(node->right, feedback);
        }
        return node;
    }

    void displayAllFeedback(Node *node)
    {
        if (node == nullptr)
            return;
        displayAllFeedback(node->left);
        cout << "Customer: " << node->feedback.customerName
             << ", Rating: " << node->feedback.rating
             << ", Review: " << node->feedback.reviewText << endl;
        displayAllFeedback(node->right);
    }

    void displayAll()
    {
        displayAllFeedback(root);
    }
};

FeedbackBST feedbackBST;
int main()
{
    // making Coffee shop
    myCafe = new Cafe;

    // setting the name
    // CHANGE NAME HERE KYA NAAM H
    // THE DSA CAFE!!!
    myCafe->shopName = "DSA Delight";

    // setting the address
    myCafe->address = "F7, Islamabad";

    // Setting the menu
    myCafe->menu = new string[11]{"",
                                  "Espresso", "Double Espresso",
                                  "Latte", "Americano",
                                  "Macchiato", "Flat White",
                                  "Cappuccino", "Matcha",
                                  "Masala Chai", "V60 Brew"};

    // setting the price

    myCafe->price = new int[11]{0, 899, 650, 540, 1200, 999, 1100, 810, 650, 25, 850};

    cout << "⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢⌢" << endl;
    cout << "﹉﹉﹉﹉﹉﹉﹉୨♡୧﹉﹉﹉﹉﹉﹉﹉" << endl;
    cout << "- ┈ - ┈ - " << myCafe->shopName << " - ┈ - ┈ -" << endl;
    cout << "┈ ┈ ┈ ┈ ┈ ┈ ┈ ୨♡୧ ┈ ┈ ┈ ┈ ┈ ┈ ┈" << endl;
    cout << "⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣⌣" << endl;
    cout << "Located at " << myCafe->address << endl;
    cout << "Menu: " << endl;
    for (int i = 1; i <= 10; i++)
    {
        cout << i << ". " << myCafe->menu[i] << " - " << myCafe->price[i] << endl;
    }

    int option = -99;

    // now starting the main program
    do
    {

        // cout << "---------------------------------" << myCafe->shopName << "-----------------------" << endl;
        // cout << "---------------------------------｡ﾟ•┈꒰ა ♡ ໒꒱┈•  ｡ﾟ-------------------------------" << endl;
        // cout << "-------------------------------------------------------------------------" << endl;

        // cout << "︵‿︵‿︵‿︵‿︵‿︵‿୨♡୧‿︵‿︵‿︵‿︵‿︵‿︵" << endl;
        // cout << "︵‿︵‿︵‿︵‿︵‿Operations‿︵‿︵‿︵‿︵‿︵‿︵" << endl;
        // cout << "︵‿︵‿︵‿︵‿︵‿︵‿୨♡୧‿︵‿︵‿︵‿︵‿︵‿︵" << endl;

        // Order placing
        // cout << "PLACE ORDER"<< endl;
        cout << "♡    ∩_∩   Operations " << endl;
        cout << "╭ („• ֊ •„)♡  ୨୧ ┈┈ • ┈╮" << endl;
        cout << "     U U " << endl;
        // cout <<"                text here ♡"<< endl;
        // cout <<"╰┈ • ┈ ┈ ୨୧ ┈┈ • ┈╯"<<endl;
        //  gotta make this cute

        cout << "╰┈➤    PLACE ORDER" << endl;
        cout << "1. Take-Away Customer" << endl;
        cout << "2. Home Delivery Customer" << endl;
        cout << "3. Dine-In Customer" << endl;

        // order serving
        cout << "╰┈➤    SERVE ORDER OF:" << endl;

        cout << "4. Take-Away Customer" << endl;
        cout << "5. Home Delivery Customer" << endl;
        cout << "6. Dine-In Customer" << endl;
        cout << "7. Serve All Orders " << endl;

        // Displaying orders
        cout << "╰┈➤    DISPLAY ALL ORDERS OF:" << endl;

        cout << "8. Take-Away Customer" << endl;
        cout << "9. Home Delivery Customers" << endl;
        cout << "10. Dine-In Customers" << endl;
        cout << "11. All Customers" << endl;

        // Served orders
        cout << "╰┈➤    SERVED ORDER" << endl;
        cout << "12. Display all served Orders" << endl;
        cout << "13. Search Served Orders " << endl;
        cout << "14. Clear the Served Orders List " << endl;
        cout << "15. Display total bill of Pending Orders " << endl;
        cout << "16. Display the total Earnings of Served Orders " << endl;
        cout << "╰┈➤    CUSTOMER FEEDBACK" << endl;
        cout << "17. Submit Feedback" << endl;
        cout << "18. Display All Feedback" << endl;

        cout << "0.  EXIT " << endl;
        cout << "╰┈ • ┈ ┈ ୨୧ ┈┈ • ┈╯" << endl;
        cout << "•───────•°•❀•°•───────•" << endl;

        cout << "Enter choice: ";

        cin >> option;
        cout << "•───────•°•❀•°•───────•" << endl;

        // for taking input of Customer Details
        int age, quantity, CoffeeIndex;
        double bill;
        string address;
        string name;

        switch (option)
        {
        case 1:
        { // placing order for take away customer
            cout << "╭┈ •      ┈ ୨୧ ┈      • ┈╮" << endl;
            cout << "★ Name: ";
            cin >> name;
            cout << "★ Age: ";
            cin >> age;
            cout << "★ Quantity of the Coffee: ";
            cin >> quantity;
            cout << "★ Option for the Coffee: ";
            cin >> CoffeeIndex;
            cout << "⋆˖   ⁺‧ ₊☽◯☾₊‧⁺ ˖    ⋆" << endl;

            bill = quantity * myCafe->price[CoffeeIndex];

            placeOrderTakeAwayCustomer(age, name, myCafe->menu[CoffeeIndex], quantity, bill);
        }
        break;

        case 2:

        {                                               // placing order for Home Delivery customer
            vector<int> distanceFromShop = dijkstra(0); // As Zero is our Source Node

            int optionDelivery = -999;

            do
            {
                cout << "The delivery is available for following areas : " << endl;
                for (int i = 1; i <= 5; i++)
                {
                    cout << i << ". " << deliveryPoints[i] << endl;
                }

                cout << "Enter your option: " << endl;
                cin >> optionDelivery;

            } while (!(optionDelivery >= 0 && optionDelivery <= 5));

            // setting the delivery address of the Customer
            address = deliveryPoints[optionDelivery];

            cout << "╭┈ •      ┈ ୨୧ ┈      • ┈╮" << endl;
            cout << "★ Name: ";
            cin >> name;
            cout << "★ Age: ";
            cin >> age;
            cout << "★ Quantity of the Coffee: ";
            cin >> quantity;
            cout << "★ Option for the Coffee: ";
            cin >> CoffeeIndex;
            cout << "⋆˖   ⁺‧ ₊☽◯☾₊‧⁺ ˖    ⋆" << endl;

            int deliveryChargesPerKM = 50;
            int deliveryCharges = deliveryChargesPerKM * distanceFromShop[optionDelivery];
            bill = quantity * myCafe->price[CoffeeIndex] + deliveryCharges;

            // distance from the shop
            int distanceFromTheShop = distanceFromShop[optionDelivery];
            placeOrderHomeDeliveryCustomer(age, name, myCafe->menu[CoffeeIndex], quantity, bill, address, distanceFromTheShop, deliveryCharges);
        }
        break;

        case 3:
        { // placing order for Dine-in customer

            cout << "╭┈ •      ┈ ୨୧ ┈      • ┈╮" << endl;
            cout << "★ Name: ";
            cin >> name;
            cout << "★ Age: ";
            cin >> age;
            cout << "★ Quantity of the Coffee: ";
            cin >> quantity;
            cout << "★ Option for the Coffee: ";
            cin >> CoffeeIndex;
            cout << "⋆˖   ⁺‧ ₊☽◯☾₊‧⁺ ˖    ⋆" << endl;

            bill = quantity * myCafe->price[CoffeeIndex];
            placeOrderDineInCustomer(age, name, myCafe->menu[CoffeeIndex], quantity, bill);
        }
        break;

        case 4:
            // serving order for Take Away customer
            serveOrderTakeAwayCustomer();
            break;

        case 5:
            // serving order for Home Delivery customer
            serveOrderHomeDeliveryCustomer();
            break;

        case 6:
            // serving order for Dine-in customer
            serveOrderDineInCustomer();
            break;

        case 7:
            // serving all orders
            serveAllOrders();
            break;

        case 8:
            // displaying all orders of Take-away customers
            displayAllOrdersTakeAwayCustomers();
            break;

        case 9:
            // displaying all orders of Home Delivery customers
            displayAllOrdersHomeDeliveryCustomers();
            break;

        case 10:
            // displaying all orders of Dine-in customers
            displayAllOrdersDineInCustomers();
            break;

        case 11:
            // displaying all orders of all customers
            displayAllOrders();
            break;

        case 12:
        { // displaying all served orders
            cout << "----Served Orders:----" << endl;
            servedCustomer *r = displayAllServedOrders(root);

            if (!r)
                cout << "No served customer yet!" << endl;
        }
        break;

        case 13:
        { // searching served orders
            cout << "Search customer name: " << endl;
            cin >> name;
            servedCustomer *searchedCustomer = search(root, name);
            if (searchedCustomer == NULL)
                cout << "No such customer was served!" << endl;
            else
                display(searchedCustomer);
        }
        break;

        case 14:
        { // clearing the served Orders

            deleteAllServedCustomers(root);
            root = NULL;
        }
        break;

        case 15:
        { // pending orders bill in queue for all!

            // resetting the state of total orders
            takeAway = 0, dineIn = 0, homeDelivery = 0, total = 0;
            totalbillofPendingOrders();
        }
        break;

        case 16:
        { // total earnings from served orders!

            // resetting thr state of total served orders
            servedTotal = 0;
            double totalx = totalEarnings(root);
            cout << "Total earnings: " << totalx << endl;
        }
        break;
        case 17:
        {
            // Ask for feedback details
            string name, reviewText;
            int rating;

            cout << "Please enter your name: ";
            cin >> name;
            cout << "Enter your rating (1 to 5): ";
            cin >> rating;
            cin.ignore(); // To clear the input buffer
            cout << "Enter your review: ";
            getline(cin, reviewText);

            // Create a Feedback object and insert it into BST
            Feedback newFeedback(name, rating, reviewText);
            feedbackBST.insert(newFeedback);

            cout << "Thank you for your feedback!" << endl;
            break;
        }

        case 18:
        {
            cout << "Displaying all customer feedback sorted by rating: " << endl;
            feedbackBST.displayAll();
            break;
        }
        }

    } while (option != 0);

    cout << "DSA Delight Management System -- Terminated" << endl;
    cout << "╭──────────.★..─╮" << endl;
    cout << "      BUBYEE!    " << endl;
    cout << "╰─..★.──────────╯" << endl;
    cout << "Thank you for Using our Services! DSAAAAAAAAAAA!!! " << endl;

    return 0;
}