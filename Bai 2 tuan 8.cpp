#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;
    // Constructor khi chỉ có dữ liệu
    Node(int val) : data(val), next(nullptr) {}
    // Constructor khi có dữ liệu và con trỏ tiếp theo
    Node(int val, Node* ptr) : data(val), next(ptr) {}
};

class LinkedList {
public:
    Node* head;
    LinkedList() : head(nullptr) {}
    // Thêm một phần tử vào đầu danh sách
    void addToHead(int val) {
        Node* newNode = new Node(val, head); // Tạo nút mới và trỏ tới head cũ
        head = newNode; // Gán nút mới làm head
    }

    // Tạo vòng lặp trong danh sách liên kết
    void createCycleList() {
        if (head == nullptr) return; // Nếu danh sách rỗng, không làm gì
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = head; // Tạo vòng lặp
    }
    // In các phần tử trong danh sách
    void print() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    // Di chuyển M bước và loại bỏ người hiện tại
    void moveAndEliminate(int step) {
        Node* current = head;
        for (int i = 1; i < step; ++i) {
            current = current->next; // Di chuyển đến bước tiếp theo
        }
        Node* toEliminate = current->next; // Người bị loại
        cout << toEliminate->data << " "; // In người bị loại
        current->next = toEliminate->next; // Loại bỏ người khỏi vòng
        delete toEliminate;
        head = current->next; // Chuyển đầu danh sách tới người tiếp theo
    }

    // Giải quyết bài toán Josephus
    void solve(int n, int m) {
        createCycleList(); // Tạo vòng lặp trong danh sách
        while (n > 1) {
            int step = m % n; // Bước đi
            if (step == 0) step = n; // Nếu M % n == 0, đi hết vòng
            moveAndEliminate(step); // Di chuyển và loại bỏ người
            n--; // Giảm số người còn lại
        }
        cout << "\nNguoi choi chien thang: " << head->data << endl; // In stt người chiến thắng
    }
};
int main() {
    int n, m;
    cout << "Nhap so nguoi choi (N): ";
    cin >> n;
    cout << "Nhap gia tri (M): ";
    cin >> m;
    LinkedList* list = new LinkedList();
    for (int i = n; i > 0; i--) {
        list->addToHead(i); // Thêm từng phần tử vào đầu danh sách
    }
    cout << "Danh sach nguoi choi: ";
    list->print(); // In ra danh sách
    cout << "Thu tu nguoi choi bi loai: ";
    list->solve(n, m); // Giải quyết bài toán Josephus

    return 0;
}
