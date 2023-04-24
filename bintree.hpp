#ifndef BINTREE_HPP_INCLUDED
#define BINTREE_HPP_INCLUDED

#include <exception> // exception
#include <string>
#include <iostream>

/** DEFINITION **/
template <class T>
class BinTree {
    private:
        class Node; /* Declaracion adelantada de la clase Node
                     * para crear la variable "Position" */

    public:
        // Exception Binary Tree
        class Exception : public std::exception {
            private:
                std::string msg;

            public:
                Exception() noexcept : msg("Error indefinido") { }
                Exception(const Exception& ex) noexcept : msg(ex.msg) { }
                Exception(const std::string& m) : msg(m) { }

                Exception& operator = (const Exception& ex) noexcept {
                    msg = ex.msg;

                    return *this;
                    }

                virtual ~Exception() { }

                virtual const char* what() const noexcept {
                    return msg.c_str();
                    }
            };

        typedef Node* Position;

    private:
        /// Node
        class Node {
            private:
                T* dataPtr;
                Position left;
                Position right;

            public:
                // Exception Node
                class Exception : public BinTree::Exception {
                    public:
                        using BinTree::Exception::Exception;
                    };

                Node();
                Node(const T&);

                ~Node();

                T* getDataPtr() const;
                T getData() const;
                Position& getLeft();
                Position& getRight();

                void setDataPtr(T*);
                void setData(const T&);
                void setLeft(Position&);
                void setRight(Position&);
            };

        /// Binary Tree
        Position root;

        void copyAll(Position&, const Position&);

        void addData(Position&, const T&);

        Position& findData(Position&, const T&);

        Position& getLowest(Position&);
        Position& getHighest(Position&);

        int getHeight(Position&);

        void parsePreOrder(Position&);
        void parseInOrder(Position&);
        void parsePostOrder(Position&);

        void deleteAll(Position&);

    public:
        BinTree();
        BinTree(const BinTree&);

        BinTree& operator = (const BinTree&);

        ~BinTree();

        bool isEmpty() const;

        void addData(const T&);

        void deleteData(Position&, const T&);

        T retrieve(Position&) const;

        Position& findData(const T&);

        /**/
        Position& getRoot();
        void setRoot(Position&);

        int getHeightFroomRoot(Position&);
        /**/

        Position& getLowest();
        Position& getHighest();

        bool isLeaf(Position&) const;

        int getHeight();

        void parsePreOrder();
        void parseInOrder();
        void parsePostOrder();

        void deleteAll();
    };

/** IMPLEMENTATION **/
/*  private */
/// Node
template <class T>
BinTree<T>::Node::Node() : dataPtr(nullptr),
    left(nullptr),
    right(nullptr) { }

template <class T>
BinTree<T>::Node::Node(const T& elem) : dataPtr(new T(elem)),
    left(nullptr),
    right(nullptr) {
    if(dataPtr == nullptr) {
        throw Exception("Memoria insuficiente, creando nodo");
        }
    }

template <class T>
BinTree<T>::Node::~Node() {
    delete dataPtr;
    }

template <class T>
T* BinTree<T>::Node::getDataPtr() const {
    return dataPtr;
    }

template <class T>
T BinTree<T>::Node::getData() const {
    if(dataPtr == nullptr) {
        throw Exception("Dato inexistente, getData");
        }

    return *dataPtr;
    }

template <class T>
typename BinTree<T>::Position& BinTree<T>::Node::getLeft() {
    return left;
    }

template <class T>
typename BinTree<T>::Position& BinTree<T>::Node::getRight() {
    return right;
    }

template <class T>
void BinTree<T>::Node::setDataPtr(T* ptr) {
    dataPtr = ptr;
    }

template <class T>
void BinTree<T>::Node::setData(const T& elem) {
    if(dataPtr == nullptr) {
        if((dataPtr = new T(elem)) == nullptr) {
            throw Exception("Memoria no disponible, setData");
            }
        }
    else {
        *dataPtr = elem;
        }
    }

template <class T>
void BinTree<T>::Node::setLeft(Position& refNode) {
    left = refNode;
    }

template <class T>
void BinTree<T>::Node::setRight(Position& refNode) {
    right = refNode;
    }

/// Binary Tree
template <class T>
void BinTree<T>::copyAll(Position& newRefNode, const Position& refNode) {
    if(refNode != nullptr) {
        try {
            newRefNode = new Node(refNode->getData());

            copyAll(newRefNode->getLeft(), refNode->getLeft());
            copyAll(newRefNode->getRight(), refNode->getRight());
            }
        catch(const typename Node::Exception& ex) {
            throw Exception("Fallo al copiarse, copyAll");
            }
        }
    else {
        newRefNode = nullptr;
        }
    }

template <class T>
void BinTree<T>::addData(Position& refNode, const T& elem) {
    if(refNode == nullptr) {
        try {
            if((refNode = new Node(elem)) == nullptr) {
                throw Exception("Memoria no disponible, insertData");
                }
            }
        catch(const typename Node::Exception& ex) {
            // ???
            throw Exception("Ocurrio un problema, insertData");
            }

        return;
        }

    else {
        if(elem < refNode->getData()) {
            addData(refNode->getLeft(), elem);
            }
        else {
            addData(refNode->getRight(), elem);
            }
        }
    }

template <class T>
typename BinTree<T>::Position& BinTree<T>::findData(Position& refNode, const T& elem) {
    if(refNode == nullptr or refNode->getData() == elem) {
        return refNode;
        }

    if(elem < refNode->getData()) {
        return findData(refNode->getLeft(), elem);
        }

    return findData(refNode->getRight(), elem);
    }

template <class T>
typename BinTree<T>::Position& BinTree<T>::getLowest(Position& refNode) {
    if(refNode == nullptr or refNode->getLeft() == nullptr) {
        return refNode;
        }

    return getLowest(refNode->getLeft());
    }

template <class T>
typename BinTree<T>::Position& BinTree<T>::getHighest(Position& refNode) {
    if(refNode == nullptr or refNode->getRight() == nullptr) {
        return refNode;
        }

    return getHighest(refNode->getRight());
    }

template <class T>
int BinTree<T>::getHeight(Position& refNode) {
    if(refNode == nullptr) {
        return 0;
        }

    int leftHeight(getHeight(refNode->getLeft()));
    int rightHeight(getHeight(refNode->getRight()));

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }

template <class T>
void BinTree<T>::parsePreOrder(Position& refNode) {
    if(refNode == nullptr) {
        return;
        }

    std::cout << refNode->getData() << ","; // imprime lo que hay en la raiz

    parsePreOrder(refNode->getLeft());
    parsePreOrder(refNode->getRight());
    }

template <class T>
void BinTree<T>::parseInOrder(Position& refNode) {
    if(refNode == nullptr) {
        return;
        }

    parseInOrder(refNode->getLeft());

    std::cout << refNode->getData() << ","; // imprime lo que hay en la raiz

    parseInOrder(refNode->getRight());
    }

template <class T>
void BinTree<T>::parsePostOrder(Position& refNode) {
    if(refNode == nullptr) {
        return;
        }

    parsePostOrder(refNode->getLeft());
    parsePostOrder(refNode->getRight());

    std::cout << refNode->getData() << ","; // imprime lo que hay en la raiz
    }

template <class T>
void BinTree<T>::deleteAll(Position& refNode) {
    if(refNode != nullptr) {
        deleteAll(refNode->getLeft());
        deleteAll(refNode->getRight());

        delete refNode;
        refNode = nullptr;
        }
    }

/*  public  */
template <class T>
BinTree<T>::BinTree() : root(nullptr) { }

template <class T>
BinTree<T>::BinTree(const BinTree<T>& tree) : root(nullptr) {
    copyAll(tree);
    }

template <class T>
BinTree<T>& BinTree<T>::operator = (const BinTree<T>& tree) {
    deleteAll();

    copyAll(tree);

    return *this;
    }

template <class T>
BinTree<T>::~BinTree() {
    deleteAll();
    }

template <class T>
bool BinTree<T>::isEmpty() const {
    return root == nullptr;
    }

template <class T>
void BinTree<T>::addData(const T& elem) {
    addData(root, elem);
    }

template <class T>
void BinTree<T>::deleteData(Position& refNode, const T& elem) {
    if(refNode == nullptr) {
        return;
        }

    if(refNode->getData() == elem) {
        if(isLeaf(refNode)) {
            delete refNode;
            refNode = nullptr;

            return;
            }

        // Dos Hijos
        if(refNode->getLeft() != nullptr and refNode->getRight() != nullptr) {
            T myData(getHighest(refNode->getLeft())->getData());

            deleteData(refNode->getLeft(), myData);

            refNode->setData(myData);

            return;
            }

        // Un solo hijo
        Position aux(refNode);

        /*                                          Hijo por derecha                Hijo por izquierda      */
        refNode = refNode->getLeft() == nullptr ? refNode = refNode->getRight() : refNode = refNode->getLeft();

        delete aux;
        return;
        }

    if(elem < refNode->getLeft(), elem) {
        deleteData(refNode->getLeft(), elem);
        }
    else {
        deleteData(refNode->getRight(), elem);
        }
    }

template <class T>
T BinTree<T>::retrieve(Position& refNode) const {
    return refNode->getData();
    }

template <class T>
typename BinTree<T>::Position& BinTree<T>::findData(const T& elem) {
    return findData(root, elem);
    }

template <class T>
typename BinTree<T>::Position& BinTree<T>::getLowest() {
    return getLowest(root);
    }

template <class T>
typename BinTree<T>::Position& BinTree<T>::getHighest() {
    return getHighest(root);
    }

template <class T>
int BinTree<T>::getHeight() {
    return getHeight(root);
    }

template <class T>
bool BinTree<T>::isLeaf(Position& refNode) const {
    return refNode != nullptr and refNode->getLeft() == refNode->getRight();
    }

template <class T>
void BinTree<T>::parsePreOrder() {
    parsePreOrder(root);
    }

template <class T>
void BinTree<T>::parseInOrder() {
    parseInOrder(root);
    }

template <class T>
void BinTree<T>::parsePostOrder() {
    parsePostOrder(root);
    }

template <class T>
void BinTree<T>::deleteAll() {
    deleteAll(root);
    }

/**/
template <class T>
typename BinTree<T>::Position& BinTree<T>::getRoot() {
    return root;
    }

template <class T>
void BinTree<T>::setRoot(Position& refNode) {
    root = refNode;
    }

template <class T>
int BinTree<T>::getHeightFroomRoot(Position& refNode) {
    if(refNode == nullptr) {
        return 0;
        }

    else {
        return 1 + std::max(getHeightFroomRoot(refNode->getLeft()), getHeightFroomRoot(refNode->getRight()));
        // obtiene el máximo valor de los dos valores
        }
    }


#endif // BINTREE_HPP_INCLUDED
