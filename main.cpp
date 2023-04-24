#include <random>
#include <chrono>
#include <functional>

#include "bintree.hpp"

using namespace std;

int main() {
    default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> distribution(0, 100000);
    auto dice = bind(distribution, generator);

    BinTree<int> tree;
    int myInt, rang;

    cout << "Cuantos valores quieres que se generen: ";
    cin >> rang;

    // Generamos valores aleatorios
    for(int i(0); i < rang; i++) {
        myInt = dice();

        cout << "Insertando: " << myInt << endl;

        tree.addData(myInt);
        }

    cout << endl << endl;

    cout << "Recorrido en PreOrder: " << endl;
    tree.parsePreOrder();
    cout << endl << endl;

    cout << "Recorrido en InOrder: " << endl;
    tree.parseInOrder();
    cout << endl << endl;

    cout << "Recorrido en PostOrder: " << endl;
    tree.parsePostOrder();
    cout << endl << endl;

    cout << "El valor menor es: " << tree.retrieve(tree.getLowest());
    cout << endl << endl;

    cout << "El valor mayor es: " << tree.retrieve(tree.getHighest());
    cout << endl << endl;

    cout << "Altura del arbol: " << tree.getHeight() << endl << endl;

    cout << "Altura del subarbol izquierdo respecto a la raiz: "
         << tree.getHeightFroomRoot(tree.getRoot()->getLeft());
    cout << endl << endl;

    cout << "Altura del subarbol derecho respecto a la raiz: "
         << tree.getHeightFroomRoot(tree.getRoot()->getRight());
    cout << endl << endl;
    }
