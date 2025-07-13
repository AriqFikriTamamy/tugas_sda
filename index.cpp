#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

class Product
{
public:
    string name;
    double price;

    Product(string n, double p) : name(n), price(p) {}
};

class Graph
{
private:
    unordered_map<string, vector<string>> adjList;

public:
    void addProduct(string category, string product)
    {
        adjList[category].push_back(product);
    }

    void BFS(string startCategory)
    {
        unordered_map<string, bool> visited;
        queue<string> q;
        q.push(startCategory);
        visited[startCategory] = true;

        while (!q.empty())
        {
            string category = q.front();
            q.pop();
            cout << "Kategori: " << category << endl;

            for (string product : adjList[category])
            {
                cout << " - Produk: " << product << endl;
                if (!visited[product])
                {
                    visited[product] = true;
                    q.push(product);
                }
            }
        }
    }

    void DFS(string startCategory)
    {
        unordered_map<string, bool> visited;
        stack<string> s;
        s.push(startCategory);

        while (!s.empty())
        {
            string category = s.top();
            s.pop();

            if (!visited[category])
            {
                visited[category] = true;
                cout << "Kategori: " << category << endl;

                for (string product : adjList[category])
                {
                    cout << " - Produk: " << product << endl;
                    if (!visited[product])
                    {
                        s.push(product);
                    }
                }
            }
        }
    }
};

class CashRegister
{
private:
    vector<Product> products;

public:
    void addProduct(string name, double price)
    {
        products.push_back(Product(name, price));
    }

    void displayProducts()
    {
        cout << "Daftar Produk:" << endl;
        for (const auto &product : products)
        {
            cout << "Nama: " << product.name << ", Harga: " << product.price << endl;
        }
    }

    void searchProduct(string name)
    {
        auto it = find_if(products.begin(), products.end(), [&](Product &p)
                          { return p.name == name; });
        if (it != products.end())
        {
            cout << "Produk ditemukan: " << it->name << ", Harga: " << it->price << endl;
        }
        else
        {
            cout << "Produk tidak ditemukan." << endl;
        }
    }

    void sortProducts()
    {
        sort(products.begin(), products.end(), [](Product &a, Product &b)
             { return a.price < b.price; });
    }
};

int main()
{
    CashRegister cashRegister;
    Graph productGraph;

    // Menambahkan produk
    cashRegister.addProduct("Apel", 15.000);
    cashRegister.addProduct("Pisang", 20.000);
    cashRegister.addProduct("Jeruk", 10.000);

    // Menambahkan kategori dan produk ke graph
    productGraph.addProduct("Buah", "Apel");
    productGraph.addProduct("Buah", "Pisang");
    productGraph.addProduct("Buah", "Jeruk");

    // Menampilkan produk
    cashRegister.displayProducts();

    // Mencari produk
    cashRegister.searchProduct("Banana");

    // Mengurutkan produk
    cashRegister.sortProducts();
    cashRegister.displayProducts();

    // Menampilkan produk menggunakan BFS
    cout << "BFS Traversal:" << endl;
    productGraph.BFS("Buah");

    // Menampilkan produk menggunakan DFS
    cout << "DFS Traversal:" << endl;
    productGraph.DFS("Buah");

    return 0;
}
