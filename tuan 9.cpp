#include <iostream>
using namespace std;

// Cấu trsc 1 node của link list lưu hạng tử của đa thức
struct Node {
    int he_so; // Hệ số và số mũ các phần tử
    int mu;
    Node* tiep;  // Con trỏ đến node tiếp theo

    Node(int c, int e) : he_so(c), mu(e), tiep(nullptr) {}
};

// Tạo class DaThuc
class DaThuc {
private:
    Node* dau;
public:
    DaThuc() : dau(nullptr) {}
    // Thêm 1 hạng tử vào đa thức
    void themHangTu(int he_so, int mu) {
        if (he_so == 0) return; // bỏ qua nếu hệ số 0
        Node* newNode = new Node(he_so, mu);

    // Thêm vào đầu danh sách nếu danh sách rỗng hoặc số mũ lớn nhất
        if (!dau || dau->mu < mu) {
            newNode->tiep = dau;
            dau = newNode;
        } else {
            Node* temp = dau;
            while (temp->tiep && temp->tiep->mu > mu) {
                temp = temp->tiep;
            }
    // Cộng hệ số
            if (temp->mu == mu) {
                temp->he_so += he_so;
                delete newNode; // Xóa node
            } else {
                newNode->tiep = temp->tiep;
                temp->tiep = newNode;
            }
        }
    }
    // Hàm cộng hai đa thức
    DaThuc cong(const DaThuc& other) const {
        DaThuc ketQua;
        Node* p1 = dau;
        Node* p2 = other.dau;

        while (p1 || p2) {
            if (p1 && (!p2 || p1->mu > p2->mu)) {
                ketQua.themHangTu(p1->he_so, p1->mu);
                p1 = p1->tiep;
            } else if (p2 && (!p1 || p2->mu > p1->mu)) {
                ketQua.themHangTu(p2->he_so, p2->mu);
                p2 = p2->tiep;
            } else {
                ketQua.themHangTu(p1->he_so + p2->he_so, p1->mu);
                p1 = p1->tiep;
                p2 = p2->tiep;
            }}return ketQua;}
    // Hàm in đa thuc
    void in() const {
        Node* temp = dau;
        bool laHangTuDau = true;
        while (temp) {
            if (!laHangTuDau && temp->he_so > 0) {
                cout << " + ";
            }
            if (temp->mu == 0) {
                cout << temp->he_so;
            } else if (temp->mu == 1) {
                cout << temp->he_so << "x";
            } else {
                cout << temp->he_so << "x^" << temp->mu;
            }
            laHangTuDau = false;
            temp = temp->tiep;
        }
        cout << endl;
    }
    ~DaThuc() {
        Node* temp;
        while (dau) {
            temp = dau;
            dau = dau->tiep;
            delete temp;
        }
    }
};
// Hàm nhập đa thức
DaThuc nhapDaThuc(const string& ten) {
    DaThuc daThuc;
    cout << "Nhap da thuc " << ten << "(x):" << endl;
    while (true) {
        int he_so, mu;
        cout << "Nhap he so: ";
        cin >> he_so;
        if (he_so == 0) break;
        cout << "Nhap so mu: ";
        cin >> mu;
        daThuc.themHangTu(he_so, mu);
    }
    return daThuc;
}
int main() {

    DaThuc f = nhapDaThuc("f");
    DaThuc g = nhapDaThuc("g");
    DaThuc h = f.cong(g);
    cout << "\nDa thuc f(x): ";
    f.in();
    cout << "Da thuc g(x): ";
    g.in();
    cout << "Da thuc h(x) = f(x) + g(x): ";
    h.in();
    return 0;
}
